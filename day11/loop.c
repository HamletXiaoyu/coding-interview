/* loop.c --- 
 * Filename: loop.c
 * Created: Wed Jun 13 20:57:35 2018 (+0800)
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

typedef struct Node{
    int data;
    struct Node *next;
}node;

node* init_list(int a[], int n)
{
    int i;
    node *p, *head, *q;
    for(i = 0; i < n; ++i) {
        node *nd = (node*)malloc(sizeof(node));
        nd->data = a[i];
        nd->next = NULL;
        if(i == 5)
            q = nd;
        if(i == 0){
            p = head = nd;
            continue;
        }
        p->next = nd;
        p = nd;
    }
    p->next = q;
    
    return head;
}

void find_loop_start(node* head)
{
    node *p, *q;
    p = head;
    q = head;
    while(q)
    {
        p = p->next;
        q = (q->next)->next;
        if(q == p)
            break;
    }
    p = head;
    while(p != q)
    {
        p = p->next;
        q = q->next;
    }
    printf("%d\n", p->data);
}

int main()
{

    int n = 10;
    int a[] = {3, 2, 1, 3, 5, 6, 2, 6, 3, 1};
    node *head = init_list(a, n);
    find_loop_start(head);
    return 0;
}
