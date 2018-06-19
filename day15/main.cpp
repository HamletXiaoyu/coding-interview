// main.cpp --- 
// Filename: main.cpp
// Created: Tue Jun 19 21:44:19 2018 (+0800)
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
