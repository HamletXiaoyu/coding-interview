/* main.c --- 
 * Filename: main.c
 * Author: Hamlet
 * Created: Fri Jun  1 21:44:00 2018 (+0800)
 */

/* Copyright Hamlet.
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

void swap(char *a, char *b)
{
    char tmp = a[0];
    a[0] = b[0];
    b[0] = tmp;
}

void reverse(char *str)
{
    if(NULL == str)
        return;
    char *p = str, *q = str;

    while(*q)
        ++q;
    --q;
    while(p < q) {
        swap(p++, q--);
    }
}

int main()
{
    char str[] = "hello world";
    // do not write like this
    // char *str = "hello world";
    reverse(str);
    printf("%s\n", str);
    
    return 0;
}
