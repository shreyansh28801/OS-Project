#include <stdio.h>
#include <stdlib.h>

enum BinarySemaphore {one ,zero};

enum BinarySemaphore s1=one;


void Manager(enum BinarySemaphore s)
{
    if (s1 == one)
    {        /* code */
        s1 = zero;
        printf("\n Your Request ahs been granted .Now upadte the page . \n");
    }
    else
    {
        printf("\n Sorry sir  , your request can't be granted because some employee are raeding the shared page. Plz wait or if in next iteration you again request then definetly you get chance to upadte the page. \n");
    }
}

void employee( enum BinarySemaphore s)
{
    if (s1 == one)
    {
        /* code */
        s1 = zero;
        printf("\n Your Request ahs been granted .Now you can read the page . \n");
    }
    else
    {
        printf("\n Sorry , your request can't be granted because amnager is updating sonthing in webPage. Plz wait or if in next iteration you again request then definetly you get chance to upadte the page \n");
    }
}

int main()
{
    printf("\n Enter 1 for manager to upadate the Page . \n");
    printf("\n Enter 2 for employee to read the Page . \n");
    printf("\n Enter 3 if you do not want to continue / wanna come out of loop . \n");
    int testInteger;
    int prev=-1;
    while (1)
    {
        printf("Enter an integer: ");
        scanf("%d", &testInteger);
        printf("\n");
        if (testInteger==3)
        {
            break;
        }
        if (prev==testInteger)
        {
            s1=one;
        }
        
        
        switch (testInteger)
        {
        case 1:
            Manager(s1);
            break;
        case 2:
            employee(s1);
            break;
        }
        prev=testInteger;
    }

    printf("\n for enjoying my software solution to manager employee problem \n");

    return 0;
}