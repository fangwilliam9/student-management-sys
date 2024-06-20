#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // malloc 
#include <string.h> // strcmp

struct DataType
{
    char name[20];
    int salary;
    int idnum;
    char depart[20];
};
typedef struct DataType DataType;

struct node
{
    DataType data;
    struct node *next;
};
typedef struct node     Node;
typedef struct node*    LinkList;


/*###################################### LinkList operations ###################################*/
// 1. To create a list with head node
Node *createListWithHead()
{
    LinkList head = (Node *)malloc(sizeof(Node));
    // No need to initiate the data field of the head node
    head->next = NULL; // Initiating the pointer next
    return head;
}

// 2. To create a new node, a node with given data field preped for inserting
Node *createnode(DataType data){
    Node *newnode = (Node *)malloc(sizeof(Node)); // If (memory allocation failed), malloc will return NULL
    if( newnode == NULL ){printf("Allocation failed");} // To check if the allocation failed or not

    newnode->data = data; // copy the data field
    newnode->next = NULL; // Eliminate any possible (dirty data)

    return newnode;
}

// 3.Head insertion method 
void insertByHead(LinkList head, DataType data){
    Node *newnode = createnode(data); // to create a new node
    (newnode->next) = (head->next); // make (newnode's next) points to (the first eleNode)
    head->next  =  newnode; // make (headnode's next) points to (the new node)
}

// Traverse the linked list from first node, removing the first node found that matches the given sth
void deleteANodeByname(LinkList head, char *name)
{
        // two adjacent pointers
        Node *pre = head;
        Node *curr = head->next;

        // strcmp(), if same strings, return 0(false)
        // conditional expressions: 0 is false, nonezero is true
        // To locate the required node
        while (curr != NULL && strcmp(curr->data.name, name)) // Exit after done traversing, exit when found a required node
        {
            pre = pre->next;
            curr = curr->next;
        }

        // Analyzing
        // two scenarios for loop exit:  curr==NULL , curr->data == posData;
        if (curr == NULL)
        {
            printf("This (name %s) no found, cannot delete!\n", name);
            return;
        }
        else // curr->data == posData;
        {
            (pre->next) = (curr->next); // use pre to jump the current node

            free(curr);

            curr = NULL;
        }
}
void deleteANodeBysalary(LinkList head, int salary)
{
        // two adjacent pointers
        Node *pre = head;
        Node *curr = head->next;

        // To locate the required node
        while (curr != NULL && curr->data.salary != salary)
        {
            pre = pre->next;
            curr = curr->next;
        }

        // Analyzing
        // two scenarios for loop exit:  curr==NULL , curr->data == posData;
        if (curr == NULL)
        {
            printf("This (salary: %d) no found, cannot delete!\n", salary);
            return;
        }
        else // curr->data == posData;
        {
            pre->next = curr->next;
            free(curr);
            curr = NULL;
        }
}
void deleteANodeByidnum(LinkList head, int idnum)
{
        // two adjacent pointers
        Node *pre = head;
        Node *curr = head->next;

        // To locate the required node
        while (curr != NULL && curr->data.idnum != idnum)
        {
            pre = pre->next;
            curr = curr->next;
        }

        // Analyzing
        // two scenarios for loop exit:  curr==NULL , curr->data == posData;
        if (curr == NULL)
        {
            printf("This (idnum: %d) no found, cannot delete!\n", idnum);
            return;
        }
        else // curr->data == posData;
        {
            pre->next = curr->next;
            free(curr);
            curr = NULL;
        }
}


// if found then return the node matches the given sth, else return NULL
Node *searchByname(LinkList head, char *name)
{
    Node *p = head->next; // Starting directly from the first element node can save the overhead of one comparison

    while (p != NULL && strcmp(p->data.name, name))
    {
        p = p->next;
    }

    return p;
}
Node *searchBysalary(LinkList head, int salary)
{
    Node *p = head->next; // Starting directly from the first element node can save the overhead of one comparison

    while (p != NULL && p->data.salary != salary)
    {
        p = p->next;
    }

    return p;
}
Node *searchByidnum(LinkList head, int idnum)
{
    Node *p = head->next; // Starting directly from the first element node can save the overhead of one comparison

    while (p != NULL && p->data.idnum != idnum)
    {
        p = p->next;
    }

    return p;
}

// Print everyone
void printList(LinkList head)
{
    Node *p = head->next; // since there's head node, printing starts from the next node of the head

    printf("name\t\tsalary\t\tidnum\t\tOrigin\n");

    while (p != NULL)
    {
        // printf("%d\t", p->data);
        printf("%s\t\t%d\t\t%d\t\t%s\n", p->data.name, p->data.salary, p->data.idnum, p->data.depart);

        p = p->next;
    }

    printf("\n"); 
}



// delete all nodes who share the same x
void deleteByname(LinkList head, char *name)
{
    while (searchByname(head, name) != NULL)
    {
        deleteANodeByname(head, name); // Traverse the linked list, remove the first node found that matches the given name
    }
}
void deleteBysalary(LinkList head, int salary)
{
    while (searchBysalary(head, salary) != NULL)
    {
        deleteANodeBysalary(head, salary);// Traverse the linked list, remove the first node found that matches the given salary
    }
}
void deleteByidnum(LinkList head, int idnum)
{
    while (searchBysalary(head, idnum) != NULL)
    {
        deleteANodeBysalary(head, idnum);// Traverse the linked list, remove the first node found that matches the given idnum
    }
}


/*###################################### LinkList operations ###################################*/


/*-------------------------Special requirements require special code------------------*/
void deleteAllElemNodes(LinkList *head){
    if(  (*head)->next == NULL  ){ 
        printf("\tNo elemNode at all\n");
        return; 
    }
    Node *temp;
    Node *curr = (*head)->next; // Start from the first elemNode

    while (curr != NULL)
    {
        temp = curr;        // Temporarily keep current node, in order to free it
        curr = curr->next;  // Move to the next node
        free(temp);         // Free current node
    }

    (*head)->next = NULL; // no more elemNodes
    printf("\tSuccessfully deleted all nodes\n");
}

// Print who share the same name
void printListSamename(LinkList head, char *name)
{
    Node *p = head->next; // since there's head node, printing starts from the next node of the head

    printf("name\tsalary\tidnum\tOrigin\n");

    while (p != NULL)
    {
        // printf("%d\t", p->data);
        if (strcmp(p->data.name, name) == 0)  // if two strings are the same, return 0
            printf("%s\t%d\t%d\t%s\n", p->data.name, p->data.salary, p->data.idnum, p->data.depart);

        p = p->next;
    }

    printf("\n"); 
}

/*-------------------------Special requirements require special code------------------*/


/*############################# File manipulation ###############################*/
// read
void readInfoFromFile(LinkList head, const char *filename)
{
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        fp = fopen(filename, "w+");
    }

    DataType info;
    while ( fscanf(fp, "%s\t%d\t%d\t%s\n", info.name, &info.salary, &info.idnum, info.depart) != EOF )
    {
        insertByHead(head, info);
    }

    fclose(fp);
}
// write
void saveInfoToFile(LinkList head, const char *filename)
{
    FILE *fp = fopen(filename, "w"); // open file using "w"-mode, will clear all file contents
    // if (fp == NULL){
    //     printf("Error opening file for writing.\n");
    //     return;
    // }    

    Node *p = head->next;  // p points2 first ElemNode
    if( p == NULL ){ // There's no more elemNode, clear all file contents, even if previously there were content in the file
        return;
    }
    else // there are ElemNode
    { 
        while (p != NULL)
        {
            fprintf(fp, "%s\t%d\t%d\t%s\n", p->data.name, p->data.salary, p->data.idnum, p->data.depart);
            p = p->next;
        }
        printf("Successfully deleted all nodes with info(ElemNodes)\n");
    }

    fclose(fp);
}
/*############################# File manipulation ###############################*/


// to simply show the menu
void printMenu(){
    printf("***************** Employee Mansalaryment System *******************\n");
    printf("\t0. Exit!\n");
    printf("\t1. Register!\n");
    printf("\t2. Browse all!\n");
    printf("\t3. Search by idnum !\n");
    printf("\t4. Delete by idnum !\n");
    printf("\t5. Modify by idnum !\n");
    printf("\t6. Delete all with the same name\n");
    printf("\t7. Delete all\n");
    printf("******************************************************************\n");
}


// To get user's input
void keyDown(LinkList L)
{
    DataType data;
    Node *result = NULL;
    int choice = 2;
    int valid_input = 0; // A variable used to record whether the input was successful
    // This do-while is used to check input's validation
    do {
        printf("Please enter: ");
        valid_input = scanf("%d", &choice); // if scanf got an int input, it'll return 1; If it's none-integer, it'll return 0

        // If the input fails (that is, it is not an integer), get the input-buffer cleared and get the user to re-enter
        if (!valid_input) {
            printf("Invalid input!!\n");
            fflush(stdin); // clear the input-buffer
        }
    } while (!valid_input); // If valid_input != 1(or valid_input == 0),  the loop continues until the user enters an integer


    switch (choice)
    {
        case 0:
            // printf("0. Exit!\n");
            printf("Successfully exited!\n");

            exit(0);

            break;
        case 1:
            // printf("1. Register employee information!\n");
            printf("Enter (name, salary, idnum, depart):");
            scanf("%s %d %d %s", data.name, &data.salary, &data.idnum, data.depart);

            insertByHead(L, data);

            saveInfoToFile(L, "1.txt");

            break;
        case 2:
            // printf("2. Browse employee information!\n");
            printList(L);

            break;
        case 3:
            // printf("3. Search employee information!\n");
            printf("Enter the employee's idnum you wanna search, idnum: ");
            scanf("%d", &data.idnum);
            result = searchByidnum(L, data.idnum);

            if (result == NULL){
                printf("None Found!\n");
            }
            else{
                printf("name\t\tsalary\t\tidnum\t\tOrigin\n");
                printf("%s\t\t%d\t\t%d\t\t%s\n", result->data.name, result->data.salary, result->data.idnum, result->data.depart);
            }

            break;
        case 4:
            // printf("4. Delete employee information!\n");
            printf("Enter the employee's idnum you wanna delete: ");
            scanf("%d", &data.idnum);
            result = searchByidnum(L, data.idnum);

            if( !result ){
                printf("None found\n");
            }else{
                deleteANodeByidnum(L, data.idnum);
                saveInfoToFile(L, "1.txt");
            }

            break;
        case 5:
            // printf("5. Modify employee information\n");
            printf("Enter the employee's name you wanna modify, idnum: ");
            scanf("%d", &data.idnum);
            result = searchByidnum(L, data.idnum);

            if (result == NULL){
                printf("None found, cannot modify\n");
            }
            else{
                printf("Enter new info (name, salary, idnum, depart): ");
                scanf("%s%d%d%s", result->data.name, &result->data.salary, &result->data.idnum, result->data.depart);

                saveInfoToFile(L, "1.txt");

                printf("Modefied!\n");
            }

            break;
        case 6:
            // printf("6. Delete all employees' information with the same name\n");
            printf("Enter employees' name you wanna delete, name:");
            scanf("%s", data.name);

            deleteByname(L, data.name);

            saveInfoToFile(L, "1.txt");

            break;        
        case 7:
            // printf("7. Delete all ElemNode\n");
            deleteAllElemNodes(&L);
            
            saveInfoToFile(L, "1.txt");

            break;


        default:
            printf("Input error!\n");

            break;
    }
}


int main()
{
    LinkList list = NULL;
    list = createListWithHead();

    readInfoFromFile(list, "1.txt");

    while (1)
    {
        printMenu(); // to simply print the menu in every loop

        keyDown(list); // To get user's input

        system("pause");
        system("cls"); // cls and this loop all over again
    }


    return 0;
}
