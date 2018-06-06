/* main.c --- 
 * Filename: main.c
 * Created: Wed Jun  6 21:07:07 2018 (+0800)
 */

/* Copyright Hamlet zheng.
 * 
 * 允许免费使用，拷贝，修改，发布，但在所有的拷贝上必须保留上述
 * copyright部分和本使用声明部分，除非显示声明，copyright的持有者
 * 不得作为再发布软件的广告。copyright的持有者对使用本软件的适用范围不做任何声明，
 * 
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#include <stdio.h>

void swap(int *a, int *b)
{
    a[0] ^= b[0];
    b[0] ^= a[0];
    a[0] ^= b[0];
}

void transpose(int a[][4], int n)
{
    int i, j;
    for(i = 0; i < n; ++i){
        for(j = i+1; j < n; ++j){
            swap(&a[i][j], &a[j][i]);
        }
    }

    for(i = 0; i < n/2; ++i){
        for(j = 0; j < n; ++j)
            swap(&a[i][j], &a[n-1-i][j]);
    }
}

void print(int a[][4], int n)
{
    int i, j;
    for(i = 0; i < n; ++i){
        for(j = 0; j < 4; ++j)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}

int main()
{
    int arr[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    print(arr, 4);
    transpose(arr, 4);
    print(arr, 4);
    
    return 0;
}
