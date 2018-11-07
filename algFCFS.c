/*    
 CSC521 Operating system
 Project:      2 mydispatcher
 Programmer:   Rob Miles
 Professor:    Dr. Lee
 File Created: Oct 15, 2018
 File Updated: Oct 15, 2018
 */

#include "mydispatcher.h"

int firstComeFirstServe(){

    unsigned short int activeProcess = 0;             //which process is "executing"
    int activeProcessesExist = 1;                      //assume at least one live process at init
    unsigned short int queuePos = 0;                  //keeps track of the last process queued, ready to "execute"
    
    /*update new processes to queue for each timestep*/
     while (activeProcessesExist) {                    //check processes left that aren't finished
        unsigned short int index = 0;                 //start evaluation of processes at row 1
        while (processes[index].pid){                  //iterate input data
            struct Process *ptr = &processes[index];   //assign pointer to the struct
            if (!ptr->complete){                       //check if the process is live
                activeProcessesExist = 1;              //any live processes sets flag
                if (ptr->arrivalTime == globalTimeTicker){  //check if it's new to the queue
                    queue[queuePos] = ptr;             //add to queue if just arrived
                    queuePos++;                        //move to next free space in array
                }
            }
            index++;                                   //increment to next struct in array
        }

        /*process the queue/currently "executing" process*/
        if (!queue[activeProcess]->exeStartTime)       //if this process just began to execute
            queue[activeProcess]->exeStartTime = globalTimeTicker;  //record the start time
        if ((queue[activeProcess]->remExeTime --) == 0){//decreast time remaining and see if it's 0
            queue[activeProcess]->complete = 1;        //if so, mark as complete
            activeProcess++;                           //move to next process in queue
            if (!queue[activeProcess]){                //if no more in queue
                activeProcessesExist = 0;              //turn off flag
            }
        }
        
        if (activeProcessesExist == 0){                //if all processes are complete
            return 0;                                  // finish successfully
        } else {
            printf("%ld=ticks %d=active ", globalTimeTicker, activeProcessesExist);
            printf("%d=rem %d=activeProcess  %d=index\n", queue[activeProcess]->remExeTime, activeProcess, index);
            globalTimeTicker ++;                       //otherwise, there's more work to do, go to next time step
        }
    }
    
    return 0;
}
