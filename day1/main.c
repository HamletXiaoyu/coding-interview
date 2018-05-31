/* main.c --- 
 * Filename: main.c
 * Author: Hamlet zheng
 * Created: Thu May 31 22:24:04 2018 (+0800)
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
#include <stdlib.h>
#include <string.h>

typedef int bool;  
#define false 0  
#define true  1

bool is_unique(char *str)
{
    int i;
    bool a[256];
    memset(a, 0, sizeof(a));
    int len = strlen(str);
    for(i = 0; i < len; ++i){
        if(a[(int)str[i]])
            return false;
        a[(int)str[i]] = true;
    }

    return true;
}

bool is_unique2(char* str)
{
    int a[8];
    int i;
    memset(a, 0, sizeof(a));
    int len = strlen(str);
    for(i = 0; i < len; ++i){
        int c = (int)str[i];
        int idx = c / 32, shift = c % 32;
        if(a[idx] & (1 << shift))
            return false;
        a[idx] |= (1 << shift);
    }

    return true;
}

int main()
{
    char *s1 = "iamzhengdf";
    char *s2 = "i am hamlet";
    printf("%s\n", is_unique(s1)==true?"true":"false");
    printf("%s\n", is_unique(s2)==true?"true":"false");
    printf("%s\n", is_unique2(s1)==true?"true":"false");
    printf("%s\n", is_unique2(s2)==true?"true":"false");
    return 0;
}
