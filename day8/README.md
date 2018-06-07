# 题目

Write code to remove duplicates from an unsorted linked list.

FOLLOW UP

How would you solve this problem if a temporary buffer is not allowed?

译文：

从一个未排序的链表中移除重复的项

进一步地，

如果不允许使用临时的缓存，你如何解决这个问题？

# 解答

如果不允许使用临时的缓存(即不能使用额外的存储空间)，那需要两个指针， 当第一个指针指向某个元素时，第二个指针把该元素后面与它相同的元素删除， 时间复杂度O(n^2 )，代码如下：

```c
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

```

