#ifndef __CRM_HPP__
#define __CRM_HPP__
#include <process/process.hpp>


#include <mesos/mesos.hpp>
#include <mesos/resources.hpp>
#include <mesos/attributes.hpp>
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

#include "master/allocator/mesos/hierarchical.hpp"

#include "common/http.hpp"
#include "common/protobuf_utils.hpp"
#include "common/resources_utils.hpp"

#include <vector>

#include <sstream>

/////////////////// AWS 
#include <aws/core/Aws.h>
#include <aws/core/Region.h>
#include <aws/ec2/model/RunInstancesRequest.h>
#include <aws/ec2/model/TerminateInstancesRequest.h>

#include <aws/ec2/EC2Client.h>
//#include <aws/client/ClientConfiguration.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/ec2/model/Instance.h>



//using namespace mesos ;
//using namespace mesos::internal ;
//using namespace mesos::internal::slave ;
//using namespace mesos::internal::master ;


//using mesos::internal::slave::Slave;

//using namespace process;
using namespace std;

class CloudRM ;
class CloudMachine ;  // Class cloudmachine defined in include/mesos/master/crm.hpp

/******************************************************************************/

struct
{
  hashmap<std::string, std::pair<int,int>> ec2 = 
{ { "t2.nano", std::make_pair(1, 0.5)} , { "t2.micro", std::make_pair(1, 1.0)} , { "t2.small", std::make_pair(1, 2.0)} , { "m3.medium", std::make_pair(1, 3.75)} , { "m1.small", std::make_pair(1, 1.7)} , { "m1.medium", std::make_pair(1, 3.75)} , { "t1.micro", std::make_pair(1, 0.613)} , { "t2.medium", std::make_pair(2, 4.0)} , { "t2.large", std::make_pair(2, 8.0)} , { "m4.large", std::make_pair(2, 8.0)} , { "c4.large", std::make_pair(2, 3.75)} , { "r3.large", std::make_pair(2, 15.25)} , { "m3.large", std::make_pair(2, 7.5)} , { "c3.large", std::make_pair(2, 3.75)} , { "m1.large", std::make_pair(2, 7.5)} , { "c1.medium", std::make_pair(2, 1.7)} , { "m2.xlarge", std::make_pair(2, 17.1)} , { "m4.xlarge", std::make_pair(4, 16.0)} , { "c4.xlarge", std::make_pair(4, 7.5)} , { "r3.xlarge", std::make_pair(4, 30.5)} , { "i2.xlarge", std::make_pair(4, 30.5)} , { "d2.xlarge", std::make_pair(4, 30.5)} , { "m3.xlarge", std::make_pair(4, 15.0)} , { "c3.xlarge", std::make_pair(4, 7.5)} , { "m1.xlarge", std::make_pair(4, 15.0)} , { "m2.2xlarge", std::make_pair(4, 34.2)} , { "m4.2xlarge", std::make_pair(8, 32.0)} , { "c4.2xlarge", std::make_pair(8, 15.0)} , { "g2.2xlarge", std::make_pair(8, 15.0)} , { "r3.2xlarge", std::make_pair(8, 61.0)} , { "i2.2xlarge", std::make_pair(8, 61.0)} , { "d2.2xlarge", std::make_pair(8, 61.0)} , { "m3.2xlarge", std::make_pair(8, 30.0)} , { "c3.2xlarge", std::make_pair(8, 15.0)} , { "c1.xlarge", std::make_pair(8, 7.0)} , { "m2.4xlarge", std::make_pair(8, 68.4)} , { "cg1.4xlarge", std::make_pair(16, 22.5)} , { "m4.4xlarge", std::make_pair(16, 64.0)} , { "c4.4xlarge", std::make_pair(16, 30.0)} , { "r3.4xlarge", std::make_pair(16, 122.0)} , { "i2.4xlarge", std::make_pair(16, 122.0)} , { "d2.4xlarge", std::make_pair(16, 122.0)} , { "hi1.4xlarge", std::make_pair(16, 60.5)} , { "hs1.8xlarge", std::make_pair(16, 117.0)} , { "c3.4xlarge", std::make_pair(16, 30.0)} , { "cc2.8xlarge", std::make_pair(32, 60.5)} , { "g2.8xlarge", std::make_pair(32, 60.0)} , { "r3.8xlarge", std::make_pair(32, 244.0)} , { "i2.8xlarge", std::make_pair(32, 244.0)} , { "c3.8xlarge", std::make_pair(32, 60.0)} , { "cr1.8xlarge", std::make_pair(32, 244.0)} , { "c4.8xlarge", std::make_pair(36, 60.0)} , { "d2.8xlarge", std::make_pair(36, 244.0)} , { "m4.10xlarge", std::make_pair(40, 160.0)} , { "x1.32xlarge", std::make_pair(128, 1952.0)}  }  ;
  
  int get_cpu(std::string type){
    return ec2[type].first ;
  }
  int get_mem(std::string type){
    return ec2[type].second ;
  }
  
} EC2_machines;

/******************************************************************************/

class Portfolios
{
public:
  // alpha -> [(mkt,wt)] 
  hashmap<double, std::vector<std::tuple<CloudMachine, double>>> out ; 

  void split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
  }

  
  void new_portfolio(double alpha) {
    std::vector<std::tuple<CloudMachine, double>> vec ;
    out[alpha] = vec ;
  }

  
  void add(double alpha, std::string market, double wt) {
    auto vec = out[alpha] ;
    CloudMachine cm ;
    //TODO PARSING LATER!
    cm.type = market ;
    cm.az = "a" ;

    std::vector<std::string> ssplit ;
    split(market, '-', ssplit) ;
    
    if(ssplit.size() > 1) {
      cm.type = ssplit[0] ;
      cm.az = ssplit[1] ;
    }
    
    auto tup = std::make_tuple(cm, wt) ;
    vec.push_back(tup) ;
  }

  //Return the portfolio for the NEAREST alpha!
  std::vector<std::tuple<CloudMachine, double>> get_portfolio_wts(double alpha) {
    //First see if we can find alpha in the hashmap!
    auto search = out.find(alpha);
    
    if(search != out.end()) {      
      LOG(INFO) << "Found matching alpha! " << alpha ;      
      return out[alpha] ;
    }
    //Need to iterate over all the hashmap entries to find the closest one
    double best_alpha = 0 ;
    double min_diff = 10000000 ;
    
    foreachkey(const double a , out) {
      double diff = std::abs(a-alpha) ;
      if (diff < min_diff) {
	min_diff = diff ;
	best_alpha = a ;
      }
    }

    
    //XXX FIX 
    return out[best_alpha] ;
  } //END METHOD 

  
}; //END CLASS



/******************************************************************************/

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
	    if(val.has_value()) {
	      double dval = val.value() ;
	      LOG(INFO) << "~~~ VALUE: "  << dval ;
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
    std::vector<std::string> types = {"cpu", "mem", "alpha"} ;
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

  double get_alpha() {
    return double(res_vec["alpha"]) ;
  }
  
};

/**********************************************************************/

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



// class CloudMachine
// {
// public:
//   CloudMachine() {
//   }
//   std::string az ; //Availability Zone 
//   std::string type ; // Machine type

  
//   bool operator==(const CloudMachine &other) const
//   {
//     return az==other.az && type==other.type ;
//   }
  
// }; //END CloudMachine class
// Class cloudmachine defined in include/mesos/master/crm.hpp

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

/********************  CLASS ServerOrder     ******************************/

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

  std::string status ;  //ordered, fulfilled
  
  
};  //End ServerOrder Class 


/***********************   CLASS SlaveManager **********************************/

class SlaveManager
{
public :
  SlaveManager() {}
  /**************************************************/
  
  //Framework, vector<slaveids> 
  hashmap<std::string, std::vector<std::string>> dedicated_slaves ;

  hashmap<std::string, std::string> slave_to_instance ;

  hashmap<std::string, CloudMachine> market_map ;

  //slave-ids 
  std::vector<std::string> free_slaves ;

  /**************************************************/
  
  void new_fmwk(std::string fmwk) {
    //Do we need to initialize this at all?
    dedicated_slaves[fmwk].clear() ;
  }

  /**************************************************/

  void add_slave(
    std::string fmwk,
    std::string slaveid,
    std::string instance_id,
    CloudMachine cm)
  {
    // Just add to dicts
    slave_to_instance[slaveid] = instance_id;

    dedicated_slaves[fmwk].push_back(slaveid);

    market_map[slaveid] = cm ;
  }

  /**************************************************/
  
  void die_fmwk(std::string fmwk) {
    //Move its slaves to free list
    for (auto s : dedicated_slaves[fmwk]) {
      free_slaves.push_back(s) ;
    }
    
    dedicated_slaves[fmwk].clear() ;
  }

  /**************************************************/
} ; //END CLASS 

/***********************  CLASS CloudRM   ***********************************/

class CloudRM : public process::Process<CloudRM>
{
public :
  CloudRM() ;
  /***************** Fields **************/
  
  int p = 42 ;

  bool local_mode ;
  
  mesos::internal::master::Master* master ;

  vector<ServerOrder> pendingOrders  ;

  SlaveManager slaveManager ; 
  
  //Framework, 
  hashmap<std::string, std::vector<ServerOrder>> dedicated_slaves ;
  
  mesos::allocator::Allocator* allocator ;
  
  std::vector<mesos::SlaveID> free_slaves ; //unbound_slaves

  std::vector<std::string> pending_frameworks ; //in unbound_slaves mode 

  Portfolios default_portfolios ;
  
  /************ AWS STUFF ****************/
  Aws::SDKOptions options ;
  
  Aws::Auth::AWSCredentials creds ;

  Aws::Client::ClientConfiguration cconfig ;

  Aws::EC2::EC2Client* client ;

  
  /****** Policy flags **********/
  int new_framework_starter_nodes = 0 ;

  std::string packing_policy = "private" ; //"private", "binpack", "any", "offline"

  std::string replenish_policy = "none" ;

  
  /************* Methods **************/
  void foo() ;
  
  int bar() ;

  /* Initialization message from the master */
  int init(mesos::internal::master::Master* master);

  /* Newly registered framework */
  int new_framework(const mesos::FrameworkInfo& frameworkinfo);

  int die_framework(mesos::internal::master::Framework* framework) ;
  
  void res_req(
    mesos::internal::master::Framework* framework,
    const std::vector<mesos::Request>& requests);

  // Should really return a vector of orders.
  std::vector<ServerOrder> pDefaultFrameworkResources(
    const mesos::FrameworkInfo& frameworkinfo);

  void add_to_pending_orders(std::vector<ServerOrder> orders);

  Portfolios read_portfolio_wts() ;

  std::vector<ServerOrder> get_servers(
    mesos::internal::master::Framework* framework,
    ResourceVector& req,
    PlacementConstraint& placement,
    std::string packing_policy);

  ServerOrder get_min_servers(
    double wt,
    const CloudMachine& cm,
    ResourceVector& req,
    std::string packing_policy);

  std::vector<ServerOrder> compute_server_order(
    std::vector<std::tuple<CloudMachine, double>>& portfolio_wts,
    ResourceVector& req,
    std::string packing_policy);

  std::vector<std::string> actually_buy_servers(ServerOrder& to_buy) ;

  int terminate_ec2_server(std::string instance_id) ;
  
  void finalize_server_order(
    std::vector<ServerOrder>& to_buy,
    mesos::internal::master::Framework* framework);
  
  hashmap<std::string, std::string> parse_slave_attributes(
    const mesos::SlaveInfo& sinfo);

  void new_server(
    mesos::internal::master::Slave* slave, const mesos::SlaveInfo& sinfo);

  bool check_unbound_slave(hashmap<std::string, std::string>& s) ;

  
  /**************************************/
  virtual ~CloudRM() {}
  
}; //end Class declaration

/******************************************************************************/

#endif 
