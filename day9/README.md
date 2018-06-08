# 题目

Implement an algorithm to find the nth to last element of a singly linked list.

译文：

实现一个算法从一个单链表中返回倒数第n个元素。

# 解答

维护两个指针， 它们之间的距离为n。然后，我将这两个指针同步地在这个单链表上移动，保持它们的距离 为n不变。那么，当第二个指针指到空时，第一个指针即为所求。很tricky的方法， 将这个问题很漂亮地解决了。代码如下：

```c
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

```



# 题目

Implement an algorithm to delete a node in the middle of a single linked list, given only access to that node.

EXAMPLE

Input: the node ‘c’ from the linked list a->b->c->d->e Result: nothing is returned, but the new linked list looks like a->b->d->e

译文：

实现一个算法来删除单链表中间的一个结点，只给出指向那个结点的指针。

例子：

输入：指向链表a->b->c->d->e中结点c的指针

结果：不需要返回什么，得到一个新链表：a->b->d->e

# 解答

```c
void remove_node(node* c)
{
    if(c == NULL || c->next == NULL)
        return;
    node* p = c->next;
    c->data = p->data;
    c->next = p->next;
    free(p);
}

```

删除节点为最后一个节点时，需要特殊处理。