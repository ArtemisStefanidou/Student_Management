#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char **argv)
{
    //Check if user gave a file name at the i/o

//    argv[1] = "artemis.txt";
    if(argc!=2)
    {
        printf("\n\tYou have to give also a file name either that already exists or a name of your choice and we will create this file for you\n");
        return 0;
    }

    //file
    //+1 for \0
    char *filename = malloc(strlen(argv[1]) + 1);
    if (filename == NULL)
    {
        printf("Could not allocate memory!\n");
        return 0;
    }
    else{
        strcpy(filename, argv[1]);
    }
    
    //The list is created
    list l=load(filename);


    //A Welcome Message
    printf("\x1B[0;35m");//from stack overflow to paint the output
    printf("\tWelcome to my program ID:21996 Name:Artemis Stefanidou\n\n");
    printf("\x1B[0m");//from stack overflow to stop paint the output


    char choice;
    int am,result,x;
    char userName[MAXSTRING],c;
    struct studentR userSt;

    while(1) 
    {
       
        printMenu();
        printf("Only one number please.\nOtherwise it will take the first digit\nof the number as an option\n");

        do 
        {
            scanf("%c", &choice);
        }
        while( choice < '1'&& choice > '6');

        //To clean buffer from stack overflow
        while((c = (char)getchar()) != '\n' && c != EOF);

        switch( choice )
        {
            
            case '1':

                //ID STUDENT
                printf("\tPlease enter student id.Only positive integer. \n");
                x=scanf("%d",&am);

                //Checks the input given by the user
                if(!input(x,am))
                {
                    break;
                }

                //Check if the am that given by the user already exist
                if (findStudent(am,l) != NULL)
                {
                    printf("\x1B[0;31m");//from stack overflow to paint the output
                    printf("\tThis student already exist!\n\n");
                    printf("\x1B[0m");//from stack overflow to stop paint the output
                    break;
                }


                //NAME STUDENT
                printf("\tPlease enter student name with maximum %d characters\nIt stops at the space\n",MAXSTRING);
                scanf("%s",userName);

                //To clean buffer by stack overflow
                while((c = (char)getchar()) != '\n' && c != EOF); 

                //Τo assign the user data to struct
                strcpy(userSt.name,userName); 
                (userSt.id)=am;

                //ADD STUDENT
                result=addStudent(userSt,l);
                if(result==1)
                {
                    printf("\x1B[0;32m");//from stack overflow to paint the output
                    printf("\n\t Τhe addition was successful \n\n");
                    printf("\x1B[0m");//from stack overflow to stop paint the output
                }else{
                    printf("\x1B[0;31m");//from stack overflow to paint the output
                    printf("\tPlease try something different\n\n");
                    printf("\x1B[0m");//from stack overflow to stop paint the output
                    break;
                }

                save(filename,l);
                break;
                
            case '2':

                if(listisempty(l))
                {
                    printf("\x1B[0;31m");//from stack overflow to paint the output
                    printf("list does not exist\n");
                    printf("\x1B[0m");//from stack overflow to stop paint the output
                    break;
                }

                //ID STUDENT
                printf("\tPlease enter student id.Only positive integer.\n");
                x=scanf("%d",&am);

                //Checks the input given by the user
                if(!input(x,am))
                {
                    break;
                }

                //Τo assign the user data to struct
                (userSt.id)=am;

                //DELETE STUDENT
                result=deleteStudent(userSt,l);
                if(result==1)
                {
                    printf("\x1B[0;32m");//from stack overflow to paint the output
                    printf("\n\tΤhe deletion was successful \n\n");
                    printf("\x1B[0m");//from stack overflow to stop paint the output
                }else{
                    printf("\x1B[0;31m");//from stack overflow to paint the output
                    printf("\tPlease try something different\n\n");
                    printf("\x1B[0m");//from stack overflow to stop paint the output
                    break;
                }

                save(filename,l);
                break;

            case '3':

                if(listisempty(l))
                {
                    printf("\x1B[0;31m");//from stack overflow to paint the output
                    printf("list does not exist\n");
                    printf("\x1B[0m");//from stack overflow to stop paint the output
                    break;
                }

                //ID STUDENT
                printf("\tPlease enter the student's initial id.Only positive integer.\n");
                x=scanf("%d",&am );

                //Checks the input given by the user
                if(!input(x,am))
                {
                    break;
                }

                //Τo assign the user data to struct
                (userSt.id)=am;

                //UPDATE STUDENT
                result=updateStudent(userSt,l);
                if(result==1)
                {
                    printf("\x1B[0;32m");//from stack overflow to paint the output
                    printf("\n\tΤhe update was successful \n\n");
                    printf("\x1B[0m");//from stack overflow to stop paint the output
                }else{
                    printf("\x1B[0;31m");//from stack overflow to paint the output
                    printf("\tPlease try something different\n\n");
                    printf("\x1B[0m");//from stack overflow to stop paint the output
                    break;
                }  

                save(filename,l);
                break;

            case '4':

                if(listisempty(l))
                {
                    printf("\x1B[0;31m");//from stack overflow to paint the output
                    printf("list does not exist\n");
                    printf("\x1B[0m");//from stack overflow to stop paint the output
                    break;
                }

                //ID STUDENT
                printf("\tPlease enter student id.Only positive integer. \n");
                x=scanf("%d",&am );

                //Checks the input given by the user
                if(!input(x,am))
                {
                    break;
                }
                else{

                    //Search to find the student from the am that given by the user
                    student currentstudent=findStudent(am,l);

                    if (currentstudent == NULL)
                    {
                        printf("\x1B[0;31m");//from stack overflow to paint the output
                        printf("\tThis student does not exist!\n\n");
                        printf("\x1B[0m");//from stack overflow to stop paint the output
                        break;
                    }

                    //Τo Assign the User Data to Struct
                    strcpy(userSt.name,currentstudent->name);
                    (userSt.id)=currentstudent->id;

                    print(userSt);
                    break;
                }
                break;

            case '5':

                if(listisempty(l))
                {
                    printf("\x1B[0;31m");//from stack overflow to paint the output
                    printf("list does not exist\n");
                    printf("\x1B[0m");//from stack overflow to stop paint the output
                    break;
                }

                printf("Exists %d students\n",l->size);
                printstudents(l);
                break;

            case '6':

                printf("\x1B[0;35m");//from stack overflow to paint the output
                printf("Exiting the program....\nGood rest of the day\n");
                printf("\x1B[0m");//from stack overflow to stop paint the output

                exit(1);

            //With default check if user gave for input a choice that is not at cases
            default:
                printf("\x1B[0;31m");//from stack overflow to paint the output
                printf("\n\tChoice is not correct.Please try something different\n\n");
                printf("\x1B[0m");//from stack overflow to stop paint the output
        }
    }
    free(filename);
    listdestroy(l);

    return 0;
}