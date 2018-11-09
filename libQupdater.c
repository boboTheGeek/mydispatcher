/*    
CSC521 Operating system
Project:      2 mydispatcher
Programmer:   Rob Miles
Professor:    Dr. Lee
File Created: Oct 15, 2018
File Updated: Nov 6, 2018
*/
#include "mydispatcher.h"

void updateQ(){
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
}
