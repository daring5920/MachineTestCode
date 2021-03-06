/*
练习题：
时间限制：1秒          内存限制：32兆
题目描述：
把一个个大小差一圈的筐叠上去，使得从上往下看时，边筐花色交错。这个工作现在要让计算机来完成，得看你的了。

输入：
输入是一个个的三元组，分别是，外筐尺寸n（n为满足0<n<80的奇整数），中心花色字符，外筐花色字符，后二者都为ASCII可见字符；

输出：
输出叠在一起的筐图案，中心花色与外筐花色字符从内层起交错相叠，多筐相叠时，最外筐的角总是被打磨掉。叠筐与叠筐之间应有一行间隔。

样例输入：
11 B A
5 @ W

样例输出：
 AAAAAAAAA 
ABBBBBBBBBA
ABAAAAAAABA
ABABBBBBABA
ABABAAABABA
ABABABABABA
ABABAAABABA
ABABBBBBABA
ABAAAAAAABA
ABBBBBBBBBA
 AAAAAAAAA 

 @@@ 
@WWW@
@W@W@
@WWW@
 @@@ 

@author:JeriYang
@time:2018
思路见代码下方
*/

#include<stdio.h>
int main () {
    int outPutBuf[82][82]; //用于预排版的输出缓存
    char a , b, c;            //输入的两个字符
    int n;                 //叠框大小
    bool firstCase = true; //是否为第一组数据标志，初始值为true
	while (scanf ("%d %c %c",&n,&a,&b) == 3){
		if (firstCase == true){  //若是第一组数据
			firstCase = false;   //将第一组数据标志标记成false
		}
        else printf("\n"); //否则输出换行
		for (int i = 1,j = 1; i <= n; i += 2,j ++){ //从里至外输出每个圈
			//获取中心坐标
			int x = n / 2 + 1; 
			int y = x;
			//获取每个圈右上角点的坐标
			x =x - j + 1;
			y =y - j + 1; 
            //获取当前圈使用字符
			if(j%2 == 1){
				c = a;
			}
			else c = b;
			//对当前圈进行赋值,排版
            for (int k = 1; k <= i; k ++) { 
                outPutBuf[x + k - 1][y] = c;         //左边赋值
                outPutBuf[x][y + k - 1] = c;         //上边赋值
                outPutBuf[x + i - 1][y + k - 1] = c; //右边赋值
                outPutBuf[x + k - 1][y + i - 1] = c; //下边赋值
            }
        }
        if (n != 1){ //注意当n为1时不需此步骤
            outPutBuf[1][1] = ' ';
            outPutBuf[n][1] = ' ';
            outPutBuf[1][n] = ' ';
            outPutBuf[n][n] = ' '; //将四角置为空格
        }
		//output
        for (i = 1; i <= n; i ++){
            for (int j = 1; j <= n; j ++){
                printf("%c",outPutBuf[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}


/*
思路(来源于《计算机考研机试指南》)：

我们利用一个缓存数组来表示将要输出的字符阵列，
我们对该字符阵列的坐标作如下规定：
规定阵列左上角字符坐标为（1，1)，阵列右下角字符坐标为（n，n），其它坐标可由此推得。
程序按照由最内圈至最外圈的的顺序来完成图形的排列。

在完成每圈排列时，我们都需要注意两个要点：
1.首先需要确定该圈左上角的坐标。我们将以这个坐标为参照点来完成该圈的其它字符位置的确定（当然也可以选用其它点）。
观察图形得知，最中间圈的左上角字符坐标为(n / 2 + 1,n / 2 + 1)，次中间圈的左上角字符坐标为（n / 2 + 1- 1,n / 2 + 1 - 1),
依次类推即可得到图形中每一个圈的参照点。其次，我们需要计算该圈每边边长长度。
这也较容易得出，中心圈长度为 1，次中心圈长度为 3，依次类推，外圈总比内圈长度增加 2
注意了这两点以后，我们按照以下顺序完成每圈的排版，
a.首先明确该圈使用哪一个字符来填充，我们使用判断循环次数指示变量 j 的奇偶性来判断当前需要使用的字符，
即奇数次循环时（j 为奇数）时使用第一个字符，偶数次循环时使用第二个字符。
b.然后，我们确定该圈左上角字符的坐标，我们使用中心坐标（n / 2 + 1，n / 2 + 1）减去当前循环次数指示变量 j 来确定该圈左上角坐标，即（n / 2 + 1- j,n / 2 + 1 - j)。
c.接着，我们计算该圈边长长度，我们利用初始值为 1 的循环指示变量 i 来表示边长长度，并在每次循环结束后加 2，代表边长由 1 开始，每外移一个圈边长长度即加上 2。
利用变量 i 所存的值我们即可对当前圈的四条边进行赋值，对应的坐标已在代码中给出，这里不再列举。
在完成所有圈的编排后，我们只需按照题目的需要去除四个角的字符，
最后将整个输出缓存中的字符阵列输出即可。

另外，此代码还有两个注意点值得我们指出。
1.输出格式。题面要求我们在输出的每个叠筐间输出一个空行，即除了最后一个叠筐后没有多余的空行，其它叠筐输出完成后都需要额外的输出一个空行。
为了完成这个要求，我们将要求形式改变为除了在第一个输出的叠筐前不输出一个空行外，在其它每一个输出的叠筐前都需要输出一个额外的空行。
为完成这一目的，我们在程序开头设立了 firstCase 变量来表示正在处理数据的是否为第一组数据，毫无疑问它的初始值为 true。
在程序读取每组数据后，我们都测试 firstCase的值，若其为 true 则表示当前处理的数据为第一组数据，我们不输出空行，并在此时将 firstCase 变量改变为 false。
以后，每当程序读入数据，测试 firstCase 变量时，该变量均为 false，于是我们完成题目的要求，在输出的叠筐前额外的输出一个空行，来达到题面对于输出格式的要求。

2.边界数据处理。按上文所说，我们在输出缓存中完成字符阵列排版后，需要将该阵列四个角的字符修改为空格，但是这一修改不是一定需要的。
当输入的n 为 1 时，该修改会变得多余，它会使输出仅变为一个空格，这与题面要求不符。
因此，在进行该修改之前，我们需要对 n 的数值作出判断，若其不为 1 则进行修改，否则跳过修改部分。
由此不难看出，机试考题要求我们在作答时，不仅能够大致的把握算法，同时还要细致的考虑边界数据会给我们的程序造成什么样的影响。
只有充分考虑了所有情况，并保证在所有题面明确将会出现的条件下，程序依旧能够正常工作，这样我们才能使自己的程序真正的万无一失、滴水不漏。

本例介绍了另一种解决排版题的思路，当输出图形所具有的规律不能或者很难直接应用到输出上时，
我们就要考虑采用该例所采用的方法，先用一个二维数组来保存将要输出的字符阵列，并在该数组上首先完成排版。
因为没有了输出时从上至下、从左至右的顺序限制，我们能更加随意的按照自己的需要或者图形的规律来依次输出图形，从而完成题目要求。
*/
