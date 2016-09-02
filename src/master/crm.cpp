#include <iostream>
//#include <sstream>

#include <process/defer.hpp>
#include <process/dispatch.hpp>
#include <process/future.hpp>
#include <process/http.hpp>

//#include <mesos/state/log.hpp>

// #include <stout/check.hpp>
// #include <stout/duration.hpp>
// #include <stout/exit.hpp>
// #include <stout/flags.hpp>
// #include <stout/nothing.hpp>
// #include <stout/option.hpp>
// #include <stout/os.hpp>
// #include <stout/path.hpp>
// #include <stout/stringify.hpp>
// #include <stout/strings.hpp>
// #include <stout/try.hpp>

#include <stout/json.hpp>
#include <stout/stringify.hpp>

//using mesos::log::Log;

#include "master/crm.hpp"

#include <fstream>
#include <streambuf>




//using std::string;
using namespace std ;

CloudRM::CloudRM()
{
  LOG(INFO) << "~~~ FROM CLOUD RM" ;
  std::cout << "  CLOUD RM \n" ;
 
}

/********************************************************************************/

Aws::Auth::AWSCredentials init_aws_stuff(Aws::SDKOptions options)
{
  //Based on the above, can ignore all these options
  
  Aws::InitAPI(options);
  //make your SDK calls in here.
  LOG(INFO) << " AWS library loaded \n" ;

  Aws::Auth::EnvironmentAWSCredentialsProvider envcreds ; //supposedly reads env vars 
  
  Aws::Auth::AWSCredentials creds = envcreds.GetAWSCredentials() ;
  LOG(INFO) << "Credentials loaded too? \n" ;
  
  //std::cout << creds.GetAWSAccessKeyId()  << "\n" ;
  //std::cout << creds.GetAWSSecretKey() << "\n" ;
  
  return creds ;
}

/********************************************************************************/

int CloudRM::init(mesos::internal::master::Master* master)
{
  this->master = master ;
  LOG(INFO) << "~~~~~~~ INITIALIZED by master" ;
  allocator = master->get_allocator();

  local_mode = true ;

  default_portfolios = read_portfolio_wts() ; //lets test this!
  
  if (local_mode) {
    //IN local mode, AWS stuff is not required at all 
    return true ;
  }
  
  //1. Get credentials 
  creds = init_aws_stuff(options); //Default options with nothing turned on 
  //2. Initialize the default config

  Aws::Region region = Aws::RegionMapper::GetRegionFromName("us-east-1") ;
 
  cconfig.region = region ; //ClientConfig 
  
  //3. Initialize the client 
  client = new Aws::EC2::EC2Client(creds, cconfig) ;
  
  return 1; 
}


/********************************************************************************/

// The frameworkinfo structure has a lot of metadata about the
// framework, which can be used by some policies eventually to directly
// allocate resources to it even if they dont ask for it explicitly. This
// can be some basic rule engine etc.  Return a vector of server orders
// here?

vector<ServerOrder> CloudRM::pDefaultFrameworkResources(
  const mesos::FrameworkInfo& frameworkinfo)
{
  //add_to_pending_orders(frameworkinfo);
  ServerOrder* order = new ServerOrder() ;
  //really should be a vector or a collection of orders.
  std::vector<ServerOrder> all_orders ;
  all_orders.push_back(*order) ;
  return all_orders ;
}


/********************************************************************************/

//should be associated with some framework?
void CloudRM::add_to_pending_orders (std::vector<ServerOrder> orders)
{
  
  
}


/********************************************************************************/


// JSON parsing for the portfolios file which looks something like this :
// [
//   {
//     "wts": [
//       {
//         "market" : "m1.small-a",
//          "wt" : 0.3 
//       },
//       {
//         "r3.large-b": 0.5
//       }
//     ],
//     "alpha": 0.5
//   },
//   {
//     "wts": [
//       {
//         "m3.large-c": 0.2
//       },
//       {
//         "r3.xlarge-d": 0.8
//       }
//     ],
//     "alpha": 1.0
//   }
// ]

Portfolios CloudRM::read_portfolio_wts()
{
  //Monstrosity of a structure, sorry!
  //For each Alpha, we want to add a new object?
  //This should be its own class!
  Portfolios portfolios ;
  //We are in mesos/build/src when launched  
  std::string path = "../../portfolios/us-east-1.json";
  //XXX change to ~/portfolios/ instead of hard-coded local path!
  
  std::ifstream t(path);
  std::string str(
    (std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());


  //The outermost object is an array.

  LOG(INFO) << "---------------- START JSON PARSING -------------- " ;
  LOG(INFO) << str ;
  LOG(INFO) << "----------------------------------------------------" ;
  
  Try<JSON::Array> jarr = JSON::parse<JSON::Array>(str);

  if(jarr.isError()) {
    LOG(INFO) << "Error in parsing the outermost array!" ;
    LOG(INFO) << jarr.error() ;
    return portfolios ; 
  }
  
  JSON::Array arr = jarr.get();

  std::vector<JSON::Value> values = arr.values;
    
  //Each file contains multiple portflios, one for each alpha 
  for (auto a_portfolio : values) {
    JSON::Object obj = a_portfolio.as<JSON::Object>();

    double alpha = obj.find<JSON::Number>("alpha").get().as<double>();
    LOG(INFO) << "alpha= " << alpha ;
    
    portfolios.new_portfolio(alpha) ;
    
    //Associated with each alpha, there is a weights array
    JSON::Array wts_array = obj.find<JSON::Array>("wts").get();

    //Each element in the wts array is an object with type and wt fields 
    for (auto wtv : wts_array.values) {
      JSON::Object wobj = wtv.as<JSON::Object>();
      
      std::string market = wobj.find<JSON::String>("market").get().value ;
      double actual_wt = wobj.find<JSON::Number>("wt").get().as<double>();

      LOG(INFO) << market  << " : " << actual_wt ;
      
      //std::tuple tup = std::make_tuple(market, actual_wt) ;
      
      portfolios.add(alpha, market, actual_wt) ;
      
    } //For each market in the portfolio 
  } // outer for portfolios in values

  
  LOG(INFO) << "---------------------- END --------------------- " ;
  
  return portfolios ;
}

/********************************************************************************/

/* Return portfolio wts for a given alpha. Read in csv file of some sort generated by the python cvxopt solver. 
*/
//XX TODO: Make this part of the portfolios class to deal with all the
//messy nearest neighbour business, because the app might requirest an
//alpha for which the portfolios are not explicitly calculated. BUT
//there might be other portfolios *VERY* close to the requested alpha,
//so we should return that instead. 0.5 vs. 0.45 for example


/********************************************************************************/

//Determine number of servers to satisfy w*cpu and w*memory from a
//given market. Depends only on the type. Servers might end up being
//too small for an application, in which case we cant do anything now!

ServerOrder CloudRM::get_min_servers(
  double wt,
  const CloudMachine& cm,
  ResourceVector& req,
  std::string packing_policy)
{
  ServerOrder out;
  std::string type = cm.type;
  LOG(INFO) << "Finding servers of type " << type;

  // Resources required in this market.
  double req_cpu = req.get_cpu() * wt;
  double req_mem = req.get_mem() * wt;

  // 2. Get CPU and mem capacity of the given server type
  int cap_cpu = EC2_machines.get_cpu(type);
  int cap_mem = EC2_machines.get_mem(type);

  // Number of additional servers of this type we will need.
  int order_count;

  // In private allocation, there is no sharing of servers, so no need
  // to do packing
  if (packing_policy == "private") {
    LOG(INFO) << "Private packing policy in operation";
    // 3. Compute min numbers here?
    double min_for_cpu = req_cpu / cap_cpu;
    double min_for_mem = req_mem / cap_mem;

    order_count = ceil(std::max(min_for_mem, min_for_cpu));
  } // IF PRIVATE

  // Ask allocator how many servers we will need.
  else if (packing_policy == "binpack") {
    // How many servers we will need AFTER packing
    int deficit = 0.0;

    deficit =
      allocator->packServers(req_cpu, req_mem, cm, packing_policy).get();

    // allocator->activateFramework(framework->id());
    order_count = deficit;
  } // IF BINPACK


  out.num = order_count;
  out.machine = cm;
  return out;
}

/********************************************************************************/

/* Translates portfolio weights to actual servers. The wts indicate what fraction of the application should be running on servers in that market. If wt=1, then simply determine how many servers we need from this market to satisfy the cpu AND memory resources. In fact lets do this. 
 */
std::vector<ServerOrder> CloudRM::compute_server_order(
  std::vector<std::tuple<CloudMachine, double>>& portfolio_wts,
  ResourceVector& req,
  std::string packing_policy)
{
  std::vector<ServerOrder> out;
  // 1. For each market, determine min servers to satisfy w*cpu and w*memory
  
  for (auto tup : portfolio_wts) {
    CloudMachine cm = std::get<0>(tup) ;
    double wt = std::get<1>(tup) ;

    ServerOrder in_market = get_min_servers(wt, cm, req, packing_policy);

    if (in_market.num == 0) {
      // Server type too small maybe?
      LOG(INFO) << "Cannot meet server order requirement, too small";
    } else {
      out.push_back(in_market);
    }
  } // end foreachkey
  
  return out;
}

/********************************************************************************/

/** Get the actual servers which must be ordered. 
 */
std::vector<ServerOrder> CloudRM::get_servers(
  mesos::internal::master::Framework* framework,
  ResourceVector& req,
  PlacementConstraint& placement,
  std::string packing_policy)
{
  std::vector<ServerOrder> out;

  if (packing_policy != "private") {
    LOG(INFO) << "Packing policy " << packing_policy << " is NOT supported ";
    return out;
  }

  // 1. Find the portfolio-vector for the given alpha first.

  std::vector<std::tuple<CloudMachine, double>> portfolio_wts =
    default_portfolios.get_portfolio_wts(placement.alpha);

  // 2. Translate wts into actual number of servers we need!
  out = compute_server_order(portfolio_wts, req, packing_policy);

  return out;
}

/********************************************************************************/

std::vector<std::string> CloudRM::actually_buy_servers(
  ServerOrder& to_buy)
{
  // Extract the cloud machine information first?
  std::vector<std::string> out ;
  
  Aws::String keyname = "prateeks"; // only used for launching AMIs
  Aws::String ami = to_buy.ami.c_str() ;
  
  //int count = to_buy.num ;

  //Expects a base-64 string of the script ?

  // std::string master_loc = "127.0.0.1:5050" ;
  // Masterinfo.address.ip.in().get().s_addr
  
  std::string master_ip = master->info().address().ip() ;
  std::string master_port = std::to_string(master->info().address().port()) ;
  std::string owner_fmwk = to_buy.framework.c_str() ;  

  std::string master_loc = master_ip +":" + master_port ;
  
  
  char* uc  = (char*)malloc(800) ;
  
  sprintf(uc, "#!/bin/bash \n /home/ubuntu/mesos/build/src/mesos-slave --master=\'%s\' --work_dir=/tmp --attributes=\"owner-fmwk:%s\" \n", master_loc.c_str(), owner_fmwk.c_str()); 

  std::string user_data(uc) ;

  std::ofstream myfile ;
  myfile.open("slave_user_data.txt") ;
  myfile << user_data ;
  myfile.close() ;

  LOG(INFO) << "Written to slave_user_data.txt file" ;

  free(uc) ; 
  //Write this to a file slave_user_data.txt
  //free(uc) ;
  
  char* uc2 = (char*) malloc(800) ;
//  --image-id ami-4f680658  --key-name prateeks --instance-type m3.xlarge
  
  sprintf(uc2, "aws ec2 run-instances --image-id %s --key-name prateeks --instance-type %s --user-data-file file://slave_user_data.txt" , ami.c_str(), to_buy.machine.type.c_str()) ;
	      

//  std::string cmd_str(uc2) ;

  int status = std::system(uc2) ;

  LOG(INFO) << "cmd status " << status ; 

  free(uc2) ;
  
  //int status = system(uc2) ;
  
  
  // Aws::EC2::Model::InstanceType type =
  //   Aws::EC2::Model::InstanceTypeMapper::GetInstanceTypeForName(
  //     to_buy.machine.type.c_str());
  

  // Aws::EC2::Model::RunInstancesRequest request;

  // request.SetImageId(ami) ;
  // request.SetMinCount(count) ;
  // request.SetKeyName(keyname) ;
  // request.SetUserData(user_data.c_str()) ;
  // request.SetInstanceType(type) ;
  // request.SetClientToken(to_buy.framework.c_str()) ;

  // //  request.SetInstanceInitiatedShutdownBehavior

  // /* Availability zone field is absent for on-demand instances, but seems to be
  //  * present for spot instances. */
  // // SpotInstanceRequest.SetAvailabilityZoneGroup
  // // SetLaunchedAvailabilityZone   SetSpotPrice


  // //  RunInstancesAsync (const Model::RunInstancesRequest &request, const
  // //  RunInstancesResponseReceivedHandler &handler, const std::shared_ptr< const
  // //  Aws::Client::AsyncCallerContext > &context=nullptr) const

  // Aws::EC2::Model::RunInstancesOutcome outcome = client->RunInstances(request);

  // //TODO XXX Error checking, retry, etc.  outcome.GetError() ;
  // Aws::EC2::Model::RunInstancesResponse r = outcome.GetResult() ; 
  // Aws::String rid = r.GetReservationId() ;
  // //instance id would be useful to terminate it etc!!!
  // Aws::Vector<Aws::EC2::Model::Instance> launched_instances = r.GetInstances() ;

  // for (auto i : launched_instances) {
  //   Aws::String id = i.GetInstanceId() ;
  //   out.push_back(id.c_str()) ;
  // }

  return out ;
}


/******************************************************************************/

/**
 * Resource request made by a framework. Framework->offeredResources is partitioned by slaveId, and we do packing etc based off of that. 
 */
void CloudRM::res_req(
  mesos::internal::master::Framework* framework,
  const std::vector<mesos::Request>& requests)
{
  LOG(INFO) << "~~~~~~ REQ RCVD ";
  // 1. Check if resources requested + totalUsedResources is within bounds or
  // not?
  // 2. See if we can find some free resources on any machine to fill these
  // demands
  // find_free(framework, requests, constraints) ;
  // 3. Buy more cloud servers if required.
  // 4. Make this a Future/Promise thingy so that we know the execution context
  // (the framework which actually requested these servers.
  // 5. Once the new servers are up, do we need to perform the packing again?

  ResourceVector req;
  req.extract_resource_vector(requests);
  PlacementConstraint placement;
  placement.extract_placement_constraint(requests);

  std::string fmwk_id = framework->id().value() ;
  
  if (local_mode) {

    if (free_slaves.empty()) {
      // If no slave exists, add to pending frameworks and exit       
      LOG(INFO) << "************ START SOME AGENTS FOR FRAMEWORK!" ;
      
      pending_frameworks.push_back(fmwk_id) ;
      
      return ;
    }
    else {
      //There are some free slaves! Assign ALL to this framework
      //XXX TODO while loop here for all slaves.
      mesos::SlaveID slaveid = free_slaves.back() ;
      
      free_slaves.pop_back() ;
      
      // Match this slave with the framework
      allocator->alloc_slave_to_fmwk(slaveid, fmwk_id) ;
      
      return ;
    }

  } //end local mode 
  
  std::vector<ServerOrder> to_buy =
    get_servers(framework, req, placement, packing_policy);

  //TODO XXX change to true to start burning EC2 money muwahaha
  
  bool actually_buy = false ;
  
  if (actually_buy) {
    
    for (auto server : to_buy) {
      
      std::vector<std::string> instance_ids = actually_buy_servers(server) ;
      // We actually dont do anything with instance ids? 
      if (instance_ids.empty()) {
	LOG(INFO) << "Instance id vec is empty, oops " ;
      }
    }
  }
  
  // TODO: tag all these orders with the framework and AMI?
  // Actually ask amazon for these servers?
  finalize_server_order(to_buy, framework);

  bool ec2_buy = false;
  std::vector<ServerOrder> servers;

  if (ec2_buy) {
    // CALL EC2 libraries here.

  } else {
    servers = to_buy;
  }
  framework->ServerOrders = servers;
  framework->numServersAssigned = servers.size();
}

/********************************************************************************/

/* Fill in the server order with the framework and the AMI information if needed?
 */
void CloudRM::finalize_server_order(
  std::vector<ServerOrder>& to_buy,
  mesos::internal::master::Framework* framework)
{
  std::string frameworkID; //=framework->frameworkID ;
  std::string ami = "8y4982";
  for (auto order : to_buy) {
    order.framework = frameworkID;
    order.ami = ami;
  }
}

/********************************************************************************/

/**
 * How to represent constraints? It can either be just some alpha for now.
 * Other locality constraints may be supported in the future. 
 */
void find_free(
  mesos::internal::master::Framework* framework,
  std::vector<mesos::Request>& requests,
  std::vector<int> constraints)
{
  //This is where the packing logic is implemented. 

}

/********************************************************************************/


//Always returns a string, either an empty string or the
//slave-provided value

hashmap<std::string, std::string> CloudRM::parse_slave_attributes(
  const mesos::SlaveInfo& sinfo)
{
  hashmap<std::string, std::string> out;
  out["instance-type"] = "";
  out["az"] = "";
  out["owner-fmwk"] = "";

  std::string itype;
  std::string az;
  std::string owner_fmwk;

  mesos::Attributes attr = sinfo.attributes();

  int a_size = attr.size();
  int i = 0;

  for (i = 0; i < a_size; i++) {
    if (attr.get(i).name() == "instance-type") {
      itype = attr.get(i).text().value();
      out["instance-type"] = itype;
    } else if (attr.get(i).name() == "az") {
      az = attr.get(i).text().value();
      out["az"] = az;
    } else if (attr.get(i).name() == "owner-fmwk") {
      owner_fmwk = attr.get(i).text().value();
      out["owner-fmwk"] = owner_fmwk;
    }
  } // end FOR loop across all attributes

  return out;
}


/********************************************************************************/

 /* A new framework has been registered with us. Most frameworks will
  * subsequently ask for resources once they have been registered with
  * the mesos master. We can put the framework on some sort of a
  * pending list?
 */
int CloudRM::new_framework(const mesos::FrameworkInfo& frameworkinfo)
{
  LOG(INFO) << "~~~~~~~ NEW FRAMEWORK" ;
  std::string fid ;
  
  if(frameworkinfo.has_id()) {
    fid = frameworkinfo.id().value() ;
  }
  if(new_framework_starter_nodes == 0){
    return 0;
  }

  if (local_mode) {
    LOG(INFO) << "In local mode, nothing to do for new framework" ;
    // we dont do anything in cloud mode anyway
    return 1 ;
  }

  /* Create the server order vector for the framework according to some rule engine*/
  std::vector<ServerOrder> order ; //= pDefaultFrameworkResources(frameworkinfo) ;
  
  //add_to_pending_orders 
  if(!order.empty()) {
    
    LOG(INFO) << "Something in order " ;
    
    add_to_pending_orders(order) ; 
    /* Now ask the cloud layer to fulfill this order for us */
//     process:dispatch(AwsAgent, GetServers, order) 
  }
  return 1; 
}


/********************************************************************************/

/** Called from _registerSlave from the master, after allocator has
 *    been informed 
 */
void CloudRM::new_server(
  mesos::internal::master::Slave* slave, const mesos::SlaveInfo& sinfo)
{
  hashmap<std::string, std::string> slave_attrs = parse_slave_attributes(sinfo);
  // Store the attributes of the slave somewhere? In the master? Allocator?
  // Here?
  // extract the owner_framework
  std::string owner_framework = slave_attrs["owner-fmwk"];

  //Check if local slave
  bool unbound_slave = check_unbound_slave(slave_attrs) ;

  
  if (unbound_slave == true) {
    LOG(INFO) << "~~~ New unbound slave registered! " ;
    
    if (pending_frameworks.empty()) {
      //There are no frameworks registered yet. So put this in a free-list
      free_slaves.push_back(sinfo.id()) ;
      
      return ;
    }
    else {
      //There IS a framework we can assign this slave to!
      std::string candidate_fmwk = pending_frameworks.back() ;
      pending_frameworks.pop_back() ;
      
      allocator->alloc_slave_to_fmwk(sinfo.id(), candidate_fmwk) ;
      return ;
    }

  } //end unbound_slave 
  

  CloudMachine cm;
  cm.az = slave_attrs["az"]; // These may not exist either?
  cm.type = slave_attrs["instance-type"];

  LOG(INFO) << "~~~~~ New slave has az " << cm.az << " and type " << cm.type;
  
  allocator->addSlave_cloudinfo(sinfo.id(), cm);

  if (packing_policy == "private") {
    allocator->alloc_slave_to_fmwk(sinfo.id(), owner_framework);

  } else if (packing_policy == "binpack") {
  }
}


/********************************************************************************/


bool CloudRM::check_unbound_slave(hashmap<std::string, std::string>& s)
{
  LOG(INFO) << "Slave instance type is " <<  s["instance-type"] ;
  
  if (s["owner-fmwk"]=="*")
    return true ;
  else
    return false ;
}

/********************************************************************************/


void CloudRM::foo()
{
  LOG(INFO) << "~~~~~~~ FOO " ;

}

int CloudRM::bar()
{
  LOG(INFO) << "~~~~~~~ BAR CALLED " ;
  return 32; 
}


/******************************************************************************/
/*****************************   END  *****************************************/
/******************************************************************************/


