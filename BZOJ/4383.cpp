#include<iostream>
#include<cstdio>
#include<cstring>
const int N=1e5+2,M=2e5+2,K=3e5+2;
int n,g,m,cn,in[(N<<1)+M],dp[(N<<1)+M],pos[N],req[(N<<1)+M],fir[(N<<1)+M];
struct edge{
	int to,wi,nx;
}eg[N+K+M*10];

inline void apx(int &x,int y){
	if(x<y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void add(int a,int b,int v){
	static int cnt;
	eg[++cnt]=(edge){b,v,fir[a]};
	fir[a]=cnt;
	++in[b];
}

namespace T{
	int x,y,t;
	struct node{
		int l,r;
	}tr[N<<1];
	void build(int k,int l,int r){
		if(l==r){
			pos[l]=k;
			return;
		}
		int mid=(l+r)>>1;
		tr[k].l=++cn;
		build(cn,l,mid);
		add(tr[k].l,k,0);
		tr[k].r=++cn;
		build(cn,mid+1,r);
		add(tr[k].r,k,0);
	}
	void mod(int k,int l,int r){
		if(l>=x&&r<=y){
			add(k,cn,0);
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid) mod(tr[k].l,l,mid);
		if(y>mid) mod(tr[k].r,mid+1,r);
	}
	void add_e(int l,int r,int t){
		T::x=l,T::y=r,T::t=t;
		mod(1,1,n);
	}
}

inline bool topu(){
	static int que[(N<<1)+M];
	static bool vis[(N<<1)+M];
	int hd=0,tl=0;
	for(int i=1;i<=cn;++i){
		if(!in[i]) que[tl++]=i,apx(dp[i],1);
	}
	while(hd!=tl){
		int x=que[hd++];
		vis[x]=1;
		if(req[x]){
			if(dp[x]>req[x]) return 0;
			else apx(dp[x],req[x]);
		}
		for(int i=fir[x];i;i=eg[i].nx){
			int y=eg[i].to;
			apx(dp[y],dp[x]+eg[i].wi);
			if(!--in[y]){
				que[tl++]=y;
			}
		}
	}
	for(int i=1;i<=n;++i){
		if(!vis[pos[i]]||dp[pos[i]]>1e9) return 0;
	}
	return 1;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
#endif
	n=nxi(),g=nxi(),m=nxi();
	cn=1;
	T::build(1,1,n);
	for(int x,i=1;i<=g;++i){
		x=nxi();
		req[pos[x]]=nxi();
	}
	for(int i=1;i<=m;++i){
		const int l=nxi(),r=nxi(),k=nxi();
		++cn;
		for(int lst=l-1,i=1;i<=k;++i){
			const int bgr=nxi();
			if(lst<bgr-1){
				T::add_e(lst+1,bgr-1,cn);
			}
			add(cn,pos[bgr],1);
			lst=bgr;
			if(i==k) T::add_e(bgr+1,r,cn);
		}
	}
	if(!topu()) puts("NIE");
	else{
		puts("TAK");
		for(int i=1;i<=n;++i){
			printf("%d ",dp[pos[i]]);
		}
		puts("");
	}
	return 0;
}
