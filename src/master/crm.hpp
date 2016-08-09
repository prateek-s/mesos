#ifndef __CRM_HPP__
#define __CRM_HPP__
#include <process/process.hpp>


#include <mesos/mesos.hpp>
#include <mesos/resources.hpp>
#include <mesos/type_utils.hpp>
#include <mesos/executor.hpp>
#include <mesos/scheduler.hpp>

//#include "slave/slave.hpp" //Required for Framework OR Request 

#include <mesos/maintenance/maintenance.hpp>


#include <mesos/allocator/allocator.hpp>
#include <mesos/master/contender.hpp>
#include <mesos/master/detector.hpp>
#include <mesos/master/master.hpp>

#include <mesos/module/authenticator.hpp>

#include <mesos/quota/quota.hpp>

#include <mesos/scheduler/scheduler.hpp>


//#include "master/master.hpp"

#include "master/constants.hpp"
#include "master/flags.hpp"
#include "master/machine.hpp"
#include "master/metrics.hpp"
#include "master/registrar.hpp"
#include "master/validation.hpp"

#include "messages/messages.hpp"


#include "common/http.hpp"
#include "common/protobuf_utils.hpp"
#include "common/resources_utils.hpp"

#include <vector>

//using namespace mesos ;
//using namespace mesos::internal ;
//using namespace mesos::internal::slave ;
//using namespace mesos::internal::master ;


//using mesos::internal::slave::Slave;

//using namespace process;
using namespace std;

//ServerOrder should be ONE order, so that when acquiring the servers, we can fill in the details one at a time.

class CloudMachine
{
public:
  CloudMachine() {
  }
  std::string az ;
  std::string type ;
}; //END CloudMachine class

/* This is a vector/collection of servers */
class ServerOrder
{
public:
  ServerOrder() {
    this->num = 0 ;
    this->machine = (CloudMachine*) NULL ;
  }

  mesos::FrameworkID owner_framework ; 

  int num ;  //number of servers that we are supposed to order

  //This is filled in by whoever actually acquires the cloud server to point to the cloud server/machine. Initialized to null. 
  CloudMachine* machine ;
};  //End ServerOrder Class 



class CloudRM : public process::Process<CloudRM>
{
public :
  CloudRM() ;
  /***************** Fields **************/
  
  int p = 42 ;
  
  mesos::internal::master::Master* master ;

  vector<ServerOrder> pendingOrders  ;

  /****** Policy flags **********/
  int new_framework_starter_nodes = 0 ;

  std::string packing_policy = "none" ;

  std::string replenish_policy = "none" ;

  
  /************* Methods **************/
  void foo() ;
  
  int bar() ;
  
  /* Initialization message from the master */
  int init(mesos::internal::master::Master* master) ;

  /* Newly registered framework */
  int new_framework(const mesos::FrameworkInfo& frameworkinfo) ;
  
  void res_req(mesos::internal::master::Framework* framework, const std::vector<mesos::Request>& requests) ;

  //Should really return a vector of orders. 
  std::vector<ServerOrder> pDefaultFrameworkResources(const mesos::FrameworkInfo& frameworkinfo) ;

  void add_to_pending_orders(std::vector<ServerOrder> orders) ;

  /**************************************/
  virtual ~CloudRM() {}
  
}; //end Class declaration


#endif 
