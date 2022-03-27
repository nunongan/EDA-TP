#pragma region includes

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

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
    struct _operation *next, *prev;
    struct _production *first, *last;

} Operation;

#pragma endregion

#pragma region headInsert

Operation *head_insert(Operation *list, int operationID)
{
    Operation *new = (Operation *)malloc(sizeof(Operation));

    new->operationID = operationID;
    new->first = new->last = NULL;
    new->next = list;

    return new;
}

#pragma endregion

#pragma region tailInsert

Production *tail_insert(Production *list, int machineID, int time)
{

    Production *new = (Production *)malloc(sizeof(Production));

    new->machineID = machineID;
    new->time = time;
    new->next = NULL;
    new->prev = list;
    if (new->prev)
    {
        new->prev->next = new;
    }

    return new;
}

#pragma endregion

#pragma region insertion
Operation *insertion(Operation *list, int operationID, int machineID, int time)
{

    Operation *point = list;

    while (point)
    {

        if (point->operationID == operationID)
        {
            break;
        }

        point = point->next;
    }

    if (!point->last)
    {
        point->first = point->last = tail_insert(point->last, machineID, time);
    }
    else
    {
        point->last = tail_insert(point->last, machineID, time);
    }
    return list;
}

#pragma endregion

#pragma region fileManipulation

void saveData(Operation *list)
{

    FILE *file;

    file = fopen("./data/productionsWrite.txt", "w+");

    for (; list; list = list->next)
    {

        Production *point = list->first;

        for (; point;)
        {

            fprintf(file, "%d,%d,%d\n", list->operationID, point->machineID, point->time);
            point = point->next;
        }
    }

    fclose(file);
}

Operation *loadData(Operation *list)
{
    FILE *file;

    file = fopen("./data/productions.txt", "r");

    while (!feof(file))
    {

        char line[1000];
        int operationID, machineID, time;
        fgets(line, 1000, file);
        sscanf(line, "%d,%d,%d", &operationID, &machineID, &time);
        list = head_insert(list, operationID);
        list = insertion(list, operationID, machineID, time);
    }

    return list;

    fclose(file);
}

#pragma endregion

#pragma region Functions

Operation *changeOperation(Operation *list, int operationID, int machineID, int time)
{
    for (; list; list = list->next)
    {
        if (list->operationID == operationID)
        {
            Production *point = list->first;

            for (; point;)
            {
                if (point->machineID == machineID)
                {

                    point->time = time;
                }
                point = point->next;
            }
        }
    }
    return list;
}

Operation *minimumTime(Operation *list)
{
    int min[50];
    for (int i = 0; i < 50; i++)
    {

        min[i] = 9999;
    }
    for (; list; list = list->next)
    {
        Production *point = list->first;
        for (; point;)
        {
            if (min[list->operationID] > point->time)
            {

                min[list->operationID] = point->time;
            }

            point = point->next;
        }
    }
    for (int i = 0; i < 50; i++)
    {
        if (min[i] != 9999)
        {
            printf("%d -> %d \n", i, min[i]);
        }
    }
    return list;
}

Operation *maximumTime(Operation *list)
{
    int max[50];
    for (int i = 0; i < 50; i++)
    {

        max[i] = 0;
    }
    for (; list; list = list->next)
    {
        Production *point = list->first;
        for (; point;)
        {
            if (max[list->operationID] < point->time)
            {

                max[list->operationID] = point->time;
            }

            point = point->next;
        }
    }
    for (int i = 0; i < 50; i++)
    {
        if (max[i] != 0)
        {
            printf("%d -> %d \n", i, max[i]);
        }
    }
    return list;
}

Operation *avg(Operation *list)
{
    int sum[50], counter[50];

    for (int i = 0; i < 50; i++)
    {
        counter[i] = 0;
        sum[i] = 0;
    }

    for (; list; list = list->next)
    {
        Production *point = list->first;
        for (; point;)
        {

            sum[list->operationID] += point->time;
            counter[list->operationID]++;

            point = point->next;
        }
    }
    for (int i = 0; i < 50; i++)
    {
        if (counter[i] != 0)
        {
            float average = sum[i] / (float)counter[i];
            printf("%d -> %.2f \n", i, average);
        }
    }
    return list;
}

void showList(Operation *list)
{

    for (; list; list = list->next)
    {

        Production *point = list->first;

        for (; point;)
        {

            printf("%d | %d | %d\n", list->operationID, point->machineID, point->time);
            point = point->next;
        }
    }
}


#pragma endregion

int main()
{

    Operation *test = NULL;

    test = loadData(test);
    avg(test);
    showList(test);

    return 0;
}