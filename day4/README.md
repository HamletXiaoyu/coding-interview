# 题目

Write a method to decide if two strings are anagrams or not.

译文：

写一个函数判断两个字符串是否是变位词。

# 解答

变位词(anagrams)指的是组成两个单词的字符相同，但位置不同的单词。比如说， abbcd和abcdb就是一对变位词。

由于组成变位词的字符是一模一样的， 因此我们可以先统计每个字符串中各个字符出现的次数， 然后看这两个字符串中各字符出现次数是否一样。如果是，则它们是一对变位词。 这需要开一个辅助数组来保存各字符的出现次数。我们可以开一个大小是256的整数数组， 遍历第一个字符串时，将相应字符出现的次数加1；遍历第二个字符串时， 将相应字符出现的次数减1。最后如果数组中256个数都为0，说明两个字符串是一对变位词。 (第1个字符串中出现的字符都被第2个字符串出现的字符抵消了)， 如果数组中有一个不为0，说明它们不是一对变位词。

```c
bool is_anagram(char *str1, char *str2)
{
    if (str1 == NULL || str2 == NULL)
        return false;
    if (strlen(str1) != strlen(str2))
        return false;

    int len = strlen(str1), i;
    int c[256];
    memset(c, 0, sizeof(c));
    for (i = 0; i < len; ++i) {
        ++c[(int)str1[i]];
        --c[(int)str2[i]];
    }

    for (i = 0; i < 256; ++i) {
        if (c[i] != 0)
            return false;
    }

    return true;
}

```

