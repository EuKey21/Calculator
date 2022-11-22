/*
Compute the reminder for number raise to high power

For example, compute 52^307 mod 725
1.  Decompose 307 into a sum of two raised to various power 
        -> 307 = 256 + 32 + 16 + 2 + 1
2.  Using repeated the square to find the reminder for each power
        -> 52^1 mod 725 = 52
        -> 52^2 mod 725 = 529
        ...
        -> 52^256 mod 725 = 136
3.  Store the remainder assoicated to the power in the sum
        -> 136 571 36 529 52 from 256 32 16 2 1
4.  Multiple the number next in the list and find the remainder
        -> 136*571 mod 725 = 81
        -> 81*36 mod 725 = 16
        ...
5.  Obtain the final answer
        -> 52^307 mod 725 = 53
*/ 

#include <stdio.h>
#include <stdlib.h>
typedef unsigned long long int uint64;

/***************************************************************************************
*****************************     Sum      *********************************************
***************************************************************************************/
/// @brief store a list of expansion of power of two that sums to a number; Similar to stack
typedef struct Sum{   
    uint64 power;
    uint64 expand;     
    struct Sum *next;   
}Sum;

/// @brief add a number to the beginning of the list
/// @param input power
/// @param sum this pointer 
/// @return the new head pointer
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

/// @brief release the expansion in the head pointer then free the head pointer
/// @param output store the expansion
/// @param sum this pointer
/// @return the new head pointer
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

/// @brief find the expansion of the highest power of two that can go into the number 
/// @param num tagret number - power
/// @return expansion of the highest power of two
int findHighestPowerOfTwo(int num);

/// @brief find list of the power of two that sums to the number
/// @param num target number - power
/// @param sum store a list
/// @return the new head pointer
Sum *reduceNumIntoSumOfPowerOfTwo(int num, Sum *sum);

/// @brief repeated squaring the number then find the reminader 
/// @param num target number
/// @param mod module
/// @param sum store a list of the power of two that sums to the number
///            also store the (x^2 % mod) assoicated to that power 
void repeatedSquare(uint64 num, int mod, Sum *sum);

/// @brief multiply adjacent number in the sum then find the remainder until list in sum is exhausted
/// @param mod module
/// @param sum store a list of the power of two that sums to the number
uint64 findMod(int mod, Sum *sum);

int main()
{
    Sum* sum = NULL;
    int num = 52, power = 307, mod = 725;
    
    sum = reduceNumIntoSumOfPowerOfTwo(power, sum);
    repeatedSquare(num, mod, sum);
    printf("%d^%d mod %d = %d", num, power, mod, findMod(mod, sum));

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

uint64 findMod(int mod, Sum *sum)
{
    uint64 num, result = 1;
    do
    {
        sum = pop(&num, sum);
        result = (result * num) % mod;
    } while (sum != NULL);
    return result;
}