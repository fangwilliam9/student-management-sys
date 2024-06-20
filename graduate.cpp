/*   "_2" means graduate    */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // malloc 
#include <string.h> // strcmp
#define MAX_CLASSES 10


typedef struct {
    int studNum;
    char name[20];
    char gender[10]; 
    char major[50];
    char classname[20];
    char research_direction[50];
    char tutor[20];
}Data_BasicInfo_2;

typedef struct {
    int course_corprehensive_score; // ccs
    int thesis_grade; // tg

    int total;
    int class_ranking;
    int school_ranking;
}Data_Scores_2;

typedef struct {
    Data_BasicInfo_2 info;
    Data_Scores_2 scores; 
}DataType_2;

typedef struct Node_2{
    DataType_2 data;
    struct Node_2 *next;
}Node_2, * LinkList_2;

/*###################################### LinkList_2 Operation Basic info ###################################*/

void singlyGetbasicinfo_2(DataType_2 *data, int studNum){
    // single get-input for basic info
    data->info.studNum = studNum; 
    printf("-----name, gender, major, classname, direction, tutor -----\n");
    scanf("%s %s %s %s %s %s", 
        (data->info.name), 
        (data->info.gender), 
        (data->info.major), 
        (data->info.classname),
        (data->info.research_direction),
        (data->info.tutor)
    );

}
void singlyGetscores_2(Node_2 *p)
{
    printf("\nccs, tg\n");
    scanf("%d %d", 
        &(p->data.scores.course_corprehensive_score), 
        &(p->data.scores.thesis_grade)
    );
}

void printANode_2(Node_2 *p)
{
    // printf("num\tname\tsex\tmajor\tclass\tdirect\ttutor\tccscore\tthesis\ttotal\tclassR\tschoolR\n");
    printf( "%d\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\n", 
        (p->data.info.studNum), 
        (p->data.info.name), 
        (p->data.info.gender), 
        (p->data.info.major), 
        (p->data.info.classname), 
        (p->data.info.research_direction), 
        (p->data.info.tutor), 
        
        (p->data.scores.course_corprehensive_score), 
        (p->data.scores.thesis_grade), 
        (p->data.scores.total), 
        (p->data.scores.class_ranking), 
        (p->data.scores.school_ranking)
    ); 
}

// To create a list with head Node_2
void createListWithHead_2(Node_2* *head_ref)
{
    (*head_ref) = (Node_2 *)malloc(sizeof(Node_2));
    if ( (*head_ref) == NULL ) {
        printf("Memory allocation failed.\n");
        return;
    }
    (*head_ref)->next = NULL; // Initiating the pointer next
}

// readDataFromFile_2 use this tailInsert_2()
void tailInsert_2(LinkList_2 L, DataType_2 *data)
{
    Node_2 *s = (Node_2 *)malloc(sizeof(Node_2));
    if( !s ) // To check if the allocation failed or not
    {
        printf("Allocation failed\n");
        return;
    }
    // (*data).info.studNum = generated_studNum;
    s->data = (*data);
    s->next = NULL;

    Node_2 *t = L;
    while( t->next != NULL )
    {
        t = t->next;
    }
    t->next = s;
}

// when creating new Node_2
void tailInsertInit_2(LinkList_2 head, DataType_2 data)
{
    Node_2 *s = (Node_2 *)malloc(sizeof(Node_2));
    if( s == NULL ) // To check if the allocation failed or not
    {
        printf("Allocation failed\n");
        return;
    }
    

    // (*data).info.studNum = generated_studNum;
    s->data = data;
    s->next = NULL;

    s->data.scores.course_corprehensive_score = -1;
    s->data.scores.thesis_grade = -1;

    s->data.scores.total = -3;
    s->data.scores.class_ranking = -3;
    s->data.scores.school_ranking = -3;

    Node_2 *t = head;
    while( t->next != NULL )
    {
        t = t->next;
    }
    t->next = s;
}

// 1_1.(2)
void updateANodeBystudNum_2(LinkList_2 head, int studNum)
{
    Node_2 *p = head->next; // Starting directly from the first element Node_2
    while( (p->next->data.info.studNum) != studNum )
    {
        p = p->next;
    }
    singlyGetbasicinfo_2(&(p->data), studNum); // to update basic info
}

// 1_1.(3)
void deleteANodeBystudNum_2(LinkList_2 head, int studNum)
{
        // two adjacent pointers
        Node_2 *pre = head;
        Node_2 *curr = head->next;

        // To locate the required Node_2
        while (curr && curr->data.info.studNum != studNum)
        {
            pre = pre->next;
            curr = curr->next;
        }

        // Analyzing
        // two scenarios for loop exit:  curr==NULL , curr->data == posData;
        if (curr == NULL)
        {
            printf("This (studNum: %d) no found, cannot delete!\n", studNum);
            return;
        }
        else // curr->data == posData;
        {
            pre->next = curr->next;
            free(curr);
            curr = NULL;
        }
}

// 1_1.(4)
Node_2 *searchBystudNum_2(LinkList_2 head, int studNum){
    Node_2 *p = head->next; 
    while (p && p->data.info.studNum != studNum)
    {
        p = p->next;
    }
    return p;
}
/*###################################### LinkList_2 Operation Basic info ###################################*/




/*###################################### Data_Scores_2 ###################################*/
// 1_2.(1) singly input
void inputScores_2(LinkList_2 head)
{
    Node_2 *p = head->next; // from first elemNode_2
    while(p)
    {
        printf("for student-%d\n", (p->data.info.studNum));
        singlyGetscores_2(p);
        p = p->next;
    }
}

// 1_2.(2)
void updateScores_2(LinkList_2 head, int studNum)
{
    Node_2 *p = searchBystudNum_2(head, studNum);
    if(p){
        singlyGetscores_2(p);
        printf("UPDATED!\n");
    }else{
        printf("No found\n");
    }
}

// 1_2.(3)
void deleteScores_2(LinkList_2 head, int studNum)
{
    Node_2 *p = searchBystudNum_2(head, studNum);
    if(p){
        p->data.scores.course_corprehensive_score = -1;
        p->data.scores.thesis_grade = -1;
    }else{
        printf("No found\n");
    }

}


// 1_2.(5) 
void calculateTotalForAll_2(LinkList_2 head)
{
    Node_2 *p = head->next;

/* If -1(scores were deleted), calculate its total as well, so total will be -3, meaning can't be ranked */
    while(p)
    {
        /*
        if( (p->data.scores.math != -1) && (p->data.scores.english != -1) && (p->data.scores.cpp != -1) ){
            p->data.scores.total  =  p->data.scores.math + p->data.scores.english + p->data.scores.cpp;
        }
        */
        p->data.scores.total  =  p->data.scores.course_corprehensive_score + p->data.scores.thesis_grade ;
        p = p->next;
    }
}

// 2.1 calculateClassRanking
void calculaClassRanking_2(LinkList_2 descend_sorted)
{
    Node_2 *p = descend_sorted->next;
    while(p)
    {
        if( p->data.scores.total == -3 )
        {
            p->data.scores.class_ranking = p->data.scores.total; // set ranking same as total(-3), ranking is minus means can't be ranked
        }else{
            // init (students with scores)'s class_rank as 0, meaning to be calculated
            p->data.scores.class_ranking = 0; 
        }

        p = p->next;
    }


    printf("\tname(class)------class_ranking(total)\n"); // display at terminal
    p  =  descend_sorted->next;
    while(p)
    {
            // Check whether the class_ranking of current Node_2 has been calculated, if calculated, skip it; if not, ex this
            if( p->data.scores.class_ranking == 0 )
            {
                int rank = 1;
                p->data.scores.class_ranking = rank;
                rank++;
                printf("\t%s(%s)------%d(%d)\n", (p->data.info.name), (p->data.info.classname), (p->data.scores.class_ranking), (p->data.scores.total));

                // Iterate from the next Node_2 of the current Node_2, comparing classes and grades
                Node_2* q = p->next;
                while (q)
                {
                    // to find all the students with scores in the list who're in the same class as current Node_2
                    if( strcmp(q->data.info.classname, p->data.info.classname) == 0 && q->data.scores.class_ranking == 0  )
                    {
                        q->data.scores.class_ranking = rank;
                        rank++;
                        printf("\t%s(%s)------%d(%d)\n", (q->data.info.name), (q->data.info.classname), (q->data.scores.class_ranking), (q->data.scores.total));
                    }
                    q = q->next;
                }
            }else{
                // class_ranking == -1(<0), just jump over, do nothing(no need printf) 
            }
            
            p = p->next;
    }
}

// 2.2 
void calculateShcoolRanking_2(LinkList_2 descend_sorted)
// calcula & display at terminal & save to list(file)
{
    Node_2* p = descend_sorted->next;
    while(p)
    {
        if( p->data.scores.total == -3 )
        {
            p->data.scores.school_ranking = p->data.scores.total; // set ranking as -3(same as total), minus means can't be ranked
        }else{
            // init (students with scores) school_ranking as 0, meaning to be calculated
            p->data.scores.school_ranking = 0; 
        }

        p = p->next;
    }
    
    int rank = 1;
    printf("\tname(num)------school_ranking(total)\n"); // display at terminal
    p  =  descend_sorted->next;
    while(p)
    {
        if( p->data.scores.school_ranking == 0 )
        {
            p->data.scores.school_ranking = rank;
            rank++;
            // print main info at the terminal
            printf("\t%s(%d)------%d(%d)\n", (p->data.info.name), (p->data.info.studNum), (p->data.scores.school_ranking), (p->data.scores.total));
        }else{
            // school_ranking == -3 (<0), just jump over, do nothing(no need printf) 
        }

        p = p->next;
    }
}

/*-------------------------------- 3. ------------------------------ */
void sortDescending_2(Node_2* head)
{
    if (head == NULL || head->next == NULL || head->next->next == NULL) {
        // If the list is empty or has only one or two Node_2s, it's already sorted
        return;
    }

    Node_2* curr = head->next;
    while (curr != NULL) 
    {
        Node_2* minNode_2 = curr; // Assume curr Node_2 has minimum salary
        Node_2* temp = curr->next;
        while (temp != NULL) 
        {
            if (temp->data.scores.total > minNode_2->data.scores.total) 
            {
                minNode_2 = temp; // Update minNode_2 if smaller salary found
            }
            temp = temp->next;
        }

        // Swap data between curr Node_2 and minNode_2 if they are different
        if (curr != minNode_2) 
        {
            DataType_2 tempData = curr->data;
            curr->data = minNode_2->data;
            minNode_2->data = tempData;
        }

        // Move to the next Node_2 in the list
        curr = curr->next;
    }
}
// 3.(2) 
void printByClass_2(LinkList_2 sorted, const char *classname)
{
    Node_2 *p = sorted->next;

    while(p)
    {
        if( strcmp(p->data.info.classname, classname) == 0 )
        {
            printANode_2(p);
            // printf("%d\t%s\t%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n", (p->data.info.studNum), (p->data.info.name), (p->data.info.gender), (p->data.info.major), (p->data.info.classname), (p->data.scores.math), (p->data.scores.english), (p->data.scores.cpp), (p->data.scores.total), (p->data.scores.class_ranking), (p->data.scores.school_ranking)); 
        }
        
        p = p->next;
    }
}
/*-------------------------------- 3. ------------------------------ */


/*-------------------------------- 4. Query------------------------------ */
// 4.1
void displayAllStudentsPerPage_2(LinkList_2 L, int currentPage, int pageSize) {
    int totalStudents = 0;
    Node_2 *p = L->next;

    // total number of students of the list
    while (p) {
        totalStudents++;
        p = p->next;
    }

    int totalPages = (totalStudents + pageSize - 1) / pageSize;

    int start = (currentPage - 1) * pageSize + 1;
    int end = start + pageSize - 1;
    if (end > totalStudents) {
        end = totalStudents;
    }

    int count = 0;
    p = L->next;
    while (p && count < end) {
        if (count >= start - 1) 
        {
            printf("%d\t%s\t%s\t%s\t%s\n", 
                p->data.info.studNum, 
                p->data.info.name, 
                p->data.info.gender, 
                p->data.info.major, 
                p->data.info.classname);
        }
        p = p->next;
        count++;
    }
}

// 4.2
void displayStudentsByClass_2(LinkList_2 L, const char *classname) {
    Node_2 *p = L->next;
    while (p) {
        if (strcmp(p->data.info.classname, classname) == 0) 
        {
            printANode_2(p);
        }
        p = p->next;
    }
}

// 4.3
Node_2* searchByname_2(LinkList_2 L, const char *name) 
{
    Node_2 *p = L->next;
    while (p) {
        if (strcmp(p->data.info.name, name) == 0) 
        {
            return p; // if matched, return the Node_2 that matches with given name
        }
        p = p->next;
    }

    return p; // traversed all, still no found, then return NULL
}

// 4.4
void displayFailedStudentsInOneClass_2(LinkList_2 head, const char *classname) {
    int threshold = 60;
    
    printf("num\tname\tsex\tmajor\tclass\tdirect\ttutor\tccscore\tthesis\ttotal\tclassR\tschoolR\n");
    Node_2 *p = head->next;
    while (p) 
    {
        if (strcmp(p->data.info.classname, classname) == 0) 
        {
            if (p->data.scores.course_corprehensive_score < threshold || p->data.scores.thesis_grade < threshold) 
            {
                printANode_2(p);
            }
        }
        p = p->next;
    }
}
/*-------------------------------- 4. Query------------------------------ */

/*-------------------------------- 5. Statistical function------------------------------ */
// 5.1 
void calculateAvgByClass_2(LinkList_2 L, const char* classname)
{
    double sum_ccs=0, sum_tg=0;
    int count=0;

    Node_2 *p = L->next;
    while(p)
    {
        // firstly, check class mathes or not
        if( strcmp(p->data.info.classname, classname) == 0 )
        {
            if( p->data.scores.course_corprehensive_score == -1 || p->data.scores.thesis_grade == -1 )
            {
                // if no scores, then do nothing, ignoring this student
            }else{
                sum_ccs += p->data.scores.course_corprehensive_score;
                sum_tg += p->data.scores.thesis_grade;
                count++;
            }
        }
        p = p->next;
    }

    printf("\tFor class: %s\n", classname);
    printf("\t\tavg_ccs= %.1lf\n", sum_ccs/count);
    printf("\t\tavg_tg= %.1lf\n", sum_tg/count);
}

// 5.2
void calculateLevelCount_2(LinkList_2 L, const char* classname)
{
    int count_ccs[6]  = {0,0,0,0,0,0};
    int count_tg[6] = {0,0,0,0,0,0};

    Node_2 *p = L->next;
    while(p)
    {
        // firstly, check class matches or not
        if( strcmp(p->data.info.classname, classname) == 0 )
        {
            if( p->data.scores.course_corprehensive_score != -1 && p->data.scores.thesis_grade != -1 )
            {
                if (p->data.scores.course_corprehensive_score >= 90) { count_ccs[1]++; }
                else if (p->data.scores.course_corprehensive_score >= 80) { count_ccs[2]++; }
                else if (p->data.scores.course_corprehensive_score >= 70) { count_ccs[3]++; }
                else if (p->data.scores.course_corprehensive_score >= 60) { count_ccs[4]++; }
                else { count_ccs[5]++; }

                if (p->data.scores.thesis_grade >= 90) { count_tg[1]++; }
                else if (p->data.scores.thesis_grade >= 80) { count_tg[2]++; }
                else if (p->data.scores.thesis_grade >= 70) { count_tg[3]++; }
                else if (p->data.scores.thesis_grade >= 60) { count_tg[4]++; }
                else { count_tg[5]++; }
            }
        }
        p = p->next;
    }

    printf("\t\t\tFor class: %s\n", classname);

    printf("\tMath: \n");
    printf("\t\tnum of A = %d\n", count_ccs[1]);
    printf("\t\tnum of B = %d\n", count_ccs[2]);
    printf("\t\tnum of C = %d\n", count_ccs[3]);
    printf("\t\tnum of D = %d\n", count_ccs[4]);
    printf("\t\tnum of F = %d\n", count_ccs[5]);

    printf("\tEnglish: \n");
    printf("\t\tnum of A = %d\n", count_tg[1]);
    printf("\t\tnum of B = %d\n", count_tg[2]);
    printf("\t\tnum of C = %d\n", count_tg[3]);
    printf("\t\tnum of D = %d\n", count_tg[4]);
    printf("\t\tnum of F = %d\n", count_tg[5]);
}
/*-------------------------------- 5. Statistical function------------------------------ */



/*-------------------------Special requirements require special code------------------*/
void printList_2(LinkList_2 L){
    Node_2 *p = L;
    printf("num\tname\tsex\tmajor\tclass\tdirect\ttutor\tccscore\tthesis\ttotal\tclassR\tschoolR\n");

    while(p->next){
        printANode_2(p->next);
        p = p->next;
    }
}
void deleteAll_2(Node_2* *head_ref){
    if(  (*head_ref)==NULL  || (*head_ref)->next == NULL  ){ 
        return; 
    }
    Node_2 *t;
    Node_2 *p = (*head_ref);
    while(p)
    {
        t = p;
        p = p->next;
        free(t);
    } 
    // init (*head_ref)
    (*head_ref) = NULL;
}
/*-------------------------Special requirements require special code------------------*/




/*################################################# File manipulation ###############################*/
// read
void readDataFromFile_2(LinkList_2 L, const char *data_file_2) {
    FILE *fp = fopen(data_file_2, "r");
    if (fp == NULL) {
        // File doesn't exist, create an empty file
        fp = fopen(data_file_2, "w");
        if (fp == NULL) {
            // If creation of the file fails, return
            return;
        }
        fclose(fp);
        // Reopen the file in read mode
        fp = fopen(data_file_2, "r");
        if (fp == NULL) {
            // If reopening the file fails, return
            return;
        }
    }

    DataType_2 data;

    while (fscanf(fp, "%d\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\n",
                  &(data.info.studNum), 
                  data.info.name, 
                  data.info.gender,
                  data.info.major, 
                  data.info.classname, 
                  data.info.research_direction,
                  data.info.tutor,
                  &(data.scores.course_corprehensive_score),
                  &(data.scores.thesis_grade), 
                  &(data.scores.total),
                  &(data.scores.class_ranking), 
                  &(data.scores.school_ranking)) != EOF) 
    {
        tailInsert_2(L, &data);
    }

    fclose(fp);
}


// write
void saveDataToFile_2(LinkList_2 L, const char *data_file_2)
{
    FILE *fp = fopen(data_file_2, "w"); // open file using "w"-mode, will clear all file contents  
    if (fp == NULL){
        printf("Error opening file\n");
        return;
    }

    // There's no elemNode_2, clear all file contents, even if previously there were content in the file
    if( L == NULL  || L->next == NULL){
        fclose(fp);
        return;
    } 
    // precondition: there are ElemNode_2(s)
    Node_2 *p = L->next;
    while (p != NULL)
    {
        fprintf(fp, "%d\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\n", 
            (p->data.info.studNum), 
            (p->data.info.name), 
            (p->data.info.gender), 
            (p->data.info.major), 
            (p->data.info.classname), 
            (p->data.info.research_direction), 
            (p->data.info.tutor), 
            (p->data.scores.course_corprehensive_score), 
            (p->data.scores.thesis_grade), 
            (p->data.scores.total), 
            (p->data.scores.class_ranking), 
            (p->data.scores.school_ranking)); 

        p = p->next;
    }
    
    fclose(fp);
}
void getnum_2(LinkList_2 L, int *studNum){
    // if there's no previous data in the file, then make studnum start from 1
    if(L==NULL || L->next == NULL){
        (*studNum) = 1;
        return;
    }

    Node_2 *tail = L;
    while(tail->next != NULL){
        tail = tail->next;
    }
    (*studNum) = tail->data.info.studNum + 1;
}
/*################################################# File manipulation ###############################*/

// to simply show the menu
void printMenu_2(){
    printf("***************** Student Management System *******************\n");
    printf("\t0. Exit!\n");
    printf("\t1. Data\n");
    printf("\t2. Ranking\n");
    printf("\t3. Sorting\n");
    printf("\t4. Searching\n");
    printf("\t5. Statistical\n");
    printf("\t6. printAll()\n");
    printf("\t7. Delete all\n");
    printf("******************************************************************\n");
}

// To get user's input
void keyDown_2(LinkList_2 L, int *studNum, const char* data_file_2)
{
    // check to see where studnum should start
    getnum_2(L, studNum); // also monitor if there're changes in keyDown_2() loop

    DataType_2 data; // info & scores
    Node_2 *result = NULL;
    int i=0, n=0, num=0;
    int ch1, ch2, ch3;

    scanf("%d", &ch1);
    switch (ch1)
    {
        case 0:
        // printf("0. Exit!\n");
            printf("Successfully exited!\n");
            exit(0);
            break;

        case 1:
        // printf("\t1. Data\n");
            printf("\t1(A)---Basic info\n");
            printf("\t2(B)---Scores\n");

            scanf("%d", &ch2);
            switch (ch2)
            {
                    case 1:
                    // printf("\t1(A)---Basic info\n");
                            printf("\t\t1x---BasicInfo\t2x---Scores\n\n");
                            printf("0---last step\n");
                            printf("1---register\n");
                            printf("2---update basic info\n");
                            printf("3---delete basic info\n");
                            printf("4---search basic info\n");

                            scanf("%d", &ch3);
                            switch (ch3)
                            {
                                case 1:
                                // register info
                                    printf("How many you wanna register this time: ");
                                    scanf("%d", &n);
                                    for(i=1; i<=n; i++)
                                    {
                                        singlyGetbasicinfo_2( &data, (*studNum) );
                                        tailInsertInit_2(L, data);
                                        (*studNum)++; // studNum is unique and auto generated
                                    }

                                    saveDataToFile_2(L, data_file_2);
                                    break;

                                case 2:
                                // update info
                                    int num; // studNum to be operated
                                    scanf("%d", &num);
                                    updateANodeBystudNum_2(L, num);
                                    printf("UPDATED!\n");
                                    break;

                                case 3:
                                // delete info
                                    printf("who u wanna delete: ");
                                    scanf("%d", &num);
                                    deleteANodeBystudNum_2(L, num);
                                    printf("DELETED!\n");
                                    break;

                                case 4:
                                // search info
                                    printf("who u wanna search: ");
                                    scanf("%d", &num);
                                    result = searchBystudNum_2(L, num);
                                    printANode_2(result);
                                    break;

                                default:
                                    printf("input error\n");
                                    break;
                            }
                        break;

                    case 2:
                    // printf("\t2(B)---Scores\n");
                            printf("\t1\tinput scores\n");
                            printf("\t2\tupdate scores\n");
                            printf("\t3\tdelete scores\n");
                            printf("\t4\tsearch scores\n");
                            printf("\t5\tcalculate total\n");
                            
                            scanf("%d", &ch3);
                            switch (ch3)
                            {
                                case 1:
                                // input scores
                                    inputScores_2(L);
                                    printf("Done!\n");
                                    saveDataToFile_2(L, data_file_2);

                                    break;

                                case 2:
                                // update scores
                                    printf("Enter studNum to update: ");
                                    scanf("%d", &num);
                                    updateScores_2(L, num);

                                    saveDataToFile_2(L, data_file_2);
                                    break;

                                case 3:
                                // delete scores(set -1)
                                    printf("Enter studNum to delete: ");
                                    scanf("%d", &num);
                                    deleteScores_2(L, num);

                                    // to auto update
                                    calculateTotalForAll_2(L);
                                    sortDescending_2(L);
                                    calculaClassRanking_2(L);
                                    calculateShcoolRanking_2(L);

                                    saveDataToFile_2(L, data_file_2);
                                    break;

                                case 4:
                                // search scores
                                    printf("Enter studNum to search: ");
                                    scanf("%d", &num);
                                    result = searchBystudNum_2(L, num);
                               
                                    if( result ){
                                        printANode_2(result);
                                    }else{
                                        printf("No found!\n");
                                    }

                                    break;

                                case 5:
                                // calculate total scores
                                    calculateTotalForAll_2(L);
                                    saveDataToFile_2(L, data_file_2);

                                    break;
                            
                                default:
                                    printf("ch3 input error\n");
                                    break;
                            }
                        break;

                    // default:
                    //     printf("ch2 input error\n");
                    //     break;
            }
            break;

        case 2:
        // printf("2. Ranking\n");
                printf("\t1\tcalculate class_ranking\n");
                printf("\t2\tcalculate school_ranking\n");
                scanf("%d", &ch2);
                
                switch (ch2)
                {
                    case 1:
                    // class ranking
                        sortDescending_2(L);
                        calculaClassRanking_2(L);
                        saveDataToFile_2(L, data_file_2);
                        printf("Saved!\n");
                        
                        break;

                    case 2:
                    // school_ranking
                        sortDescending_2(L);
                        calculateShcoolRanking_2(L);
                        saveDataToFile_2(L, data_file_2);
                        printf("Saved!\n");

                        break;

//                    default:
//                        printf("ch2 input error\n");
//                        break;
                }
            break;

        case 3:
        // printf("3. Sorting\n");
                printf("\t1\tDescending sort all and display \n");
                printf("\t2\tPrint a class descendingly\n");
                scanf("%d", &ch2);

                switch (ch2)
                {
                    case 1:
                    // Descending sort all and display sorted
                        sortDescending_2(L);
                        printList_2(L);
                        saveDataToFile_2(L, data_file_2);
                        break;
                    
                    case 2:
                    // Print a class descendingly
                        sortDescending_2(L);
                        saveDataToFile_2(L, data_file_2);
                        printf("Enter the class you wanna display: ");
                        scanf("%s", &data.info.classname);
                        printByClass_2(L, data.info.classname);
                        break;
                    
                    // default:
                    //     printf("ch2 input error\n");
                    //     break;
                }
            break;

        case 4:
        // printf("\t4. Searching\n");
                printf("\t1\tDisplay all in pages\n");
                printf("\t2\tDisplay by class\n");
                printf("\t3\tSearch by name/studNum\n");
                printf("\t4\tDisplay failed studnets in one class\n");
                scanf("%d", &ch2);

                switch (ch2)
                {
                    case 1:
                    // printf("\t1\tDisplay all in pages\n");
                        displayAllStudentsPerPage_2(L, 1, 10);
                        break;
                    
                    case 2:
                    // printf("\t2\tDisplay by class\n");
                        printf("enter classname u wanna display: ");
                        scanf("%s", data.info.classname);
                        displayStudentsByClass_2(L, data.info.classname);

                        break;

                    case 3:
                    // printf("\t3\tSearch by name/studNum\n");
                        printf("\t1\tsearchBystudNum_2\n");
                        printf("\t2\tsearchByname_2\n");

                        scanf("%d", &ch3);
                        switch (ch3)
                        {
                            case 1:
                                printf("studNum u wanna search: ");
                                scanf("%d", &data.info.studNum);
                                result = searchBystudNum_2(L, data.info.studNum);
                                if( result != NULL )
                                {
                                    printANode_2(result);
                                }else
                                {
                                    printf("No found!\n");
                                }    
                                
                                break;
                            
                            case 2:
                                printf("name u wanna search: ");
                                scanf("%s", &data.info.name);
                                result = searchByname_2(L, data.info.name);
                                if( result )
                                {
                                    printANode_2(result);
                                }else
                                {
                                    printf("No found!\n");
                                }

                                break;
                        } 

                    break;

                case 4:
                // printf("\t4\tdisplay failed studnets in one class\n");
                    printf("which class you wanna search: ");
                    scanf("%s", &data.info.classname);
                    displayFailedStudentsInOneClass_2(L, data.info.classname);

                    break;
                }

            break;
            
        case 5:
        // printf("\t5. Statistical\n");
                printf("\t1\tCal and display avg by class\n");
                printf("\t2\tCal and display level count by subject and by class\n");
                scanf("%d", &ch2);

                switch (ch2)
                {
                    case 1:
                    // printf("\t1\tCal and display avg by class\n");
                        printf("which class's avg you wanna cal and display: ");
                        scanf("%s", &data.info.classname);
                        calculateAvgByClass_2(L, data.info.classname);
                        
                        break;
                    
                    case 2:
                    // printf("\t2\tCal and display level count by subject and by class\n");
                        printf("which class's levelCount you wanna cal and display: ");
                        scanf("%s", &data.info.classname);
                        calculateLevelCount_2(L, data.info.classname);

                        break;
                }
            break;
            
        case 6:
        // printf("6. printAll()\n");
            printList_2(L);

            break;        
        case 7:
        // printf("7. Delete all ElemNode_2\n");
            deleteAll_2(&L);
            printf("all deleted\n");
            createListWithHead_2(&L); // cannot delete the headNode_2

            saveDataToFile_2(L, data_file_2);
            printf("saved\n");

            break;


        default:
            printf("Input error!\n");
            break;
    }

}



int main()
{
    int studNum_2 = -100;
    const char *data_file_2 = "data_2.txt";

    LinkList_2 list_2;
    createListWithHead_2(&list_2);

    // firstly, open the file, load possible previous data
    readDataFromFile_2(list_2, data_file_2);

    while (1)
    {
        printMenu_2();
        keyDown_2(list_2, &studNum_2, data_file_2); 

        printf("\n\n\tcls right away\n");
        system("pause");
        system("cls"); // cls and this loop all over again
    }

    deleteAll_2(&list_2);

    return 0;
}
