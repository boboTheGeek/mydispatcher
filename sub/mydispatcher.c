#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Process{
	unsigned short pid;
	unsigned short arrivalTime;
	unsigned short exeTime;
	unsigned short remExeTime;
	unsigned short exeStartTime;
	unsigned short exeDoneTime;
	char complete;
	unsigned short turnaroundTime;
	unsigned short waitTime;
	struct Process *next;
};

/* Given a reference (pointer to pointer) to the head
of a list and an int, appends a new node at the end  */
void append(struct Process** head_ref, int arrivalTime_in, int exeTime_in, int pid_in)
{
	/* 1. allocate node */
	struct Process* new_node = (struct Process*) malloc(sizeof(struct Process));

	struct Process *last = *head_ref;  /* used in step 5*/

	/* 2. put in the data  */
	new_node->pid = pid_in;
	new_node->arrivalTime = arrivalTime_in;
	new_node->exeTime = exeTime_in;
	new_node->remExeTime = exeTime_in;      //set the remaining time counter to service time as well
	new_node->complete = 0;                 //initialize to incomplete
	new_node->exeDoneTime = 0;

	/* 3. This new node is going to be the last node, so make next
	of it as NULL*/
	new_node->next = NULL;

	/* 4. If the Linked List is empty, then make the new node as head */
	if (*head_ref == NULL)
	{
		*head_ref = new_node;
		return;
	}

	/* 5. Else traverse till the last node */
	while (last->next != NULL)
		last = last->next;

	/* 6. Change the next of last node */
	last->next = new_node;
	return;
}

void printList(struct Process *node)
{
	while (node != NULL)
	{
		printf("P %d   ", node->pid);
		printf("A %d   ", node->arrivalTime);
		printf("S %d   ", node->exeTime);
		printf("R %d   ", node->remExeTime);
		printf("C %d   ", node->complete);
		printf("D %d\n ", node->exeDoneTime);
		node = node->next;
	}
}

int main(int argc, char *argv[]){

	struct Process *currentProcess;
	currentProcess = NULL;

	FILE *fp;                                          //pointer for a file
	int arrivalTime_in, exeTime_in, pid = 1;           //

	if (!(fp = fopen("test.dat", "rb"))){
		perror("sorry, .dat file import problem\n");
		printf("provide the .dat file as first argument, should be in the same folder as executible\n");
	}
	
	while (fscanf(fp, "%d %d", &arrivalTime_in, &exeTime_in) != EOF) { //grab col 1 and 2 from file if it's not the end
		append(&currentProcess, arrivalTime_in, exeTime_in, pid);
		pid++;
	}

	printList(currentProcess);

return 0;                                          //finish successfully
}




