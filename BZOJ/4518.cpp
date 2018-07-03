#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long lint;
const int N=3005;
int n,m,qh,qt,pr[N],dp[N],fp[N],que[N];

inline lint _x(int x){return pr[x]<<1;}

inline lint _y(int x){return fp[x]+pr[x]*pr[x];}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int top(int x){
	int a,b;
	while(qt-qh>1&&_y(b=que[qh+1])-_y(a=que[qh])<pr[x]*(_x(b)-_x(a))) ++qh;
	return que[qh];
}

inline bool jdg(int a,int b,int c){
	int x=_x(b),y=_y(b);
	return (x-_x(a))*(_y(c)-y)-(_x(c)-x)*(y-_y(a))>=0;//
}

inline void psh(int x){
	while(qt-qh>1&&jdg(que[qt-2],que[qt-1],x)==0) --qt;
	que[qt++]=x;
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1;i<=n;++i) pr[i]=pr[i-1]+nxi();
	for(int i=1;i<=n;++i) fp[i]=pr[i]*pr[i];
	for(int i=2;i<=m;++i){
		//get the queue before
		que[qh=(qt=1)-1]=i-1;
		for(int j=i;j<=n;++j){
			int k=top(j);
			dp[j]=fp[k]+(pr[j]-pr[k])*(pr[j]-pr[k]);
			psh(j);
		}
		memcpy(fp,dp,sizeof(dp));
	}
	printf("%d\n",m*dp[n]-pr[n]*pr[n]);
	return 0;
}
