# 题目

You have two numbers represented by a linked list, where each node contains a single digit. The digits are stored in reverse order, such that the 1’s digit is at the head of the list. Write a function that adds the two numbers and returns the sum as a linked list.

EXAMPLE

Input: (3 -> 1 -> 5), (5 -> 9 -> 2)

Output: 8 -> 0 -> 8

译文：

你有两个由单链表表示的数。每个结点代表其中的一位数字。数字的存储是逆序的， 也就是说个位位于链表的表头。写一函数使这两个数相加并返回结果，结果也由链表表示。

例子：(3 -> 1 -> 5), (5 -> 9 -> 2)

输入：8 -> 0 -> 8

# 解答

```c
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

```

