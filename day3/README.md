# 题目

原文：

Design an algorithm and write code to remove the duplicate characters in a string without using any additional buffer. NOTE: One or two additional variables are fine. An extra copy of the array is not.

FOLLOW UP

Write the test cases for this method.

译文：

设计算法并写出代码移除字符串中重复的字符，不能使用额外的缓存空间。注意： 可以使用额外的一个或两个变量，但不允许额外再开一个数组拷贝。

进一步地，

为你的程序写测试用例。

# 解答

依次访问 这个数组的每个元素，每访问一个，就将该元素到字符串结尾的元素中相同的元素去掉( 比如置为’\0’).时间复杂度为O(n^2 )，代码如下：

```c
void remove_duplicate(char *str)
{
    int i, j, len, p;
    if(NULL == str)
        return;
    len = strlen(str);
    if(len < 2)
        return;
    p = 0;
    for(i = 0; i < len; ++i) {
        if(str[i] != '\0') {
            str[p++] = str[i];
            for(j = i+1; j < len; ++j) {
                if(str[j] == str[i])
                    str[j] = '\0';
            }
        }
    }
    str[p] = '\0';
}

```

