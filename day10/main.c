/* main.c --- 
 * Filename: main.c
 * Created: Mon Jun 11 21:26:30 2018 (+0800)
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

node* add_list(node* head1, node* head2)
{
    if(NULL == head1)
        return head2;
    if(NULL == head1)
        return head2;

    node* head = NULL, *p = head1, *q = head2, *tail = NULL;
    int ten = 0;
    while(p!=NULL && q!=NULL){
        node *c = (node*)malloc(sizeof(node));
        c->data = (p->data + q->data + ten)%10;
        ten = (p->data + q->data)/10;
        c->next = NULL;
        if (head == NULL)
            head = tail = c;
        else{
            tail->next = c;
            tail = c;
        }
        p = p->next;
        q = q->next;
    }
    while(p!=NULL){
        node *c = (node*)malloc(sizeof(node));
        c->data = (p->data + ten) % 10;
        ten = (p->data + ten) / 10;
        c->next = NULL;
        tail->next = c;
        tail = c;
        p = p->next;
    }
    while(q!=NULL){
        node *c = (node*)malloc(sizeof(node));
        c->data = (q->data + ten) % 10;
        ten = (q->data + ten) / 10;
        c->next = NULL;
        tail->next = c;
        tail = c;
        q = q->next;
    }

    return head;
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
    int n = 4;
    int a[] = {
        1, 2, 9, 3
    };
    int m = 3;
    int b[] = {
        9, 9, 2
    };

    node* p = init_list(a, n);
    node* q = init_list(b, m);
    node* result = add_list(p, q);
    //0->2->2->4
    print_list(result);

    return 0;
}
