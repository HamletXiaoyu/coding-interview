## 题目

原文：

Write a method to print the last K lines of an input file using C++.

译文：

用C++写一个函数，打印输入文件的最后k行。

## 解答

一种方法是打开文件两次，第一次计算文件的行数N，第二次打开文件，跳过N-K行， 然后开始输出。如果文件很大，这种方法的时间开销会非常大。

我们希望可以只打开文件一次，就可以输出文件中的最后k行。 我们可以开一个大小为k的字符串数组，然后将文件中的每一行循环读入。 怎么样循环读入呢？就是将k行字符串保存到字符串数组后， 在读第k+1时，将它保存到数组的第1个元素，依次类推。这样一来， 实际上文件中第i行的字符串会被保存到数组的第i%k的位置。最后当文件读完时， 数组保存的就是最后k行的字符串。当然了，它的开始位置不是0，而是i%k。

代码如下：

```
#include <iostream>
#include <fstream>
using namespace std;

void printLastKLines(ifstream &fin, int k){
    string line[k];
    int lines = 0;
    string tmp;
    while(getline(fin, tmp)){
        line[lines%k] = tmp;
        ++lines;
    }
    int start, cnt;
    if(lines < k){
        start = 0;
        cnt = lines;
    }
    else{
        start = lines%k;
        cnt = k;
    }
    for(int i=0; i<cnt; ++i)
        cout<<line[(start+i)%k]<<endl;
}
int main(){
    ifstream fin("13.1.in");
    int k = 4;
    printLastKLines(fin, k);
    fin.close();
    return 0;
}

```

注意上面函数中的while循环，不能写成下面的样子：

```
while(!fin.eof()){
	getline(fin, line[lines%k]);
	++lines;
}

```

eof()函数是在fin中已经没有内容可输入时，才被置为true。 如果使用上面的循环，getline在读入最后一行后，由于这一行仍然是有内容的， 所以eof()返回的仍然为false，表示还没到文件结尾。然后会再进入循环一次， 这时getline读入一个空串，已经没有内容可输入，eof()返回true而退出循环。 结果就是因为多读入一个空串，line数组中保存的是最后k-1行再加一个空串， 两个字：错误。如果我们将循环改成printLastKLines中的样子，那就没问题了。

## 题目

原文：

Compare and contrast a hash table vs. an STL map. How is a hash table implemented?If the number of inputs is small, what data structure options can be used instead of a hash table?

译文：

对比哈希表和STL map。哈希表是怎么实现的？如果输入数据规模不大， 我们可以使用什么数据结构来代替哈希表。

## 解答

**对比哈希表和STL map**

在哈希表中，实值的存储位置由其键值对应的哈希函数值决定。因此， 存储在哈希表中的值是无序的。在哈希表中插入元素和查找元素的时间复杂度都是O(1)。 (假设冲突很少)。实现一个哈希表，冲突处理是必须要考虑的。

对于STL中的map，键/值对在其中是根据键进行排序的。它使用一根红黑树来保存数据， 因此插入和查找元素的时间复杂度都是O(logn)。而且不需要处理冲突问题。 STL中的map适合以下情况使用：

1. 查找最小元素
2. 查找最大元素
3. 有序地输出元素
4. 查找某个元素，或是当元素找不到时，查找比它大的最小元素

**哈希表是怎么实现的**

1. 首先需要一个好的哈希函数来确保哈希值是均匀分布的。比如：对大质数取模
2. 其次需要一个好的冲突解决方法：链表法(chaining，表中元素比较密集时用此法)， 探测法(probing，开放地址法，表中元素比较稀疏时用此法)。
3. 动态地增加或减少哈希表的大小。比如，(表中元素数量)/(表大小)大于一个阈值时， 就增加哈希表的大小。我们新建一个大的哈希表，然后将旧表中的元素值， 通过新的哈希函数映射到新表。

**如果输入数据规模不大，我们可以使用什么数据结构来代替哈希表。**

你可以使用STL map来代替哈希表，尽管插入和查找元素的时间复杂度是O(logn)， 但由于输入数据的规模不大，因此这点时间差别可以忽略不计.



## 题目

原文：

How do virtual functions work in C++?

译文：

C++中的虚函数是如何工作的？

## 解答

虚函数依赖虚函数表进行工作。如果一个类中，有函数被关键词virtual进行修饰， 那么一个虚函数表就会被构建起来保存这个类中虚函数的地址。同时， 编译器会为这个类添加一个隐藏指针指向虚函数表。如果在派生类中没有重写虚函数， 那么，派生类中虚表存储的是父类虚函数的地址。每当虚函数被调用时， 虚表会决定具体去调用哪个函数。因此，C++中的动态绑定是通过虚函数表机制进行的。

当我们用基类指针指向派生类时，虚表指针vptr指向派生类的虚函数表。 这个机制可以保证派生类中的虚函数被调用到。

```
class Shape{
public:
    int edge_length;
    virtual int circumference () {
        cout<<"Circumference of Base Class\n";
        return 0;
    }
};
class Triangle: public Shape{
public:
    int circumference () {
        cout<<"Circumference of Triangle Class\n";
        return 3 * edge_length;
    }
};
int main(){
    Shape *x = new Shape();
    x->circumference(); // prints “Circumference of Base Class”
    Shape *y = new Triangle();
    y->circumference(); // prints “Circumference of Triangle Class”
    return 0;
}

```

在上面的例子中，circumference是Shape类中的虚函数，因此在它的派生类中， 它也是虚函数。C++中非虚函数的调用是在编译期静态绑定的， 而虚函数的调用则是在执行时才进行动态绑定。

## 题目

原文：

What is the difference between deep copy and shallow copy? Explain how you would use each.

译文：

深拷贝和浅拷贝的区别是什么？你会如何使用它们？

## 解答

浅拷贝并不复制数据，只复制指向数据的指针，因此是多个指针指向同一份数据。 深拷贝会复制原始数据，每个指针指向一份独立的数据。通过下面的代码， 可以清楚地看出它们的区别：

```
struct Test{
    char *ptr;
};
void shallow_copy(Test &src, Test &dest){
    dest.ptr = src.ptr;
}
void deep_copy(Test &src, Test &dest){
    dest.ptr = (char*)malloc(strlen(src.ptr) + 1);
    memcpy(dest.ptr, src.ptr);
}

```

浅拷贝在构造和删除对象时容易产生问题，因此使用时要十分小心。如无必要， 尽量不用浅拷贝。当我们要传递复杂结构的信息，而又不想产生另一份数据时， 可以使用浅拷贝，比如引用传参。浅拷贝特别需要注意的就是析构时的问题， 当多个指针指向同一份内存时，删除这些指针将导致多次释放同一内存而出错。

实际情况下是很少使用浅拷贝的，而智能指针是浅拷贝概念的增强。 比如智能指针可以维护一个引用计数来表明指向某块内存的指针数量， 只有当引用计数减至0时，才真正释放内存。

大部分时候，我们用的是深拷贝，特别是当拷贝的结构不大的时候。



## 题目

原文：

What is the significance of the keyword “volatile” in C?

译文：

谈谈C语言关键字”volatile”的意义(或重要性)？

## 解答

volatile的意思是”易变的”，因为访问寄存器比访问内存要快得多， 所以编译器一般都会做减少存取内存的优化。volatile 这个关键字会提醒编译器，它声明的变量随时可能发生变化(在外部被修改)， 因此，与该变量相关的代码不要进行编译优化，以免出错。

声明一个volatile变量：

```
volatile int x;
int volatile x;

```

声明一个指针，指向volatile型的内存(即指针指向的内存中的变量随时可能变化):

```
volatile int *x;
int volatile *x

```

声明一个volatile指针，指向非volatile内存:

```
int* volatile x;

```

声明一个volatile指针，指向volatile内存(即指针和指针所指物都随机可能变化):

```
volatile int * volatile x;
int volatile * volatile x;

```

volatile在声明上的使用和const是一样的。volatile在*号左边， 修饰的是指针所指物；在*号右边修饰的是指针。

用volatile修饰的变量相关的代码不会被编译器优化，那么它有什么好处呢？ 来看下面的例子：

```
int opt = 1;
void Fn(void){
	start:
		if (opt == 1) goto start;
		else break;
}

```

上述代码看起来就是一个无限循环的节奏，编译器可能会将它优化成下面的样子：

```
void Fn(void){
	start:
		int opt = 1;
		if (true)
			goto start;
}

```

由于程序中并没有对opt进行修改，因此将if中的条件设置为恒真。这样一来， 就陷入了无限循环中。但是，如果我们给opt加上volatile修饰， 表明外部程序有可能对它进行修改。那么，编译器就不会做上述优化， 上述程序在opt被外部程序修改后将跳出循环。此外， 当我们在一个多线程程序中声明了一些全局变量，且任何一个线程都可以修改这些变量时， 关键字volatile也会派上用场。在这种情况下， 我们就要明确地告诉编译器不要对这些全局变量的相关代码做优化。

