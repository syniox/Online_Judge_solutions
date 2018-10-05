#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int N=1002;
int n,m,in[N],hx[N],fir[N];
lint dp[N];
bool map[N][N];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void topo(){
	static int que[N];
	int hd=0,tl=0,cnt=0;
	for(int i=1;i<=n;++i){
		if(!in[i]) que[tl++]=i;
	}
	while(hd!=tl){
		const int x=que[hd++];
		hx[x]=++cnt;
		for(int i=1;i<=n;++i){
			if(!map[x][i]) continue;
			if(!--in[i]) que[tl++]=i;
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=m;++i){
		const int x=nxi()+1,y=nxi()+1;
		if(x>y){
			map[x][y]=1;
			++in[y];
		}
		else{
			map[y][x]=1;
			++in[x];
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=i+1;j<=n;++j){
			if(!map[i][j]&&!map[j][i]){
				map[i][j]=1;
				++in[j];
			}
		}
	}
	topo();
	hx[n+1]=1e8;
	dp[0]=1;
	for(int i=1;i<=n+1;++i){
		int max_hx=-1e8;
		for(int j=i-1;j>=0;--j){
			if(max_hx<hx[j]&&hx[j]<hx[i]) dp[i]+=dp[j];
			if(hx[j]<hx[i]) apx(max_hx,hx[j]);
		}
	}
	printf("%lld\n",dp[n+1]);
	return 0;
}
