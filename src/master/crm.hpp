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

class CloudRM : public process::Process<CloudRM>
{
public :
    CloudRM() ;
    int p = 42 ;

    void foo() ;
	
    int bar() ;

    /* Initialization message from the master */
    int init() ;

    int new_framework(const mesos::FrameworkInfo& frameworkinfo) ;

void res_req(mesos::internal::master::Framework* framework, const std::vector<mesos::Request>& requests) ;

//void resource_request(mesos::internal::master::Framework* framework, const scheduler::Call::Request& request) ;

    
    virtual ~CloudRM() {} 

};


#endif 
