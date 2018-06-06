# 题目

Given an image represented by an NxN matrix, where each pixel in the image is 4 bytes, write a method to rotate the image by 90 degrees. Can you do this in place?

译文：

一张图像表示成NxN的矩阵，图像中每个像素是4个字节，写一个函数把图像旋转90度。 你能原地进行操作吗？(即不开辟额外的存储空间)

# 解答

假设要将图像逆时针旋转90度，顺时针是一个道理。如果原图如下所示：

```
1 2 3 4 
5 6 7 8 
9 10 11 12 
13 14 15 16

```

那么逆时针旋转90度后的图应该是：

```
4 8 12 16 
3 7 11 15 
2 6 10 14 
1 5 9 13
```

可以分两步走。 第一步交换主对角线两侧的对称元素，第二步交换第i行和第n-1-i行，即得到结果。 看图示：

```
原图：           第一步操作后：	第二步操作后：
1 2 3 4 		1 5 9 13		4 8 12 16
5 6 7 8 		2 6 10 14		3 7 11 15
9 10 11 12 		3 7 11 15		2 6 10 14
13 14 15 16		4 8 12 16		1 5 9 13
```

```c
void transpose(int a[][4], int n)
{
    int i, j;
    for(i = 0; i < n; ++i){
        for(j = i+1; j < n; ++j){
            swap(&a[i][j], &a[j][i]);
        }
    }

    for(i = 0; i < n/2; ++i){
        for(j = 0; j < n; ++j)
            swap(&a[i][j], &a[n-1-i][j]);
    }
}

```

