/* main.c --- 
 * Filename: main.c
 * Created: Thu Jun  7 21:58:57 2018 (+0800)
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
    node *p, *head;
    for(i = 0; i < n; ++i) {
        node *nd = (node*)malloc(sizeof(node));
        nd->data = a[i];
        nd->next = NULL;
        if(i == 0){
            p = head = nd;
            continue;
        }
        p->next = nd;
        p = nd;
    }

    return head;
}

void remove_dulicate(node* head)
{
    if (NULL == head)
        return;
    node *p = head, *q = head->next;
    while(p) {
        while(q) {
            if(p->data == q->data) {
                node* tmp = q->next;
                q->data = tmp->data;
                q->next = tmp->next;
                free(tmp);
                continue;
            }
            q = q->next;
        }
        p = p->next;
        if (p!=NULL)
            q = p->next;
    }
}

void print_list(node* head)
{
    node *p = head;
    while(p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

void deinit(node* head)
{
    node *p = head;
    while(head) {
        p = head;
        head = head->next;
        free(p);
    }
}

int main()
{
    int a[] = {1, 2, 3, 4, 5, 3, 4, 6, 5, 7};
    node *head = init_list(a, 10);
    print_list(head);
    remove_dulicate(head);
    print_list(head);
    deinit(head);
    
    return 0;
}
