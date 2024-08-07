# question 1
```c
#include<stdio.h>
#include<stdlib.h>
typedef struct sub{
  int Physics;
  int Maths;
  int English;
  int Computer;
  int Hindi;
  int avg;
  int total;
}Subject;

typedef struct Stud{
  char name[100];
  char address[500];
  struct sub* subs;
} Student;

typedef struct stddb{
  Student * studs;
} StdDB;

Student* findmax(StdDB *studentdb,int subchoice,int len){
  Student * res = (studentdb->studs);// initializing with first student
  switch(subchoice){
    case(1)://physics
    {
      for(int i=0;i<len;i++){
        if((studentdb->studs[i].subs->Physics)>(res->subs->Physics))
          res = &(studentdb->studs[i]);
      }
      return res;
      break;
    }
    case(2)://Maths
    {
      for(int i=0;i<len;i++){
        if((studentdb->studs[i].subs->Maths)>(res->subs->Maths))
          res = &(studentdb->studs[i]);
      }
      return res;
      break;
    }
    case(3)://English
    {
      for(int i=0;i<len;i++){
        if((studentdb->studs[i].subs->English)>(res->subs->English))
          res = &(studentdb->studs[i]);
      }
      return res;
      break;
    }
    case(4)://Computer
    {
      for(int i=0;i<len;i++){
        if((studentdb->studs[i].subs->Computer)>(res->subs->Computer))
          res = &(studentdb->studs[i]);
      }
      return res;
      break;
    }
    default:
    {
      for(int i=0;i<len;i++){
        if((studentdb->studs[i].subs->Hindi)>(res->subs->Hindi))
          res = &(studentdb->studs[i]);
      }
      return res;
      break;
    }
  }
}
int calc_passes(Subject *sub){
  int cnt = 0,fail = 0;
  if( sub->Physics>=40)cnt++;
  if( sub->Maths>=40)cnt++;
  if( sub->English>=40)cnt++;
  if( sub->Computer>=40)cnt++;
  if( sub->Hindi>=40)cnt++;
  return cnt;
}
void showdetailstud(Student *stud){
    printf("name %s\n",stud->name);
    printf("address %s\n",stud->address);
    printf("Physics %d\n",stud->subs->Physics);
    printf("Maths %d\n",stud->subs->Maths);
    printf("English %d\n",stud->subs->English);
    printf("Computer %d\n",stud->subs->Computer);
    printf("Hindi %d\n",stud->subs->Hindi);
    printf("AVG %d\n",stud->subs->avg);
    printf("TOTAL %d\n",stud->subs->total);
}
int main(){
  //make it 12 as per the progams
  const int rep = 2; // denotes the no of students in the database
  // basic initialization;
  StdDB studentdb;
  studentdb.studs = (Student*)malloc(sizeof(Student) * (rep));
  int i=0;
  // assigning memory for subject of each studetn
  for(;i<rep;i++){
    studentdb.studs[i].subs = (Subject*)malloc(sizeof(Subject));
  }
  for( i=0;i<rep;i++){
    printf("For %d\n", i+1);
    studentdb.studs[i].subs->avg = 0;
    printf("name : ");
    scanf("%s",(studentdb.studs)[i].name);
    printf("addr : ");
    scanf("%s",(studentdb.studs)[i].address);
    printf("Physics : ");
    scanf("%d",&(studentdb.studs)[i].subs->Physics);
    studentdb.studs[i].subs->avg+= (studentdb.studs)[i].subs->Physics;
    printf("Maths : ");
    scanf("%d",&(studentdb.studs)[i].subs->Maths);
    studentdb.studs[i].subs->avg+= (studentdb.studs)[i].subs->Maths;
    printf("English : ");
    scanf("%d",&(studentdb.studs)[i].subs->English);
    studentdb.studs[i].subs->avg+= (studentdb.studs)[i].subs->English;
    printf("Computer : ");
    scanf("%d",&(studentdb.studs)[i].subs->Computer);
    studentdb.studs[i].subs->avg+= (studentdb.studs)[i].subs->Computer;
    printf("Hindi : ");
    scanf("%d",&(studentdb.studs)[i].subs->Hindi);
    studentdb.studs[i].subs->avg+= (studentdb.studs)[i].subs->Hindi;
    studentdb.studs[i].subs->total = studentdb.studs[i].subs->avg;
    studentdb.studs[i].subs->avg /= 5;
  }
  //menu driven program starts
  int c = 1;
  while(c){
    printf("choose any one of the options : ->\n");
    printf("1. name of students who have passed and failed in min 3 subjects\n");
    printf("2. Show the record of the student who has got maximum marks in Mathematics.\n");
    printf("3. Show the record of the student who has got minimum marks in Physics.\n");
    printf("4. Show the record of the student whose average marks is maximum.(done)\n");
    printf("5. Print the record of the student with name and total.\n");
    printf("->");scanf("%d",&c);
    switch(c){
      case (1):
        {
          printf("passed in 3 subs :-> ");
          for(int i=0;i<rep;i++){
            if(calc_passes(studentdb.studs[i].subs)>=3) {
              printf("%s, ", studentdb.studs[i].name);
            }
          }
          printf("failed in 3 subs :-> ");
          for(int i=0;i<rep;i++){
            if((5-calc_passes(studentdb.studs[i].subs))>=3) {
              printf("%s, ", studentdb.studs[i].name);
            }
          }
          printf("\n");
          printf("\n");
          break;
        }
      case(2):
        {
          showdetailstud(findmax(&studentdb,2,rep)); // for mathematics
          break;
        }
      case(3):
        {
          showdetailstud(findmax(&studentdb,1,rep));// for physics
          break;
        }
      case(4):
        {
          Student *maxiavg = studentdb.studs;
          for(int i=0;i<rep;i++){
            if((studentdb.studs[i].subs->avg)>(maxiavg->subs->avg)) {
              maxiavg = &studentdb.studs[i];
            }
          }
          showdetailstud(maxiavg);
          break;
        }
      case(5):
        {
          for(int i=0;i<rep;i++){
            printf("FOR : %d\n",i+1 );
            printf("Name : %s\n", studentdb.studs[i].name);
            printf("total : %d\n", studentdb.studs[i].subs->total);
          }
          break;
        }
      default:
        {
          printf("Invalid input \n");
          break;
        }
    }
    printf("Want to continue(press 1):");scanf("%d",&c);
  }
}

```
