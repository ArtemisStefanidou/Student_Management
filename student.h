#ifndef STUDENT_H
#define STUDENT_H
#define MAXSTRING 50 

typedef struct studentR* student;
struct studentR
{
   char name[MAXSTRING];
   int id;
};

typedef struct nodeR* node;
struct nodeR 
{
   student st;
   node next;
};

typedef struct listR* list;
struct listR 
{
 node head,tail;
 int size;
};

void printMenu();        

void print(struct studentR);    

void printstudents(list);   

list load(char*);

void save(char*,list); 

int addStudent(struct studentR,list) ; 

student findStudent(int,list); 

int deleteStudent(struct studentR,list); 

int updateStudent(struct studentR,list); 

int input(int,int);

list listcreate();

int listisempty(list);

void listdestroy(list);

node listaddnode(list);

#endif
