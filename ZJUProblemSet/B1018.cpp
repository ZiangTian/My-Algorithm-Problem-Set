// 大家应该都会玩“锤子剪刀布”的游戏：两人同时给出手势，胜负规则如图所示：

// 现给出两人的交锋记录，请统计双方的胜、平、负次数，并且给出双方分别出什么手势的胜算最大。

// 输入格式：
// 输入第 1 行给出正整数 N（≤105），即双方交锋的次数。随后 N 行，每行给出一次交锋的信息，即甲、乙双方同时给出的的手势。C 代表“锤子”、J 代表“剪刀”、B 代表“布”，第 1 个字母代表甲方，第 2 个代表乙方，中间有 1 个空格。

// 输出格式：
// 输出第 1、2 行分别给出甲、乙的胜、平、负次数，数字间以 1 个空格分隔。第 3 行给出两个字母，分别代表甲、乙获胜次数最多的手势，中间有 1 个空格。如果解不唯一，则输出按字母序最小的解。

// 输入样例：
// 10
// C J
// J B
// C B
// B B
// B C
// C C
// C B
// J B
// B C
// J J
// 输出样例：
// 5 3 2
// 2 3 5
// B B

#include <cstdio>
int main() {
    int n, a=0, b=0, c=0, jia[3]={0}, yi[3]={0};
    scanf("%d",&n);
    getchar();
    while(n--) {
        char g1,g2;
        scanf("%c %c",&g1,&g2);
        if(g1=='C'&&g2=='J'||g1=='J'&&g2=='B'||g1=='B'&&g2=='C') {
            a++;
            if(g1=='C') jia[1]++;
            if(g1=='J') jia[2]++;
            if(g1=='B') jia[0]++;
        }
        else if(g1==g2) {
            b++;
        }
        else {
            c++;
            if(g2=='C') yi[1]++;
            if(g2=='J') yi[2]++;
            if(g2=='B') yi[0]++;
        }
        getchar();
    }
    printf("%d %d %d\n%d %d %d\n",a,b,c,c,b,a);
    int flag1=-1, flag2=-1, max1=-1, max2=-1;
    for(int i=0; i<3; i++) {
        if(jia[i]>max1) {
            max1=jia[i];
            flag1=i;
        }
        if(yi[i]>max2) {
            max2=yi[i];
            flag2=i;
        }
    }
    if(flag1==0) printf("B ");
    else if(flag1==1) printf("C ");
    else printf("J ");
    if(flag2==0) printf("B");
    else if(flag2==1) printf("C");
    else printf("J");
}