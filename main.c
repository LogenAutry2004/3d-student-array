/*
 Logen Auty
 5/17/24
 Lab 1
*/

#include <stdio.h>
//#include "leak_detector_c.h" currently memory leak detector is not working :(
#include <string.h>
#include <stdlib.h>

// student structure
typedef struct student
{
  char *lname;
  int assignment;
  int finalExam;
  int total;
  int *quizzes;
}student; 

// function prototypes
student** readCourses(int *C, int *N, int *M);
void printHighestTotal(student ** st, int C, int N, int M);
void release_memroy(student ** st, int C, int N, int M);

int main()
{

  // reports memory leak
  //atexit(report_mem_leak); not working

  // initializing variables
  student **courseList;
  int i, j,C, N, M;

  // calling the functions
  courseList = readCourses(&C, &N, &M);
  printHighestTotal(courseList, C, N, M);
  release_memroy(courseList, C, N, M);
  
  return 0;
}

// reads input
student** readCourses(int *C, int *N, int *M){
  // takes in courses number of students number of quizzes
  scanf("%d %d %d", C, N, M);

  // initializes variables
  student **courArr;
  char tempName[51];
  int len;

  // creating course array full of student arrays
  courArr = (student**)malloc(*C * sizeof(student*));

  // creating student arrays for each course
  for(int i = 0; i < *C; i++){
    courArr[i] = (student*)malloc(*N * sizeof(student));
  }

  // filling those arrays
  for(int i = 0; i < *C; i++){
    for(int j = 0; j < *N; j++){

      // scans name and assignment
      scanf("%s %d", tempName, &courArr[i][j].assignment);

      // gets size of name and then creates a char array to that size
      len = strlen(tempName) +1;
      courArr[i][j].total += courArr[i][j].assignment;
      courArr[i][j].lname = (char*)malloc(sizeof(char) *len);
      strcpy(courArr[i][j].lname, tempName);
      courArr[i][j].quizzes = (int*)malloc(sizeof(int) * *N);

      // takes in quizzes
      for(int k = 0; k < *M; k++){
        scanf("%d", &courArr[i][j].quizzes[k]);
        courArr[i][j].total += courArr[i][j].quizzes[k];
      }

      // takes in final exam
      scanf("%d", &courArr[i][j].finalExam);
      courArr[i][j].total += courArr[i][j].finalExam;
    }
  }
  return courArr;
}

// prints highest total
void printHighestTotal(student ** st, int C, int N, int M){

  // initializes max indices
  int maxCIndex = 0;
  int maxNIndex = 0;
  for(int i = 0; i < C; i++){
    for(int j = 0; j < N; j++){
      
      // if total is bigger, update max indices
      if(st[i][j].total > st[maxCIndex][maxNIndex].total){
        maxCIndex = i;
        maxNIndex = j;
      }
    }
  }

  // prints max indices data
  printf("Name: %s\nAssignment: %d\n", st[maxCIndex][maxNIndex].lname, st[maxCIndex][maxNIndex].assignment);
  printf("Quizzes: ");
  for(int l = 0; l < M; l++){
    printf("%d ", st[maxCIndex][maxNIndex].quizzes[l]);
  }
  printf("\nFinal exam: %d\nTotal: %d\nCourse number: %d",st[maxCIndex][maxNIndex].finalExam, st[maxCIndex][maxNIndex].total, maxCIndex + 1);
}

// releases memory
void release_memroy(student ** st, int C, int N, int M){
  for(int i = 0; i < C; i++){
    for(int j = 0; j < N; j++){
      // frees lnam array and quiz array
      free(st[i][j].lname);
      free(st[i][j].quizzes);
    }
    // frees student array
    free(st[i]);
  }

  // frees course array
  free(st);
}