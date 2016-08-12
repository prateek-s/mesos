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

#ifndef __MASTER_HPP__
#include "master/master.hpp" //was commented!
#endif

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

class CloudRM ;

struct
{
hashmap<std::string, std::pair<int,int>> ec2 ={ {"m1.small",  std::make_pair(1,1)} }  ;
  int get_cpu(std::string type){
    return ec2[type].first ;
  }
  int get_mem(std::string type){
    return ec2[type].second ;
  }
  
} EC2_machines;

class ResourceVector
{
public:
  
  hashmap<std::string, double> res_vec ;
  /* TODO. Operators < > == . Will be useful for packing */

  static  double get_scalar_value(const std::vector<mesos::Request>& requests, std::string res_name)
  {
    for(auto req: requests) {

      const std::vector<mesos::Resource>& resources = google::protobuf::convert(req.resources()) ;
      for(auto res: resources) {
	//Each resource is still a protocol buffer?
	if(res.has_name()) {
	  LOG(INFO) << "~~~ Res req of type: "  << res.name() ;
					 
	  if(res_name == res.name() && res.has_scalar()) {
	    mesos::Value_Scalar val = res.scalar() ;
	    if(val.has_value()){
	      double dval = val.value() ;
	      LOG(INFO) << "~~~ Res req of type: "  << dval ;
	      return dval ;
	    } //value exists 
	  } //if CPU and scalar
	} //if resource has name
      } // for each resource 
    } // for each request
    return 0.0 ;
  }

  
  /* From the mesos request vector, get the CPU and memory requirements, convert them to numbers (Cores, MB memory, etc). Handle empty cases, etc. */
  void extract_resource_vector(const std::vector<mesos::Request>& requests)
  {
    //Although we get only one request in the vector, may get multiple, so process all!
    std::vector<std::string> types = {"cpu", "mem"} ;
    double dval ;
    
    for(auto t : types) {      
      dval = get_scalar_value(requests, t) ;
      if(dval != 0.0) {
	res_vec[t] = dval ;
      }
    }
  }

  int get_cpu() {
    return int(res_vec["cpu"]) ;
  }
  int get_mem() {
    return int(res_vec["mem"]) ;
  }
  
};

class PlacementConstraint
{
public:
  PlacementConstraint() {
    alpha = 0.2 ;
  }
  double alpha ; //Risk tolerance 
  void extract_placement_constraint(const std::vector<mesos::Request>& requests) {
    //TODO
  }
  
  virtual ~PlacementConstraint() {}
};

class CloudMachine
{
public:
  CloudMachine() {
  }
  std::string az ; //Availability Zone 
  std::string type ; // Machine type

  
  bool operator==(const CloudMachine &other) const
  {
    return az==other.az && type==other.type ;
  }
  
}; //END CloudMachine class

namespace std {
template <>
struct hash<CloudMachine>
{
  std::size_t operator()(const CloudMachine& c) const
  {
    return (std::hash<string>() (c.az)) ^  (std::hash<string>() (c.type)) ;
  }
} ;
} //namespace std 
//ServerOrder should be ONE order, so that when acquiring the servers, we can fill in the details one at a time.

/* This is a vector/collection of servers */
class ServerOrder
{
public:
  ServerOrder() {
    this->num = 0 ;
//    this->machine = (CloudMachine&) NULL ;
  }

  int num ;  //number of servers that we are supposed to order

  std::string framework ;

  std::string ami ;
  
  //This is filled in by whoever actually acquires the cloud server to point to the cloud server/machine. Initialized to null. 
  CloudMachine machine ;
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


  std::vector<ServerOrder> get_servers(mesos::internal::master::Framework* framework, ResourceVector& req, PlacementConstraint& placement, std::string packing_policy) ;

  hashmap<CloudMachine, int> get_portfolio_wts(double alpha) ;

  ServerOrder get_min_servers(double wt, const CloudMachine& cm, ResourceVector& req) ;

  std::vector<ServerOrder> compute_server_order(hashmap<CloudMachine, int> & portfolio_wts, ResourceVector& req, std::string packing_policy) ;

  void finalize_server_order(std::vector<ServerOrder>& to_buy, mesos::internal::master::Framework* framework) ;


  
  /**************************************/
  virtual ~CloudRM() {}
  
}; //end Class declaration


#endif 
