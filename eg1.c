#include<stdio.h>
#include "ymath.h"
void printMatrix(int **matrix3,int r1,int c1)
{
for(int i=0;i<r1;i++)
{
for(int j=0;j<c1;j++)
{
printf("%d ",matrix3[i][j]);
}
printf("\n");
}
}
int main()
{
int count=1;
int **matrix1=(int **)malloc(3*sizeof(int *));
for(int i=0;i<3;i++)
{
matrix1[i]=(int *)malloc(3*sizeof(int));
}
int **matrix2=(int **)malloc(3*sizeof(int *));
for(int i=0;i<3;i++)
{
matrix2[i]=(int *)malloc(3*sizeof(int));
}
int **matrix3=(int **)malloc(3*sizeof(int *));
for(int i=0;i<3;i++)
{
matrix3[i]=(int *)malloc(3*sizeof(int));
}
for(int i=0;i<3;i++)
{
for(int j=0;j<3;j++)
{
matrix1[i][j]=count;
matrix2[i][j]=count;
count++;
}
}
matrix3=addMatrix(matrix1,matrix2,3,3,3,3);
printMatrix(matrix3,3,3);
return 0;
}
