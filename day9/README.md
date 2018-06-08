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

