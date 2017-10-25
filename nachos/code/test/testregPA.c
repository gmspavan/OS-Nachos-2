#include "syscall.h"
#define SIZE 100
int
main()
{   
    syscall_wrapper_PrintString("Total Time: ");
    syscall_wrapper_PrintInt(syscall_wrapper_GetTime());
    syscall_wrapper_PrintChar('\n');
    int array[SIZE], i, sum=0;
    //syscall_wrapper_PrintInt(array);
    syscall_wrapper_PrintString("PID of current thread: ");
    syscall_wrapper_PrintInt(syscall_wrapper_GetPID());
    syscall_wrapper_PrintChar('\n');
    syscall_wrapper_PrintString("PPID of current thread: ");
    syscall_wrapper_PrintInt(syscall_wrapper_GetPPID());
    syscall_wrapper_PrintChar('\n');
    syscall_wrapper_PrintString("Total Instr: ");
    syscall_wrapper_PrintInt(syscall_wrapper_GetNumInstr());
    syscall_wrapper_PrintChar('\n');
    syscall_wrapper_PrintString("Starting physical address of array: ");
    syscall_wrapper_PrintInt(syscall_wrapper_GetPA((unsigned)array));
    syscall_wrapper_PrintChar('\n');
    syscall_wrapper_PrintString("Physical address of array[50]: ");
    syscall_wrapper_PrintInt(syscall_wrapper_GetPA(&array[50]));
    syscall_wrapper_PrintChar('\n');
    syscall_wrapper_PrintString("Total Time: ");
    syscall_wrapper_PrintInt(syscall_wrapper_GetTime());
    syscall_wrapper_PrintChar('\n');
    syscall_wrapper_Sleep(2908);
    syscall_wrapper_PrintString("Total Time: ");
    syscall_wrapper_PrintInt(syscall_wrapper_GetTime());
    syscall_wrapper_PrintChar('\n');
    syscall_wrapper_PrintString("Current physical address of stack top: ");
    syscall_wrapper_PrintInt(syscall_wrapper_GetPA(syscall_wrapper_GetReg(29)));
    syscall_wrapper_PrintChar('\n');
    for (i=0; i<SIZE; i++) array[i] = i;
    syscall_wrapper_PrintString("We are currently at PC: ");
    syscall_wrapper_PrintIntHex(syscall_wrapper_GetReg(34));
    syscall_wrapper_PrintChar('\n');
    syscall_wrapper_PrintString("Total Instr: ");
    syscall_wrapper_PrintInt(syscall_wrapper_GetNumInstr());
    syscall_wrapper_PrintChar('\n');
    syscall_wrapper_PrintString("Total Instr: ");
    syscall_wrapper_PrintInt(syscall_wrapper_GetNumInstr());
    syscall_wrapper_PrintChar('\n');
    for (i=0; i<SIZE; i++) sum += array[i];
    syscall_wrapper_PrintString("Total sum: ");
    syscall_wrapper_PrintInt(sum);
    syscall_wrapper_PrintChar('\n');
    syscall_wrapper_Exit(0);
    syscall_wrapper_PrintString("Total Time: ");
    syscall_wrapper_PrintInt(syscall_wrapper_GetTime());
    syscall_wrapper_PrintChar('\n');
    return 0;
}
