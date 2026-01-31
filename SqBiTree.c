#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

typedef char ElemType;
#define  MAXSIZE 100

typedef ElemType SqBiTree[MAXSIZE];
SqBiTree bt;