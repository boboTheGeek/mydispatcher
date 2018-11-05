/*    
 CSC521 Operating system
 Project:      2 mydispatcher
 Programmer:   Rob Miles
 Professor:    Dr. Lee
 File Created: Oct 15, 2018
 File Updated: Oct 15, 2018
 */
#include <stdio.h>

#include "mydispatcher.h"

void addNewToQueue(){
    
    
}


int firstComeFirstServe(){
    
    unsigned short int activeProcess = 0;  //keeps track of which process is "executing"
    int activeProcessesExist = 1;       //if items in queue
    unsigned short int queuePos = 0;  //keeps track of the last process queued, ready to "execute"
    
     while (activeProcessesExist) {

        unsigned short int index = 0; //start evaluation of processes at row 1
        while (processes[index].pid){
            struct Process *ptr = &processes[index];
            if (!ptr->complete){        //check if the process is live
                activeProcessesExist = 1;
                if (ptr->arrivalTime == globalTimeTicker){
                    queue[queuePos] = ptr;  //add to queue if just arrived
                    queuePos++;
                }
            }
            index++;
        }

        //process the queue
        //
        if (!queue[activeProcess]->exeStartTime)  //if this process just began to execute
            queue[activeProcess]->exeStartTime = globalTimeTicker;  //record the start
        queue[activeProcess]->totExeTime ++;        //increment the time it has run ///////
        if ((queue[activeProcess]->remExeTime --) == 0){  //decreast time remaining
            queue[activeProcess]->complete = 1;
            activeProcess++;
            if (!queue[activeProcess]){
                activeProcessesExist = 0;
            }
        }
        
        if (activeProcessesExist == 0){
            printf("exit\n");
            return 0;
        } else {
            printf("%ld=ticks %d=active ", globalTimeTicker, activeProcessesExist);
            printf("%d=rem %d=activeProcess  %d=index\n", queue[activeProcess]->remExeTime, activeProcess, index);
            globalTimeTicker ++;
        }
        
    }
    
    return 0;                           //return successfully
}
