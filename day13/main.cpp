// main.cpp --- 
// Filename: main.cpp
// Created: Mon Jun 18 19:52:56 2018 (+0800)
// 
// 
// Copyright Hamlet zheng.
// 
// 允许免费使用，拷贝，修改，发布，但在所有的拷贝上必须保留上述
// copyright部分和本使用声明部分，除非显示声明，copyright的持有者
// 不得作为再发布软件的广告。copyright的持有者对使用本软件的适用范围不做任何声明，
// 
// THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
// INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
// EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
// CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
// DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
// TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
// OF THIS SOFTWARE.
// 
// 

#include <iostream>
using namespace std;

const int MAX_INT = ~(1<<31);//2147483647

typedef struct node{
	int val, min;
}node;

class StackWithMin{
public:
	StackWithMin(int size=1000){
		buf = new node[size];
		buf[0].min = MAX_INT;
		cur = 0;
	}
	~StackWithMin(){
		delete[] buf;
	}
	void push(int val){
		buf[++cur].val = val;
		if(val<buf[cur-1].min) buf[cur].min = val;
		else buf[cur].min = buf[cur-1].min;
	}
	void pop(){
		--cur;
	}
	int top(){
		return buf[cur].val;
	}
	bool empty(){
		return cur==0;
	}
	int min(){
		return buf[cur].min;
	}

private:
	node *buf;
	int cur;
};

class stack{
public:
	stack(int size=1000){
		buf = new int[size];
		cur = -1;
	}
	~stack(){
		delete[] buf;
	}
	void push(int val){
		buf[++cur] = val;
	}
	void pop(){
		--cur;
	}
	int top(){
		return buf[cur];
	}
	bool empty(){
		return cur==-1;
	}

private:
	int *buf;
	int cur;
};

class StackWithMin1{
public:
	StackWithMin1(){

	}
	~StackWithMin1(){

	}
	void push(int val){
		s1.push(val);
		if(val<=min())
			s2.push(val);
	}
	void pop(){
		if(s1.top()==min())
			s2.pop();
		s1.pop();
	}
	int top(){
		return s1.top();
	}
	bool empty(){
		return s1.empty();
	}
	int min(){
		if(s2.empty()) return MAX_INT;
		else return s2.top();
	}

private:
	stack s1, s2;
};

int main(){
    StackWithMin1 mystack;
    for(int i=0; i<20; ++i)
        mystack.push(i);
    cout<<mystack.min()<<" "<<mystack.top()<<endl;
    mystack.push(-100);
    mystack.push(-100);
    cout<<mystack.min()<<" "<<mystack.top()<<endl;
    mystack.pop();
    cout<<mystack.min()<<" "<<mystack.top()<<endl;
    return 0;
}
