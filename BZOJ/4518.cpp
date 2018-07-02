#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=3002;
const int Q=9000005;
int n,m,qh,qt,pre[N],dp[N][N];
//dp[i][j]=min(dp[i-1][k]+(pre[j]-pre[k+1])^2)(i<=k<j)
struct node{
	int x,y;
	node operator - (const node b) const {
		return (node){x-b.x,y-b.y};
	}
}que[Q];
inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int crs(node x,node y,node z){
	node a=y-x,b=z-y;
	return (a.x-b.y)*(a.y-b.x);
}

inline int q_sz(){
	return qt-qh+(qt<qh?Q:0)+1;
}

inline void q_psh(node x){
	if(q_sz()>1){
		node y=que[qt-2+(qt-2<0?Q:0)],z=que[qt-1==-1?Q-1:qt-1];
		while(q_sz()>1&&crs(y,z,x)<0){
			z=y;
			y=que[--qt==-1?qt=Q-1:qt];
		}
	}
	que[qt++]=x;
}

inline node q_top(int x){
	node t=que[hd];
	while(q_sz()&&t.y<t.x*x) t=que[hd++];
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1;i<=n;++i){
		pre[i]=pre[i-1]+nxi();
	}
	for(int i=1;i<=n;++i){
		dp[1][i]=pre[i]*pre[i];
		q_psh((node){pre[i]<<1,dp[1][i]<<1});
	}
	for(int i=2;i<=m;++i){
		for(int j=1;j<=n;++j){
			node k=q_top(pre[j]);
		}
	}
}
