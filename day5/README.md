# 题目

Write a method to replace all spaces in a string with ‘%20’.

译文：

写一个函数，把字符串中所有的空格替换为%20 。

# 解答

简单题。先遍历一次字符串，得到空格个数，进而得到将空格转换成%20后的串长度 (每个空格替换为%20需要增加2个字符，x个空格增加2x个字符)。 然后从后向前依次对空格进行替换，非空格原样拷贝。

```
旧字符串：i am hawstein
旧串索引：   p
新字符串：i%20am%20hawstein              
新串索引：     q
```

```c
char *replace(char *str)
{
    int len, i, j, n;
    char *p = NULL;
    if (NULL == str)
        return NULL;
    len = strlen(str);
    n = 1;
    for (i = 0; i < len; ++i) {
        if (str[i] == ' ')
            ++n;
    }
    p = (char*)malloc((len+2*n+1) * sizeof(char));
    memset(p, 0, (len+2*n+1) * sizeof(char));
    for (j = 0, i = 0; i < len; ++i) {
        if (str[i] != ' ')
            p[j++] = str[i];
        else {
            p[j] = '%';
            p[j+1] = '2';
            p[j+2] = '0';
            j += 3;
        }
    }

    return p;
}
```

