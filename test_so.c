#include "callstack.h"


static void function_so_static()
{
    callstack_print();
}


void function_so()
{
    function_so_static();
}
