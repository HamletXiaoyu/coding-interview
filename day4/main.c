/* main.c --- 
 * Filename: main.c
 * Created: Mon Jun  4 21:06:29 2018 (+0800)
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define  bool int
#define  true  1
#define  false 0

bool is_anagram(char *str1, char *str2)
{
    if (str1 == NULL || str2 == NULL)
        return false;
    if (strlen(str1) != strlen(str2))
        return false;

    int len = strlen(str1), i;
    int c[256];
    memset(c, 0, sizeof(c));
    for (i = 0; i < len; ++i) {
        ++c[(int)str1[i]];
        --c[(int)str2[i]];
    }

    for (i = 0; i < 256; ++i) {
        if (c[i] != 0)
            return false;
    }

    return true;
}

int main()
{
    char *str1 = "asdfghjkl";
    char *str2 = "ghjklasdf";
    printf("is anagram %s\n", is_anagram(str1, str2) == 1 ? "true" : "false");
    return 0;
}
