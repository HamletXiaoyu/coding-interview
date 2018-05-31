# 题目

Implement an algorithm to determine if a string has all unique characters. What if you can not use additional data structures?

实现一个算法来判断一个字符串中的字符是否唯一(即没有重复).不能使用额外的数据结构。 (即只使用基本的数据结构)

# 解答

首先，你可以问面试官，构成字符串的字符集有多大？是ASCII字符，还是只是26个字母？ 还是有更大的字符集，对于不同的情况，我们可能会有不同的解决方案。

如果我们假设字符集是ASCII字符，那么我们可以开一个大小为256的bool数组来表征每个字 符的出现。数组初始化为false，遍历一遍字符串中的字符，当bool数组对应位置的值为真， 表明该字符在之前已经出现过，即可得出该字符串中有重复字符。否则将该位置的bool数组 值置为true。代码如下：

```c
bool is_unique(char *str)
{
    int i;
    bool a[256];
    memset(a, 0, sizeof(a));
    int len = strlen(str);
    for(i = 0; i < len; ++i){
        if(a[(int)str[i]])
            return false;
        a[(int)str[i]] = true;
    }

    return true;
}
```

该算法的时间复杂度为O(n)。我们还可以通过位运算来减少空间的使用量。 用每一位表征相应位置字符的出现。对于ASCII字符，我们需要256位，即一个长度为8的int 数组a即可。这里的关键是要把字符对应的数字，映射到正确的位上去。比如字符’b’对应的 代码是98，那么我们应该将数组中的哪一位置为1呢？用98除以32，得到对应数组a的下标： 3。98对32取模得到相应的位：2。相应代码如下：

```c
bool is_unique2(char* str)
{
    int a[8];
    int i;
    memset(a, 0, sizeof(a));
    int len = strlen(str);
    for(i = 0; i < len; ++i){
        int c = (int)str[i];
        int idx = c / 32, shift = c % 32;
        if(a[idx] & (1 << shift))
            return false;
        a[idx] |= (1 << shift);
    }

    return true;
}
```

