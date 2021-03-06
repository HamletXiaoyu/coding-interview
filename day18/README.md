## 题目

原文：

Implement a function to check if a tree is balanced. For the purposes of this question, a balanced tree is defined to be a tree such that no two leaf nodes differ in distance from the root by more than one.

译文：

实现一个函数检查一棵树是否平衡。对于这个问题而言， 平衡指的是这棵树任意两个叶子结点到根结点的距离之差不大于1。

## 解答

对于这道题，要审清题意。它并不是让你判断一棵树是否为平衡二叉树。 平衡二叉树的定义为：它是一棵空树或它的左右两个子树的高度差的绝对值不超过1， 并且左右两个子树都是一棵平衡二叉树。 而本题的平衡指的是这棵树任意两个叶子结点到根结点的距离之差不大于1。 这两个概念是不一样的。例如下图，它是一棵平衡二叉树，但不满足本题的平衡条件。 (叶子结点f和l到根结点的距离之差等于2，不满足题目条件)

![tree](./tree.png)

对于本题，只需要求出离根结点最近和最远的叶子结点， 然后看它们到根结点的距离之差是否大于1即可。

假设只考虑二叉树，我们可以通过遍历一遍二叉树求出每个叶子结点到根结点的距离。 使用中序遍历，依次求出从左到右的叶子结点到根结点的距离，递归实现。

```c++
int d = 0, num = 0, dep[maxn];
void getDepth(Node *head){
	if(head == NULL) return;
	++d;
	getDepth(head->lchild);
	if(head->lchild == NULL && head->rchild == NULL)
		dep[num++] = d;
	getDepth(head->rchild);
	--d;
}

```

求出所有叶子结点到根结点的距离后，再求出其中的最大值和最小值， 然后作差与1比较即可。此外，空树认为是平衡的。代码如下：

```c++
bool isBalance(Node *head){
	if(head == NULL) return true;
	getDepth(head);
	int max = dep[0], min = dep[0];
	for(int i=0; i<num; ++i){
		if(dep[i]>max) max = dep[i];
		if(dep[i]<min) min = dep[i];
	}
	if(max-min > 1) return false;
	else return true;
}

```

完整代码如下：

```c++
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

const int maxn = 100;
struct Node{
	int key;
	Node *lchild, *rchild, *parent;
};
Node *head, *p, node[maxn];
int cnt;

void init(){
	head = p = NULL;
	memset(node, '\0', sizeof(node));
	cnt = 0;
}
void insert(Node* &head, int x){
	if(head == NULL){
		node[cnt].key = x;
		node[cnt].parent = p;
		head = &node[cnt++];
		return;
	}
	p = head;
	if(x < head->key)
		insert(head->lchild, x);
	else
		insert(head->rchild, x);
}
int d = 0, num = 0, dep[maxn];
void getDepth(Node *head){
	if(head == NULL) return;
	++d;
	getDepth(head->lchild);
	if(head->lchild == NULL && head->rchild == NULL)
		dep[num++] = d;
	getDepth(head->rchild);
	--d;
}
bool isBalance(Node *head){
	if(head == NULL) return true;
	getDepth(head);
	int max = dep[0], min = dep[0];
	for(int i=0; i<num; ++i){
		if(dep[i]>max) max = dep[i];
		if(dep[i]<min) min = dep[i];
	}
	if(max-min > 1) return false;
	else return true;
}
int main(){
	init();
	int a[] = {
		5, 3, 8, 1, 4, 7, 10, 2, 6, 9, 11, 12
	};
	for(int i=0; i<12; ++i)
		insert(head, a[i]);
	cout<<isBalance(head)<<endl;
	return 0;
}

```