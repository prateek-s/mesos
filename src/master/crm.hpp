
#include <process/defer.hpp>
#include <process/dispatch.hpp>
#include <process/future.hpp>
#include <process/http.hpp>

#include <process/process.hpp>
//#include <mesos/state/log.hpp>

#include <stout/check.hpp>
#include <stout/duration.hpp>
#include <stout/exit.hpp>
#include <stout/flags.hpp>
#include <stout/nothing.hpp>
#include <stout/option.hpp>
#include <stout/os.hpp>
#include <stout/path.hpp>
#include <stout/stringify.hpp>
#include <stout/strings.hpp>
#include <stout/try.hpp>

#include "logging/flags.hpp"
#include "logging/logging.hpp"


using namespace process;


class CloudRM : public Process<CloudRM>
{
public :
    CloudRM() ;
    int p = 42 ;

    void foo() ;
	
    int bar() ;
    
    virtual ~CloudRM() {}

};
