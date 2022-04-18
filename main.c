#pragma region includes

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
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
    if (list)
    {
    }
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
            printf("Operation %d -> %d seconds \n", i, min[i]);
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
            printf("Operation %d -> %d seconds \n", i, max[i]);
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
            printf("Operation %d -> %.2f seconds \n", i, average);
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
int menu();

int main()
{
    // printf("hello");
    menu();
}
#pragma region Menu

int menu()
{

    Operation *list = NULL;
    Production *list2 = NULL;

    list = loadData(list);
    bool off = false;
    do
    {
        int option = -1;

        system("cls");

        printf("========= MENU =========\n");
        printf("Please, choose a function.\n");
        printf("=========================\n");
        printf("\n");
        printf("1. Insert Operation.\n");
        printf("2. Change Operation.\n");
        printf("3. Minimum time to complete a job - List respective operations\n");
        printf("4. Maximum time to complete a job - List respective operations\n");
        printf("5. Average time to complete an operation - Listing every possibility.\n");
        printf("6. Exit\n\n");
        printf("Option: ");
        scanf("%d", &option);
        if (option > 0 || option < 7)
        {
            switch (option)
            {
            case 1:

                system("cls");

                int opID;
                int mID;
                int time;

                printf("Operation ID: ");
                scanf("%d", &opID);

                printf("\nMachine ID: ");
                scanf("%d", &mID);
                printf("\nTime: ");
                scanf("%d", &time);
                list = head_insert(list, opID);
                list = insertion(list, opID, mID, time);

                showList(list);
                saveData(list);

                printf("Operation Inserted.\n\n");

                system("pause");

                // menu()

                break;

            case 2:

                system("cls");

                int option;
                int operationFlag = 0;
                int machineFlag = 0;

                printf("Here is the current data: \n\n");

                showList(list);

                printf("\n Operation ID: ");
                scanf("%d", &opID);

                printf("\n Machine ID: ");
                scanf("%d", &mID);

                printf("\n Time: ");
                scanf("%d", &time);

                changeOperation(list, opID, mID, time);

                system("cls");
                showList(list);
                printf("Operation Changed.\n\n");

                system("pause");
                saveData(list);

                // menu();

                break;

            case 3:

                system("cls");

                printf("Here is the minimum time to complete a job with the respective operations:\n\n");

                minimumTime(list);

                printf("\n\n");
                system("pause");
                // menu();

                break;

            case 4:

                system("cls");

                printf("Here is the maximum time to complete a job with the respective operations:\n\n");

                maximumTime(list);

                printf("\n\n");
                system("pause");
                // menu();

                break;

            case 5:

                system("cls");
                printf("Here is the average time to complete an operation, with every possibility listed: \n\n");

                avg(list);

                printf("\n\n");
                system("pause");
                // menu();

                break;

            case 6:

                printf("Thank you for using my program!\n\n");
                system("pause");
                exit(0);

                break;
            }
        }
    } while (off == false);

    return 0;
}

#pragma endregion
