# 13 C++ tips



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

## 题目13.6

原文：

What is name hiding in C++?

译文

C++中名字隐藏是什么？

## 解答

让我们通过一个例子来讲解C++中的名字隐藏。在C++中，如果一个类里有一个重载的方法， 你用另一个类去继承它并重写(覆盖)那个方法。你必须重写所有的重载方法， 否则未被重写的方法会因为名字相同而被隐藏，从而使它在派生类中不可见。

请看例子：

```
class FirstClass{
public:
    virtual void MethodA(int);
    virtual void MethodA(int, int);
};
void FirstClass::MethodA(int i){
    cout<<"ONE"<<endl;
}
void FirstClass::MethodA(int i, int j){
    cout<<"TWO"<<endl;
}

```

上面的类中有两个方法(重载的方法)，如果你想在派生类中重写一个参数的函数， 你可以这么做：

```
class SecondClass : public FirstClass{
public:
    void MethodA(int);
};
void SecondClass::MethodA(int i){
    cout<<"THREE"<<endl;
}

int main (){
    SecondClass a;
    a.MethodA(1);
    a.MethodA(1, 1);
    return 0;
}

```

上面的main函数中，第2个MethodA在编译时会报错，提示没有与之匹配的函数。 这是因为两个参数的MethodA在派生类中是不可见的，这就是名字隐藏。

名字隐藏与虚函数无关。所以不管基类中那两个函数是不是虚函数， 在这里都会发生名字隐藏。解决方法有两个。第一个是将2个参数的MethodA换一个名字， 那么它在派生类中就可见了。但我们既然重载了MethodA，说明它们只是参数不同， 而实际上应该是在做相同或是相似的事的。所以换掉名字并不是个好办法。因此， 我们一般采用第二种方法，在派生类中重写所有的重载函数。



## 题目

原文：

Why does a destructor in base class need to be declared virtual?

译文：

为什么基类中的析构函数要声明为虚析构函数？

## 解答

用对象指针来调用一个函数，有以下两种情况：

1. 如果是虚函数，会调用派生类中的版本。
2. 如果是非虚函数，会调用指针所指类型的实现版本。

析构函数也会遵循以上两种情况，因为析构函数也是函数嘛，不要把它看得太特殊。 当对象出了作用域或是我们删除对象指针，析构函数就会被调用。

当派生类对象出了作用域，派生类的析构函数会先调用，然后再调用它父类的析构函数， 这样能保证分配给对象的内存得到正确释放。

但是，如果我们删除一个指向派生类对象的基类指针，而基类析构函数又是非虚的话， 那么就会先调用基类的析构函数(上面第2种情况)，派生类的析构函数得不到调用。

请看例子：

```
class Base{
public:
    Base() { cout<<"Base Constructor"<<endl; }
    ~Base() { cout<<"Base Destructor"<<endl; }
};
class Derived: public Base{
public:
    Derived() { cout<<"Derived Constructor"<<endl; }
    ~Derived() { cout<<"Derived Destructor"<<endl; }
};
int main(){
    Base *p = new Derived();
    delete p;
    return 0;
}

```

输出是：

```
Base Constructor
Derived Constructor
Base Destructor

```

如果我们把基类的析构函数声明为虚析构函数，这会使得所有派生类的析构函数也为虚。 从而使析构函数得到正确调用。

将基类的析构函数声明为虚的之后，得到的输出是：

```
Base Constructor
Derived Constructor
Derived Destructor
Base Destructor

```

因此，如果我们可能会删除一个指向派生类的基类指针时，应该把析构函数声明为虚函数。 事实上，《Effective C++》中的观点是，只要一个类有可能会被其它类所继承， 就应该声明虚析构函数。

## 题目

原文：

Write a method that takes a pointer to a Node structure as a parameter and returns a complete copy of the passed-in data structure. The Node structure contains two pointers to other Node structures.

译文：

写一个函数，其中一个参数是指向Node结构的指针，返回传入数据结构的一份完全拷贝。 Node结构包含两个指针，指向另外两个Node。

## 解答

以下算法将维护一个从原结构的地址到新结构的地址的映射， 这种映射可以让程序发现之前已经拷贝的结点，从而不用为已有结点再拷贝一份。 由于结点中包含指向Node的指针，我们可以通过递归的方式进行结点复制。以下是代码：

```
typedef map<Node*, Node*> NodeMap;
Node* copy_recursive(Node *cur, NodeMap &nodeMap){
    if(cur == NULL){
        return NULL;
    }
    NodeMap::iterator i = nodeMap.find(cur);
    if (i != nodeMap.end()){
        // we’ve been here before, return the copy
        return i->second;
    }
    Node *node = new Node;
    nodeMap[cur] = node; // map current node before traversing links
    node->ptr1 = copy_recursive(cur->ptr1, nodeMap);
    node->ptr2 = copy_recursive(cur->ptr2, nodeMap);
    return node;
}
Node* copy_structure(Node* root){
    NodeMap nodeMap; // we will need an empty map
    return copy_recursive(root, nodeMap);
}
```



## 题目

原文：

Write a smart pointer (smart_ptr) class.

译文：

写一个智能指针类(smart_ptr)。

## 解答

比起一般指针，智能指针会自动地管理内存(释放不需要的内存)，而不需要程序员去操心。 它能避免迷途指针(dangling pointers)，内存泄漏(memory leaks)， 分配失败等情况的发生。智能指针需要为所有实例维护一个引用计数， 这样才能在恰当的时刻(引用计数为0时)将内存释放。

```
#include <iostream>
#include <cstdlib>
using namespace std;

template <typename T>
class SmartPointer{
public:
    SmartPointer(T* ptr){
        ref = ptr;
        ref_count = (unsigned*)malloc(sizeof(unsigned));
        *ref_count = 1;
    }
	
    SmartPointer(SmartPointer<T> &sptr){
        ref = sptr.ref;
        ref_count = sptr.ref_count;
        ++*ref_count;
    }
	
    SmartPointer<T>& operator=(SmartPointer<T> &sptr){
        if (this != &sptr) {
            if (--*ref_count == 0){
                clear();
                cout<<"operator= clear"<<endl;
            }
            
            ref = sptr.ref;
            ref_count = sptr.ref_count;
            ++*ref_count;
        }
        return *this;
    }
	
    ~SmartPointer(){
        if (--*ref_count == 0){
            clear();
            cout<<"destructor clear"<<endl;
        }
    }
	
    T getValue() { return *ref; }
    
private:
    void clear(){
        delete ref;
        free(ref_count);
        ref = NULL; // 避免它成为迷途指针
        ref_count = NULL;
    }
   
protected:	
    T *ref;
    unsigned *ref_count;
};

int main(){
    int *ip1 = new int();
    *ip1 = 11111;
    int *ip2 = new int();
    *ip2 = 22222;
    SmartPointer<int> sp1(ip1), sp2(ip2);
    SmartPointer<int> spa = sp1;
    sp2 = spa; // 注释掉它将得到不同输出
    return 0;
}

```

上述代码有一点值得注意一下，原书在赋值函数中， 并没有检查原指针的引用计数是否已经减为0，然后去释放原指针所指向的内存。 也就是原书的代码有可能导致内存泄漏。正确的做法应该是在把指针指向新的地址前， 将原来指向的引用计数减1，如果为0，说明这个指针在指向新的地址后， 原来指向的内存将不再有指针指向它。那么我们就要把它释放， 否则内存就会在你眼皮底下泄漏的哦。

上述代码main函数中，sp2 = spa这一句如果注释掉，我们得到的输出是：

```
destructor clear
destructor clear

```

说明内存的清理都是在main函数退出调用析构函数时。如果我们没有注释掉那行代码， 输出是：

```
operator= clear
destructor clear

```

说明当sp2指向新的内存后，原来的内存由于没有指针指向它而被释放掉。 另一块内存则是在main函数退出时释放的。

如果像CTCI书上所写，当sp2 = spa这一句没有注释掉时，输出是：

```
destructor clear

```

也就是只释放了一块内存(ip1指向的内存)，另一块由于没有指针指向它， 而又不及时清理，结果泄漏了。