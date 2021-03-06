# 题目

In the classic problem of the Towers of Hanoi, you have 3 rods and N disks of different sizes which can slide onto any tower. The puzzle starts with disks sorted in ascending order of size from top to bottom (e.g., each disk sits on top of an even larger one). You have the following constraints:

- Only one disk can be moved at a time.
- A disk is slid off the top of one rod onto the next rod.
- A disk can only be placed on top of a larger disk.

Write a program to move the disks from the first rod to the last using Stacks

译文：

编程解决汉诺塔问题，使用数据结构栈(偷个懒，如果不知道汉诺塔是什么，请自行Google)

# 解答

汉诺塔是个非常经典的问题，讲递归时应该都会讲到它。如果我们没有递归的先验知识， 直接去解答这道题，常常会觉得不知道如何下手。用递归却可以非常优美地解决这个问题。

`使用递归的一个关键就是，我们先定义一个函数，不用急着去实现它， 但要明确它的功能。`

对于汉诺塔问题，我们定义如下函数原型：

```
void hanoi(int n, char src, char bri, char dst);

```

我们先不去关心它是怎么实现的，而是明确它的功能是：

```
将n个圆盘从柱子src移动到柱子dst，其中可以借助柱子bri(bridge)。
注：n个圆盘从上到下依次的标号依次为1到n，表示圆盘从小到大。
移动的过程中，不允许大圆盘放在小圆盘的上面。

```

OK，既然要用到递归，当然是在这个函数中还是用到这个函数本身， 也就是说，我们完成这个任务中的步骤还会用到hanoi这个操作，只是参数可能不一样了。 我们定义一组元组来表示三根柱子的状态：(src上的圆盘，bri上的圆盘，dst上的圆盘) 初始状态是：(1~n, 0, 0)表示src上有1到n共n个圆盘，另外两个柱子上没有圆盘。 目标状态是：(0, 0, 1~n)表示dst上有1到n共n个圆盘，另外两个柱子上没有圆盘。 由于最大的圆盘n最后是放在dst的最下面，且大圆盘是不能放在小圆盘上面的， 所以，一定存在这样一个中间状态：(n, 1~n-1, 0)，这样才能把最大的圆盘n 移动到dst的最下面。这时候，有人就会问，你怎么就想到这个中间状态而不是其它呢？ 好问题。因为，我现在手头上的工具(可用的函数)只有hanoi， 那我自然要想办法创造可以使用这个函数的情景，而不是其它情景。

- 初始状态是：(1~n, 0, 0)
- 中间状态是：(n, 1~n-1, 0)

从初始状态到中间状态使用操作hanoi(n-1, src, dst, bri)就可以到达了。即把n-1 个圆盘从src移动到bri，中间可以借助柱子dst。

接下来就是将圆盘n从src移动到dst了，这个可以直接输出：

```
cout<<"Move disk "<<n<<" from "<<src<<" to "<<dst<<endl;

```

这个操作后得到的状态是：

```
(0, 1~n-1, n)

```

然后再利用hanoi函数，将n-1个圆盘从bri移动到dst，中间可借助柱子src， hanoi(n-1, bri, src, dst)，操作后得到最终状态：

```
(0, 0, 1~n)

```

这些操作合起来就三行代码：

```
hanoi(n-1, src, dst, bri);
cout<<"Move disk "<<n<<" from "<<src<<" to "<<dst<<endl;
hanoi(n-1, bri, src, dst);

```

最后，我们还需要递归停止条件。什么时候递归结束呢？当n等于1时，既只有一个圆盘时， 直接把它从src移动到dst即可：

```
if(n==1){
	cout<<"Move disk "<<n<<" from "<<src<<" to "<<dst<<endl;
}

```

所以，完整的汉诺塔问题的递归解法如下：

```c++
#include <iostream>
using namespace std;

void hanoi(int n, char src, char bri, char dst){
	if(n==1){
		cout<<"Move disk "<<n<<" from "<<src<<" to "<<dst<<endl;
	}
	else{
		hanoi(n-1, src, dst, bri);
		cout<<"Move disk "<<n<<" from "<<src<<" to "<<dst<<endl;
		hanoi(n-1, bri, src, dst);
	}
}

int main(){
	int n = 3;
	hanoi(n, 'A', 'B', 'C');
	return 0;
}
```

汉诺塔的递归解法讲完了，可是这并不是题目要求的。题目要求用栈来解决这个问题。 递归解法其实也是用到了栈的，在每次递归调用自己的时候， 将中间的状态参数压入栈中。不过这些操作都是系统隐式进行的， 所以你不用去关心它具体是怎么压栈出栈的。如果我们要用栈自己来实现这个过程， 就不得不考虑这其中的细节了。

接下来，我们就显式地用栈来实现递归过程中，这些状态参数的压栈出栈过程。首先， 我们需要定义一个数据结构来保存操作过程中的参数。

```
struct op{
	int begin, end;
	char src, bri, dst;
	op(){

	}
	op(int pbegin, int pend, int psrc, int pbri, int pdst):begin(pbegin), end(pend), src(psrc), bri(pbri), dst(pdst){

	}
};

```

其中的5个参数表示，在柱子src上有一叠圆盘，标号从begin到end， 要将它们从src移动到dst，中间可借助柱子bri。end其实相当于递归解法中的n， src，bri，dst与递归解法中的对应。那为什么还要定义begin这个变量呢？ 为了判断柱子上是否只剩下一个盘子。如果begin等于end， 说明柱子上只剩下“最后”一个圆盘，可以进行移动。当然了， 用另外一个布尔变量来表示是否只剩下一个圆盘也是可以的，效果一样。 讲递归方法的时候，说到从初始状态到最终状态一共要经过以下几个状态：

```
(1~n, 0, 0)
(n, 1~n-1, 0)
(0, 1~n-1, n)
(0, 0, 1~n)

```

这些过程我们现在需要自己压栈出栈处理。压栈的时候不做处理，出栈时进行处理。因此， 压栈的时候需要与实际要操作的步骤相反。一开始，我们将最终想要完成的任务压栈。 听起来怪怪的，其实就是往栈中压入一组参数：

```
stack<op> st;
st.push(op(1, n, src, bri, dst));

```

这组参数表示，柱子src上有1~n个圆盘，要把它移动到dst上，可以借助柱子bri。 当栈st不为空时，不断地出栈，当begin和end不相等时，进行三个push操作 (对应上面四个状态，相邻状态对应一个push操作，使状态变化)， push与实际操作顺序相反(因为出栈时才进行处理，出栈时顺序就正确了)， 如果，begin与end相等，则剩下当前问题规模下的“最后”一个圆盘，直接打印移动方案， hanoi代码如下：

```c++
void hanoi(int n, char src, char bri, char dst){
	stack<op> st;
	op tmp;
	st.push(op(1, n, src, bri, dst));
	while(!st.empty()){
		tmp = st.top();
		st.pop();
		if(tmp.begin != tmp.end){
			st.push(op(tmp.begin, tmp.end-1, tmp.bri, tmp.src, tmp.dst));
			st.push(op(tmp.end, tmp.end, tmp.src, tmp.bri, tmp.dst));
			st.push(op(tmp.begin, tmp.end-1, tmp.src, tmp.dst, tmp.bri));
		}
		else{
			cout<<"Move disk "<<tmp.begin<<" from "<<tmp.src<<" to "<<tmp.dst<<endl;
		}

	}
}

```

完整代码如下：

```c++
#include <iostream>
#include <stack>
using namespace std;

struct op{
	int begin, end;
	char src, bri, dst;
	op(){

	}
	op(int pbegin, int pend, int psrc, int pbri, int pdst):begin(pbegin), end(pend), src(psrc), bri(pbri), dst(pdst){

	}
};
void hanoi(int n, char src, char bri, char dst){
	stack<op> st;
	op tmp;
	st.push(op(1, n, src, bri, dst));
	while(!st.empty()){
		tmp = st.top();
		st.pop();
		if(tmp.begin != tmp.end){
			st.push(op(tmp.begin, tmp.end-1, tmp.bri, tmp.src, tmp.dst));
			st.push(op(tmp.end, tmp.end, tmp.src, tmp.bri, tmp.dst));
			st.push(op(tmp.begin, tmp.end-1, tmp.src, tmp.dst, tmp.bri));
		}
		else{
			cout<<"Move disk "<<tmp.begin<<" from "<<tmp.src<<" to "<<tmp.dst<<endl;
		}

	}
}
int main(){
	int n = 3;
	hanoi(n, 'A', 'B', 'C');
	return 0;
}
```