//==================================================== INCLUDES ===============================================================

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

// ============================================================================================================================

typedef struct operation{

    int machineID;
    int operationID;
    int time;

    struct operation *next, *prev;
    struct job *first, *last;

} Operation;

typedef struct job{

    int jobID;
    int operationID;

    struct job *next, *prev;
    struct operation *first, *last;

} Job;


Operation * createOpList(int machineID, int operationID, int time){

    Operation * list = (Operation *)malloc(sizeof(Operation));
    list->machineID = machineID;
    list->operationID = operationID;
    list->time = time;
    list->next = NULL;
    list->prev = NULL;
    list->first = list;
    list->last = list;

    return list;
}