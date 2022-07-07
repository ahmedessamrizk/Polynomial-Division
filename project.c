#include <stdio.h>
#include <stdlib.h>
#include "math.h"

// Input of num
void Get_Num_Coeff (double* num_coeff, int *num_degree){
    printf("Enter the degree of numerator: ");
    scanf ("%d",&num_degree[0]);
    printf("------------------------------\n");
    int i;

    for (i = 0; i <= num_degree[0]; i++)
    {
        printf("Enter the coefficient of X^%d: ",num_degree[0] - i);
        scanf ("%lf", &num_coeff[i]);
        num_degree[i+1] = num_degree[i] - 1;
    }
    num_degree[i+1]++;
    printf("**********************************\n");
}
//Input of dum
void Get_den_Coeff (double* den_coeff , int *den_degree){

    printf("Enter the degree of denominator: ");
    scanf ("%d", &den_degree[0]);
    printf("------------------------------\n");
    int i;
    for (i=0; i <= den_degree[0]; i++)
    {
        printf("Enter the coefficient of X^%d: ", den_degree[0] - i);
        scanf ("%lf", &den_coeff[i]);
        den_degree[i+1] = den_degree[i]-1;
    }
    den_degree[i+1]++;
    printf("**********************************\n");
}

//Steps for long division
void Division(double* num_coeff, int* num_degree, double* den_coeff, int* den_degree, double* resultCoeff, int* resultDegree){
    static int i = 0;
    resultCoeff[i] = num_coeff[i] / den_coeff[0];
    resultDegree[i] = num_degree[i] - den_degree[0];
    i++;
}

void Multiplication(double* den_coeff, int* den_degree, double* result_coeff, int* result_degree, int* multiply_degree, double* multiply_Coeff){
    int i;
    static int j = 0;
    for(i=0; i <= den_degree[0]; i++)
    {
        multiply_Coeff[i] = result_coeff[j] * den_coeff[i];
        multiply_degree[i] = result_degree[j] + den_degree[i];
    }
    j++;
}

void Subtraction(double* multiply_Coeff, int* multiply_degree, double*  num_coeff, int* num_degree){
    int i,j;

    for(i = 0; i <= num_degree[0]; i++)
    {
        for(j = 0; j <= multiply_degree[0]; j++)
        {
            if(num_degree[i]== multiply_degree[j])
            {
                num_coeff[i] = num_coeff[i] - multiply_Coeff[j];
                break;
            }
        }
    }
}

int longDivision(double* num_coeff, double* den_coeff, int* num_degree, int* den_degree, double* result_coeff, int* result_degree){

    double multiply_Coeff[50]={0};
    int multiply_degree[50]= {0};

    int i = 0;
    int check = 0; // To check degree of numerator is greater than degree of denominator
    while (num_degree[i] >= den_degree[0])//check for degree of num to degree of den
    {
        Division(num_coeff, num_degree, den_coeff, den_degree, result_coeff, result_degree);
        Multiplication(den_coeff, den_degree, result_coeff, result_degree, multiply_degree, multiply_Coeff);
        Subtraction(multiply_Coeff, multiply_degree, num_coeff, num_degree);
        check++;
        i++;
    }
    if (check !=0 ) return 1;
    else return 0;

}
//Check in case of reminder
short check_Reminder(double* num_coeff, int* num_degree){
    int i;
    for(i = 0; i <= num_degree[0]; i++)
    {
        if(num_coeff[i] != 0) return 1;
    }
    return 0;
}
//Printing the result of the long division
void printResult(double* num_coeff, double* den_coeff, int* num_degree, int* den_degree, double* result_coeff, int* result_degree, short reminder, short check){
    printf("Result is: ");
    int i;
    for(i = 0; i <= result_degree[0]; i++)
    {
        if(result_coeff[i] != 0)
        {
            if(i >= 1 && result_coeff[i] >= 0) {printf(" + ");}
            printf("%0.2lf X^%d ",result_coeff[i], result_degree[i]);
        }
    }

    if (reminder == 1)
    {
        if(check != 0 ){printf(" + ");}
        printf("( ");
        for(i = 0; i <= num_degree[0]; i++)
        {
            if(num_coeff[i] !=0)
            {
                if(i >= 1 && num_coeff[i] >= 0 && num_coeff[i-1] !=0 ) {printf(" + ");}
                if(num_coeff[i] < 0)
                {
                    printf("- ");
                    num_coeff[i] *= -1;
                }
                    printf("%0.2lf X^%d ",num_coeff[i] , num_degree[i]);
            }
        }
        printf(")");

        printf(" / ");

        printf("( ");

        for(i = 0; i <= den_degree[0]; i++)
        {
            if(den_coeff[i] !=0 )
            {
                if(i >= 1 && den_coeff[i] >= 0 && den_coeff[i-1] !=0) {printf(" + ");}
                if(den_coeff[i] < 0)
                {
                    printf("- ");
                    den_coeff[i] *= -1;
                }
                    printf("%0.2lf X^%d ", den_coeff[i], den_degree[i]);
            }
        }
        printf(")");
    }
    printf("\n");
}

int main(){
    double num_coeff[50] = {0};
    double den_coeff[50]= {0};
    double result_coeff[50]= {0};
    int result_degree[50];
    int num_degree[50]= {0};
    int den_degree[50]= {0};

    Get_Num_Coeff (num_coeff, num_degree);
    Get_den_Coeff (den_coeff,den_degree);

    short check = longDivision(num_coeff, den_coeff, num_degree, den_degree, result_coeff, result_degree);
    short reminder = check_Reminder(num_coeff, num_degree);

    printResult(num_coeff, den_coeff, num_degree, den_degree, result_coeff, result_degree, reminder, check);

    return 0;
}
