# 第5章



## 题目

原文：

You are given two 32-bit numbers, N and M, and two bit positions, i and j. Write a method to set all bits between i and j in N equal to M (e.g., M becomes a substring of N located at i and starting at j).

EXAMPLE:

Input: N = 10000000000, M = 10101, i = 2, j = 6

Output: N = 10001010100

译文：

给定两个32位的数，N和M，还有两个指示位的数，i和j。 写程序使得N中第i位到第j位的值与M中的相同(即：M变成N的子串且位于N的第i位和第j位之间)

例子：

输入: N = 10000000000, M = 10101, i = 2, j = 6

输出: N = 10001010100

## 解答

方案1：先将N中第0位到第i位保存下来(左闭右开：[0, i))，记作ret， 然后将N中第0位到第j位全清0([0, j])，通过向右移动j+1位然后再向左移动j+1位得到。 最后用上面清0后的值或上(m«i)再或上ret即可。

代码如下：

```c++
int update_bits(int n, int m, int i, int j){
    int ret = (1 << i) -1;
    ret &= n;
    return ((n>>(j+1)) << (j+1)) | (m<<i) | ret;
}

```

方案2：用一个左边全为1，中间一段全为0(这段的长度与m长度一样)， 右边全为1的掩码mask去和n按位与，得到的值是将n中间一段清0的结果。 然后再与m左移i位后按位或，得到最终结果。

代码如下：

```c++
int update_bits1(int n, int m, int i, int j){
    int max = ~0;	//全为1
    int left = max - ((1 << j+1) - 1);
    int right = ((1 << i) -1);
    int mask = left | right;
    return (n & mask) | (m << i);
}

```

C++中关于位操作，记录几点需要注意的地方：

- 一个有符号数，如果它的最高位为1，它右移若干位后到达位置i， 那么最高位到第i位之间全是1，例如：

```
int a = 1;
a <<= 31;	//a:1后面带31个0
a >>= 31;	//a:32个1，即-1
cout<<a<<endl;	//输出-1(写下负号，然后取反加1)

```

- 一个无符号数，如果它的最高位为1，它右移若干位后到达位置i， 那么最高位到第i位之间全是0，例如：

```
unsigned int a = 1;
a <<= 31;	//a:1后面带31个0
a >>= 31;	//a:31个0后面带一个1，即1
cout<<a<<endl;	//输出1

```

- 无论是有符号数还是无符号数，左移若干位后，原来最低位右边新出现的位全为0
- 一个有符号的正数，它的最高位为0，如果因为左移使得最高位为1，那么它变为负数， 而后无论怎样右移，它都还是负数。除非因为再次左移使最高位变为0，那么它变回正数。
- int的最大值：~(1«31)，即0后面跟31个1
- int的最小值：1«31，即1后面跟31个0
- unsigned int最大值：~0，即32个1
- unsigned int最小值：0
- 其它数据类型与int类似，只是位长不一样。

完整代码如下：

```c++
#include <iostream>
#include <vector>
using namespace std;

void print_binary(int n){
    vector<int> v;
    int len = 8 * sizeof(int);
    int mask = 1;
    while(len--){
        if(n&mask) v.push_back(1);
        else v.push_back(0);
        mask <<= 1;
    }
    while(!v.empty()){
        cout<<v.back();
        v.pop_back();
    }
    cout<<endl;
}
int update_bits(int n, int m, int i, int j){
    int ret = (1 << i) -1;
    ret &= n;
    return ((n>>(j+1)) << (j+1)) | (m<<i) | ret;
}
int update_bits1(int n, int m, int i, int j){
    int max = ~0;
    int left = max - ((1 << j+1) - 1);
    int right = ((1 << i) -1);
    int mask = left | right;
    return (n & mask) | (m << i);
}
int main(){
    int n = 1<<10, m = 21;
    int ans = update_bits(n, m, 2, 6);
    print_binary(n);
    print_binary(m);
    print_binary(ans);
    return 0;
}
```


## 题目

原文：

Given a (decimal - e.g. 3.72) number that is passed in as a string, print the binary representation.If the number can not be represented accurately in binary, print “ERROR”.

译文：

给定一个字符串类型(string)表示的小数，打印出它的二进制表示。 如果这个数无法精确地表示为二进制形式，输出”ERROR”。

## 解答

整数部分通过不断地对2取余然后除以2来得到其二进制表示， 或是不断地和1按位与然后除以2得到其二进制表示。 小数部分则通过不断地乘以2然后与1比较来得到其二进制表示。 小数部分转化为二进制，通过乘以2然后与1比较，大于等于1则该位为1，并且该值减去1； 否则该位为0。不断地通过这种操作最终能使该小数部分的值变为0的，即可精确表示。 否则将无法用有限的位数来表示这个小数部分。我们可以设定一个长度，比如说32， 在32位之内还无法精确地表示这个小数部分的，我们就认为它无法精确表示了。

代码如下：

```c++
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

string print_binary(string val){
    int pos = val.find('.', 0);
    int intpart = atoi(val.substr(0, pos).c_str());
    double decpart = atof(val.substr(pos, val.length()-pos).c_str());
    string intstr = "", decstr = "";
    while(intpart > 0){
        if(intpart&1) intstr = "1" + intstr;
        else intstr = "0" + intstr;
        intpart >>= 1;
    }
    while(decpart > 0){
        if(decstr.length() > 32) return "ERROR";
        decpart *= 2;
        if(decpart >= 1){
            decstr += "1";
            decpart -= 1;
        }
        else
            decstr += "0";
    }
    return intstr + "." + decstr;
}
int main(){
    string val = "19.25";
    cout<<print_binary(val)<<endl;
    return 0;
}
```



## 题目

原文：

Given an integer, print the next smallest and next largest number that have the same number of 1 bits in their binary representation.

译文：

给定一个整数x，找出另外两个整数，这两个整数的二进制表示中1的个数和x相同， 其中一个是比x大的数中最小的，另一个是比x小的数中最大的。

## 解答

对于这道题，我们先完成一个最朴素最直接的版本，以保证其正确性。 这个版本可以作为其它版本的验证工具。

什么方法是最直接的呢？给定一个数x，计算出它的二进制表示中1的个数为num， 然后x不断加1并计算其二进制表示中1的个数，当它再次等于num时， 就找到了比x大且二进制表示中1的个数相同的最小的数。类似地， 可以找到比x小且二进制表示中1的个数相同的最大的数，只不过x变为不断减1而已。

代码如下：

```
int next(int x){
    int max_int = ~(1<<31);
    int num = count_one(x);
    if(num == 0 || x == -1) return -1;
    for(++x; count_one(x) != num && x < max_int; ++x);
    if(count_one(x) == num) return x;
    return -1;    
}
int previous(int x){
    int min_int = (1<<31);
    int num = count_one(x);
    if(num == 0 || x == -1) return -1;
    for(--x; count_one(x) != num && x > min_int; --x);
    if(count_one(x) == num) return x;
    return -1;	
}

```

count_one函数的功能是计算一个数的二进制表示中1的个数，这个要怎么实现呢？ 一种方法是通过不断地移位判断最低位是否为1然后计数器累加，代码如下：

```
int count_one(int x){
    int cnt = 0;
    for(int i=0; i<32; ++i){
        if(x & 1) ++cnt;
        x >>= 1;
    }
    return cnt;
}

```

这里for循环可否换成`while(x > 0)`呢，如果x恒为正数是没问题的，可是如果x为负数， 那么x是无法通过不断地右移变为非负数的。所以这里用for循环比较保险。

这种方法非常直观，不过还有更高效更优美的方法。 这种方法先将相邻的位包含的1的个数相加，然后将相邻每2位包含的1的个数相加， 再然后将相邻每4位包含的1的个数相加……最后即可统计出一个数中包含的1的个数。 代码中大部分操作都是位操作，执行起来非常高效。

代码如下：

```
int count_one(int x){
    x = (x & (0x55555555)) + ((x >> 1) & (0x55555555));
    x = (x & (0x33333333)) + ((x >> 2) & (0x33333333));
    x = (x & (0x0f0f0f0f)) + ((x >> 4) & (0x0f0f0f0f));
    x = (x & (0x00ff00ff)) + ((x >> 8) & (0x00ff00ff));
    x = (x & (0x0000ffff)) + ((x >> 16) & (0x0000ffff));
    return x;
}

```

好了，接下来考虑除了朴素方案外，有没有更高效的方案。假设给定的数的二进制表示为： 1101110，我们从低位看起，找到第一个1，从它开始找到第一个0，然后把这个0变为1， 比这个位低的位全置0，得到1110000，这个数比原数大，但比它少了两个1， 直接在低位补上这两个1，得到，1110011，这就是最终答案。 我们可以通过朴素版本来模拟这个答案是怎么得到的：

```
1101110->1101111->1110000->1110001->1110010->1110011

```

接下来，我们来考虑一些边界情况，这是最容易被忽略的地方(感谢细心的读者)。 假设一个32位的整数， 它的第31位为1，即：0100..00，那么按照上面的操作，我们会得到1000..00， 很不幸，这是错误的。因为int是有符号的，意味着我们得到了一个负数。 我们想要得到的是一个比0100..00大的数，结果得到一个负数，自然是不对的。 事实上比0100..00大的且1的个数和它一样的整数是不存在的，扩展可知， 对于所有的0111..，都没有比它们大且1的个数和它们一样的整数。对于这种情况， 直接返回-1。-1的所有二进制位全为1，不存在一个数说1的个数和它一样还比它大或小的， 因此适合作为找不到答案时的返回值。

另一个边界情况是什么呢？就是对于形如11100..00的整数，它是一个负数， 比它大且1的个数相同的整数有好多个，最小的当然是把1都放在最低位了：00..0111。

代码如下：

```
int next1(int x){
    int xx = x, bit = 0;
    for(; (x&1) != 1 && bit < 32; x >>= 1, ++bit);
    for(; (x&1) != 0 && bit < 32; x >>= 1, ++bit);
    if(bit == 31) return -1; //011.., none satisify
    x |= 1;
    x <<= bit; // wtf, x<<32 != 0,so use next line to make x=0
    if(bit == 32) x = 0; // for 11100..00
    int num1 = count_one(xx) - count_one(x);
    int c = 1;
    for(; num1 > 0; x |= c, --num1, c <<= 1);
    return x;
}

```

类似的方法可以求出另一个数，这里不再赘述。代码如下：

```
int previous1(int x){
    int xx = x, bit = 0;
    for(; (x&1) != 0 && bit < 32; x >>= 1, ++bit);
    for(; (x&1) != 1 && bit < 32; x >>= 1, ++bit);
    if(bit == 31) return -1; //100..11, none satisify
    x -= 1;
    x <<= bit;
    if(bit == 32) x = 0;
    int num1 = count_one(xx) - count_one(x);
    x >>= bit;
    for(; num1 > 0; x = (x<<1) | 1, --num1, --bit);
    for(; bit > 0; x <<= 1, --bit);
    return x;
}

```

完整代码如下：

```c++
#include <iostream>
using namespace std;

int count_one0(int x){
    int cnt = 0;
    for(int i=0; i<32; ++i){
        if(x & 1) ++cnt;
        x >>= 1;
    }
    return cnt;
}
int count_one(int x){
    x = (x & (0x55555555)) + ((x >> 1) & (0x55555555));
    x = (x & (0x33333333)) + ((x >> 2) & (0x33333333));
    x = (x & (0x0f0f0f0f)) + ((x >> 4) & (0x0f0f0f0f));
    x = (x & (0x00ff00ff)) + ((x >> 8) & (0x00ff00ff));
    x = (x & (0x0000ffff)) + ((x >> 16) & (0x0000ffff));
    return x;
}
int next(int x){
    int max_int = ~(1<<31);
    int num = count_one(x);
    if(num == 0 || x == -1) return -1;
    for(++x; count_one(x) != num && x < max_int; ++x);
    if(count_one(x) == num) return x;
    return -1;	
}
int previous(int x){
    int min_int = (1<<31);
    int num = count_one(x);
    if(num == 0 || x == -1) return -1;
    for(--x; count_one(x) != num && x > min_int; --x);
    if(count_one(x) == num) return x;
    return -1;	
}
int next1(int x){
    int xx = x, bit = 0;
    for(; (x&1) != 1 && bit < 32; x >>= 1, ++bit);
    for(; (x&1) != 0 && bit < 32; x >>= 1, ++bit);
    if(bit == 31) return -1; //011.., none satisify
    x |= 1;
    x <<= bit; // wtf, x<<32 != 0,so use next line to make x=0
    if(bit == 32) x = 0; // for 11100..00
    int num1 = count_one(xx) - count_one(x);
    int c = 1;
    for(; num1 > 0; x |= c, --num1, c <<= 1);
    return x;
}
int previous1(int x){
    int xx = x, bit = 0;
    for(; (x&1) != 0 && bit < 32; x >>= 1, ++bit);
    for(; (x&1) != 1 && bit < 32; x >>= 1, ++bit);
    if(bit == 31) return -1; //100..11, none satisify
    x -= 1;
    x <<= bit;
    if(bit == 32) x = 0;
    int num1 = count_one(xx) - count_one(x);
    x >>= bit;
    for(; num1 > 0; x = (x<<1) | 1, --num1, --bit);
    x <<= bit;
    return x;
}
int main(){
    int a = -976756;//(1<<31)+(1<<29);//-8737776;
    cout<<next(a)<<" "<<previous(a)<<endl; // very slow
    cout<<next1(a)<<" "<<previous1(a)<<endl;;
    return 0;
}
```



# 5.5

## 题目

原文：

Write a function to determine the number of bits required to convert integer A to integer B.

Input: 31, 14

Output: 2

译文：

写程序计算从整数A变为整数B需要修改的二进制位数。

输入：31，14

输出：2

## 解答

这道题目也比较简单，从整数A变到整数B，所需要修改的就只是A和B二进制表示中不同的位， 先将A和B做异或，然后再统计结果的二进制表示中1的个数即可。

代码如下：

```
int count_one(int x){
    x = (x & (0x55555555)) + ((x >> 1) & (0x55555555));
    x = (x & (0x33333333)) + ((x >> 2) & (0x33333333));
    x = (x & (0x0f0f0f0f)) + ((x >> 4) & (0x0f0f0f0f));
    x = (x & (0x00ff00ff)) + ((x >> 8) & (0x00ff00ff));
    x = (x & (0x0000ffff)) + ((x >> 16) & (0x0000ffff));
    return x;
}

int convert_num(int a, int b){
    return count_one(a^b);
}

```

完整代码如下：

```c++
#include <iostream>
using namespace std;

int count_one(int x){
    x = (x & (0x55555555)) + ((x >> 1) & (0x55555555));
    x = (x & (0x33333333)) + ((x >> 2) & (0x33333333));
    x = (x & (0x0f0f0f0f)) + ((x >> 4) & (0x0f0f0f0f));
    x = (x & (0x00ff00ff)) + ((x >> 8) & (0x00ff00ff));
    x = (x & (0x0000ffff)) + ((x >> 16) & (0x0000ffff));
    return x;
}

int convert_num(int a, int b){
    return count_one(a^b);
}
int main(){
    int a = 7, b = 14;
    cout<<convert_num(a, b)<<endl;
    return 0;
}
```

# 5.6

## 题目

原文：

Write a program to swap odd and even bits in an integer with as few instructions as possible (e.g., bit 0 and bit 1 are swapped, bit 2 and bit 3 are swapped, etc).

译文：

写程序交换一个整数二进制表示中的奇数位和偶数位，用尽可能少的代码实现。 (比如，第0位和第1位交换，第2位和第3位交换…)

## 解答

这道题目比较简单。分别将这个整数的奇数位和偶数位提取出来，然后移位取或即可。

代码如下：

```
int swap_bits(int x){
    return ((x & 0x55555555) << 1) | ((x >> 1) & 0x55555555);
}

```

当然也可以采用更自然的方式来写这段代码：

```
int swap_bits1(int x){
    return ((x & 0x55555555) << 1) | ((x & 0xAAAAAAAA) >> 1);
}

```

上面的代码思路和作用都是一样的，不过按照《Hacker’s delight》这本书里的说法， 第一种方法避免了在一个寄存器中生成两个大常量。如果计算机没有与非指令， 将导致第二种方法多使用1个指令。总结之，就是第一种方法更好。:P

完整代码如下： 

```c++
#include <iostream>
using namespace std;

void print_binary(int x){ 
  string s = “”;
  for(int i=0; i<32 && x!=0; ++i, x »= 1)
  { if(x&1) s = “1” + s; else s = “0” + s; } 
  cout«s«endl; 
} 
int swap_bits(int x){ return ((x & 0x55555555) « 1) | ((x » 1) & 0x55555555); } 
int swap_bits1(int x){ return ((x & 0x55555555) « 1) | ((x & 0xAAAAAAAA) » 1); } 
int main(){ 
  int x = -7665543; 
  print_binary(x); 
  print_binary(swap_bits(x)); 
  print_binary(swap_bits1(x)); 
  return 0;
}
```

