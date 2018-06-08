/* main.c --- 
 * Filename: main.c
 * Created: Fri Jun  8 21:48:00 2018 (+0800)
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

node* get_n_to_last(node* head, int n)
{
    node *p, *q;
    int len = 0, i;
    p = head;
    while(p){
        len++;
        p = p->next;
    }
    if(n > len || n < 0)
        return NULL;
    p = head;
    q = head;
    for(i = 0; i < n; ++i){
        p = p->next;
    }
    while(p){
        p = p->next;
        q = q->next;
    }
    return q;
}

void remove_node(node* c)
{
    if(c == NULL || c->next == NULL)
        return;
    node* p = c->next;
    c->data = p->data;
    c->next = p->next;
    free(p);
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

void print_list(node* head)
{
    node *p = head;
    while(p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    node *head = init_list(a, 10);
    node *p = get_n_to_last(head, 3);
    printf("%d\n", p->data);
    remove_node(head->next);
    print_list(head);
    deinit(head);
    
    return 0;
}
