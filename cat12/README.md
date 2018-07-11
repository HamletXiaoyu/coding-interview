## 题目12.1

原文：

If you were integrating a feed of end of day stock price information ( open, high, low,and closing price) for 5,000 companies, how would you do it? You are responsible for the development, rollout and ongoing monitoring and maintenance of the feed. Describe the different methods you considered and why you would recommend your approach. The feed is delivered once per trading day in a comma-separated format via an FTP site. The feed will be used by 1000 daily users in a web application.

译文：

如果你要为5000家公司的股价信息整合摘要，你会怎么做？ 你要负责摘要的开发，部署，监控和维护。描述你能想到的不同方法， 及为什么你会推荐这些方法。摘要以逗号分隔的格式经由FTP进行交付，每个交易日一次。 每日有1000个用户在web应用程序中使用这些摘要信息。

## 解答

假设我们有一些脚本在每日结束时通过FTP获取数据。我们把数据存储在哪？ 我们怎样存储数据有助于我们对数据进行分析？

**方案一**

将数据保存在文本文件中。这样子的话，管理和更新都非常麻烦，而且难以查询。 保存无组织的文本文件是一种非常低效的方法。

**方案二**

使用数据库。这将带来以下的好处：

1. 数据的逻辑存储
2. 提供了非常便捷的数据查询方式

例子：return all stocks having open > N AND closing price < M (返回开盘价大于N且收盘价小于M的所有股票)

优势：

1. 使得维护更加简单
2. 标准数据库提供了回滚，数据备份和安全保证等功能。我们不需要重复造轮子。

**方案三**

如果要求不是那么宽泛，我们只想做简单的分析和数据分发，那么XML是另一个很好的选择。 我们的数据有固定的格式和大小：公司名称，开盘价，最高价，最低价和收盘价。 XML看起来应当如下所示：

```xml
<root>
  <date value=“2008-10-12”>
	<company name=“foo”>
	  <open>126.23</open>
	  <high>130.27</high>
	  <low>122.83</low>
	  <closingPrice>127.30</closingPrice>
	</company>
	<company name=“bar”>
	  <open>52.73</open>
	  <high>60.27</high>
	  <low>50.29</low>
	  <closingPrice>54.91</closingPrice>
	</company>
  </date>
  <date value=“2008-10-11”> . . . </date>
</root>

```

优势：

1. 便于数据分发。这就是为什么XML是共享及分发数据的一个标准模型。
2. 我们有高效的解析器来提取出想要的数据
3. 我们可以往XML文件中追加新数据

不足之处是数据查询比较麻烦(这点比不上数据库)。



## 题目12.2

原文：

How would you design the data structures for a very large social network (Facebook,LinkedIn, etc)? Describe how you would design an algorithm to show the connection, or path, between two people (e.g., Me -> Bob -> Susan -> Jason -> You).

译文：

你会怎样给一个非常大型的社交网站设计数据结构（比如Facebook，LinkedIn）？ 设计一个算法来找到任意两个人之间的联系，比如：我 -> Bob -> Susan -> Jason -> 你

## 解答

方法：

首先，我们先不去考虑数据规模。先从简单的入手。

我们可以把每个人看作一个结点，如果两个人之间是朋友，则这两个结点间有一条边， 这样一来我们就可以构建出一个图。假设我们将“人”这个类设计如下：

```
class Person {
	Person[] friends;
	// Other info
}

```

如果要找到两个人之间的联系，即两个人之间间隔着哪些人。我们就从其中的一个人开始， 做广度优先搜索(BFS)。（做双向的BFS会更快）

但是。。。数据规模太大了！

如果我们去处理Orkut或是Facebook上的数据，单台机器根本无法完成这个任务。 因此，我们考虑用多台机器来处理这个问题。这样一来，Person这个类就需要修改了。 在Person类中，我们存储朋友的ID，然后按照以下方式找到朋友：

```
对于每个朋友id：int machine_index = lookupMachineForUserID(id);
转到标号为machine_index的机器去
Person friend = lookupFriend(machine_index);

```

对于这个问题，要考虑的优化和问题非常多，这里只列出一些。

**优化：减少机器间的跳转次数**

机器间的跳转是非常耗时的，因此我们不随机的跳转，而是进行批处理： 比如一个人，他其中的5个朋友在同一台机器上，那么跳转到那台机器后，一次性处理他们。

**聪明地划分人与机器**

由于同一国家的人更有可能是朋友，因此我们并不随机地把人分配到不同的机器上， 而是以国家，城市，州等进行划分。这样也可以减少机器间的跳转次数。

**问题：广度优先搜索会标记已访问结点，对于这个问题，你怎么处理？**

在这个问题中，有可能同时有许多人在搜索两人间的联系， 因此直接在原数据上做修改并不好。那怎么办呢？我们可以对每一个搜索， 使用一个哈希表来记录一个结点是否已经访问过。这样一来， 不同人的搜索之间就不会互相干扰。

**其它问题**

1. 在真实的世界中，服务器有可能会出故障。你会怎么做？
2. 你怎么利用缓存？
3. 你是否一直搜索直到把图上的结点都遍历一次。如何决定什么时间停止搜索。
4. 在真实世界中，你的朋友里，有一些人的朋友会更多。 那么通过他是否更有可能让你找到与特定某个人的联系。 你怎么利用这个数据来选择遍历的顺序。

下面是算法的示例代码：（java的，就不写成C++了）

```java
public class Server {	
    ArrayList<Machine> machines = new ArrayList<Machine>();
}
public class Machine {
    public ArrayList<Person> persons = new ArrayList<Person>();
    public int machineID;
}

public class Person {	
    private ArrayList<Integer> friends;
    private int ID;
    private int machineID;
    private String info;
    private Server server = new Server();
	
    public String getInfo() { return info; }
	
    public void setInfo(String info) {
        this.info = info;
    }
	
    public int[] getFriends() {
        int[] temp = new int[friends.size()];
        for (int i = 0; i < temp.length; i++) {
            temp[i] = friends.get(i);
        }
        return temp;
    }
	
	
	
    public int getID() { return ID; }
    public int getMachineID() { return machineID; }
    public void addFriend(int id) { friends.add(id); }
	
	
    // Look up a person given their ID and Machine ID
	
    public Person lookUpFriend(int machineID, int ID) {
        for (Machine m : server.machines) {
            if (m.machineID == machineID) {
                for (Person p : m.persons) {
                    if (p.ID == ID){
                        return p;						
                    }
                }
            }
        }
        return null;
    }
	
	
    // Look up a machine given the machine ID
	
    public Machine lookUpMachine(int machineID) {
        for (Machine m:server.machines) {
            if (m.machineID == machineID)
                return m;
        }
        return null;
    }
	
	
    public Person(int iD, int machineID) {
        ID = iD;
        this.machineID = machineID;
    }
}
```



## 题目12.3

原文：

Given an input file with four billion integers, provide an algorithm to generate an integer which is not contained in the file. Assume you have 1 GB of memory.

FOLLOW UP

What if you have only 10 MB of memory?

译文：

给你一个文件，里面包含40亿个整数，写一个算法找出该文件中不包含的一个整数， 假设你有1GB内存可用。

如果你只有10MB的内存呢？

## 解答

我们先来做个算术题，40亿个整数大概有多大？

```
40 * 10^8 * 4B = 16GB (大约值，因为不是按照2的幂来做单位换算)

```

这个明显无法一次性装入内存中。但是，如果我们用计算机中的一位来表示某个数出现与否， 就可以减少内存使用量。比如在一块连续的内存区域，15出现，则将第15位置1。 这个就是Bit Map算法。关于这个算法，网上有篇文章写得挺通俗易懂的，推荐：

<http://blog.csdn.net/hguisu/article/details/7880288>

如果用Bit Map算法，一个整数用一位表示出现与否，需要的内存大小是：

```
40 * 10^8 b = 5 * 10^8 B = 0.5GB

```

而我们有1GB的内存，因此该算法可行。由于Bit Map只能处理非负数， (没有说在第-1位上置1的)，因此对于有符号整数，可以将所有的数加上0x7FFFFFFF， 将数据移动到正半轴，找到一个满足条件的数再减去0x7FFFFFFF即可。 因此本文只考虑无符号整数，对于有负数的情况，按照上面的方法处理即可。

我们遍历一遍文件，将出现的数对应的那一位置1，然后遍历这些位， 找到第一个有0的位即可，这一位对应的数没有出现。代码如下：

```
#include <iostream>
#include <cstdio>
using namespace std;


int main(){
    // freopen("12.3.in", "w", stdout);
    // int miss = 12345;
    // for(int i=0; i<20000; ++i){
    //     if(i == miss) continue;
    //     cout<<i<<endl;
    // }
    // fclose(stdout);
    
    freopen("12.3.in", "r", stdin);
    
    int int_len = sizeof(int) * 8;
    int bit_len = 0xFFFFFFFF / int_len;
    int* bit = new int[bit_len];
    int v;
    while(scanf("%d", &v) != EOF){
        bit[v/int_len] |= 1<<(v%int_len);
    }
    bool found = false;
    for(int i=0; i<bit_len; ++i){
        for(int j=0; j<int_len; ++j){
            if((bit[i] & (1<<j)) == 0){
                cout<<i*int_len + j<<endl;
                found = true;
                break;
            }
                
        }
        if(found) break;
    }
    
    delete[] bit;
    fclose(stdin);
    return 0;
}

```

第二问，如果我们只有10MB的内存，明显使用Bit Map也无济于事了。 内存这么小，注定只能分块处理。我们可以将这么多的数据分成许多块， 比如每一个块的大小是1000，那么第一块保存的就是0到999的数，第2块保存的就是1000 到1999的数……实际上我们并不保存这些数，而是给每一个块设置一个计数器。 这样每读入一个数，我们就在它所在的块对应的计数器加1。处理结束之后， 我们找到一个块，它的计数器值小于块大小(1000)， 说明了这一段里面一定有数字是文件中所不包含的。然后我们单独处理这个块即可。

接下来我们就可以用Bit Map算法了。我们再遍历一遍数据， 把落在这个块的数对应的位置1(我们要先把这个数归约到0到blocksize之间)。 最后我们找到这个块中第一个为0的位，其对应的数就是一个没有出现在该文件中的数。 代码如下：

```c++
#include <iostream>
#include <cstdio>
using namespace std;

int main(){
    freopen("12.3.in", "r", stdin);// 20000 number
    int int_len = sizeof(int) * 8;
    int totalnum = 20000;
    int blocksize = 2000;
    int blocknum = totalnum / blocksize;
    int* block = new int[blocknum];
    int* bit = new int[blocksize/int_len+1];
    int v;
    while(scanf("%d", &v) != EOF){
        ++block[v/blocksize];
    }
    fclose(stdin);
    int start;
    for(int i=0; i<blocknum; ++i){
        if(block[i] < blocksize){
            start = i * blocksize;
            break;
        }
    }
    freopen("12.3.in", "r", stdin);
    while(scanf("%d", &v) != EOF){
        if(v>=start && v<start+blocksize){
            v -= start; // make v in [0, blocksize)
            bit[v/int_len] |= 1<<(v%int_len);
        }
    }

    bool found = false;
    for(int i=0; i<blocksize/int_len+1; ++i){
        for(int j=0; j<int_len; ++j){
            if((bit[i] & (1<<j)) == 0){
                cout<<i*int_len+j+start<<endl;
                found = true;
                break;
            }
        }
        if(found) break;
    }

    delete[] block;
    delete[] bit;
    fclose(stdin);
    return 0;
}
```