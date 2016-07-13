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


CloudRM::CloudRM() {
    LOG(INFO) << "~~~ FROM CLOUD RM" ;
    std::cout << "  CLOUD RM \n" ;
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

int CloudRM::init()
{
   LOG(INFO) << "~~~~~~~ INITIALIZED by master" ;
   return 1; 
}


int CloudRM::new_framework(const mesos::FrameworkInfo& frameworkinfo)
{
   LOG(INFO) << "~~~~~~~ NEW FRAMEWORK" ;
   return 1; 

}
