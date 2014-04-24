#include <signal.h>
#include "callstack.h"


void function_global()
{
    callstack_print();
}


static void function_static()
{
    function_global();
}

static void function_callso()
{
    function_so();
}


int main(int argc, char **argv)
{
    if (argc == 1)
    {
        callstack_print();
    }
    else if (atoi(argv[1]) == 1)
    {
        callstack_set_print_onsignal(SIGSEGV);
        callstack_set_print_onsignal(SIGFPE);

        *(int *)123 = 456;
    }
    else if (atoi(argv[1]) == 2)
    {
        function_static();
    }
    else if (atoi(argv[1]) == 3)
    {
        function_callso();
    }

    return 0;
}
