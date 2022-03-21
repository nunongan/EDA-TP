#pragma region includes

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#pragma endregion

#pragma region structs

typedef struct _production
{
    int machineID;
    int time;
    struct _production *next, *prev;

} Production;

typedef struct _operation
{

    int operationID;
    struct _operation *next;
    struct _production *first, *last;

} Operation;

#pragma endregion

Operation *head_insert(Operation *list, int operationID)
{
    Operation *new = (Operation *)malloc(sizeof(Operation));

    new->operationID = operationID;
    new->first = new->last = NULL;
    new->next = list;

    return new;
}

Production *tail_insert(Production *list, int machineID, int time)
{

    Production *cell = (Production *)malloc(sizeof(Production));

    cell->machineID = machineID;
    cell->time = time;
    cell->next = NULL;
    cell->prev = list;
    if (cell->prev)
    {
        cell->prev->next = cell;
    }

    return cell;
}

Operation *insertion(Operation *list, int operationID, int machineID, int time)
{

    Operation *aux = list;

    while (aux)
    {

        if (aux->operationID == operationID)
        {
            break;
        }

        aux = aux->next;
    }

    // if(!aux) return list;

    if (!aux->last) // nobody in the waiting line
    {
        aux->first = aux->last = tail_insert(aux->last, machineID, time);
    }
    else
    {
        aux->last = tail_insert(aux->last, machineID, time);
    }
    return list;
}

void saveData(Operation *list)
{

    FILE *file;

    file = fopen("./data/productions_tmp.txt", "w+");

    for (; list; list = list->next)
    {

        Production *ptr = list->first;

        for (; ptr;)
        {

            fprintf(file, "%d,%d,%d\n", list->operationID, ptr->machineID, ptr->time);
            ptr = ptr->next;
        }
    }

    fclose(file);
}

Operation *readData(Operation *list)
{
    FILE *file;

    file = fopen("./data/productions.txt", "r");

    while (!feof(file))
    {

        char line[1000];
        int operationID, machineID, time;
        fgets(line, 1000, file);
        printf("%s",line);
        sscanf(line, "%d,%d,%d", &operationID, &machineID, &time);
        list = head_insert(list, operationID);
        list = insertion(list, operationID, machineID, time);
    }

    return list;

    fclose(file);
}

int main()
{

    Operation *test = NULL;

    test = readData(test);
    saveData(test);
    return 0;
}