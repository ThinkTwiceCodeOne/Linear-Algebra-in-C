#include<stdio.h>
#include "ylinAlg.h"
void printMatrix(double *matrix3,int r1)
{
for(int i=0;i<r1;i++)
{
printf("%lf\n",matrix3[i]);
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
double **matrix3=(double **)malloc(3*sizeof(double *));
for(int i=0;i<3;i++)
{
matrix3[i]=(double *)malloc(3*sizeof(double));
}
for(int i=0;i<3;i++)
{
for(int j=0;j<3;j++)
{
scanf("%d",&matrix1[i][j]);
}
}
double* matrix5=(double *)malloc(3*sizeof(double));
int* matrix4=(int *)malloc(3*sizeof(int));
for(int i=0;i<3;i++)
{
scanf("%d",&matrix4[i]);
}
matrix5=rootsOfEquations(matrix1,matrix4,3,3);
printMatrix(matrix5,3);
return 0;
}
