通过backtrace()函数可以获得当前的程序堆栈地址. 提供一个指针数组, backtrace()函数会把调用堆栈的地址填到里面.
#include <execinfo.h>
int backtrace(void **buffer, int size);

为了跟踪动态库, 需要给gcc添加-rdynamic参数. 另外, 为了看到函数名, 行号等调试信息, 还要添加-g参数.
-rdynamic参数的涵义: This instructs the linker to add all symbols, not only used ones, to the dynamic symbol table. This option is needed for some uses of dlopen or to allow obtaining backtraces from within a program

backtrace_symbols()可以将堆栈地址转换成可读的信息用于打印, 但不是很具体, 无法显示出函数名和行号, 通过binutils的addr2line可以做到这一点. 调用方式为: addr2line -Cif -e 文件名 地址

对于动态库中的函数, 文件名是动态库的. backtrace给出的堆栈地址是经过map的, 因此需要将映射后的地址还原. 映射的基地址可通过读取/proc/self/maps得到.

对于程序运行环境没有addr2line工具的情况, 如嵌入式平台, 可以打印出地址, 在PC上用交叉工具链的addr2line工具分析.

对于一些系统或第三方没有加-g编译的so库, addr2line可能看不到函数名和行号的信息, 这时使用dladdr()函数可看到一些导出函数的函数名. dladdr()要使用backtrace()获得的原始地址, 不是还原后的.

通过sigaction()注册一些系统信号的处理回调, 如SIGSEGV, 可以在Segmentation fault时打印程序堆栈.

由于C++的符号是经过name mangling, 为了显示的友好性, 可先做demangle.

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
[01] 0x7ffbda2dd5ca   0x5ca            func: function_so_static, file: /data/callstack/test_so.c L7, module: /data/callstack/libtest.so
[02] 0x7ffbda2dd5da   0x5da            func: function_so, file: /data/callstack/test_so.c L13, module: /data/callstack/libtest.so
[03] 0x401c5e         0x401c5e         func: function_callso, file: /data/callstack/test.c L19, module: /data/callstack/callstack
[04] 0x401d12         0x401d12         func: main, file: /data/callstack/test.c L44, module: /data/callstack/callstack
[05] 0x7ffbd9f3e76d   0x2176d          func: __libc_start_main, file: unknown, module: /lib/x86_64-linux-gnu/libc.so.6
[06] 0x400f59         0x400f59         func: _start, file: unknown, module: /data/callstack/callstack
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
