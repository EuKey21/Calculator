#include <stdio.h>
#include <stdlib.h>
typedef unsigned long long int uint64;

/***************************************************************************************
*****************************     Sum      *********************************************
***************************************************************************************/
typedef struct Sum{   
    uint64 power;
    uint64 expand;     
    struct Sum *next;   
}Sum;

Sum *push(uint64 input, Sum *sum)
{
    Sum *newNode    =   (Sum*)malloc(sizeof(Sum));
    newNode->power    =   input;
    if(sum == NULL) // initialize the first node
        newNode->next   =   NULL;
    else
        newNode->next   =   sum;
    return newNode;
}

Sum *pop(uint64 *output, Sum *sum)
{
    if(sum != NULL)
    {
        Sum *ptr = sum;
        sum = sum->next;
        *output = ptr->expand;
        free(ptr);
    }
    return sum;
}

/***************************************************************************************
****************************************************************************************
***************************************************************************************/


int findHighestPowerOfTwo(int num);
Sum *reduceNumIntoSumOfPowerOfTwo(int num, Sum *sum);
void repeatedSquare(uint64 num, int mod, Sum *sum);
uint64 repeatedSquare2(int mod, Sum *sum);

int main()
{
    Sum* sum = NULL;
    int num = 19, power = 43, mod = 713;
    
    sum = reduceNumIntoSumOfPowerOfTwo(power, sum);
    repeatedSquare(num, mod, sum);
    printf("The Answer is: %d", repeatedSquare2(mod, sum));

    return 0;
}

int findHighestPowerOfTwo(int num)
{
    // The highest power of 2 in 307 is 256 which is 2^8

    // 2^0 = 1
    int two = 1;

    while(two < num) two *= 2;

    if (two == num) return two;
    else return two/2;
}

Sum *reduceNumIntoSumOfPowerOfTwo(int num, Sum *sum)
{
    // 307 = 256 + 32  + 16  + 2   + 1
    // 307 = 2^8 + 2^5 + 2^4 + 2^1 + 2^0

    while(num != 0)
    {
        int powerOfTwo = findHighestPowerOfTwo(num);
        sum = push(powerOfTwo, sum);
        num -= powerOfTwo;
    }

    return sum;
}

void repeatedSquare(uint64 num, int mod, Sum *sum)
{
    Sum *ptr = sum;
    int power = 1;
    uint64 result = num;
    while(ptr != NULL)
    {
        result %= mod;
        if(ptr->power == power)
        {
            ptr->expand = result;
            ptr = ptr->next;
        }
        power *= 2;
        result *= result;
    }
}

uint64 repeatedSquare2(int mod, Sum *sum)
{
    uint64 num, result = 1;
    sum = pop(&num, sum);
    while(sum != NULL)
    {
        result = (result * num) % mod;
        sum = pop(&num, sum);
    }
    result = (result * num) % mod;
    return result;
}