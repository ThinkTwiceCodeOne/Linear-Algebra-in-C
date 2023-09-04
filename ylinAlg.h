#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include<stdlib.h> 
double determinant(int **matrix, int r, int c);
double **reducedRowEchelon(int **matrix, int r, int c)
{
    double **matrix1 = (double **)malloc(r * sizeof(double *));
    for (int i = 0; i < r; i++)
    {
        matrix1[i] = (double *)malloc(c * sizeof(double));
    }
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            matrix1[i][j] = (double)matrix[i][j];
        }
    }
        int len=2*c;
        int j=0;
        int m=0;
        int flag=0;
        //making all element of last row as 0
        for(int i=0;i<len;i++)
        {
            if(i%2==0)
            {
                if(matrix[r-1][j]==0.0) 
                {
                    continue;
                }
                else
                {    
                    double ratio;
                    if(matrix1[r-2][j]==0.0) ratio=matrix1[r-1][j];
                    else ratio=matrix1[r-1][j]/matrix1[r-2][j];
                    for(int k=0;k<c;k++)
                    {
                        matrix1[r-1][k]=matrix1[r-1][k]-(ratio*matrix1[r-2][k]);
                    }
                    j++;
                }

            }
            else
            {
                if(matrix1[r-2][m]==0.0) 
                {
                    continue;
                }
                else
                {
                    double ratio;
                    if(matrix1[0][m]==0.0) ratio=matrix[r-2][m];
                    else ratio=matrix1[r-2][m]/matrix1[0][m];
                    for(int k=0;k<c;k++)
                    {
                        matrix1[r-2][k]=matrix1[r-2][k]-(ratio*matrix1[0][k]);
                    }
                    m++;
                }
            }   
        }

        //making upper triangular matrix for r-2 rows
        for (int i = 0; i < r - 2; i++)
        {
            for (int j = i + 1; j < c; j++)
            {
                double ratio = 0.0;
                if (matrix1[i][i] != 0)
                {
                    ratio = (double)matrix1[j][i] / matrix1[i][i];
                }
                else
                    ratio = (double)matrix[j][i];
                for (int k = 0; k < c; k++)
                {
                    matrix1[j][k] = matrix1[j][k] - (ratio * matrix1[i][k]);
                    if(matrix1[j][k]==-0.0) matrix1[j][k]=0.0;
                }
            }
        }
        //dividing diagonal by itself to make them 1
        for(int i=0;i<r-1;i++)
        {
            double temp=matrix1[i][i];
            if(temp==0.0) continue;
            for(int j=0;j<c;j++)
            {
                matrix1[i][j]=matrix1[i][j]/temp;
                if(matrix1[i][j]==-0.0) matrix1[i][j]=0.0;
            }
        }
        
        //If there is 1 in any column then making remaining column element as 0
        for(int i=0;i<r;i++)
        {
            for(int j=0;j<c;j++)
            {
                if(matrix[j][i]==0 && i!=j) continue;
                else if(i!=j && matrix1[j][i]!=0 && matrix1[i][i]==1)
                {
                    double temp=matrix1[i][i];
                    double ratio;
                    if(temp==0.0) ratio=matrix1[j][i];
                    else ratio=matrix1[j][i]/temp;
                    for(int k=0;k<c;k++)
                    {
                        matrix1[j][k]=matrix1[j][k]-(ratio*matrix1[i][k]);
                    }
                }
            }
        }

    
    
    return matrix1;
}
int rank(int **matrix, int r, int c)
{
    int res=0;
    double** matrix2=(double **)malloc(r*sizeof(double *));
    for(int i=0;i<r;i++)
    {
        matrix2[i]=(double *)malloc(c*sizeof(double));
    }
    
    matrix2=reducedRowEchelon(matrix,r,c);
    for(int i=0;i<c;i++)
    {
        int count1=0;
        int count0=0;
        for(int j=0;j<r;j++)
        {
            if(matrix2[j][i]==1.0) count1=count1+1;
            else if(matrix2[j][i]==0.0) count0=count0+1;
        }
        if(count1==1 && count0==r-1) res++; 
    }
    return res;
}
double *rootsOfEquations(int **matrix, int *variable, int r, int c)
{
    double matrix1[r][c];
    double matrix2[r];
    double *result = (double *)malloc(r * sizeof(double));
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            matrix1[i][j] = (double)matrix[i][j];
        }
    }
    for (int i = 0; i < r; i++)
    {
        matrix2[i] = (double)variable[i];
    }
    for (int i = 0; i < r - 1; i++)
    {
        for (int j = i + 1; j < c; j++)
        {
            double ratio = 0.0;
            if (matrix1[i][i] != 0)
            {
                ratio = (double)matrix1[j][i] / matrix1[i][i];
            }
            else
                ratio = (double)matrix[j][i];
            for (int k = 0; k < r; k++)
            {
                matrix1[j][k] = matrix1[j][k] - (ratio * matrix1[i][k]);
                // matrix2[j]=matrix2[j]-(ratio*matrix2[i]);
            }
            matrix2[j] = matrix2[j] - (ratio * matrix2[i]);
        }
    }
    for (int i = 0; i < r - 1; i++)
    {
        for (int j = i + 1; j < r; j++)
        {
            double ratio;
            if (matrix1[j][j] != 0)
            {
                ratio = (double)matrix1[i][j] / matrix1[j][j];
            }
            else
                ratio = (double)matrix1[i][j];
            for (int k = 0; k < r; k++)
            {
                matrix1[i][k] = matrix1[i][k] - (ratio * matrix1[j][k]);
                // matrix2[i]=matrix2[i]-(ratio*matrix2[j]);
            }
            matrix2[i] = matrix2[i] - (ratio * matrix2[j]);
        }
    }
    for (int i = 0; i < r; i++)
    {
        double temp = matrix1[i][i];
        matrix1[i][i] = matrix1[i][i] / temp;
        matrix2[i] = matrix2[i] / temp;
    }
    for (int i = 0; i < r; i++)
    {
        result[i] = matrix2[i];
    }
    return result;
}
double **inverse(int **matrix, int r, int c)
{
    double matrix1[r][c];
    if (r == c)
    {
        double **matrix2 = (double **)malloc(r * sizeof(double *));
        for (int i = 0; i < r; i++)
        {
            matrix2[i] = (double *)malloc(c * sizeof(double));
        }
        if (determinant(matrix, r, c) == 0.0)
        {
            printf("For this matrix inverse is not possible\n");
            return NULL;
        }
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                matrix1[i][j] = (double)matrix[i][j];
                if (i == j)
                    matrix2[i][j] = 1.0;
                else
                    matrix2[i][j] = 0.0;
            }
        }
        for (int i = 0; i < r - 1; i++)
        {
            for (int j = i + 1; j < c; j++)
            {
                double ratio = 0.0;
                if (matrix1[i][i] != 0)
                {
                    ratio = (double)matrix1[j][i] / matrix1[i][i];
                }
                else
                    ratio = (double)matrix[j][i];
                for (int k = 0; k < r; k++)
                {
                    matrix1[j][k] = matrix1[j][k] - (ratio * matrix1[i][k]);
                    matrix2[j][k] = matrix2[j][k] - (ratio * matrix2[i][k]);
                }
            }
        }
        for (int i = 0; i < r - 1; i++)
        {
            for (int j = i + 1; j < r; j++)
            {
                double ratio;
                if (matrix1[j][j] != 0)
                {
                    ratio = (double)matrix1[i][j] / matrix1[j][j];
                }
                else
                    ratio = (double)matrix1[i][j];
                for (int k = 0; k < r; k++)
                {
                    matrix1[i][k] = matrix1[i][k] - (ratio * matrix1[j][k]);
                    matrix2[i][k] = matrix2[i][k] - (ratio * matrix2[j][k]);
                }
            }
        }
        for (int i = 0; i < r; i++)
        {
            double temp = matrix1[i][i];
            for (int j = 0; j < r; j++)
            {
                matrix2[i][j] = matrix2[i][j] / temp;
            }
        }
        return matrix2;
    }
    else
    {
        printf("Number of rows and columns should be equal");
        return NULL;
    }
    return NULL;
}
double determinant(int **matrix, int r, int c)
{
    double result = 1;
    if (r == c)
    {
        double matrix1[r][c];
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                matrix1[i][j] = (double)matrix[i][j];
            }
        }
        for (int i = 0; i < r - 1; i++)
        {
            for (int j = i + 1; j < c; j++)
            {
                double ratio = (double)matrix1[j][i] / matrix1[i][i];
                // printf("ratio is %f\n",ratio);
                for (int k = 0; k < r; k++)
                {
                    matrix1[j][k] = matrix1[j][k] - (ratio * matrix1[i][k]);
                }
                // printf("%d %d\n",j,i);
            }
        }
        /*for(int i=0;i<r;i++)
        {
        for(int j=0;j<c;j++)
        {
        printf("%f ",matrix1[i][j]);
        }
        printf("\n");
        }*/
        for (int i = 0; i < r; i++)
        {
            if (matrix1[i][i] == 0)
                return 0;
            result = result * matrix1[i][i];
            // printf("result is %f\n",result);
        }
    }
    else
    {
        printf("The matrix should be a square matrix\n");
        return 0;
    }
    return result;
}
int trace(int **matrix1, int r, int c)
{
    int trace = 0;
    if (r == c)
    {
        for (int i = 0; i < r; i++)
        {
            trace = trace + matrix1[i][i];
        }
    }
    else
    {
        printf("The matrix should be square matrix\n");
        return 0;
    }
    return trace;
}
int **addMatrix(int **matrix1, int **matrix2, int r1, int c1, int r2, int c2)
{
    int **result;
    if (r1 == r2 && c1 == c2)
    {
        result = (int **)malloc(r1 * sizeof(int *));
        for (int i = 0; i < r1; i++)
        {
            result[i] = (int *)malloc(c1 * sizeof(int));
        }
        for (int i = 0; i < r1; i++)
        {
            for (int j = 0; j < c1; j++)
            {
                result[i][j] = matrix1[i][j] + matrix2[i][j];
            }
        }
    }
    else
    {
        printf("Both matrix should have equal no of rows and columns");
        return NULL;
    }
    return result;
}
int **subtractMatrix(int **matrix1, int **matrix2, int r1, int c1, int r2, int c2)
{
    int **result;
    if (r1 == r2 && c1 == c2)
    {
        result = (int **)malloc(r1 * sizeof(int *));
        for (int i = 0; i < r1; i++)
        {
            result[i] = (int *)malloc(c1 * sizeof(int));
        }
        for (int i = 0; i < r1; i++)
        {
            for (int j = 0; j < c1; j++)
            {
                result[j][i] = matrix1[i][j] - matrix2[i][j];
            }
        }
    }
    else
    {
        printf("Both matrix should have equal no of rows and columns");
        return NULL;
    }
    return result;
}
int **multiplyMatrix(int **matrix1, int **matrix2, int r1, int c1, int r2, int c2)
{
    int **result;
    if (c1 == r2)
    {
        result = (int **)malloc(r1 * sizeof(int *));
        for (int i = 0; i < r1; i++)
        {
            result[i] = (int *)malloc(c2 * sizeof(int));
        }
        for (int i = 0; i < c1; i++)
        {
            for (int j = 0; j < c1; j++)
            {
                for (int k = 0; k < c1; k++)
                {
                    result[j][i] += matrix1[j][k] * matrix2[k][i];
                }
            }
        }
    }
    else
    {
        printf("Number of column in 1st matrix should be equal to Number of rows in 2nd matrix");
        return NULL;
    }
    return result;
}
int **transpose(int **matrix1, int r1, int c1)
{
    int **result = (int **)malloc(c1 * sizeof(int *));
    for (int i = 0; i < c1; i++)
    {
        result[i] = (int *)malloc(r1 * sizeof(int));
    }
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c1; j++)
        {
            result[j][i] = matrix1[i][j];
        }
    }
    return result;
}
