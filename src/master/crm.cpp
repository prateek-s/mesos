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

#include "crm.hpp"

//using std::string;

//using namespace CloudRM ;

CloudRM::CloudRM()
{
    LOG(INFO) << "~~~ FROM CLOUD RM" ;
    std::cout << "  CLOUD RM \n" ;
}



/* The frameworkinfo structure has a lot of metadata about the framework, which can be used by some policies eventually to directly allocate resources to it even if they dont ask for it explicitly. This can be some basic rule engine etc. 
Return a vector of server orders here? 
 */
int pDefaultFrameworkResources(const mesos::FrameworkInfo& frameworkinfo)
{
  //add_to_pending_orders(frameworkinfo);
  return 0 ;
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

   int new_orders = pDefaultFrameworkResources(frameworkinfo) ;

   if(new_orders > 0) {
     

   }
   
   return 1; 
}


/**
 * New frameworks should call in resource requests if 
 */
void CloudRM::res_req(mesos::internal::master::Framework* framework, const std::vector<mesos::Request>& requests)
{
    LOG(INFO) << "~~~~~~ REQ RCVD " ;

}


