# 9.1



## 题目

原文：

You are given two sorted arrays, A and B, and A has a large enough buffer at the end to hold B. Write a method to merge B into A in sorted order.

译文：

A和B是两个有序数组(假设为递增序列)，而且A的长度足以放下A和B中所有的元素， 写一个函数将数组B融入数组A，并使其有序。

## 解答

最简单的方法是开一个大小可以容纳A和B的数组C，然后像归并排序中合并两个数组一样， 按照大小顺序把数组A和数组B的元素一一地放入数组C，然后再将数组C拷贝给A。 这种方法额外地使用了O(n)的空间，显然这是没有必要的开销。由于A的大小已经足够用了， 所以直接在A上直接操作即可。

可是如果我们思维定势地对比数组A和数组B，每次取小的元素放入数组A， 这样就会发现，要放入的位置上正放着有用的元素。处理起来就麻烦了。

相反，如果我们从A和B的尾部元素开始对比，每次取大的元素放在数组A的尾部， 这样一来，要放入的位置就不会出现上面的冲突问题。当对比结束时， 即可得到一个排好序的数组A。代码如下：

```
#include <iostream>
using namespace std;

void merge(int a[], int b[], int n, int m){
    int k = n + m - 1;
    int i = n - 1, j = m - 1;
    while(i>=0 && j>=0){
        if(a[i] > b[j]) a[k--] = a[i--];
        else a[k--] = b[j--];
    }
    while(j>=0) a[k--] = b[j--];
}

int main(){
    int a[15] = {
        1, 3, 7, 8, 9
    };
    int b[] = {
        2, 4, 5, 6, 10
    };
    int n = 5, m = 5;
    merge(a, b, 5, 5);
    for(int i=0; i<m+n; ++i)
        cout<<a[i]<<" ";
    return 0;
}

```

对比结束后，要检查数组B中是否还有元素，有的话要将它们拷贝到数组A。 我们并不需要检查数组A，因为如果数组A还有元素，说明while循环是因为数组B 中没有元素了才退出的。而A中的元素本来就是有序且就位于数组A中，所以不需要再管它。 如果A和B中的元素个数为n和m，则该算法的时间复杂度为O(n+m)。

让我们再加点限制条件，如果两个有序的序列并且没有额外的空间，那要怎么排序。 比如对于数组A，它的前半段和后半段分别有序，不使用额外的空间怎么使A整体有序。

首先，不可避免的我们还是要将两个有序部分中的元素拿出来对比。 我们先拿出前半段的第一个元素和后半段的第一个元素进行对比， 如果后半段的第一个元素要小，就将它们交换。由于这两个元素是各自序列的最小值， 这一对比就将整个数组A的最小值取出放在了正确的位置上。然后呢？ 交换到后半段的那个值怎么办？不理它，不太合适吧。我们可以通过两两对比， 把它移动到后半段的某个位置，使后半段保持有序。接下来呢？ 我们取出前半段的第2个元素(第1个元素已经放在它正确的位置上，不用理它了)， 还是和后半段的第1个元素对比，这一对比中较小的就会是整个数组中第2小的元素， 如果是后半段那个元素较小，则交换它们，然后仍然移动后半段使其保持有序。 这样不断进行下去，当把前半段的元素都遍历操作一遍，就会将小的元素都移动到前半段， 并且是有序的。而大的元素都在后半段且也是有序的。排序结束。

代码如下：

```c++
#include <iostream>
using namespace std;

void swap(int &a, int &b){
    a = a^b;
    b = a^b;
    a = a^b;
}
void merge(int a[], int begin, int mid , int end){
    for(int i=begin; i<=mid; ++i){
        if(a[i]>a[mid+1]){
            swap(a[i], a[mid+1]);
            for(int j=mid+1; j<end; ++j){
                if(a[j]<=a[j+1]) break;
                swap(a[j], a[j+1]);
            }
        }
    }
}
int main(){
    int a[10] = {
        8, 9, 11, 15, 17, 1, 3, 5, 12, 18
    };
    int b[10] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    };
    merge(a, 0, 4, 9);
    for(int i=0; i<10; ++i)
        cout<<a[i]<<" ";
    return 0;
}
```

# 9.2

## 题目

原文：

Write a method to sort an array of strings so that all the anagrams are next to each other.

译文：

写一个函数对字符串数组排序，使得所有的变位词都相邻。

## 解答

首先，要弄清楚什么是变位词。变位词就是组成的字母相同，但顺序不一样的单词。 比如说：live和evil就是一对变位词。OK，那么这道题目的意思就很清楚了， 它并不要求我们将字符串数组中的字符串按字典序排序，否则我们直接调用STL中的sort 函数就可以了。它要求我们在排序的过程中，按照变位词的准则来排序。 这种情况下，我们还是可以调用sort函数，不过要自己写一个对比函数。 一般情况下我们如果要排序一个长度为n的数组A，我们可以这样调用sort：

```
sort(A, A+n);

```

但如果我们有一个数组P，里面每个元素都是一个结构体：person，我们想按照person 这个结构体中年龄age来排序，这时候我们就需要自己写一个对比函数cmp：

```
bool cmp(person p1, person p2){
	return p1.age < p2.age; 
}

```

然后这样调用sort函数：

```
sort(P, P+n, cmp);

```

OK，回到我们的题目，我们的对比函数需要将两个串先按字典序排序，然后再比较， 这样一来，变位词经过字典序排序后就是一样的了。当调用sort函数时将会被排在一起。

代码如下：

```c++
#include <iostream>
#include <algorithm>
using namespace std;

bool cmp(string s1, string s2){
    sort(&s1[0], &s1[0]+s1.length());
    sort(&s2[0], &s2[0]+s2.length());
    return s1 < s2;
}
int main(){
    string s[] = {
        "axyz", "abc", "yzax", "bac", "zyxa", "fg", "gf"
    };
    sort(s, s+7, cmp);
    for(int i=0; i<7; ++i)
        cout<<s[i]<<endl;
    return 0;
}
```

# 9.3

## 题目

原文：

Given a sorted array of n integers that has been rotated an unknown number of times, give an O(log n) algorithm that finds an element in the array. You may assume that the array was originally sorted in increasing order.

EXAMPLE:

Input: find 5 in array (15 16 19 20 25 1 3 4 5 7 10 14)

Output: 8 (the index of 5 in the array)

译文：

一个数组有n个整数，它们排好序(假设为升序)但被旋转了未知次， 即每次把最右边的数放到最左边。给出一个O(log n)的算法找到特定的某个元素。

例子：

输入：在数组(15 16 19 20 25 1 3 4 5 7 10 14)中找出5

输出：8（5在数组中的下标）

## 解答

题目中提到了几个关键的词：有序，O(log n)。我们马上能联想到的就是二分查找算法。 但简单的二分查找肯定不行，因为这个数组被旋转了。也就是该数组前面一段有序， 后面一段有序，且前面那段的数要大于等于后面那段的数(本题考虑递增序列，递减同理)。 因此，我们需要对二分查找算法做一下修改，来解决这个具体的问题。

首先，我们来看一下函数原型：

```
int search(int a[], int low, int high, int x);

```

参数和二分查找一样，数组a，下界low，上界high及要查找的数x。当low <= high时， 我们会去求它们中间的那个数，然后与x对比，如果相同，就返回下标：

```
int mid = low + (high - low)/2;
if(a[mid] == x) return mid;

```

如果a[mid]不等于x，就要分情况讨论了。我们把旋转后的数组分为前半段和后半段， 两段分别都是有序的，且前半段的数都大于后半段的数。假如a[mid]落在前半段 (即a[mid]>=a[low])，这时如果x的值是位于a[low]和a[mid]之间， 则更新high = mid - 1；否则更新low = mid + 1。假如a[mid]落在后半段 (即a[mid]<a[low])，这时如果x的值是位于a[mid]和a[low]之间， 则更新low = mid + 1；否则更新high = mid - 1。

代码如下：

```c++
#include <iostream>
using namespace std;

int search(int a[], int low, int high, int x){
    while(low <= high){
        int mid = low + (high - low)/2;
        if(a[mid] == x) return mid;
        if(a[mid] >= a[low]) {
            if(x<a[mid] && x>=a[low])
                high = mid - 1;
            else
                low = mid + 1;
        }
        else {
            if(x>a[mid] && x<a[low])
                low = mid + 1;
            else
                high = mid - 1;
        }
    }
    return -1;
}

int main(){
    int a[12] = {
        15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14
    };
    int b[19] = {
        2,2,2,2,2,2,2,2,3,2,2,2,2,2,2,2,2,2,2
    };
    cout<<search(a, 0, 11, 3)<<endl;
    return 0;
}
```

# 9.4

## 题目

原文：

If you have a 2 GB file with one string per line, which sorting algorithm would you use to sort the file and why?

译文：

如果你有个2GB的文件，其中每一行是一个字符串，你会使用哪种算法来排序，为什么？

## 解答

当面试官说到2GB文件的时候，他其实就是在暗示你， 他并不希望一次性把所有的数据都载入内存。这样子的话，我们要怎么做呢？ 我们每次就将部分数据载入内存就好了。

算法：

首先我们要了解，可以用的内存有多大？假设我们有X MB的内存可用。

1. 我们将文件分为K份，其中X*K=2GB。每次取其中一份载入到内存中， 用O(nlog n)的算法排序，然后再保存到外部文件。
2. 载入下一份并排序
3. 当我们将K份小文件都排好序，合并它们。

上面的算法就是外排序，步骤3又称为N路归并。

使用外排序是由于数据太大了，无法一次全部加载到内存中，所以需要借助磁盘进行存储， 每次只从磁盘中加载一部分数据进入内存，进行排序。



# 9.5

## 题目

原文：

Given a sorted array of strings which is interspersed with empty strings, write a method to find the location of a given string.

Example: find “ball” in [“at”, “”, “”, “”, “ball”, “”, “”, “car”, “”,“”, “dad”, “”, “”] will return 4

Example: find “ballcar” in [“at”, “”, “”, “”, “”, “ball”, “car”, “”, “”, “dad”, “”, “”] will return -1

译文：

给你一个排好序的并且穿插有空字符串的字符串数组，写一个函数找到给定字符串的位置。

例子：在字符串数组 [“at”, “”, “”, “”, “ball”, “”, “”, “car”, “”,“”, “dad”, “”, “”] 中找到”ball”，返回下标4.

例子：在字符串数组 [“at”, “”, “”, “”, “”, “ball”, “car”, “”, “”, “dad”, “”, “”] 中找到”ballcar”，查找失败，返回-1.

## 解答

字符串数组已经是有序的了，所以，还是可以利用二分查找来找到指定的字符串。 当然了，由于数组中有空字符串，因此还要加些额外的处理，否则无法对比大小。 我们可以这样来处理，如果要对比的那个元素为空字符串，就一直向右移动， 直到字符串不为空或是位置已经超出了high下标。如果位置已经超出high下标， 就在[low, mid-1]这一段查找；如果没有超出high下标，那就和要查找的x进行对比。 相等时返回下标，不等时再根据比较出的大小决定到哪一半去查找。

代码如下：

```c++
#include <iostream>
using namespace std;

int search(string s[], int low, int high, string x){
    if(x == "") return -1;	
    while(low <= high){
        int mid = (low+high)>>1;
        int t = mid;
        while(s[t] == "" && t <= high) ++t;
        if(t > high) high = mid - 1;
        else{
            if(s[t] == x) return t;
            else if(s[t] < x) low = t + 1;
            else high = mid - 1; //or t-1
        }
    }
    return -1;
}
int main(){
    string s[13] = {
        "at", "", "", "", "ball", "", "", "car", "", "", "dad", "", ""
    };
    cout<<search(s, 0, 12, "ball")<<endl;
    return 0;
}
```
# 9.6

## 题目

原文：

Given a matrix in which each row and each column is sorted, write a method to find an element in it.

译文：

给出一个矩阵，其中每一行和每一列都是有序的，写一个函数在矩阵中找出指定的数。

## 解答

我们假设这个矩阵每一行都是递增的，每一列也都是递增的，并把这些数据存入文件 9.6.in(如下)，其中开头的两个数5 5表示该矩阵是5*5的。

```
5 5
1 2 3 4 5
3 7 8 9 11
5 9 10 17 18
7 12 15 19 23
9 13 16 20 25

```

这个矩阵是有序的，因此我们要利用这一点，当矩阵中元素和要查找的元素对比后， 如果相等，我们返回下标；如果不等，我们就排除掉一些元素，而不仅仅是对比的元素。 我们从矩阵的四个角的元素入手看看，有什么特点。左上角是最小的， 因为矩阵向右是递增的，向下也是递增的。同理，右下角是最大的。让我们来看看右上角， 设要查找的元素为x，比如x比右上角元素5大，那么它也会比第一行的其它元素都大。 因此可以去掉第一行；如果它比右上角元素小，那么它也会比最后一列的元素都小， 因此可以去掉最后一列；然后这样不断地比下去，只需要O(m+n)的时间就查找完。 对于左下角的元素，也有一样的特点。就不再分析了。

代码如下：

```c++
#include <iostream>
#include <cstdio>
using namespace std;

int d[20][20];
int search(int m, int n, int x){
    int r = 0, c = n-1;
    while(r<m && c>=0){
        if(d[r][c] == x) return (r * n + c);
        else if(d[r][c] < x) ++r;
        else --c;
    }
    return -1;
}
int main(){
    freopen("9.6.in", "r", stdin);
    int m, n;
    cin>>m>>n;
    for(int i=0; i<m; ++i)
        for(int j=0; j<n; ++j)
            cin>>d[i][j];

    int k = search(m, n, 13);
    if(k == -1) cout<<"not found"<<endl;
    else cout<<"position: "<<k/n<<" "<<k%n<<endl;
    fclose(stdin);
    return 0;
}
```

# 9.7

## 题目

原文：

A circus is designing a tower routine consisting of people standing atop one another’s shoulders. For practical and aesthetic reasons, each person must be both shorter and lighter than the person below him or her. Given the heights and weights of each person in the circus, write a method to compute the largest possible number of people in such a tower.

EXAMPLE:

Input (ht, wt): (65, 100) (70, 150) (56, 90) (75, 190) (60, 95) (68, 110)

Output: The longest tower is length 6 and includes from top to bottom: (56, 90) (60,95) (65,100) (68,110) (70,150) (75,190)

译文:

马戏团设计了这样一个节目：叠罗汉。一群人往上叠，每个人都踩在另一个人的肩膀上。 要求上面的人要比下面的人矮而且比下面的人轻。给出每个人的身高和体重， 写一个函数计算叠罗汉节目中最多可以叠多少人？

例子：

输入(身高 体重)：(65, 100) (70, 150) (56, 90) (75, 190) (60, 95) (68, 110)

输出：最多可叠人数：6 （从上到下是：(56, 90) (60,95) (65,100) (68,110) (70,150) (75,190)）

## 解答

给定了(身高 体重)序列，要求我们排序。不过由于要排序的对象是一个结构， 我们可以先按其中的一个指标进行排序，比如说身高。身高排好序后， 身高这个指标就都是满足叠罗汉的要求了，剩下的就看体重。 我们就只要在体重那个维度找到最长的递增子序列就可以了。

我们先定义一个结构体：

```
const int maxn = 100;
struct person{
    int h, w;
};
person p[maxn];

```

然后为了使STL中的sort函数能对这个结构体先按身高排序，当身高相等时按体重排序， 我们还需要写一个对比函数作为sort的参数：

```
bool cmp(person p1, person p2){
    if(p1.h == p2.h) return p1.w < p2.w;
    else return p1.h < p2.h;
}

```

这样一来，当我们调用sort函数，就能达到先对身高排序，若身高相等时对体重排序的要求。

```
sort(p, p+n, cmp);

```

排好序后，只需要求体重序列的最长递增子序列(LIS)即可。关于求LIS，可以参考文章： [动态规划：从新手到专家](http://www.hawstein.com/posts/dp-novice-to-advanced.html)

```
int lis(person p[], int n){
    int k = 1;
    d[0] = p[0].w;
    for(int i=1; i<n; ++i){
        if(p[i].w >= d[k-1]) d[k++] = p[i].w;
        else{
            int j;
            for(j=k-1; j>=0 && d[j]>p[i].w; --j);//用二分可将复杂度降到O(nlogn)
            d[j+1] = p[i].w;
        }
    }
    return k;
}

```

完整代码如下：

```
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 100;
struct person{
    int h, w;
};
person p[maxn];
int d[maxn];

bool cmp(person p1, person p2){
    if(p1.h == p2.h) return p1.w < p2.w;
    else return p1.h < p2.h;
}
int lis(person p[], int n){
    int k = 1;
    d[0] = p[0].w;
    for(int i=1; i<n; ++i){
        if(p[i].w >= d[k-1]) d[k++] = p[i].w;
        else{
            int j;
            for(j=k-1; j>=0 && d[j]>p[i].w; --j);//用二分可将复杂度降到O(nlogn)
            d[j+1] = p[i].w;
        }
    }
    return k;
}
int main(){
    freopen("9.7.in", "r", stdin);
    int n;
    cin>>n;
    for(int i=0; i<n; ++i)
        cin>>p[i].h>>p[i].w;
    sort(p, p+n, cmp);
    cout<<lis(p, n)<<endl;
    fclose(stdin);
    return 0;
}
```