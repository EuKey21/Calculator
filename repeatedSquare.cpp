#include <iostream>
using namespace std;
using uint64 = unsigned long long int;
#define ARR_SIZE 100

void repeatedSquare(uint64 num, int mod, int index, int *arr);
void repeatedSquareHelper(uint64 num, int mod, int index, int start, int *arr);
int reduceIndex(int index, int *arr);
void reduceIndexHelper(int index, int *count, int *arr);
uint64 findPower(uint64 num, int index);
int findLargestTwo(int num);
uint64 findMod(int *arr, int mod);

void printArr(int *arr);

int main()
{
    
    int arr[ARR_SIZE] = {0};
    int index = 122569;
    int mod = 141923;
    reduceIndex(index, arr);
    repeatedSquare(86, mod, index, arr);
    cout << endl;
    printArr(arr);
    cout << endl << endl;
    cout << "Answer: " << findMod(arr, mod);
    return 0;
}


void repeatedSquare(uint64 num, int mod, int index, int *arr)
{
    int start = 1;
    int *ptr = arr;
    while(*(ptr+1) != -1) ptr++;
    repeatedSquareHelper(num, mod, index, start, ptr);
}

void repeatedSquareHelper(uint64 num, int mod, int index, int curr, int*ptr)
{
    if (curr > index)
    {
        return;
    }
    else
    {
        num %= mod;
        cout << curr << ". " << num << endl;
        if (curr == *ptr)
        {
            *ptr = num;
            ptr--;
        }
        repeatedSquareHelper(num*num, mod, index, curr*2, ptr);
    }
}

int reduceIndex(int index, int *arr)
{
    int count = 0;
    reduceIndexHelper(index, &count, arr);
    return count;
}

void reduceIndexHelper(int index, int *count, int *arr)
{
    if(index == 0)
    {
       arr[*count] = -1;
    }
    else
    {
        arr[*count] = findLargestTwo(index);
        (*count)++;
        reduceIndexHelper(index - findLargestTwo(index), count, arr);
    }
}

uint64 findPower(uint64 num, int index)
{
    if (index == 1)
        return num;
    else
        return num*findPower(num, index-1);
}

int findLargestTwo(int num)
{
    int result = 1;
    while(result < num) result *= 2;

    if (result == num) return result;
    else return result/2;
}

uint64 findMod(int *arr, int mod)
{
    int *p = arr;
    uint64 result = 1;
    while(*p != -1)
    {
        result = (result * *p) % mod;
        p++;
    }

    return result;
}

void printArr(int *arr)
{
    for(int i = 0; arr[i] != -1; i++)
        cout << arr[i] << '\t';
}
