#include <iostream>
#include <cstdio>
#include <cstring>
const int N=2005;
int n,m,hx[N],dp[2][N];
char ch[N];

template <class T> inline bool apn(T &x,const T y){
	if(x<y) return 0;
	x=y;
	return 1;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int get(const int i,const int j,const int k){
	if(((hx[i]-j-k)<<1)-k<0) return 1e8;
	return dp[(i&1)^1][((hx[i]-j-k)<<1)-k]+hx[i]-j-k;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("b.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=n;++i){
		scanf("%s",ch+1);
		for(int j=1;j<=m;++j){
			if(ch[j]=='*'&&!hx[j]) hx[j]=n-i+1;
		}
	}
	for(int i=1;i<=m;++i){
		const int p=i&1;
		memset(dp[p],10,sizeof(dp[p]));
		for(int j=0,k=hx[i]>>1;j<=hx[i];++j){
			for(k=std::min(k+1,(hx[i]-j)>>1);k>=0;--k){
				if(!apn(dp[p][j],get(i,j,k))) break;
			}
		}
		for(int j=hx[i]+1;j<=n;++j){
			dp[p][j]=dp[p^1][0];
		}
	}
	printf("%d\n",dp[m&1][0]);
	return 0;
}
