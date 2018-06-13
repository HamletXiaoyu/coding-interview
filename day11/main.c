#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;

void printOrder(const int input[], int len, int output[])
{
    int temp;
    int i, j;
    int *p = (int*)malloc((len+1)*sizeof(int));
    for (i = 0; i< len; ++i)
        p[i] = input[i];
    
    for (i = 1; i < len; ++i)
        for (j = 0; j < len - i; ++j) {
            if (p[j] <= p[j+1]) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    int arr[1024] = {0};
    for (i=0; i<len; ++i) {
        for(j = 0; j<len; ++j){
            if(input[i] == p[j]&&arr[j] == 0) {
                output[i] = j;
                arr[j] = 1;
                break;
            }
        }
    }
    free(p);
}

int main()
{
    char str[256] = {0};
    gets(str);
    int input[256]={0};
    int output[256] = {0};
    int count = 0, len = strlen(str);

    for(int i=0; i<len; ++i)
    {
        if(str[i] >= '1' && str[i] <= '9')
        {
            input[count++] = int(str[i]-'0');
        }
    }
    printOrder(input, count, output);
    for(int i = 0; i<count; ++i)
    {
        cout<<output[i];
        if(i != count - 1)
            cout<<", ";
    }
    return 0;
}
