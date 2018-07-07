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