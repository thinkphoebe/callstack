/**
 * @brief a piece of code print calling stack information
 *
 * @author Ye Shengnan
 * @date 2014-04-22 created
 */

#ifndef __CALLSTACK_H__
#define __CALLSTACK_H__

#ifdef __cplusplus
extern "C" {
#endif


void callstack_print(int max_frames);


typedef int (*callstack_output_func)(const char *format, ...);

//callstack_print use printf by default, to integrate with your program,
//you could set it to your log print functions
void callstack_set_output_func(callstack_output_func func);

int callstack_set_print_onsignal(int signum);


#ifdef __cplusplus
}
#endif

#endif // __CALLSTACK_H__

