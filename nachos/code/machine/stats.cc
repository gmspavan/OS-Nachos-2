// stats.h
//	Routines for managing statistics about Nachos performance.
//
// DO NOT CHANGE -- these stats are maintained by the machine emulation.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "utility.h"
#include "stats.h"

//Edited_Assignment2_Start
extern int numThreadsExited;
//Edited_Assignment2_Stop

//----------------------------------------------------------------------
// Statistics::Statistics
// 	Initialize performance metrics to zero, at system startup.
//----------------------------------------------------------------------

Statistics::Statistics()
{
    totalTicks = idleTicks = systemTicks = userTicks = 0;
    numDiskReads = numDiskWrites = 0;
    numConsoleCharsRead = numConsoleCharsWritten = 0;
    numPageFaults = numPacketsSent = numPacketsRecvd = 0;
    //Edited_Assignment2_Start
    totalCPUbursts=0;
    CPUburstlen=0;
    totalExecTime=0;
    maxCPUburstlen=0;
    minCPUburstlen=0;
    totalreadyQueueWaitTime=0;
    maxThreadCompletionTime=0;
    minThreadCompletionTime=0;
    sumThreadCompletionTime=0;
    sumSqrThreadCompletionTime=0;
    //Edited_Assignment2_Stop
}

//----------------------------------------------------------------------
// Statistics::Print
// 	Print performance metrics, when we've finished everything
//	at system shutdown.
//----------------------------------------------------------------------

void
Statistics::Print()
{
    printf("Ticks: total %d, idle %d, system %d, user %d\n", totalTicks,
	idleTicks, systemTicks, userTicks);
  //Edited_Assignment2_Start
    printf("Total CPU Busy Time : %d\n",this->CPUburstlen);
    printf("Total Execution Time : %d\n",this->totalExecTime);
    printf("CPU utilisation : %f\n",(this->CPUburstlen/(1.0*this->totalExecTime)) );
    printf("CPUBursts: maximum %d, minimum %d, average %f\n", this->maxCPUburstlen, this->minCPUburstlen, this->CPUburstlen/(1.0*this->totalCPUbursts));
    printf("non-zero CPUBursts : %d\n", this->totalCPUbursts);
    if(numThreadsExited) printf("Average waiting in Ready Queue : %f\n", this->totalreadyQueueWaitTime/(1.0*numThreadsExited));
    else printf("No threads Executed to print average waiting time in ready queue\n");
    if(numThreadsExited) printf("threadCompletionTime: maximum %d, minimum %d, average %lf, variance %lf\n", maxThreadCompletionTime, minThreadCompletionTime, sumThreadCompletionTime/(1.0*numThreadsExited), (((sumSqrThreadCompletionTime)/(1.0*numThreadsExited)) - ((sumThreadCompletionTime/(1.0*numThreadsExited))*(sumThreadCompletionTime/(1.0*numThreadsExited)))));
    else printf("No threads Executed to print thread Completion time\n");
  //Edited_Assignment2_Stop
    printf("Disk I/O: reads %d, writes %d\n", numDiskReads, numDiskWrites);
    printf("Console I/O: reads %d, writes %d\n", numConsoleCharsRead,
	numConsoleCharsWritten);
    printf("Paging: faults %d\n", numPageFaults);
    printf("Network I/O: packets received %d, sent %d\n", numPacketsRecvd,
	numPacketsSent);
}
