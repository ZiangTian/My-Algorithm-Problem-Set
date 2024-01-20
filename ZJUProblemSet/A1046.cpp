//注意本题技巧，对dis数组进行预处理，即直接存储1号顶点到每个顶点的距离
//这样可以直接作差得到结果，而不要把每段距离分别存储，否则会有求和运算，导致超时
#include <cstdio>
#include <cmath>
int min(int a, int b) {
    return (a<b)?a:b;
}
int main() {
    int n,m,sum=0;
    scanf("%d",&n);
    int dis[n+1]={0};
    //PreProcess
    for(int i=1; i<=n; i++) {
        int d;
        scanf("%d",&d);
        sum+=d;
        dis[i+1]=dis[i]+d;
    }//EndPreProcess

    scanf("%d",&m);
    while(m--) {
        int a,b,c;
        scanf("%d%d",&a,&b);
        c=abs(dis[a]-dis[b]);
        printf("%d\n",min(c,sum-c));
    }
}