/*    
CSC521 Operating system
Project:      2 mydispatcher
Programmer:   Rob Miles
Professor:    Dr. Lee
File Created: Oct 15, 2018
File Updated: Oct 15, 2018
*/

#include "mydispatcher.h"

int shortestRemainingTime(int tPin){
    
    unsigned short activeProcess = 0;                 //which process is "executing"
    unsigned short activeProcessesExist = 1;          //assume at least one live process at init
    unsigned short queuePos = 0;                      //keeps track of the last process queued, ready to "execute"
    unsigned short tP = tPin;                         //grab the total number of processes
    unsigned short expiredCounter = 0;                //keep track of number of complete processes
    unsigned short i = 0;                             //counter
    
    /*update new processes to queue for each timestep*/
    while (activeProcessesExist) {                    //check processes left that aren't finished
        
        unsigned short sizeComp = 65535;              //set large number to compare shorter processes to
        
        unsigned short index = 0;                     //start evaluation of processes at row 1
        while (processes[index].pid){                  //iterate input data
            struct Process *ptr = &processes[index];   //assign pointer to the struct
            if (!ptr->complete){                       //check if the process is live
                activeProcessesExist = 1;              //any live processes sets flag
                if (ptr->arrivalTime == globalTimeTicker){  //check if it's new to the queue
                    queue[queuePos] = ptr;             //add to queue if just arrived
                    
                    for (i = 0; i < queuePos; i++){    //scan for next shortest process in queue
                        if ((queue[i]->remExeTime < sizeComp) && (!queue[i]->complete)){
                            activeProcess = i;         //set the active process to that with shortest time left
                            sizeComp = queue[i]->remExeTime; //set value to compare others to
                            printf("sizeComp = %d pid%d\n", sizeComp, queue[i]->pid);
                        }
                    }
                    queuePos++;                        //move to next free space in array
                }
            }
            index++;                                   //increment to next struct in array
        }
        
        if (!queue[activeProcess]->exeStartTime)       //if this process just began to execute
            queue[activeProcess]->exeStartTime = globalTimeTicker;  //record the start time
        
        if ((queue[activeProcess]->remExeTime--) == 0){//decreast time remaining and see if it's 0
            queue[activeProcess]->complete = 1;        //if so, mark as complete
            expiredCounter++;                          //increase counter for completed processes
            for (i = 0; i < queuePos; i++){            //scan for next shortest process in queue
                if ((queue[i]->remExeTime < sizeComp) && (!queue[i]->complete)){
                    activeProcess = i;                 //set the active process to that with shortest time left
                    sizeComp = queue[i]->remExeTime;   //set value to compare others to
                    printf("sizeComp = %d pid%d\n", sizeComp, queue[i]->pid);
                }
            }
            if (expiredCounter >= tP){                 //quit loop if all processes expired
                break;
            }
        }
        
        if (activeProcessesExist == 0){                //if all processes are complete
            return 0;                                  // finish successfully
        }
        else {
            printf("time:%6ld   Q[i]:%6d   PID:%6d   ", globalTimeTicker, activeProcess, queue[activeProcess]->pid);
            printf("remains:%4d\n", queue[activeProcess]->remExeTime);
            globalTimeTicker++;                        //otherwise, there's more work to do, go to next time step
        }
    }
    return 0;
}

