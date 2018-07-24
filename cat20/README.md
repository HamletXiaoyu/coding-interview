# cat20



## 题目

原文：

Write a function that adds two numbers. You should not use + or any arithmetic operators.

译文：

写一个Add函数求两个数的和，不能使用+号或其它算术运算符。

## 解答

为了解决这个问题，让我们来深入地思考一下，我们是如何去加两个数的。为了易于理解， 我们考虑10进制的情况。比如我们要算759 + 674，我们通常从最低位开始加， 考虑进位；然后加第二位，考虑进位…对于二进制，我们可以使用相同的方法， 每一位求和，然后考虑进位。

能把这个过程弄得更简单点吗？答案是YES，我们可以把求两个数的和分成两步， “加”与”进位”，看例子：

1. 计算759 + 674，但不考虑进位，得到323。
2. 计算759 + 674，只考虑进位，而不是去加每一位，得到1110。
3. 把上面得到的两个数加起来(这里又要用到加，所以使用递归调用即可)

由于我们不能使用任何算术运算符，因此可供我们使用的就只有位运算符了。 于是我们把操作数看成二进制表示，然后对它们做类似的操作：

1. 不考虑进位的按位求和，(0,0),(1,1)得0，(1,0),(0,1)得1， 使用异或操作可以满足要求。
2. 只考虑进位，只有(1,1)才会产生进位，使用按位与可以满足要求。 当前位产生进位，要参与高一位的运算，因此按位与后要向左移动一位。
3. 递归求和，直到进位为0

代码如下：

```
int Add2(int a, int b){
    if(b == 0) return a;
    int sum = a ^ b; // 各位相加，不计进位
    int carry = (a & b) << 1; // 记下进位
    return Add2(sum, carry); // 求sum和carry的和
}

```

递归的迭代版本如下：

```
int Add3(int a, int b){
    while(b != 0){
        int sum = a ^ b;
        int carry = (a & b) << 1;
        a = sum;
        b = carry;
    }
    return a;
}

```

对于这道题目，还有一个非常巧妙的解法。我们知道，数组操作本质上其实是指针操作。 数组名其实是指向数组首元素地址的指针。比如说整数数组a，a[1]表示的是数组中的第 1个元素，这是一直以来我们的理解。而编译器看到a[1]，它是怎么去理解的呢？

首先，它会用数组首元素地址，加上偏移量，得到目标数据的地址， 然后再把里面的数据按指针指向类型的大小取出。所以，当编译器看到a[1]， 它实际上做了下面的事：假设a指向的地址为0xbfc86d98

```
得到目标数据地址：0xbfc86d98 + sizeof(int) * 1 = 0xbfc86d9c
取出0xbfc86d9中的数据

```

从上面可以看出，操作数组元素其实隐含了加法！所以呢，如果我们要求两个数的和， 只需要把其中一个看成地址，另一个看成偏移量，然后用返回它们对应数组元素的地址即可。 看代码：

```
int Add1(int a, int b){
    char *c = (char*)a;
    return (int)&c[b]; // c+sizeof(char)*b=a + b
}

```

上述代码将a强制转换为指向char的指针c，然后返回c[b]的地址即可。c[b] 的地址就等于c + sizeof(char)*b = a + b。有人会问，它b是负数时OK吗？ OK，没问题的。它代表偏移量为负，往反方向计算地址就是了。

由于编译器对数组的解释方式如上所述，因此上面代码中的c[b]也可以写成b[c]，或 a[5]可以写成5[a]，效果是一样的，因为编译器都会先去求地址和偏移量的和。

如果还想知道更多关于c语言的奇奇怪怪的点，推荐阅读《C陷阱与缺陷》。



## 题目

原文：

Write a method to shuffle a deck of cards. It must be a perfect shuffle - in other words, each 52! permutations of the deck has to be equally likely. Assume that you are given a random number generator which is perfect.

译文：

写一个随机洗牌函数。要求洗出的52!种组合都是等概率的。 也就是你洗出的一种组合的概率是1/(52!)。假设已经给你一个完美的随机数发生器。

## 解答

这是一道非常有名的面试题，及非常有名的算法——随机洗牌算法。

最直观的思路是什么？很简单，每次从牌堆中**随机**地拿一张出来。那么， 第一次拿有52种可能，拿完后剩下51张；第二次拿有51种可能，第三次拿有50种可能， …，一直这样随机地拿下去直到拿完最后1张，我们就从52!种可能中取出了一种排列， 这个排列对应的概率是1/(52!)，正好是题目所要求的。

接下来的问题是，如何写代码去实现上面的算法？假设扑克牌是一个52维的数组cards， 我们要做的就是从这个数组中随机取一个元素，然后在剩下的元素里再随机取一个元素… 这里涉及到一个问题，就是每次取完元素后，我们就不会让这个元素参与下一次的选取。 这个要怎么做呢。

我们先假设一个5维数组：1，2，3，4，5。如果第1次随机取到的数是4， 那么我们希望参与第2次随机选取的只有1，2，3，5。既然4已经不用， 我们可以把它和1交换，第2次就只需要从后面4位(2,3,1,5)中随机选取即可。同理， 第2次随机选取的元素和数组中第2个元素交换，然后再从后面3个元素中随机选取元素， 依次类推。

代码如下：

```
#include <iostream>
#include <cstdlib>
using namespace std;

void Swap(int &a, int &b){// 有可能swap同一变量，不能用异或版本
    int t = a;
    a = b;
    b = t;
}
void RandomShuffle(int a[], int n){
    for(int i=0; i<n; ++i){
        int j = rand() % (n-i) + i;// 产生i到n-1间的随机数
        Swap(a[i], a[j]);
    }
}
int main(){
    srand((unsigned)time(0));
    int n = 9;
    int a[] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9
    };
    RandomShuffle(a, n);
    for(int i=0; i<n; ++i)
        cout<<a[i]<<endl;
    return 0;
}

```

关于如何测试随机洗牌程序，推荐阅读耗叔的文章： [如何测试洗牌程序](http://coolshell.cn/articles/8593.html)

## 题目

原文：

Write a method to randomly generate a set of m integers from an array of size n. Each element must have equal probability of being chosen.

译文：

写一个函数，随机地从大小为n的数组中选取m个整数。要求每个元素被选中的概率相等。

## 解答

这道题目和[随机洗牌问题](http://www.hawstein.com/posts/20.2.html)类似，只需要随机选取1个元素， 然后在剩下的元素里面随机选取下一个元素，不断这样操作即可。

这样做能保证每个元素选中的概率一样吗？也就是选中每个元素的概率都是1/n？ 答案是YES，让我们来做一下简单的计算。

- 选第1个元素：在n个中随机选，因此概率为1/n
- 选第2个元素：在剩下的n-1个中随机选：1/(n-1)，由于第1次没有选中它， 而是在另外n-1个中选：(n-1)/n，因此概率为：(n-1)/n * 1/(n-1) = 1/n
- 选第3个元素：同上：(n-1)/n * (n-2)/(n-1) * 1/(n-2) = 1/n

。。。

因此，按照这种方法选取k个元素，每个元素都是以1/n的概率被选出来的。代码如下： 选出的m个数放到数组前m个位置。

```
#include <iostream>
#include <cstdlib>
using namespace std;

void Swap(int &a, int &b){// 有可能swap同一变量，不能用异或版本
    int t = a;
    a = b;
    b = t;
}
void PickMRandomly(int a[], int n, int m){
    for(int i=0; i<m; ++i){
        int j = rand() % (n-i) + i;// 产生i到n-1间的随机数
        Swap(a[i], a[j]);
    }
}
int main(){
    srand((unsigned)time(0));
    int n = 9, m = 5;
    int a[] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9
    };
    PickMRandomly(a, n, m);
    for(int i=0; i<m; ++i)
        cout<<a[i]<<endl;
    return 0;
}

```

## 题目

原文：

Write a method to count the number of 2s between 0 and n.

译文：

写一个函数，计算0到n之间2的个数。

## 解答

最简单直观的方法就是对于0到n之间的数，一个个地去统计2在它们上出现的个数， 然后累加起来即可。求2在某个数上出现的次数需要O(logn)的时间，一共有n个数， 所以共需要O(nlogn)的时间。

代码如下：

```
int Count2(int n){
    int count = 0;
    while(n > 0){
        if(n%10 == 2)
            ++count;
        n /= 10;
    }
    return count;
}

int Count2s1(int n){
    int count = 0;
    for(int i=0; i<=n; ++i)
        count += Count2(i);
    return count;

}

```

上述方法最大的问题就是效率，当n非常大时，就需要很长的运行时间。 想要提高效率，就要避开暴力法，从数字中找出规律。对于这道题， 《编程之美》已经给出了很漂亮的解法，这里再简述一下。

假设一个5位数N=abcde，我们现在来考虑百位上出现2的次数，即，从0到abcde的数中， 有多少个数的百位上是2。分析完它，就可以用同样的方法去计算个位，十位，千位， 万位等各个位上出现2的次数。

当百位c为0时，比如说12013，0到12013中哪些数的百位会出现2？我们从小的数起， 200~299, 1200~1299, 2200~2299, … , 11200~11299, 也就是固定低3位为200~299，然后高位依次从0到11，共12个。再往下12200~12299 已经大于12013，因此不再往下。所以，当百位为0时，百位出现2的次数只由更高位决定， 等于更高位数字(12)x当前位数(100)=1200个。

当百位c为1时，比如说12113。分析同上，并且和上面的情况一模一样。 最大也只能到11200~11299，所以百位出现2的次数也是1200个。

上面两步综合起来，可以得到以下结论：

```
当某一位的数字小于2时，那么该位出现2的次数为：更高位数字x当前位数

```

当百位c为2时，比如说12213。那么，我们还是有200~299, 1200~1299, 2200~2299, … , 11200~11299这1200个数，他们的百位为2。但同时，还有一部分12200~12213， 共14个(低位数字+1)。所以，当百位数字为2时， 百位出现2的次数既受高位影响也受低位影响，结论如下：

```
当某一位的数字等于2时，那么该位出现2的次数为：更高位数字x当前位数+低位数字+1

```

当百位c大于2时，比如说12313，那么固定低3位为200~299，高位依次可以从0到12， 这一次就把12200~12299也包含了，同时也没低位什么事情。因此出现2的次数是： (更高位数字+1)x当前位数。结论如下：

```
当某一位的数字大于2时，那么该位出现2的次数为：(更高位数字+1)x当前位数

```

根据上面得出的3条结论，我们可以编写出代码如下：

```
int Count2s(int n){
    int count = 0;
    int factor = 1;
    int low = 0, cur = 0, high = 0;

    while(n/factor != 0){
        low = n - (n/factor) * factor;//低位数字
        cur = (n/factor) % 10;//当前位数字
        high = n / (factor*10);//高位数字

        switch(cur){
        case 0:
        case 1:
            count += high * factor;
            break;
        case 2:
            count += high * factor + low + 1;
            break;
        default:
            count += (high + 1) * factor;
            break;
        }

        factor *= 10;
    }

    return count;
}

```

如果我们把问题一般化一下：写一个函数，计算0到n之间i出现的次数，i是1到9的数。 这里为了简化，i没有包含0，因为按以上的算法计算0出现的次数， 比如计算0到11间出现的0的次数，会把1，2，3，4…视为01，02，03，04… 从而得出错误的结果。所以0是需要单独考虑的，为了保持一致性，这里不做讨论。 将上面的三条结论应用到这就是：

```
当某一位的数字小于i时，那么该位出现i的次数为：更高位数字x当前位数
当某一位的数字等于i时，那么该位出现i的次数为：更高位数字x当前位数+低位数字+1
当某一位的数字大于i时，那么该位出现i的次数为：(更高位数字+1)x当前位数

```

代码如下：

```
int Countis(int n, int i){
    if(i<1 || i>9) return -1;//i只能是1到9

    int count = 0;
    int factor = 1;
    int low = 0, cur = 0, high = 0;

    while(n/factor != 0){
        low = n - (n/factor) * factor;//低位数字
        cur = (n/factor) % 10;//当前位数字
        high = n / (factor*10);//高位数字

        if(cur < i)
            count += high * factor;
        else if(cur == i)
            count += high * factor + low + 1;
        else
            count += (high + 1) * factor;

        factor *= 10;
    }

    return count;
}
```

## 题目

原文：

You have a large text file containing words. Given any two words, find the shortest distance (in terms of number of words) between them in the file. Can you make the searching operation in O(1) time? What about the space complexity for your solution?

译文：

有一个很大的文本文件，里面包含许多英文单词。给出两个单词，找到它们的最短距离 (以它们之间隔了多少个单词计数)。你能在O(1)的时间内返回任意两个单词间的最短距离吗？ 你的解法空间复杂度是多少？

## 解答

先看一个例子，为了简单起见，我们假设文件里就只有以下两句话。然后， 我们现在来求is和name的最短距离。假设相邻的两个单词距离为1。

```
What is your name My name is Hawstein

```

首先，我们遇到的第一个问题是：是否要考虑顺序？我们求的是is和name间的距离， 那么文本中先出现name再出现is的情况要不要算进来。这一点是要和面试官进行交流确认的。 这里我们假设不考虑顺序，并且认为本文中只有单词，没有标点。 为了进一步简化问题，我们可以用一个字符串数组来保存单词， 接下来考虑如何计算两个单词间的最短距离。

最直观的一个解法是，遍历单词数组，遇到is或name就更新它们的位置， 然后计算is和name之间的距离，如果这个距离小于之前的最小距离，则更新这个最小距离。 看图示：

```
What is your name My name is Hawstein
0    1  2    3    4  5    6  7
                  p

```

p表示遍历的当前位置。此时已经经过了前面的一个is和name，is位置为1，name位置为3， 最小距离min=3-1=2。当p移动到下一个单词，发现是name，则更新name的位置为5， 减去is的位置1得到4，并不小于min，不更新，继续。当p移动到is，更新is的位置为6， 减去name的位置5，得到距离为1，小于min，更新min=1。p之后一直移动到末尾， 没遇到is或name，不再更新。最后返回最小值min。时间复杂度O(n)，空间复杂度O(1)。

代码如下：

```
int ShortestDist(string text[], int n, string word1, string word2){
    int min = kMaxInt / 2;
    int pos1 = -min;
    int pos2 = -min;

    for(int pos=0; pos<n; ++pos){
        if(text[pos] == word1){
            pos1 = pos;
            int dist = pos1 - pos2;
            if(dist < min)
                min = dist;
        }
        else if(text[pos] == word2){
            pos2 = pos;
            int dist = pos2 - pos1;
            if(dist < min)
                min = dist;
        }
    }

    return min;
}

```

题目要求在O(1)的时间内返回两个单词的最短距离，上述代码肯定是无法满足要求的。 那要怎么做呢？只能用哈希表做预处理了，空间换时间。

**方法一**

遍历一次文本，用哈希函数将每个单词映射到不同结点，结点后保存该单词出现的位置。 比如对于上面的例子

```
What is your name My name is Hawstein
0    1  2    3    4  5    6  7	

```

遍历一次并处理后，我们得到每个单词在文本中出现的位置：(哈希值是随便写的，示意用)

```
单词	  哈希值   出现位置
What:     3		  0
is:       7    	  1, 6
your:     13      2
name:     14      3, 5
My:       25      4
Hawstein: 27      7

```

求两个单词间的最小距离时，首先用O(1)时间通过哈希函数映射到指定结点， 然后对于其中一个单词的每个位置，去与第二个单词的所有位置比较，找到最小的差值。 由于位置是递增的，因此可以修改二分查找进行搜索。

该方法的平均查找复杂度应该是O(1)的，但最坏情况下无法保证O(1)的查找时间， 考虑一种极端情况，文本中的单词就只有is和name，它们的数量各为(1/2)n， 使用这种算法，我们需要O(nlogn)的时间。

**方法二**

预处理阶段把文本中任意两个单词间的最小距离计算出来， key是两个单词连接后的哈希值，value保存的就是最小距离。 查找阶段就只需要把两个单词连接求其哈希值，然后直接返回其对应的value即可。 查找两个单词的最小距离时间复杂度O(1)。需要O(n^2 )的时间来做预处理。

由于我们是不考虑顺序的，因此做两个单词的连接时，不能直接连接， 这样会导致is和name连接后是isname，而name和is连接后nameis， 它们的哈希值不一样，这并不是我们想要的。因此，在做两个单词的连接时， 我们可以让第一个字符较小的单词放在前面(反正定义一个规则来保证连接的唯一性即可)。 比如对于name和is，由于在字典序中，i<n，所以连接是isname。

还是用上面的例子，预处理后得到：(哈希值是随便写的数字，示意用)

```
单词连接      哈希值   最小距离
(isWhat)     8       1
... 		 ...	 ...
(isname)     12  	 1
... 		 ...	 ...
(isMy) 		 33      2
... 		 ...	 ...

```

这样当我要求is和name之间的最小距离时，就只需要先连接它们得到isname， 然后用哈希函数求出isname的哈希值12，然后直接返回它对应的最小距离即可。

如果有冲突怎么办？即两个不同的字符串映射到同一个哈希值，我们可以用链地址法， 把冲突的连接字符串链接起来，这样每个结点就需要保存连接字符及其对应的最小距离。 比如对于上面的例子，假设isname和isMy的哈希值相同，我们可以按如下所示去做：

```
哈希值   最小距离
8       (isWhat,1)
...	    ...
12  	(isname,1) -> (isMy,2)
...     ...

```

这样一来，当我们求得一个连接字符串str的哈希值是12， 就依次去与其后面的结点做比较。如果str等于isname，返回1；否则，移动到下一个结点， 继续比较。如果str等于isMy，返回2。

**方法三**

也可以先将两个单词分别映射到两个哈希值，比如is映射到哈希值i，name映射到哈希值j， 然后将它们的最小距离保存在d[i][j]中。这里由于是不考虑单词顺序的，因此， 我们可以将较小的哈希值放在d的第一维，较大的放在第二维。也就是对于d[i][j]， 有i<j。同样，这种方法也要考虑冲突问题。

## 题目

原文：

Describe an algorithm to find the largest 1 million numbers in 1 billion numbers. Assume that the computer memory can hold all one billion numbers.

译文：

描述一个算法，在10亿个数中找到最大的1百万个数。假设内存可以一次性装入这10亿个数。

## 解答

虽然这道题的数据量很大，但由于题目已经假设所有的数据可以一次性装入内存， 所以题目中的10亿，1百万也就没有什么特殊含义了。 我们完全可以想像成在100个数中查找最大的10个数。

这是一道经典的面试题，一般有以下几种解法：

**排序法**

最直观的方法就是将数组从大到小排序，然后取前1百万个数即可。时间复杂度O(nlogn)。

**最小堆**

利用最小堆来维护最大的1百万个数，堆顶元素是这1百万个数中最小的。 遍历剩下的元素，当某一元素大于堆顶元素，则用该元素替换堆顶元素， 然后调整堆结构，使其仍为最小堆。当遍历完所有10亿个数后， 堆中维护的就是最大的1百万个数。在n个数中查找最大的k个数，该算法需要O(nlogk) 的时间。由于k一般要比n小得多，所以该算法比排序法要快。

该算法还有一个优点，就是便于处理大数据。比如说， 我们一般需要在非常多的数中找到最大(最小)的k个数，这个k一般比较小， 而n却可能大得无法一次性载入内存。这时候我们就可以在内存中维护一个k 个元素的最小(最大)堆，然后把数据分多次从磁盘读入内存进行处理。

**线性求k最大**

线性求k最大利用的是快排中的partition函数。每次选取一个基准元素pivot (可以用第1个元素，也可以随机选)，然后将其它元素与pivot对比。大于等于pivot 的放到左边，小于pivot的放到右边。调用一次partition后， pivot左边的数都是大于等于它的，pivot右边的数都是小于它的。 如果pivot此时正好是第k-1个元素，那么它左边加上它一共有k个元素， 而且这k个元素都是比右边的元素要大的，即它们就是最大的k个元素。如果pivot 左边不足k-1个元素，则在它右边进行同样的partition操作。如果pivot 左边是多于k-1个元素的，则在它左边进行partition操作。

该算法会改变数组中元素的顺序，期望时间复杂度是O(n)。

## 题目

原文：

Write a program to find the longest word made of other words.

译文：

写一个程序，找到由其它单词组成的最长单词。

## 解答

我们从例子着手开始分析问题。假如我们有一个单词数组，如下：

```
string arr[] = {"test", "tester", "testertest", "testing", 
			"apple", "seattle", "banana",  "batting", "ngcat", 
			"batti","bat", "testingtester", "testbattingcat"};

```

哪一个是题目要求的最长单词？这时候假如你有另一个“我”能跳出来， 观察自己的思考过程。你就会发现自己是怎么去解这个问题的， 然后只需要把你的思考过程变成算法，写成代码就OK了。

题目说要找最长单词，所以你的眼睛自然会去寻找那些长单词，至少你不会从bat 开始找起，对吧。找到最长的单词是testbattingcat， 下一步去看它是否可以由其它单词组成。我们发现test是testbattingcat的一部分， bat也是它的一部分，然后呢？剩下的tingcat不能由其它单词构成。不过， 我们可以用test，batti，ngcat来组成它。所以， 它就是我们要找的可以由其它单词组成的最长单词。

把上面的思考过程转换成算法，可以描述如下：

1. 按单词的长度从大到小排序。(先寻找最长的单词)
2. 不断地取单词的前缀s，当s存在于单词数组中，递归调用该函数， 判断剩余串是否可以由其它单词组成。如果可以，返回true。

对于上面的例子testbattingcat，我们通过不断取前缀：t不在数组中，te不在数组中， tes不在数组中，test在数组中；递归调用去处理剩余串battingcat，b不在数组中， ba不在数组中，bat在数组中；递归调用去处理剩余串tingcat， 发现它所有的前缀都不存在于数组中，退递归来到处理battingcat那一层。 接着上次的bat继续处理：batt不在数组中，batti在数组中；递归调用去处理剩余串 ngcat，n，ng，ngc，ngca都不在数组中，ngcat存在数组中。递归调用处理剩余串， 发现剩余串为空，返回真。

代码如下：

```
#include <iostream>
#include <algorithm>
#include "hash.h"
using namespace std;

Hash hash;

inline bool cmp(string s1, string s2){//按长度从大到小排
    return s2.length() < s1.length();
}

bool MakeOfWords(string word, int length){
    //cout<<"curr: "<<word<<endl;
    int len = word.length();
    //cout<<"len:"<<len<<endl;
    if(len == 0) return true;

    for(int i=1; i<=len; ++i){
        if(i == length) return false;//取到原始串，即自身
        string str = word.substr(0, i);
        //cout<<str<<endl;
        if(hash.find((char*)&str[0])){
            if(MakeOfWords(word.substr(i), length))
                return true;
        }
    }
    return false;
}

void PrintLongestWord(string word[], int n){
    for(int i=0; i<n; ++i)
        hash.insert((char*)&word[i][0]);
    sort(word, word+n, cmp);

    for(int i=0; i<n; ++i){
        if(MakeOfWords(word[i], word[i].length())){
            cout<<"Longest Word: "<<word[i]<<endl;
            return;
        }
    }
}

int main(){
    string arr[] = {"test", "tester", "testertest", "testing", 
				"apple", "seattle", "banana",  "batting", "ngcat", 
                "batti","bat", "testingtester", "testbattingcat"};
    int len = 13;
    PrintLongestWord(arr, len);
    return 0;
}

```

上述代码将单词存放在哈希表中，以得到O(1)的查找时间。排序需要用O(nlogn)的时间， 判断某个单词是否可以由其它单词组成平均需要O(d)的时间(d为单词长度)， 总共有n个单词，需要O(nd)的时间。所以时间复杂度为：O(nlogn + nd)。 n比较小时，时间复杂度可以认为是O(nd)；n比较大时，时间复杂度可以认为是O(nlogn)。

注意上述代码中有一句：

```
 if(i == length) return false;//取到原始串，即自身

```

意思是当我们取一个单词前缀，最后取到整个单词时， 这种情况就认为是没有其它单词可以组成它。如果不要这一句， 那么你在哈希表中总是能查找到和它自身相等的串(就是它自己)，从而返回true。 而这明显不是我们想要的。我们要的是其它单词来组成它，不包括它自己。

这样一来，又引出一个问题，如果单词中就是存在两个相同的单词。 比如一个单词数组中最长的单词是abcdefg，并且存在2个，而它又不能被更小的单词组成， 那么我们可以认为这个abcdefg是由另一个abcdefg组成的吗？ 关于这一点，你可以和面试官进行讨论。(上述代码认为是不能的。)

由于使用哈希表会占用较多空间，一种不使用额外空间的算法是直接在单词数组中查找， 由于单词数组已经按长度从大小到排，因此单次查找时间为O(n)。一共有n个单词， 平均长度为d，所以总共需要的时间为O(nd*n)=O(dn^2 )。 如果我们再开一个数组来保存所有单词，并将它按字典序排序， 那么我们可以使用二分查找，单次查找时间变为O(logn)，总共需要O(dnlogn)。

## 题目

原文：

Numbers are randomly generated and passed to a method. Write a program to find and maintain the median value as new values are generated.

译文：

随机产生一些数传递给一个函数，写程序找出并维护这些数的中位数。

## 解答

**方法一**

最简单直观的方法是用一个足够大的数组A来维护这些数，使其按升序排列。 这样一来，可以用O(1)的时间找到中位数。下面是图示：

```
元素：1 3 5			元素：1 3 5 7
下标：0 1 2			下标：0 1 2 3
中位数：A[n/2]		中位数：(A[(n-1)/2] + A[n/2])/2

```

这种方法插入一个新来的元素需要O(n)的时间， 需要在原来有序的数组中找到一个合适的位置插入它，并把比它大的元素都向后移动1位。

**方法二**

用一个最大堆(或最小堆)来维护这些数。那么插入一个新元素需要O(logn)的时间， 比方法一要好。但取中位数需要先排序，时间复杂度O(nlogn)。

**方法三**

使用堆来维护数据是个不错的选择，因为插入一个新元素只需要O(logn)的时间， 但取中位数比较耗时，时间主要花在排序上。有没方法可以不排序呢？ 我们知道，中位数是一个有序序列中排在中间的数，它左右两边的数相当。 从方法一的示意图可以看出，当数组大小n为奇数时，中位数就是有序序列中正中间那个数， 如果n为偶数，它是中间两个数的平均数。它只和序列中间的一个或两个数有关， 和其它的元素无关。那么，如果我用一个最大堆维护中位数左边的数(包含它)， 用一个最小堆维护中位数右边的数。当n为偶数时，我只需要把左边的数最大那个， 和右边的数最小那个相加除以2即可。左边的最大数即最大堆的堆顶元素， 右边最小数即最小堆的堆顶元素。当n为奇数时，如果最大堆的元素比最小堆的元素多1， 则最大堆的堆顶元素是中位数；如果最小堆的元素比最大堆的元素多1， 则最小堆的堆顶元素是中位数。在插入新元素的时候，我们只要维护两个堆， 使其堆中元素的数量差别不超过1即可。

这样一来，插入新元素还是O(logn)的时间，而取中位数只需要O(1)的时间， 要优于方法一和方法二。

```
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstdlib>
using namespace std;

class Median{
private:
    priority_queue<int,vector<int>,less<int> > max_heap;//左边的数
    priority_queue<int,vector<int>,greater<int> > min_heap;//右边的数

public:
    void Insert(int v);
    int GetValue();
};

void Median::Insert(int v){
    if(max_heap.empty() && min_heap.empty())
        max_heap.push(v);
    else if(!max_heap.empty() && min_heap.empty())
        max_heap.push(v);
    else if(max_heap.empty() && !min_heap.empty())
        min_heap.push(v);
    else{
        if(v < max_heap.top())
            max_heap.push(v);
        else
            min_heap.push(v);
    }
    //调整，保证两个堆的元素数量差别不大于1
    //不要用max_heap.size()-min_heap.size()>1
    //因为size返回的是unsigned类型，当左边相减得到一个负数时，本来为false
    //但会被转为一个大的正数，结果为true，出问题
    while(max_heap.size() > min_heap.size()+1){
        int data = max_heap.top();
        min_heap.push(data);
        max_heap.pop();
    }
    while(min_heap.size() > max_heap.size()+1){
        int data = min_heap.top();
        max_heap.push(data);
        min_heap.pop();
    }
}

int Median::GetValue(){//中位数为int，由于有除法，也可改为float
	if(max_heap.empty() && min_heap.empty())
        return (1<<31); //都为空时，返回int最小值
    if(max_heap.size() == min_heap.size())
        return (max_heap.top()+min_heap.top()) / 2;
    else if(max_heap.size() > min_heap.size())
        return max_heap.top();
    else
        return min_heap.top();
}

int main(){
    srand((unsigned)time(0));
    Median md;
    vector<int> vi;
    int num = rand() % 30; //数量是30以内的随机数
    for(int i=0; i<num; ++i){
        int data = rand() % 100; //元素是100内的数
        vi.push_back(data);
        md.Insert(data);
    }
    sort(vi.begin(), vi.end());
    for(int i=0; i<num; ++i)
        cout<<vi.at(i)<<" "; //排序的序列
    cout<<endl<<md.GetValue()<<endl; //中位数
    return 0;
}
```

## 题目

原文：

Imagine you have a square matrix, where each cell is filled with either black or white. Design an algorithm to find the maximum subsquare such that all four borders are filled with black pixels.

译文：

有一个正方形矩阵，里面的每一个小格子要么被涂上黑色要么被涂上白色。 设计算法，找到四条边都是黑色格子的最大子正方形。

## 解答

暴力法，从左到右，从上到下遍历格子，将它作为子正方形左上角的点。 固定了子正方形左上角的点，我们只需要知道边长，就能把子正方形确定下来。 我们按边长从大到小开始，去检查每一个子正方形的四条边是否都为黑色格子。 如果是，则记下当前最大的边长值。将子正方形左上角的点移动到下一行(即向下移动一格)， 进入下一轮循环。

代码如下：

```
#include <iostream>
#include <cstdio>
using namespace std;

const int MAX_N = 100;
int matrix[MAX_N][MAX_N];

struct SubSquare{
    int row, col, size;
};

inline int max(int a, int b){
    return a > b ? a : b;
}

bool IsSquare(int row, int col, int size){
    for(int i=0; i<size; ++i){
        if(matrix[row][col+i] == 1)// 1代表白色，0代表黑色
            return false;
        if(matrix[row+size-1][col+i] == 1)
            return false;
        if(matrix[row+i][col] == 1)
            return false;
        if(matrix[row+i][col+size-1] == 1)
            return false;
    }
    return true;
}

SubSquare FindSubSquare(int n){
    int max_size = 0; //最大边长
    int col = 0;
    SubSquare sq;
    while(n-col > max_size){
        for(int row=0; row<n; ++row){
            int size = n - max(row, col);
            while(size > max_size){
                if(IsSquare(row, col, size)){
                    max_size = size;
                    sq.row = row;
                    sq.col = col;
                    sq.size = size;
                    break;
                }
                --size;
            }
        }
        ++col;
    }
    return sq;
}

int main(){
    freopen("20.11.in", "r", stdin);
    int n;
    cin>>n;
    for(int i=0; i<n; ++i)
        for(int j=0; j<n; ++j)
            cin>>matrix[i][j];
    SubSquare sq = FindSubSquare(n);
    cout<<"top:    "<<sq.row<<endl;
    cout<<"bottom: "<<sq.row+sq.size-1<<endl;
    cout<<"left:   "<<sq.col<<endl;
    cout<<"right:  "<<sq.col+sq.size-1<<endl;
    fclose(stdin);
    return 0;
}
```

## 题目

原文：

Given an NxN matrix of positive and negative integers, write code to find the submatrix with the largest possible sum.

译文：

给一个NxN的矩阵，矩阵上每个格子中填有一个整数(正，负或0)， 写代码计算子矩阵之和的最大值。

## 解答

**暴力法，时间复杂度O(n^6 )**

最简单粗暴的方法就是枚举所有的子矩阵，求和，然后找出最大值。 枚举子矩阵一共有C(n, 2)*C(n, 2)个(水平方向选两条边，垂直方向选两条边)， 时间复杂度O(n^4 )，求子矩阵中元素的和需要O(n^2 )的时间。 因此总的时间复杂度为O(n^6 )。

**部分和预处理，时间复杂度降到O(n^4 )**

上面的方法需要O(n^2 )去计算子矩阵中元素的和。 这一部分我们可以在预处理的时候求出部分和，在使用的时候就只需要O(1) 的时间来得到子矩阵中元素的和。

![img](http://www.hawstein.com/assets/img/2013/3/8/rect.png)

我们用一个二维数组p来保存矩阵的部分和，p[i][j]表示左上角是(1, 1)，(下标从1开始)， 右下角是(i, j)的矩阵中元素的和。这样一来，如果我们要求矩阵(x1, x2, y1, y2) 中元素的和(即上图矩阵D)，我们可以通过以下式子计算得出：

```
sum(D) = p[y2][x2] - p[y2][x1-1] - p[y1-1][x2] + p[y1-1][x1-1]

```

只需要O(1)的时间。

部分和p[i][j]要怎么计算呢？我们可以通过更小的部分和来计算得到它：

```
p[i][j] = p[i-1][j] + p[i][j-1] - p[i-1][j-1] + A[i][j]

```

其中A[i][j]是格子(i, j)中的整数。我们只需要O(n^2 ) 的时间即可预处理得到所有的部分和。

**降维，O(n^3 )的解法**

[如果有一个一维的数组，我们要求它子数组之和的最大值，最好的时间复杂度是O(n)。](http://www.hawstein.com/posts/19.7.html) 既然如此，我们可以把二维数组一个方向的数累加起来，将它变为一维数组， 然后就转化成了求一维数组子数组之和的最大值。看示意图：

```
			第k列	第l列
第i行：...	...		...		...
	  ...	...		...		...
第j行：...	...		...		...

```

在同一列中，我们把第i行到第j行的数加起来，得到如下：

```
				第k列	第l列
只剩下一行：...	...		...		...

```

这时候我们可以用O(n)的时候算出子数组之和的最大值，假设是第k个元素到第l 个元素的子数组。那么它实际上就对应二维数组中第i，j行，第k，l 列组成的子矩阵的元素和。

枚举i，j行需要O(n^2 )的时间，求一维情况的子数组最大和需要O(n)的时间， 所以总的时间复杂度为O(n^3 )。其中求第k列元素中， 第i行到第j行的元素和可以用部分和求解，仅需要O(1)的时间：

```
sum(i,j,k) = p[j][k] - p[j][k-1] - p[i-1][k] + p[i-1][k-1]

```

代码如下：

```
#include <iostream>
#include <cstdio>
using namespace std;

const int MAX_N = 100;
int p[MAX_N][MAX_N], A[MAX_N][MAX_N];

void PreCompute(int n){
    for(int i=0; i<=n; ++i)
        p[0][i] = p[i][0] = 0;
    for(int i=1; i<=n; ++i)
        for(int j=1; j<=n; ++j)
            p[i][j] = p[i-1][j] + p[i][j-1] - p[i-1][j-1] + A[i][j];
}

int MaxSum(int n){
    int max_sum = 1<<31; //min int
    for(int i=1; i<=n; ++i)
        for(int j=i; j<=n; ++j){
            int cur_sum = 0;
            for(int k=1; k<=n; ++k){
                int val = p[j][k]-p[j][k-1]-p[i-1][k]+p[i-1][k-1];
                if(cur_sum <= 0)
                    cur_sum = val;
                else
                    cur_sum += val;

                if(cur_sum > max_sum)
                    max_sum = cur_sum;
            }
        }

    return max_sum;
}

int main(){
    freopen("20.12.in", "r", stdin);
    int n;
    cin>>n;
    for(int i=1; i<=n; ++i)//元素存储从1开始
        for(int j=1; j<=n; ++j)
            cin>>A[i][j];
    PreCompute(n);
    cout<<MaxSum(n)<<endl;
    fclose(stdin);
    return 0;
}
```

