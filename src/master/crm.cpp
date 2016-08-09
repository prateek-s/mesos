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


//using mesos::log::Log;

#include "master/crm.hpp"

//using std::string;
using namespace std ;

CloudRM::CloudRM()
{
  LOG(INFO) << "~~~ FROM CLOUD RM" ;
  std::cout << "  CLOUD RM \n" ;
}



/* The frameworkinfo structure has a lot of metadata about the framework, which can be used by some policies eventually to directly allocate resources to it even if they dont ask for it explicitly. This can be some basic rule engine etc. 
Return a vector of server orders here? 
 */
vector<ServerOrder> CloudRM::pDefaultFrameworkResources(const mesos::FrameworkInfo& frameworkinfo)
{
  //add_to_pending_orders(frameworkinfo);
  ServerOrder* order = new ServerOrder() ;
  //really should be a vector or a collection of orders.
  std::vector<ServerOrder> all_orders ;
  all_orders.push_back(*order) ;
  return all_orders ;
}


int CloudRM::init(mesos::internal::master::Master* master)
{
  this->master = master ;
  LOG(INFO) << "~~~~~~~ INITIALIZED by master" ;
  return 1; 
}


 /* A new framework has been registered with us. Most frameworks will subsequently ask for resources once they have been registered with the mesos master. We can put the framework on some sort of a pending list? 
 */
int CloudRM::new_framework(const mesos::FrameworkInfo& frameworkinfo)
{
  LOG(INFO) << "~~~~~~~ NEW FRAMEWORK" ;
  std::string fid ;
  
  if(frameworkinfo.has_id()) {
    fid = frameworkinfo.id().value() ;
  }
  if(new_framework_starter_nodes==0){
    return 0;
  }
    
  /* Create the server order vector for the framework according to some rule engine*/
  std::vector<ServerOrder> order = pDefaultFrameworkResources(frameworkinfo) ;
  
  //add_to_pending_orders 
  if(!order.empty()) {
    LOG(INFO) << "Something in order " ;
    add_to_pending_orders(order) ;
    /* Now ask the cloud layer to fulfill this order for us */
//     process:dispatch(AwsAgent, GetServers, order) 
  }
  return 1; 
}

void CloudRM::add_to_pending_orders(std::vector<ServerOrder> orders)
{
  
  
}

/**
 * Resource request made by a framework. Framework->offeredResources is partitioned by slaveId, and we do packing etc based off of that. 
 */
void CloudRM::res_req(mesos::internal::master::Framework* framework, const std::vector<mesos::Request>& requests)
{
  LOG(INFO) << "~~~~~~ REQ RCVD " ;
  //1. Check if resources requested + totalUsedResources is within bounds or not?
  //2. See if we can find some free resources on any machine to fill these demands
  // find_free(framework, requests, constraints) ;
  //3. Buy more cloud servers if required.
  //4. Make this a Future/Promise thingy so that we know the execution context (the framework which actually requested these servers.
  //5. Once the new servers are up, do we need to perform the packing again?


  
}

/**
 * How to represent constraints? It can either be just some alpha for now.
 * Other locality constraints may be supported in the future. 
 */
void find_free(mesos::internal::master::Framework* framework, std::vector<mesos::Request>& requests, std::vector<int> constraints) {
  //This is where the packing logic is implemented. 

}


void CloudRM::foo()
{
  LOG(INFO) << "~~~~~~~ FOO " ;

}

int CloudRM::bar()
{
  LOG(INFO) << "~~~~~~~ BAR CALLED " ;
  return 32; 
}
