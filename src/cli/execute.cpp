// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <iostream>
#include <queue>
#include <vector>

#include <mesos/type_utils.hpp>

#include <mesos/v1/mesos.hpp>
#include <mesos/v1/resources.hpp>
#include <mesos/v1/scheduler.hpp>

#include <process/delay.hpp>
#include <process/future.hpp>
#include <process/owned.hpp>
#include <process/pid.hpp>
#include <process/protobuf.hpp>

#include <stout/check.hpp>
#include <stout/duration.hpp>
#include <stout/flags.hpp>
#include <stout/foreach.hpp>
#include <stout/hashmap.hpp>
#include <stout/none.hpp>
#include <stout/option.hpp>
#include <stout/os.hpp>
#include <stout/unreachable.hpp>

#include "common/parse.hpp"
#include "common/protobuf_utils.hpp"

#include "hdfs/hdfs.hpp"

#include "internal/devolve.hpp"

using std::cerr;
using std::cout;
using std::endl;
using std::queue;
using std::string;
using std::vector;

using google::protobuf::RepeatedPtrField;

using mesos::internal::devolve;

using mesos::v1::AgentID;
using mesos::v1::CommandInfo;
using mesos::v1::ContainerInfo;
using mesos::v1::Credential;
using mesos::v1::Environment;
using mesos::v1::FrameworkID;
using mesos::v1::FrameworkInfo;
using mesos::v1::Image;
using mesos::v1::Label;
using mesos::v1::Labels;
using mesos::v1::Offer;
using mesos::v1::Resources;
using mesos::v1::TaskID;
using mesos::v1::TaskInfo;
using mesos::v1::TaskState;
using mesos::v1::TaskStatus;
using mesos::v1::Volume;

using mesos::v1::scheduler::Call;
using mesos::v1::scheduler::Event;
using mesos::v1::scheduler::Mesos;

using process::Future;
using process::Owned;
using process::UPID;


class Flags : public flags::FlagsBase
{
public:
  Flags()
  {
    add(&master,
        "master",
        "Mesos master (e.g., IP:PORT).");

    add(&name,
        "name",
        "Name for the command.");

    add(&shell,
        "shell",
        "Determine the command is a shell or not. If not, 'command' will be\n"
        "treated as executable value and arguments (TODO).",
        true);

    // TODO(alexr): Once MESOS-4882 lands, elaborate on what `command` can
    // mean: an executable, a shell command, an entrypoint for a container.
    add(&command,
        "command",
        "Command to launch.");

    add(&environment,
        "env",
        "Shell command environment variables.\n"
        "The value could be a JSON formatted string of environment variables\n"
        "(i.e., {\"name1\": \"value1\"}) or a file path containing the JSON\n"
        "formatted environment variables. Path should be of the form\n"
        "'file:///path/to/file'.");

    add(&resources,
        "resources",
        "Resources for the command.",
        "cpus:1;mem:128");

    add(&hadoop,
        "hadoop",
        "Path to 'hadoop' script (used for copying packages).",
        "hadoop");

    add(&hdfs,
        "hdfs",
        "The ip:port of the NameNode service.",
        "localhost:9000");

    add(&package,
        "package",
        "Package to upload into HDFS and copy into command's\n"
        "working directory (requires 'hadoop', see --hadoop).");

    add(&overwrite,
        "overwrite",
        "Overwrite the package in HDFS if it already exists.",
        false);

    add(&checkpoint,
        "checkpoint",
        "Enable checkpointing for the framework.",
        false);

    add(&appc_image,
        "appc_image",
        "Appc image name that follows the Appc spec\n"
        "(e.g., ubuntu, example.com/reduce-worker).");

    add(&docker_image,
        "docker_image",
        "Docker image that follows the Docker CLI naming <image>:<tag>\n"
        "(i.e., ubuntu, busybox:latest).");

    add(&containerizer,
        "containerizer",
        "Containerizer to be used (i.e., docker, mesos).",
        "mesos");

    add(&role,
        "role",
        "Role to use when registering.",
        "*");

    add(&kill_after,
        "kill_after",
        "Specifies a delay after which the task is killed\n"
        "(e.g., 10secs, 2mins, etc).");

    add(&networks,
        "networks",
        "Comma-separated list of networks that the container will join,\n"
        "e.g., `net1,net2`.");

    add(&principal,
        "principal",
        "The principal to use for framework authentication.");

    add(&secret,
        "secret",
        "The secret to use for framework authentication.");

    add(&volumes,
        "volumes",
        "The value could be a JSON-formatted string of volumes or a\n"
        "file path containing the JSON-formatted volumes. Path must\n"
        "be of the form `file:///path/to/file` or `/path/to/file`.\n"
        "\n"
        "See the `Volume` message in `mesos.proto` for the expected format.\n"
        "\n"
        "Example:\n"
        "[\n"
        "  {\n"
        "    \"container_path\":\"/path/to/container\"\n"
        "    \"mode\":\"RW\"\n"
        "    \"source\":\n"
        "    {\n"
        "      \"docker_volume\":\n"
        "        {\n"
        "          \"driver\": \"volume_driver\",\n"
        "          \"docker_options\":\n"
        "            {\"parameter\":[\n"
        "              {\n"
        "                \"key\": \"key\",\n"
        "                \"value\": \"value\"\n"
        "              }\n"
        "            ]},\n"
        "            \"name\": \"volume_name\"\n"
        "        },\n"
        "      \"type\": \"DOCKER_VOLUME\"\n"
        "    }\n"
        "  }\n"
        "]");
  }

  Option<string> master;
  Option<string> name;
  bool shell;
  Option<string> command;
  Option<hashmap<string, string>> environment;
  string resources;
  string hadoop;
  string hdfs;
  Option<string> package;
  bool overwrite;
  bool checkpoint;
  Option<string> appc_image;
  Option<string> docker_image;
  Option<JSON::Array> volumes;
  string containerizer;
  string role;
  Option<Duration> kill_after;
  Option<string> networks;
  Option<string> principal;
  Option<string> secret;
};


class CommandScheduler : public process::Process<CommandScheduler>
{
public:
  CommandScheduler(
      const FrameworkInfo& _frameworkInfo,
      const string& _master,
      const string& _name,
      const bool _shell,
      const Option<string>& _command,
      const Option<hashmap<string, string>>& _environment,
      const string& _resources,
      const Option<string>& _uri,
      const Option<string>& _appcImage,
      const Option<string>& _dockerImage,
      const vector<Volume>& _volumes,
      const string& _containerizer,
      const Option<Duration>& _killAfter,
      const Option<string>& _networks,
      const Option<Credential> _credential)
    : state(DISCONNECTED),
      frameworkInfo(_frameworkInfo),
      master(_master),
      name(_name),
      shell(_shell),
      command(_command),
      environment(_environment),
      resources(_resources),
      uri(_uri),
      appcImage(_appcImage),
      dockerImage(_dockerImage),
      volumes(_volumes),
      containerizer(_containerizer),
      killAfter(_killAfter),
      networks(_networks),
      credential(_credential),
      launched(false) {}

  virtual ~CommandScheduler() {}

protected:
  virtual void initialize()
  {
    // We initialize the library here to ensure that callbacks are only invoked
    // after the process has spawned.
    mesos.reset(new Mesos(
      master,
      mesos::ContentType::PROTOBUF,
      process::defer(self(), &Self::connected),
      process::defer(self(), &Self::disconnected),
      process::defer(self(), &Self::received, lambda::_1),
      credential));
  }

  void connected()
  {
    state = CONNECTED;

    doReliableRegistration();
  }

  void disconnected()
  {
    state = DISCONNECTED;
  }

  void doReliableRegistration()
  {
    if (state == SUBSCRIBED || state == DISCONNECTED) {
      return;
    }

    Call call;
    call.set_type(Call::SUBSCRIBE);

    if (frameworkInfo.has_id()) {
      call.mutable_framework_id()->CopyFrom(frameworkInfo.id());
    }

    Call::Subscribe* subscribe = call.mutable_subscribe();
    subscribe->mutable_framework_info()->CopyFrom(frameworkInfo);

    mesos->send(call);

    process::delay(Seconds(1), self(), &Self::doReliableRegistration);
  }

  void killTask(const TaskID& taskId, const AgentID& agentId)
  {
    cout << "Asked to kill task '" << taskId
         << "' on agent '" << agentId << "'" << endl;

    Call call;
    call.set_type(Call::KILL);

    CHECK(frameworkInfo.has_id());
    call.mutable_framework_id()->CopyFrom(frameworkInfo.id());

    Call::Kill* kill = call.mutable_kill();
    kill->mutable_task_id()->CopyFrom(taskId);
    kill->mutable_agent_id()->CopyFrom(agentId);

    mesos->send(call);
  }

  void offers(const vector<Offer>& offers)
  {
    CHECK_EQ(SUBSCRIBED, state);

    static const Try<Resources> TASK_RESOURCES = Resources::parse(resources);

    if (TASK_RESOURCES.isError()) {
      EXIT(EXIT_FAILURE)
        << "Failed to parse resources '" << resources << "': "
        << TASK_RESOURCES.error();
    }

    foreach (const Offer& offer, offers) {
      Resources offered = offer.resources();

      if (!launched && offered.flatten().contains(TASK_RESOURCES.get())) {
        TaskInfo task;
        task.set_name(name);
        task.mutable_task_id()->set_value(name);
        task.mutable_agent_id()->MergeFrom(offer.agent_id());

        // Takes resources first from the specified role, then from '*'.
        Option<Resources> resources =
          offered.find(TASK_RESOURCES.get().flatten(frameworkInfo.role()));

        CHECK_SOME(resources);

        task.mutable_resources()->CopyFrom(resources.get());

        CommandInfo* commandInfo = task.mutable_command();

        if (shell) {
          CHECK_SOME(command);

          commandInfo->set_shell(true);
          commandInfo->set_value(command.get());
        } else {
          // TODO(gilbert): Treat 'command' as executable value and arguments.
          commandInfo->set_shell(false);
        }

        if (environment.isSome()) {
          Environment* environment_ = commandInfo->mutable_environment();
          foreachpair (
              const string& name, const string& value, environment.get()) {
            Environment::Variable* environmentVariable =
              environment_->add_variables();

            environmentVariable->set_name(name);
            environmentVariable->set_value(value);
          }
        }

        if (uri.isSome()) {
          task.mutable_command()->add_uris()->set_value(uri.get());
        }

        Result<ContainerInfo> containerInfo = getContainerInfo();

        if (containerInfo.isError()){
          EXIT(EXIT_FAILURE) << containerInfo.error();
          return;
        }

        if (containerInfo.isSome()) {
          task.mutable_container()->CopyFrom(containerInfo.get());
        }

        Call call;
        call.set_type(Call::ACCEPT);

        CHECK(frameworkInfo.has_id());
        call.mutable_framework_id()->CopyFrom(frameworkInfo.id());

        Call::Accept* accept = call.mutable_accept();
        accept->add_offer_ids()->CopyFrom(offer.id());

        Offer::Operation* operation = accept->add_operations();
        operation->set_type(Offer::Operation::LAUNCH);

        operation->mutable_launch()->add_task_infos()->CopyFrom(task);

        mesos->send(call);

        cout << "Submitted task '" << name << "' to agent '"
             << offer.agent_id() << "'" << endl;

        launched = true;
      } else {
        Call call;
        call.set_type(Call::DECLINE);

        CHECK(frameworkInfo.has_id());
        call.mutable_framework_id()->CopyFrom(frameworkInfo.id());

        Call::Decline* decline = call.mutable_decline();
        decline->add_offer_ids()->CopyFrom(offer.id());

        mesos->send(call);
      }
    }
  }

  void received(queue<Event> events)
  {
    while (!events.empty()) {
      Event event = events.front();
      events.pop();

      switch (event.type()) {
        case Event::SUBSCRIBED: {
          frameworkInfo.mutable_id()->
            CopyFrom(event.subscribed().framework_id());

          state = SUBSCRIBED;

          cout << "Subscribed with ID '" << frameworkInfo.id() << "'" << endl;
          break;
        }

        case Event::OFFERS: {
          offers(google::protobuf::convert(event.offers().offers()));
          break;
        }

        case Event::UPDATE: {
          update(event.update().status());
          break;
        }

        case Event::ERROR: {
          EXIT(EXIT_FAILURE)
            << "Received an ERROR event: " << event.error().message();

          break;
        }

        case Event::HEARTBEAT:
        case Event::INVERSE_OFFERS:
        case Event::FAILURE:
        case Event::RESCIND:
        case Event::RESCIND_INVERSE_OFFER:
        case Event::MESSAGE: {
          break;
        }
        case Event::CLOUD_INFO: {
	 // XXX: atleast print something here? 
	  break;
        }
      case Event::TERMINATION_WARNING: {
	// XXX. Print the termination warning inverse offer passed to frameworks here
	break ;
      }

	  
        case Event::UNKNOWN: {
          LOG(WARNING) << "Received an UNKNOWN event and ignored";
          break;
        }
      }
    }
  }

  void update(const TaskStatus& status)
  {
    CHECK_EQ(SUBSCRIBED, state);
    CHECK_EQ(name, status.task_id().value());

    cout << "Received status update " << status.state()
         << " for task '" << status.task_id() << "'" << endl;
    if (status.has_message()) {
      cout << "  message: '" << status.message() << "'" << endl;
    }
    if (status.has_source()) {
      cout << "  source: " << TaskStatus::Source_Name(status.source()) << endl;
    }
    if (status.has_reason()) {
      cout << "  reason: " << TaskStatus::Reason_Name(status.reason()) << endl;
    }
    if (status.has_healthy()) {
      cout << "  healthy?: " << status.healthy() << endl;
    }

    if (status.has_uuid()) {
      Call call;
      call.set_type(Call::ACKNOWLEDGE);

      CHECK(frameworkInfo.has_id());
      call.mutable_framework_id()->CopyFrom(frameworkInfo.id());

      Call::Acknowledge* acknowledge = call.mutable_acknowledge();
      acknowledge->mutable_agent_id()->CopyFrom(status.agent_id());
      acknowledge->mutable_task_id()->CopyFrom(status.task_id());
      acknowledge->set_uuid(status.uuid());

      mesos->send(call);
    }

    // If a task kill delay has been specified, schedule task kill.
    if (killAfter.isSome() && TaskState::TASK_RUNNING == status.state()) {
      delay(killAfter.get(),
            self(),
            &Self::killTask,
            status.task_id(),
            status.agent_id());
    }

    if (mesos::internal::protobuf::isTerminalState(devolve(status).state())) {
      terminate(self());
    }
  }

private:
  enum State
  {
    DISCONNECTED,
    CONNECTED,
    SUBSCRIBED
  } state;

  // TODO(jojy): Consider breaking down the method for each 'containerizer'.
  Result<ContainerInfo> getContainerInfo() const
  {
    if (containerizer.empty()) {
      return None();
    }

    ContainerInfo containerInfo;

    foreach (const Volume& volume, volumes) {
      containerInfo.add_volumes()->CopyFrom(volume);
    }

    // Mesos containerizer supports 'appc' and 'docker' images.
    if (containerizer == "mesos") {
      if (dockerImage.isNone() && appcImage.isNone() &&
          (networks.isNone() || networks->empty()) &&
          volumes.empty()) {
        return None();
      }

      containerInfo.set_type(ContainerInfo::MESOS);

      if (dockerImage.isSome()) {
        Image* image = containerInfo.mutable_mesos()->mutable_image();
        image->set_type(Image::DOCKER);
        image->mutable_docker()->set_name(dockerImage.get());
      } else if (appcImage.isSome()) {
        Image::Appc appc;

        appc.set_name(appcImage.get());

        // TODO(jojy): Labels are hard coded right now. Consider
        // adding label flags for customization.
        Label arch;
        arch.set_key("arch");
        arch.set_value("amd64");

        Label os;
        os.set_key("os");
        os.set_value("linux");

        Labels labels;
        labels.add_labels()->CopyFrom(os);
        labels.add_labels()->CopyFrom(arch);

        appc.mutable_labels()->CopyFrom(labels);

        Image* image = containerInfo.mutable_mesos()->mutable_image();
        image->set_type(Image::APPC);
        image->mutable_appc()->CopyFrom(appc);
      }

      if (networks.isSome() && !networks->empty()) {
        foreach (const string& network,
                 strings::tokenize(networks.get(), ",")) {
          containerInfo.add_network_infos()->set_name(network);
        }
      }

      return containerInfo;
    } else if (containerizer == "docker") {
      // 'docker' containerizer only supports 'docker' images.
      if (dockerImage.isNone()) {
        return Error("'Docker' containerizer requires docker image name");
      }

      containerInfo.set_type(ContainerInfo::DOCKER);
      containerInfo.mutable_docker()->set_image(dockerImage.get());

      if (networks.isSome() && !networks->empty()) {
        vector<string> tokens = strings::tokenize(networks.get(), ",");
        if (tokens.size() > 1) {
          EXIT(EXIT_FAILURE)
            << "'Docker' containerizer can only support a single network";
        } else {
          containerInfo.mutable_docker()->set_network(
              ContainerInfo::DockerInfo::USER);
          containerInfo.add_network_infos()->set_name(tokens.front());
        }
      }

      return containerInfo;
    }

    return Error("Unsupported containerizer: " + containerizer);
  }

  FrameworkInfo frameworkInfo;
  const string master;
  const string name;
  bool shell;
  const Option<string> command;
  const Option<hashmap<string, string>> environment;
  const string resources;
  const Option<string> uri;
  const Option<string> appcImage;
  const Option<string> dockerImage;
  const vector<Volume> volumes;
  const string containerizer;
  const Option<Duration> killAfter;
  const Option<string> networks;
  const Option<Credential> credential;
  bool launched;
  Owned<Mesos> mesos;
};


int main(int argc, char** argv)
{
  Flags flags;

  // Load flags from command line only.
  Try<flags::Warnings> load = flags.load(None(), argc, argv);

  if (load.isError()) {
    cerr << flags.usage(load.error()) << endl;
    return EXIT_FAILURE;
  }

  // TODO(marco): this should be encapsulated entirely into the
  // FlagsBase API - possibly with a 'guard' that prevents FlagsBase
  // from calling ::exit(EXIT_FAILURE) after calling usage() (which
  // would be the default behavior); see MESOS-2766.
  if (flags.help) {
    cout << flags.usage() << endl;
    return EXIT_SUCCESS;
  }

  // Log any flag warnings.
  foreach (const flags::Warning& warning, load->warnings) {
    LOG(WARNING) << warning.message;
  }

  if (flags.master.isNone()) {
    cerr << flags.usage("Missing required option --master") << endl;
    return EXIT_FAILURE;
  }

  UPID master("master@" + flags.master.get());
  if (!master) {
    cerr << flags.usage("Could not parse --master=" + flags.master.get())
         << endl;
    return EXIT_FAILURE;
  }

  if (flags.name.isNone()) {
    cerr << flags.usage("Missing required option --name") << endl;
    return EXIT_FAILURE;
  }

  if (flags.shell && flags.command.isNone()) {
    cerr << flags.usage("Missing required option --command") << endl;
    return EXIT_FAILURE;
  }

  Result<string> user = os::user();
  if (!user.isSome()) {
    if (user.isError()) {
      cerr << "Failed to get username: " << user.error() << endl;
    } else {
      cerr << "No username for uid " << ::getuid() << endl;
    }
    return EXIT_FAILURE;
  }

  Option<hashmap<string, string>> environment = None();

  if (flags.environment.isSome()) {
    environment = flags.environment.get();
  }

  // Copy the package to HDFS if requested save it's location as a URI
  // for passing to the command (in CommandInfo).
  Option<string> uri = None();

  if (flags.package.isSome()) {
    Try<Owned<HDFS>> hdfs = HDFS::create(flags.hadoop);
    if (hdfs.isError()) {
      cerr << "Failed to create HDFS client: " << hdfs.error() << endl;
      return EXIT_FAILURE;
    }

    // TODO(benh): If HDFS is not properly configured with
    // 'fs.default.name' then we'll copy to the local
    // filesystem. Currently this will silently fail on our end (i.e.,
    // the 'copyFromLocal' will be successful) but we'll fail to
    // download the URI when we launch the executor (unless it's
    // already been uploaded before ...).

    // Store the file at '/user/package'.
    string path = path::join("/", user.get(), flags.package.get());

    // Check if the file exists and remove it if we're overwriting.
    Future<bool> exists = hdfs.get()->exists(path);
    exists.await();

    if (!exists.isReady()) {
      cerr << "Failed to check if file exists: "
           << (exists.isFailed() ? exists.failure() : "discarded") << endl;
      return EXIT_FAILURE;
    } else if (exists.get() && flags.overwrite) {
      Future<Nothing> rm = hdfs.get()->rm(path);
      rm.await();

      if (!rm.isReady()) {
        cerr << "Failed to remove existing file: "
             << (rm.isFailed() ? rm.failure() : "discarded") << endl;
        return EXIT_FAILURE;
      }
    } else if (exists.get()) {
      cerr << "File already exists (see --overwrite)" << endl;
      return EXIT_FAILURE;
    }

    Future<Nothing> copy = hdfs.get()->copyFromLocal(flags.package.get(), path);
    copy.await();

    if (!copy.isReady()) {
      cerr << "Failed to copy package: "
           << (copy.isFailed() ? copy.failure() : "discarded") << endl;
      return EXIT_FAILURE;
    }

    // Now save the URI.
    uri = "hdfs://" + flags.hdfs + path;
  }

  Option<string> appcImage;
  if (flags.appc_image.isSome()) {
    appcImage = flags.appc_image.get();
  }

  Option<string> dockerImage;
  if (flags.docker_image.isSome()) {
    dockerImage = flags.docker_image.get();
  }

  if (appcImage.isSome() && dockerImage.isSome()) {
    cerr << "Flags '--docker-image' and '--appc-image' are both set" << endl;
    return EXIT_FAILURE;
  }

  vector<Volume> volumes;
  if (flags.volumes.isSome()) {
    Try<RepeatedPtrField<Volume>> _volumes =
      ::protobuf::parse<RepeatedPtrField<Volume>>(flags.volumes.get());

    if (_volumes.isError()) {
      cerr << "Failed to convert '--volumes' to protobuf: "
           << _volumes.error() << endl;
      return EXIT_FAILURE;
    }

    foreach (const Volume& volume, _volumes.get()) {
      volumes.push_back(volume);
    }
  }

  FrameworkInfo frameworkInfo;
  frameworkInfo.set_user(user.get());
  frameworkInfo.set_name("mesos-execute instance");
  frameworkInfo.set_role(flags.role);
  frameworkInfo.set_checkpoint(flags.checkpoint);
  frameworkInfo.add_capabilities()->set_type(
      FrameworkInfo::Capability::TASK_KILLING_STATE);

  Option<Credential> credential = None();

  if (flags.principal.isSome()) {
    frameworkInfo.set_principal(flags.principal.get());

    if (flags.secret.isSome()) {
      Credential credential_;
      credential_.set_principal(flags.principal.get());
      credential_.set_secret(flags.secret.get());
      credential = credential_;
    }
  }

  Owned<CommandScheduler> scheduler(
      new CommandScheduler(
        frameworkInfo,
        flags.master.get(),
        flags.name.get(),
        flags.shell,
        flags.command,
        environment,
        flags.resources,
        uri,
        appcImage,
        dockerImage,
        volumes,
        flags.containerizer,
        flags.kill_after,
        flags.networks,
        credential));

  process::spawn(scheduler.get());
  process::wait(scheduler.get());

  return EXIT_SUCCESS;
}
