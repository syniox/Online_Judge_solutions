#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
const int N=105;
int n,m,q,hx[N],pos[N],hei[N],dp[N][N][N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline void init(){
	memset(dp,0,sizeof(dp));
	memset(hx,0,sizeof(hx));
}

inline void sanitize(){
	static int qx[N],qy[N];
	for(int i=1;i<=n;++i){
		qx[i]=nxi(),qy[i]=nxi();
	}
	memcpy(pos+1,qx+1,n<<2);
	memcpy(hei+1,qy+1,n<<2);
	std::sort(pos+1,pos+n+1);
	std::sort(hei+1,hei+n+1);
	int nwn=std::unique(pos+1,pos+n+1)-pos-1;
	m=std::unique(hei+1,hei+n+1)-hei-1;
	for(int i=1;i<=n;++i){
		int tp=std::lower_bound(pos+1,pos+nwn+1,qx[i])-pos;
		apx(hx[tp],(int)(std::lower_bound(hei+1,hei+m+1,qy[i])-hei));
	}
	n=nwn;
}

int dfs(int l,int r,const int t){
	while(l<=r&&hx[l]<=t) ++l;
	while(l<=r&&hx[r]<=t) --r;
	if(l>=r) return l==r;
	if(dp[l][r][t]) return dp[l][r][t];
	int ans=1e9;
	for(int i=l;i<r;++i){
		apn(ans,dfs(l,i,t)+dfs(i+1,r,t));
	}
	int tp=std::upper_bound(hei+1,hei+m+1,q/(pos[r]-pos[l]))-hei-1;
	return dp[l][r][t]=std::min(ans,tp==t?N:dfs(l,r,tp)+1);
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("b.in","r",stdin);
#endif
	int T=nxi();
	while(T--){
		n=nxi(),q=nxi();
		init();
		sanitize();
		printf("%d\n",dfs(1,n,0));
	}
	return 0;
}
