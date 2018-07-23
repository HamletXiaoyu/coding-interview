# cat 19

## 题目

原文：

Write a function to swap a number in place without temporary variables.

译文：

写一个函数交换两个数，不能使用临时变量。

## 解答

交换函数swap是经常用到的函数，小巧简单，以下两种实现方式都不需要使用临时变量：

```
// 实现1
void swap(int &a, int &b){
    b = a - b;
    a = a - b;
    b = a + b;
}
// 实现2
void swap(int &a, int &b){
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

```

以上的swap函数，尤其是第2个实现，简洁美观高效，乃居家旅行必备良品。但是， 使用它们之前一定要想一想，你的程序中，是否有可能会让swap中的两个形参引用同一变量。 如果是，那么上述两个swap函数都将出问题。有人说，谁那么无聊去swap同一个变量。 那可不好说，比如你在操作一个数组中的元素，然后用到了以下语句：

```
swap(a[i], a[j]); // i==j时，出问题

```

你并没有注意到swap会去操作同一变量，可是当i等于j时，就相当于你这么干了。 然后呢，上面两个实现执行完第一条语句后，操作的那个内存中的数就变成0了。 后面的语句不会起到什么实际作用。

所以如果程序中有可能让swap函数去操作同一变量，就老老实实用最朴素的版本：

```
void swap(int &a, int &b){
    int t = a;
    a = b;
    b = t;
}
```

## 题目

原文：

Design an algorithm to figure out if someone has won in a game of tic-tac-toe.

译文：

设计算法检查某人是否赢得了井字游戏。

## 解答

假设这个检查某人是否赢得了井字游戏的函数为HasWon，那么我们第一步要向面试官确认， 这个函数是只调用一次，还是要多次频繁调用。如果是多次调用， 我们可以通过预处理来得到一个非常快速的版本。

**方法一：如果HasWon函数需要被频繁调用**

对于井字游戏，每个格子可以是空，我的棋子和对方的棋子3种可能，总共有3^9 = 19683 种可能状态。我们可以把每一种状态转换成一个整数， 预处理时把这个状态下是否有人赢得了井字游戏保存起来，每次检索时就只需要O(1)时间。 比如每个格子上的3种状态为0(空)，1(我方棋子)，2(对方棋子)，棋盘从左到右， 从上到下依次记为0到8，那么任何一个状态都可以写成一个3进制的数，再转成10进制即可。 比如，下面的状态：

```
1 2 2
2 1 1
2 0 1
可以写成:
122211201=1*3^8 + 2*3^7 +...+ 0*3^1 + 1*3^0

```

如果只需要返回是否有人赢，而不需要知道是我方还是对方。 那可以用一个二进制位来表示是否有人赢。比如上面的状态，1赢， 就可以把那个状态转换成的数对应的位置1。如果需要知道是谁赢， 可以用一个char数组来保存预处理结果。

**方法二：如果HasWon函数只被调用一次或很少次**

如果HasWon函数只被调用一次或很少次，那我们就没必要去预存结果了， 直接判断一下就好。只为一次调用去做预处理是不值得的。

代码如下，判断n*n的棋盘是否有人赢，即同一棋子连成一线：

```
#include <iostream>
using namespace std;

enum Check{
    ROW, COLUMN, DIAGONAL, REDIAGONAL
};

int CheckRowColumn(int board[], int n, Check check){
    int type = 0;
    for(int i=0; i<n; ++i){
        bool found = true;
        for(int j=0; j<n; ++j){
            int k = 0;
            if(check == ROW)
                k = i * n + j;
            else
                k = i + j * n;
            if(j == 0){
                type = board[k];
            }
            else if(board[k] != type){
                found = false;
                break; // 有一个不满足，检查下一行
            }
        }
        if(found) return type;
    }
    return 0;
}
int CheckDiagonal(int board[], int n, Check check){
    int type = 0;
    bool found = true;
    // 主对角
    for(int i=0; i<n; ++i){
        int k = 0;
        if(check == DIAGONAL)
            k = i + i * n;
        else
            k = i + (n-1-i) * n;
        if(i == 0){
            type = board[k];
        }
        else if(board[k] != type){
            found = false;
            break;
        }
    }
    if(found) return type;

    return 0;
}
int HasWon(int board[], int n){
    int type = 0;
    type = CheckRowColumn(board, n, ROW);
    if(type != 0) return type;
    type = CheckRowColumn(board, n, COLUMN);
    if(type != 0) return type;
    type = CheckDiagonal(board, n, DIAGONAL);
    if(type != 0) return type;
    type = CheckDiagonal(board, n, REDIAGONAL);
    if(type != 0) return type;

    return 0;
}
int main(){
    int n = 3; // 3*3
    int board[] = {
        2, 2, 1,
        2, 1, 1,
        1, 2, 0,
    };
    int type = HasWon(board, n);
    if(type != 0)
        cout<<type<<" won!"<<endl;
    else
        cout<<"nobody won!"<<endl;
    return 0;
}
```

## 题目

原文：

Write an algorithm which computes the number of trailing zeros in n factorial.

译文：

写一个算法计算n的阶乘末尾0的个数。

## 解答

首先，算出n的阶乘的结果再去计算末尾有多少个0这种方法是不可取的， 因为n的阶乘是一个非常大的数，分分种就会溢出。我们应当去分析， 是什么使n的阶乘结果末尾出现0。

n阶乘末尾的0来自因子5和2相乘，5*2=10。因此，我们只需要计算n的阶乘里， 有多少对5和2。注意到2出现的频率比5多，因此，我们只需要计算有多少个因子5即可。 我们可以列举一些例子，看看需要注意些什么：

```
5!, 包含1*5, 1个5
10!, 包含1*5,2*5, 2个5
15!, 包含1*5,2*5,3*5, 3个5
20!, 包含1*5,2*5,3*5,4*5, 4个5
25!, 包含1*5,2*5,3*5,4*5,5*5, 6个5
...

```

给定一个n，用n除以5，得到的是从1到n中包含1个5的数的个数；然后用n除以5去更新n， 相当于把每一个包含5的数中的因子5取出来一个。然后继续同样的操作，让n除以5， 将得到此时仍包含有5的数的个数，依次类推。最后把计算出来的个数相加即可。 比如计算25的阶乘中末尾有几个0， 先用25除以5得到5，表示我们从5,10,15,20,25中各拿一个因子5出来，总共拿了5个。 更新n=25/5=5，再用n除以5得到1，表示我们从25中拿出另一个因子5， 其它的在第一次除以5后就不再包含因子5了。

代码如下：

```
int NumZeros(int n){
    if(n < 0) return -1;
    int num = 0;
    while((n /= 5) > 0){
        num += n;
    }
    return num;
}
```

## 题目

原文：

Write a method which finds the maximum of two numbers. You should not use if-else or any other comparison operator.

EXAMPLE

Input: 5, 10

Output: 10

译文：

写一个函数返回两个数中的较大者，你不能使用if-else及任何比较操作符。

## 解答

我们可以通过一步步的分析来将需要用到的if-else和比较操作符去掉：

```
If a > b, return a; else, return b.
If (a - b) < 0, return b; else, return a.
If (a - b) < 0, 令k = 1; else, 令k = 0. return a - k * (a - b).
令z = a - b. 令k是z的最高位，return a - k * z.

```

当a大于b的时候，a-b为正数，最高位为0，返回的a-k*z = a；当a小于b的时候， a-b为负数，最高位为1，返回的a-k*z = b。可以正确返回两数中较大的。

另外，k是z的最高位(0或1)，我们也可以用一个数组c来存a,b，然后返回c[k]即可。

代码如下：

```
#include <iostream>
using namespace std;

int Max1(int a, int b){
    int c[2] = {
        a, b
    };
    int z = a - b;
    z = (z>>31) & 1;
    return c[z];
}
int Max2(int a, int b){
    int z = a - b;
    int k = (z>>31) & 1;
    return a - k * z;
}
int main(){
    int a = 5, b = 10;
    cout<<Max1(a, b)<<endl;
    cout<<Max2(a, b)<<endl;
    return 0;
}
```

## 题目

原文：

The Game of Master Mind is played as follows:

The computer has four slots containing balls that are red (R ), yellow (Y), green (G) or blue (B). For example, the computer might have RGGB (e.g., Slot #1 is red, Slots #2 and #3 are green, Slot #4 is blue).

You, the user, are trying to guess the solution. You might, for example, guess YRGB.When you guess the correct color for the correct slot, you get a “hit”. If you guess a color that exists but is in the wrong slot, you get a “pseudo-hit”. For example, the guess YRGB has 2 hits and one pseudo hit.

For each guess, you are told the number of hits and pseudo-hits. Write a method that, given a guess and a solution, returns the number of hits and pseudo hits.

译文：

Master Mind游戏规则如下：

4个槽，里面放4个球，球的颜色有4种，红(R )，黄(Y)，绿(G)，蓝(B)。比如， 给出一个排列RGGB，表示第一个槽放红色球，第二和第三个槽放绿色球，第四个槽放蓝色球。

你要去猜这个排列。比如你可能猜排列是：YRGB。当你猜的颜色是正确的，位置也是正确的， 你就得到一个hit，比如上面第3和第4个槽猜的和真实排列一样(都是GB)，所以得到2个hit。 如果你猜的颜色在真实排列中是存在的，但位置没猜对，你就得到一个pseudo-hit。比如， 上面的R，猜对了颜色，但位置没对，得到一个pseudo-hit。

对于你的每次猜测，你会得到两个数：hits和pseudo-hits。写一个函数， 输入一个真实排列和一个猜测，返回hits和pseudo-hits。

## 解答

这个问题十分直观，但有一个地方需要去向面试官明确一下题意。关于pseudo-hits的定义， 猜对颜色但位置没对，得到一个pseudo-hit，这里是否可以包含重复？举个例子， 比如真实排列是：RYGB，猜测是：YRRR。那么hits很明显为0了。pseudo-hits呢？ 猜测中Y对应真实排列中的Y，得到一个pseudo-hits。猜测中有3个R， 而真实排列中只有一个，那这里应该认为得到1个pseudo-hits还是3个？ CTCI书认为是3个，想必理由是猜测中的3个R都满足：出现在真实排列中，位置不正确。 所以算3个。但我认为，这里算1个比较合理，真实排列中的R只和猜测中的一个R配对， 剩余的没有配对，不算。弄清题意后，代码就不难写出了。

以下是两种不同理解的实现：

```
#include <iostream>
#include <cstring>
using namespace std;

struct Result{
    int hits;
    int pseudo_hits;
};

Result Estimate(const char* solution, const char* guess){
    Result res;
    res.hits = 0;
    res.pseudo_hits = 0;
    int solution_mask = 0;
    for(int i=0; i<4; ++i){
        solution_mask |= 1 << (solution[i] - 'A');
    }
    for(int i=0; i<4; ++i){
        if(guess[i] == solution[i])
            ++res.hits;
        else if(solution_mask & ( 1<<(guess[i] - 'A')))
            ++res.pseudo_hits;
    }
    return res;
}

int Min(int a, int b){
    return a < b ? a : b;
}
Result Estimate1(const char* solution, const char* guess){
    Result res;
    res.hits = 0;
    res.pseudo_hits = 0;
    int num = 26 + 5;
    int guess_count[num], solution_count[num];
    memset(guess_count, 0, sizeof(guess_count));
    memset(solution_count, 0, sizeof(solution_count));
    for(int i=0; i<4; ++i){
        if(guess[i] == solution[i])
            ++res.hits;
        ++guess_count[(int)(guess[i]-'A')];
        ++solution_count[(int)(solution[i]-'A')];
    }
    char color[] = "RGBY";
    for(int i=0; i<4; ++i){
        int idx = (int)(color[i] - 'A');
        res.pseudo_hits += Min(guess_count[idx], solution_count[idx]);
    }
    res.pseudo_hits -= res.hits;
    return res;
}
int main(){
    char solution[] = "RYGB";
    char guess[] = "YRRR";
    Result res = Estimate(solution, guess);
    cout<<res.hits<<" "<<res.pseudo_hits<<endl;
    Result res1 = Estimate1(solution, guess);
    cout<<res1.hits<<" "<<res1.pseudo_hits<<endl;
    return 0;
}

```

## 题目

原文：

You are given an array of integers (both positive and negative). Find the continuous sequence with the largest sum. Return the sum.

EXAMPLE

Input: {2, -8, 3, -2, 4, -10}

Output: 5 (i.e., {3, -2, 4} )

译文：

给出一个整数数组(包含正数和负数)，找到和最大的连续子序列，返回和。

例子：

输入: {2, -8, 3, -2, 4, -10}

输出: 5 (即, {3, -2, 4} )

## 解答

经典的面试题目，遍历一遍数组，用变量maxsum保存遍历过程中的最大和， 用变量cursum保存遍历过程中的当前和。在遍历的过程中，我们只需要做3件事， 第一：如果当前和cursum小于等于0，说明前面的连续和不会对后面的连续和产生贡献， 要么使后面的连续和减少，要么不变。因此舍弃cursum，用当前的元素更新它。 第二：如果当前和cursum是大于0的，累加当前元素。第三：如果当前和cursum 大于最大和maxsum，则更新最大和maxsum。

此外，我们可以用一个全局变量来标示非法输入。代码如下：

```
#include <iostream>
using namespace std;

bool g_Invalid = false;

int GetMaxSum(int a[], int n){
    if(a==NULL || n<=0){
        g_Invalid = true;
        return 0;
    }
    g_Invalid = false;
    
    int max_sum = 1<<31; // Min Int
    int cur_sum = 0;
    for(int i=0; i<n; ++i){
        if(cur_sum <= 0)
            cur_sum = a[i];
        else
            cur_sum += a[i];

        if(cur_sum > max_sum)
            max_sum = cur_sum;
    }

    return max_sum;
}
int main(){
    int a[] = {
        2, -8, 3, -2, 4, -10
    };
    int max_sum = GetMaxSum(a, 6);
    if(g_Invalid)
        cout<<"Invalid Input!"<<endl;
    else
        cout<<max_sum<<endl;
    return 0;
}
```

## 题目

原文：

Design a method to find the frequency of occurrences of any given word in a book.

译文：

设计一个函数，找到给定单词在一本书中的出现次数。

## 解答

这道题目和[19.2](http://www.hawstein.com/posts/19.2.html)是一个思路。如果只需要查询一次， 那就直接做；如果要多次查询，而且要查询各种不同的单词，那就先预处理一遍， 接下来就只需要用O(1)的时间进行查询。

**只查询一次**

遍历这本书的每个单词，计算给定单词出现的次数。时间复杂度O(n)，我们无法继续优化它， 因为书中每个单词都需要访问一次。当然，如果我们假设书中的单词是均匀分布， 那我们就可以只统计前半本书某个单词出现的次数，然后乘以2； 或是只统计前四分之一本书某个单词出现的次数，然后乘以4。这样能计算出一个大概值。 当然，单词均匀分布这个假设太强了，一般是不成立的。

**多次查询**

如果我们要对一本书进行多次的查询，就可以遍历一次这本书的单词， 把它出现的次数存入哈希表中。查询的时候即可用O(1)的时间完成。

## 题目

原文：

Write a method to generate a random number between 1 and 7, given a method that generates a random number between 1 and 5 (i.e., implement rand7() using rand5()).

译文：

给你一个能生成1到5随机数的函数，用它写一个函数生成1到7的随机数。 (即，使用函数rand5()来实现函数rand7())。

## 解答

rand5可以随机生成1,2,3,4,5；rand7可以随机生成1,2,3,4,5,6,7。 rand5并不能直接产生6，7，所以直接用rand5去实现函数rand7似乎不太好入手。 如果反过来呢？给你rand7，让你实现rand5，这个好实现吗？

一个非常直观的想法就是不断地调用rand7，直到它产生1到5之间的数，然后返回。 代码如下：

```
int Rand5(){
    int x = ~(1<<31); // max int
    while(x > 5)
        x = Rand7();
    return x;
}

```

等等，这个函数可以等概率地产生1到5的数吗？首先，它确确实实只会返回1到5这几个数， 其次，对于这些数，都是由Rand7等概率产生的(1/7)，没有对任何一个数有偏袒， 直觉告诉我们，Rand5就是等概率地产生1到5的。事实呢？让我们来计算一下， 产生1到5中的数的概率是不是1/5就OK了。比如说，让我们来计算一下Rand5生成1 的概率是多少。上面的函数中有个while循环，只要没生成1到5间的数就会一直执行下去。 因此，我们要的1可能是第一次调用Rand7时产生，也可能是第二次，第三次，…第n次。 第1次就生成1，概率是1/7；第2次生成1，说明第1次没生成1到5间的数而生成了6，7， 所以概率是(2/7)*(1/7)，依次类推。生成1的概率计算如下：

```
P(x=1)=1/7 + (2/7) * 1/7 + (2/7)^2 * 1/7 + (2/7)^3 * 1/7 + ...
      =1/7 * (1 + 2/7 + (2/7)^2 + ...) // 等比数列
	  =1/7 * 1 / (1 - 2/7)
	  =1/7 * 7/5
	  =1/5

```

上述计算说明Rand5是等概率地生成1,2,3,4,5的(1/5的概率)。从上面的分析中， 我们可以得到一个一般的结论，如果a > b，那么一定可以用Randa去实现Randb。其中， Randa表示等概率生成1到a的函数，Randb表示等概率生成1到b的函数。代码如下：

```
// a > b
int Randb(){
    int x = ~(1<<31); // max int
    while(x > b)
        x = Randa();
    return x;
}

```

回到正题，现在题目要求我们要用Rand5来实现Rand7，只要我们将Rand5 映射到一个能产生更大随机数的Randa，其中a > 7，就可以套用上面的模板了。 这里要注意一点的是，你映射后的Randa一定是要满足等概率生成1到a的。比如，

```
Rand5() + Rand5() - 1

```

上述代码可以生成1到9的数，但它们是等概率生成的吗？不是。生成1只有一种组合： 两个Rand5()都生成1时：(1, 1)；而生成2有两种：(1, 2)和(2, 1)；生成6更多。 它们的生成是不等概率的。那要怎样找到一个等概率生成数的组合呢？

我们先给出一个组合，再来进行分析。组合如下：

```
5 * (Rand5() - 1) + Rand5()

```

Rand5产生1到5的数，减1就产生0到4的数，乘以5后可以产生的数是：0,5,10,15,20。 再加上第二个Rand5()产生的1,2,3,4,5。我们可以得到1到25， 而且每个数都只由一种组合得到，即上述代码可以等概率地生成1到25。OK， 到这基本上也就解决了。

套用上面的模板，我们可以得到如下代码：

```
int Rand7(){
    int x = ~(1<<31); // max int
    while(x > 7)
        x = 5 * (Rand5() - 1) + Rand5() // Rand25
    return x;
}

```

上面的代码有什么问题呢？可能while循环要进行很多次才能返回。 因为Rand25会产生1到25的数，而只有1到7时才跳出while循环， 生成大部分的数都舍弃掉了。这样的实现明显不好。我们应该让舍弃的数尽量少， 于是我们可以修改while中的判断条件，让x与最接近25且小于25的7的倍数相比。 于是判断条件可改为x > 21，于是x的取值就是1到21。 我们再通过取模运算把它映射到1-7即可。代码如下：

```
int Rand7(){
    int x = ~(1<<31); // max int
    while(x > 21)
        x = 5 * (Rand5() - 1) + Rand5() // Rand25
    return x%7 + 1;
}

```

这个实现就比上面的实现要好，并且可以保证等概率生成1到7的数。

让我们把这个问题泛化一下，从特殊到一般。现在我给你两个生成随机数的函数Randa， Randb。Randa和Randb分别产生1到a的随机数和1到b的随机数，a，b不相等 (相等就没必要做转换了)。现在让你用Randa实现Randb。

通过上文分析，我们可以得到步骤如下：

1. 如果a > b，进入步骤2；否则构造Randa^2 = a * (Randa - 1) + Randa， 表示生成1到a^2 随机数的函数。如果a^2 仍小于b，继教构造 Randa^3 = a * (Randa^2 - 1) + Randa…直到a^k > b，这时我们得到Randa^k , 我们记为RandA。
2. 步骤1中我们得到了RandA(可能是Randa或Randa^k )，其中A > b， 我们用下述代码构造Randb：

```
// A > b
int Randb(){
    int x = ~(1<<31); // max int
    while(x > b*(A/b)) // b*(A/b)表示最接近A且小于A的b的倍数
        x = RandA();
    return x%b + 1;
}

```

从上面一系列的分析可以发现，如果给你两个生成随机数的函数Randa和Randb， 你可以通过以下方式轻松构造Randab，生成1到a*b的随机数。

```
Randab = b * (Randa - 1) + Randb
Randab = a * (Randb - 1) + Randa

```

如果再一般化一下，我们还可以把问题变成：给你一个随机生成a到b的函数， 用它去实现一个随机生成c到d的函数。有兴趣的同学可以思考一下，这里不再讨论。



## 题目

原文：

Design an algorithm to find all pairs of integers within an array which sum to a specified value.

译文：

设计一个算法，找到数组中所有和为指定值的整数对。

## 解答

**时间复杂度O(n)的解法**

我们可以用一个哈希表或数组或bitmap(后两者要求数组中的整数非负)来保存sum-x的值， 这样我们就只需要遍历数组两次即可找到和为指定值的整数对。这种方法需要O(n) 的辅助空间。如果直接用数组或是bitmap来做，辅助空间的大小与数组中的最大整数相关， 常常导致大量空间浪费。比如原数组中有5个数：1亿，2亿，3亿，4亿，5亿。sum为5亿， 那么我们将bitmap中的sum-x位置1，即第4亿位，第3亿位，第2亿位，第1亿位，第0位置1. 而其它位置都浪费了。

如果使用哈希表，虽然不会有大量空间浪费，但要考虑冲突问题。

**时间复杂度为O(nlogn)的解法**

我们来考虑一种空间复杂度为O(1)，而且实现也很简单的算法。首先，将数组排序。 比如排序后得到的数组a是：-2 -1 0 3 5 6 7 9 13 14。然后使用low和high 两个下标指向数组的首尾元素。如果a[low]+a[high] > sum，那么说明a[high] 和数组中的任何其它一个数的和都一定大于sum(因为它和最小的a[low]相加都大于sum)。 因此，a[high]不会与数组中任何一个数相加得到sum，于是我们可以直接不要它， 即让high向前移动一位。同样的，如果a[low]+a[high] < sum，那么说明a[low] 和数组中的任何其它一个数的和都一定小于sum(因为它和最大的a[high]相加都小于sum)。 因此，我们也可以直接不要它，让low向前移动一位。如果a[low]+a[high]等于sum， 则输出。当low小于high时，不断地重复上面的操作即可。

代码如下：

```
#include <iostream>
#include <algorithm>
using namespace std;

void PrintPairSum(int a[], int n, int sum){
    if(a==NULL || n<2) return;
    
    sort(a, a+n);
    int low = 0, high = n-1;
    while(low < high){
        if(a[low]+a[high] > sum)
            --high;
        else if(a[low]+a[high] < sum)
            ++low;
        else{
            cout<<a[low]<<" "<<a[high]<<endl;
            ++low; --high;
        }
            
    }
}

int main(){
    int n = 6, sum = 6;
    int a[] = {
        1, 2, 3, 4, 5, 6
    };
    PrintPairSum(a, n, sum);
    return 0;
}
```