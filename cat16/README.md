# cat16 内存

## 题目

原文：

Explain the following terms: virtual memory, page fault, thrashing.

译文：

解释下列术语：虚拟内存，缺页中断，抖动。

## 解答

**虚拟内存**是计算机系统内存管理的一种技术。它使得应用程序认为它拥有连续的可用的内存 （一个连续完整的地址空间），而实际上，它通常是被分隔成多个物理内存碎片， 还有部分暂时存储在外部磁盘存储器上，在需要时进行数据交换。 与没有使用虚拟内存技术的系统相比，使用这种技术的系统使得大型程序的编写变得更容易， 对真正的物理内存（例如RAM）的使用也更有效率。

<http://zh.wikipedia.org/wiki/%E8%99%9A%E6%8B%9F%E5%86%85%E5%AD%98>

**缺页中断**一个页(Page)是一个固定容量的内存区块，是物理内存和外部存储(如硬盘等) 传输的单位。当一个程序访问一个映射到地址空间却实际并未加载到物理内存的页（page）时， 硬件向软件发出的一次中断（或异常）就是一个缺页中断或叫页错误（page fault）。

<http://zh.wikipedia.org/wiki/%E9%A1%B5%E7%BC%BA%E5%A4%B1_(%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%A7%91%E5%AD%A6)>

**抖动**在分页存储管理系统中，内存中只存放了那些经常使用的页面， 而其它页面则存放在外存中，当进程运行需要的内容不在内存时， 便启动磁盘读操作将所需内容调入内存，若内存中没有空闲物理块， 还需要将内存中的某页面置换出去。也就是说，系统需要不断地在内外存之间交换信息。 若在系统运行过程中，刚被淘汰出内存的页面，过后不久又要访问它， 需要再次将其调入。而该页面调入内存后不久又再次被淘汰出内存，然后又要访问它。 如此反复，使得系统把大部分时间用在了页面的调入/换出上， 而几乎不能完成任何有效的工作，这种现象称为抖动。

参考资料：《操作系统教程》 <http://en.wikipedia.org/wiki/Thrash_(computer_science)>

## 题目

原文：

Write a function called my2DAlloc which allocates a two dimensional array. Minimize the number of calls to malloc and make sure that the memory is accessible by the notation arr[i][j].

译文：

写一个名为my2DAlloc的函数，用它开一个二维数组。尽可能地少用malloc函数， 确保可以用arr[i][j]这种形式来访问第i行第j列的元素。

## 解答

这道题目最简单的方法就是先开一个数组来存储指向每一行的指针， 然后再为每一行动态地分配空间。这是非常常见的动态申请二维数组空间的方法：

```
int** My2DAlloc(int rows, int cols){
    int **arr = (int**)malloc(rows*sizeof(int*));
    for(int i=0; i<rows; ++i)
        arr[i] = (int*)malloc(cols*sizeof(int));
    return arr;
}

```

上述方法使用了(rows+1)次的malloc，malloc使用过多会影响程序的运行效率， 那么有没有办法减少malloc的使用呢。

虽然我们做的事情是动态申请二维数组空间，但这些申请的空间本质上是一维， 只不过有些空间存储了地址，而有些空间则存储了数据。比如上面的方法， 申请了一个长度为rows的一维数组，里面存放的是指针(int*)，指向每一行的地址。 然后又申请了rows*cols大小的空间，里面存放的是整型数据(int)。既然如此， 我们一次性将这么多的空间申请下来，然后在该存放地址的空间存放地址， 在该存放数据的空间存放数据就OK了。

我们需要存储指向每一行的地址，大小为：

```
int header = rows * sizeof(int*);

```

同时需要存储rows*cols的整型数据，大小为：

```
int data = rows * cols * sizeof(int);

```

我们一次性将这些空间申请下来：

```
int **arr = (int**)malloc(header + data);

```

由于前面rows * sizeof(int*)的大小存放的是指针，因此arr类型是int**。 而跨过rows个单元后，后面存放的是整型数据，因此需要将其类型转为int*：

```
int *buf = (int*)(arr + rows);

```

最后，从buf指向的地址开始，每cols个单元组成一行，将行首地址存放到arr 的相应位置即可。

```
for(int i=0; i<rows; ++i)
    arr[i] = buf + i * cols;

```

代码如下：

```
int** My2DAlloc1(int rows, int cols){
    int header = rows * sizeof(int*);
    int data = rows * cols * sizeof(int);
    int **arr = (int**)malloc(header + data);
    int *buf = (int*)(arr + rows);
    for(int i=0; i<rows; ++i)
        arr[i] = buf + i * cols;
    return arr;
}

```

这样一来，我们使用一次的malloc就可以动态地申请二维数组空间， 并且可以用arr[i][j]对数组元素进行访问。



## 题目

原文：

Write a program to find whether a machine is big endian or little endian.

译文：

写一个程序判断一台机器是大端序还是小端序。

## 解答

关于什么是大端序和小端序，可参见维基百科： [字节序](http://zh.wikipedia.org/wiki/%E5%AD%97%E8%8A%82%E5%BA%8F)

判断程序如下：

```
#define BIG_ENDIAN 0
#define LITTLE_ENDIAN 1
int TestByteOrder(){
	short int word = 0x0001;
	char *byte = (char *) &word;
	return (byte[0] ? LITTLE_ENDIAN : BIG_ENDIAN);
}

```

