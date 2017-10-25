#include "syscall.h"

int
main()
{   
    syscall_wrapper_PrintString("Program Started\n");
    int x, i;
    x = syscall_wrapper_Fork();
    for (i=0; i<5; i++) {
       syscall_wrapper_PrintString("*** thread ");
       syscall_wrapper_PrintInt(syscall_wrapper_GetPID());
       syscall_wrapper_PrintString(" looped ");
       syscall_wrapper_PrintInt(i);
       syscall_wrapper_PrintString(" times.\n");
       syscall_wrapper_Yield();
    }
    if (x != 0) {
       syscall_wrapper_PrintString("Before join.\n");
       int exitCode = syscall_wrapper_Join(x);
       syscall_wrapper_PrintString("After join.\n");
    }
    return 0;
}
