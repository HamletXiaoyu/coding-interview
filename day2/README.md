# 题目

Write code to reverse a C-Style String. (C-String means that “abcd” is represented as five characters, including the null character.)

写代码翻转一个C风格的字符串。(C风格的意思是”abcd”需要用5个字符来表示，包含末尾的 结束字符)

# 解答

```c
void swap(char *a, char *b)
{
    char tmp = a[0];
    a[0] = b[0];
    b[0] = tmp;
}

void reverse(char *str)
{
    if(NULL == str)
        return;
    char *p = str, *q = str;

    while(*q)
        ++q;
    --q;
    while(p < q) {
        swap(p++, q--);
    }
}
```

