#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//From lab7
list listcreate()
{
    list l =malloc(sizeof(struct listR));
    if(l==NULL)
    {
        printf("\n\tCould not allocate memory!\n");
        exit(1);
    }
    l -> head = NULL ;
    l ->tail=NULL;
    l -> size = 0;
    return l ;
}

//From lab7
int listisempty(list l)
{
    if ( l->size == 0)
    {
        return 1;
    }
    else 
    {
        return 0;
    }
    
}

//From lab7
void listdestroy(list l)
{
    while ( l->size != 0)
    {
        node currenthead= l->head;
        node tmp = currenthead->next ;
        free(currenthead->st);
        free(currenthead);
        l->head = tmp;
        l->size--;
    }
    free(l);
}

void printMenu()
{
    printf("\tPlease choose an option from 1 to 6\n");
    printf("\t1.Create A New Student\n");
    printf("\t2.Delete Student\n");
    printf("\t3.Change Student's Data\n");
    printf("\t4.Print one of the Students\n");
    printf("\t5.Print all of the Students\n");
    printf("\t6.Exit\n");
    
}

void printstudents(list l)
{
    node currenthead;
    for(currenthead =l->head; currenthead!=NULL; currenthead=currenthead->next)
    {
        printf("\n\tName : %s\n", currenthead->st->name );
        printf("\tId : %d\n\n", currenthead->st->id );
    }
}

void print(struct studentR userSt)
{
    printf("\n\tName : %s \n",userSt.name);
    printf("\tId : %d\n\n",userSt.id);   
}

student findStudent(int userId,list l)
{  
    node currentNode;
    for(currentNode =l->head; currentNode!=NULL; currentNode=currentNode->next)
    {
        if(currentNode->st->id==userId)
        {
            return currentNode->st;
        }
    }  
    return NULL;
}


//To add an empty node to the list from lab7
node listaddnode(list l)
{
    node Newnode = malloc(sizeof(struct nodeR));
    if(Newnode==NULL)
    {
        printf("\n\tCould not allocate memory!\n");
        exit(1);
    }
    Newnode->next=NULL;
    if(listisempty(l))     
    {
        l->head=Newnode;
        l->tail=Newnode;
    }else{
        node currentTail = l-> tail;
        currentTail->next=Newnode;
        l->tail=Newnode;
        
    }
    return Newnode;
}
//To fill the empty node 
int addStudent(struct studentR userSt, list l)
{   
    node n=listaddnode(l);
    student Newstudent = malloc(sizeof(struct studentR));
    if(Newstudent == NULL)
    {
        printf("\n\tCould not allocate memory!\n");
        exit(1);
    }
    strcpy(Newstudent->name,userSt.name);
    (Newstudent->id)=userSt.id;
    n->st=Newstudent;
    n->next=NULL;
    (l->size)++;
    return 1;
}

int deleteStudent(struct studentR userSt, list l) 
{
    student currentstudent=findStudent(userSt.id,l);
    if(currentstudent==NULL)
    {
        printf("\x1B[0;31m");//from stack overflow to paint the output
        printf("\tThis student does not exist.Please enter an other id\n");
        printf("\x1B[0m");//from stack overflow to stop paint the output
        return 0;
    }
    node backNode=NULL;
    node currentNode;
    for(currentNode=l->head;currentNode!=NULL;currentNode=currentNode->next)
    {
        //For deleted first node
        if(currentNode==l->head && currentNode->st==currentstudent)
        {
            l->head=currentNode->next;
            free(currentNode->st);
            free(currentNode);
            (l->size)--;
            return 1;
        }
        
        //For deleted the middle nodes
        if(currentNode->st==currentstudent && currentNode!=l->tail)
        {
            backNode->next=currentNode->next;
            free(currentNode->st);
            free(currentNode);
            l->size--;
            return 1;
        }
        //For deleted the last node
        if(currentNode==l->tail)
        {
            backNode->next=NULL;
            free(currentNode->st);
            free(currentNode);
            (l->size)--;
            l->tail=backNode;
            return 1;
        }
        backNode=currentNode;
    }
    return 0;
}

int updateStudent(struct studentR st, list l)
{
    student currentstudent=findStudent(st.id,l);
    if(currentstudent==NULL)
    {
        printf("\x1B[0;31m");//from stack overflow to paint the output
        printf("\n\tThe student does not exist.\n");
        printf("\x1B[0");//from stack overflow to stop paint the output
        return 0;
    }
    int newid,x;
    char newname[MAXSTRING],c;
    char choice;

    
    printf("\tTo changed only id press 1\n");
    printf("\tTo changed only the name press 2\n");
    printf("\tTo changed both press 3\n");
    printf("Only one number please.\nΟtherwise it will take the first digit\nof the number as an option\n");

    do 
    {
        scanf("%c", &choice);
    }
    while( choice < '1' && choice > '3' );
    //From stack overflow to clean buffer
    while((c = (char)getchar()) != '\n' && c != EOF);
    switch(choice)
    {
        case '1':
            printf("\tPlease enter the new student id\n");
            //save what returned to see if scanf read and assigned only one input data
            x=scanf("%d", &newid);
            //Checks the input given by the user
            if(!input(x,newid))
            {
                return 0;
            }
            //Check if the newid that given by the user already exist
            if(findStudent(newid,l)!=NULL)
            {
                printf("\x1B[0;31m");//from stack overflow to paint the output
                printf("\n\tThis student already exist\n\n");
                printf("\x1B[0");//from stack overflow to stop paint the output
                return 0;
            }
            (currentstudent->id)=newid;
            break;
        case '2':
            printf("\tPlease enter the new student name with maximum %d characters\nIt stops at the space\n",MAXSTRING);
            scanf("%s", newname );
            //From stack overflow to clean buffer
            while((c = (char)getchar()) != '\n' && c != EOF);
            strcpy(currentstudent->name,newname);//Τo assign the name
            break;
        case '3':
            printf("\tPlease enter the new student id\n");
            x=scanf("%d", &newid );
            //Checks the input given by the user
            if(!input(x,newid))
            {
                return 0;
            }
            //Check if the newid that given by the user already exist
            if(findStudent(newid,l)!=NULL)
            {
                printf("\x1B[0;31m");//from stack overflow to paint the output
                printf("\n\tThis student already exist\n\n");
                printf("\x1B[0m");//from stack overflow to stop paint the output
                return 0;
            }
            printf("\tPlease enter the new student name with maximum %d characters\nIt stops at the space\n",MAXSTRING);
            scanf("%s", newname );
            //From stack overflow to clean buffer
            while((c = (char)getchar()) != '\n' && c != EOF);
            (currentstudent->id)=newid;
            strcpy(currentstudent->name,newname);//Τo assign the name
            break;
        //With default check if user gave for input a choice that is not at cases
        default:
            printf("\x1B[0;31m");//from stack overflow to paint the output
            printf("\n\tChoice is not correct.\n");
            printf("\x1B[0m");//from stack overflow to stop paint the output
            return 0;
    }
    return 1;
}

void save(char *filename,list l)
{
    printf("\x1B[0;31m");//from stack overflow to paint the output
    int result;
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("\n\tThere was a problem when storing the list with the students.Please try again\n\n");
        printf("\x1B[0m");//from stack overflow to stop paint the output
        return;
    }

    node currentNode;
    for(currentNode =l->head; currentNode!=NULL; currentNode=currentNode->next)
    {
        result=fwrite(currentNode->st,sizeof(struct studentR),1,fp);
        if(result<=0)
        {
            printf("\n\tΑ problem occurred while registering the file.Please try again\n\n");
            printf("\x1B[0m");//from stack overflow to stop paint the output
            return;
        }
    }
    printf("\x1B[0m");//from stack overflow to stop paint the output
    fclose(fp);
    return;
    
}

list load(char *filename)
{
    printf("\x1B[1;37m");//from stack overflow to paint the output
    list l = listcreate(); 
    
    FILE *fp ;
    fp = fopen(filename,"r");

    if( fp==NULL)
    {
        printf("\n\tThe file does not exist.Continued normally\n\n");
        printf("\x1B[0m");//from stack overflow to stop paint the output
        return l;
    }

    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);

    if( filesize ==0 )
    {
        printf("\n\tThe file is empty.Continued normally\n\n");
        printf("\x1B[0m");//from stack overflow to stop paint the output
        return l;
    }
    struct studentR st;
    //To reset the file position index at the beginning of the file
    rewind(fp);

       
    //Reads from the beginning of the file struct studentR by struct studentR and add them in the file when it opens
    while(ftell(fp) < filesize)
    {
        fread(&st, sizeof(struct studentR), 1, fp);
        addStudent(st,l);
        
    }
    printf("\n\tThe file has %d student(s) that saved\n\n",l->size);
    
    printf("\x1B[0m");//from stack overflow to stop paint the output
    fclose(fp);
    return l;
}

//Checks the input given by the user
int input(int x,int am)
{
    printf("\x1B[0;31m");//from stack overflow to paint the output
    //Check the buffer if what it has kept includes character
    char c;
    c = (char)getchar() ;
    if( !(( c<0 && c>9 ) || c== '\n' || c == EOF))
    {
        printf("\n\tWrong input .Only positive integers please .\n\n");
        printf("\x1B[0m");//from stack overflow to stop paint the output
        while((c = (char)getchar())!= '\n' && c != EOF);
        return 0;
    }
    //Check scanf if returns an integer that states if scanf read and assigned only one input data 
    if(x!=1)
    {
        printf("\n\tOnly integers please\n\n");
        printf("\x1B[0m");//from stack overflow to stop paint the output
        return 0;
    }
    if( am <0 )
    {
        printf("\n\tOnly positive integers please\n\n");
        printf("\x1B[0m");//from stack overflow to stop paint the output
        return 0;
    }
    printf("\x1B[0m");//from stack overflow to stop paint the output
    return 1;
    
}














