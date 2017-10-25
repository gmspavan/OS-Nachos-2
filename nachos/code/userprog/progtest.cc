// progtest.cc
//	Test routines for demonstrating that Nachos can load
//	a user program and execute it.
//
//	Also, routines for testing the Console hardware device.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "console.h"
#include "addrspace.h"
#include "synch.h"



//Edited_Assignment2_Start

extern void ForkStartFunction(int dummy);

void LaunchThreads(char *fileName)
{
//  printf("batch jobs file %s\n", fileName);
  int priority_val=0;
  ProcessAddressSpace *space;
  OpenFile *executable;
  NachOSThread *tempThread;

  int temp;
	char a[100];
	char b[4], c[3];
	int fileName_given = 0;
	int priority_given = 0;
  int schedulerType = 0;
  FILE * file;
	file = fopen(fileName, "r");
  temp = fgetc(file);
  int i=0, j=0;
  while(!(temp == ' ' || feof(file) || temp=='\n'))
  {
      schedulerType = schedulerType*10 + (temp - '0');
      temp = fgetc(file);
  }
  scheduler->setSchedulerAlgo(schedulerType);
  while(!feof(file))
  {
    //Code for file parsing
        fileName_given = 0;
    		priority_given = 0;
        temp = fgetc(file);
        while(!(temp == ' ' || feof(file) || temp=='\n'))
    		{
            *(a+i)=(char)temp;
        		i++;
    				temp = fgetc(file);
    		}
        if(i!=0){
    			fileName_given = 1;
    			*(a+i)='\0';
        }
        if(temp == ' '){
    			while(temp == ' ') temp = fgetc(file);
    			while(!(temp == ' ' || feof(file) || temp=='\n')){
    				ASSERT(!(j>2 || (temp>'9' || temp<'0')));
    				*(b+j)=(char)temp;
        		j++;
    				temp = fgetc(file);
    			}
    			while(temp == ' ') temp = fgetc(file);
    			if(j!=0)
    			{
    				priority_given = 1;
    				*(b+j)='\0';
    			}
    		}
        if(priority_given)
        {
          int i;
          for(i=0; *(b+i)!='\0'; i++)
          {
            priority_val = priority_val*10 + (*(b+i)-'0');
          }
        }
        if(fileName_given)
        {
          executable = fileSystem->Open(a);
          if (executable == NULL) {
            printf("Unable to open file %s\n", a);
            return;
          }
          tempThread = new NachOSThread(a);
          space = new ProcessAddressSpace(executable);
          tempThread->space = space;
          delete executable;			// close file
          space->InitUserModeCPURegisters();
          tempThread->SaveUserState();
          if(priority_given) tempThread->setPriority(priority_val);
          tempThread->ThreadFork(ForkStartFunction, 0);     // Make it ready for a later context switch
          }
  }
}
//Edited_Assignment2_Stop


//----------------------------------------------------------------------
// LaunchUserProcess
// 	Run a user program.  Open the executable, load it into
//	memory, and jump to it.
//----------------------------------------------------------------------

void
LaunchUserProcess(char *filename)
{
    OpenFile *executable = fileSystem->Open(filename);
    ProcessAddressSpace *space;

    if (executable == NULL) {
	printf("Unable to open file %s\n", filename);
	return;
    }
    space = new ProcessAddressSpace(executable);
    currentThread->space = space;

    delete executable;			// close file

    space->InitUserModeCPURegisters();		// set the initial register values
    space->RestoreContextOnSwitch();		// load page table register
    machine->Run();			// jump to the user progam
    ASSERT(FALSE);			// machine->Run never returns;
					// the address space exits
					// by doing the syscall "exit"
}

// Data structures needed for the console test.  Threads making
// I/O requests wait on a Semaphore to delay until the I/O completes.

static Console *console;
static Semaphore *readAvail;
static Semaphore *writeDone;

//----------------------------------------------------------------------
// ConsoleInterruptHandlers
// 	Wake up the thread that requested the I/O.
//----------------------------------------------------------------------

static void ReadAvail(int arg) { readAvail->V(); }
static void WriteDone(int arg) { writeDone->V(); }

//----------------------------------------------------------------------
// ConsoleTest
// 	Test the console by echoing characters typed at the input onto
//	the output.  Stop when the user types a 'q'.
//----------------------------------------------------------------------

void
ConsoleTest (char *in, char *out)
{
    char ch;

    console = new Console(in, out, ReadAvail, WriteDone, 0);
    readAvail = new Semaphore("read avail", 0);
    writeDone = new Semaphore("write done", 0);

    for (;;) {
	readAvail->P();		// wait for character to arrive
	ch = console->GetChar();
	console->PutChar(ch);	// echo it!
	writeDone->P() ;        // wait for write to finish
	if (ch == 'q') return;  // if q, quit
    }
}
