/* main.c --- 
 * Filename: main.c
 * Created: Tue Jun  5 21:12:57 2018 (+0800)
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

char *replace(char *str)
{
    int len, i, j, n;
    char *p = NULL;
    if (NULL == str)
        return NULL;
    len = strlen(str);
    n = 1;
    for (i = 0; i < len; ++i) {
        if (str[i] == ' ')
            ++n;
    }
    p = (char*)malloc((len+2*n+1) * sizeof(char));
    memset(p, 0, (len+2*n+1) * sizeof(char));
    for (j = 0, i = 0; i < len; ++i) {
        if (str[i] != ' ')
            p[j++] = str[i];
        else {
            p[j] = '%';
            p[j+1] = '2';
            p[j+2] = '0';
            j += 3;
        }
    }

    return p;
}


int main()
{
    char *s = "hello world! yeah";
    printf("%s\n", replace(s));
    return 0;
}
