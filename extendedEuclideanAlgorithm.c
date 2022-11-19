/*
A simple program for small values of extended euclidean algorithm
*/
#include<stdio.h>

void extendedEuclideanAlgorithm(int num1, int num2);

int main()
{
    int num1, num2;
    printf("Enter two integers: ");
    scanf("%d%d", &num1, &num2);
    extendedEuclideanAlgorithm(num1, num2);
    return 0;
}

void extendedEuclideanAlgorithm(int num1, int num2)
{
    // x*a + y*b = gcd(a, b)
    
    typedef struct{
        int quotient;
        int remainder;
        int x;
        int y;
    }record;

    int a, b, i = 2;
    record table[1000]; //buffer

    // find the larger of the two nums
    if(num1 > num2)
    {
        a = num1;
        b = num2;
    }
    else
    {
        a = num2;
        b = num1;
    }

    table[0] = (record) {0, a, 1, 0};
    table[1] = (record) {0, b, 0, 1};

    printf("i\tquotient\tremainder\tx\ty\n");
    for(; i < 1000; i++)
    {
        table[i].quotient = table[i-2].remainder / table[i-1].remainder;
        table[i].remainder = table[i-2].remainder % table[i-1].remainder;
        if(table[i].remainder == 0) break; // end of algorithm
        table[i].x = table[i-2].x - table[i-1].x * table[i].quotient;
        table[i].y = table[i-2].y - table[i-1].y * table[i].quotient;

        printf("%d\t%d\t\t%d\t\t%d\t%d\n", i-1, table[i].quotient, table[i].remainder, table[i].x, table[i].y);
    }

    printf("\n\n%d * (%d) + %d * (%d) = %d", a, table[i-1].x, b, table[i-1].y, table[i-1].remainder);

}