#include<iostream>
#include<cstdio>
#include<cstring>
const int N=52;
int n,cnt,cnd,hx[N],buk[N];
bool cf[N];
struct data{
	int l,r;
}dt[N];

inline int nxi(){
	int x=0;
	char c;
	while(((c=getchar())>'9'||c<'0')&&(c!='-'));
	const bool f=(c=='-')&&(c=getchar());
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return f?-x:x;
}

namespace G{
	int cnt,fir[N],col[N];
	struct edge{
		int to,wi,nx;
	}eg[N<<2];
	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,v,fir[b]};
		fir[b]=cnt;
	}
	inline void init(){
		cnt=0;
		memset(fir,0,sizeof(fir));
		for(int i=1;i<=cnd;++i){
			if(!buk[i]) add(dt[i].l,dt[i].r-1,0);
			else add(dt[i].l,dt[i].r-1,cf[dt[i].l]^cf[dt[i].r]);
		}
		for(int i=1;i<=n;++i){
			if(~hx[i]) add(i-1,i,0);
		}
		add(0,n,0);
		memset(col,-1,sizeof(col));
	}
	inline bool dfs(const int x,const int v){
		if(~col[x]) return col[x]==v;
		col[x]=v;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!dfs(y,col[x]^eg[i].wi)) return 0;
		}
		return 1;
	}
	inline bool jdg(){
		init();
		for(int i=1;i<=n;++i){
			if(col[i]==-1&&!dfs(i,0)) return 0;
		}
		return 1;
	}
}

inline bool get_ans(const int t){
	if(t==cnd) return G::jdg();
	bool vld[2];
	vld[0]=vld[1]=1;
	for(int i=1;i<=t;++i){
		const bool b1=(dt[i].l<dt[t+1].l)==(dt[i].r<dt[t+1].r);
		const bool b2=(dt[i].l<dt[t+1].r)^(dt[i].r<dt[t+1].l);
		vld[buk[i]]&=!(b1&&b2);
	}
	if(vld[0]){
		buk[t+1]=0;
		if(get_ans(t+1)) return 1;
	}
	if(vld[1]){
		buk[t+1]=1;
		if(get_ans(t+1)) return 1;
	}
	return 0;
}

int main(){
#ifndef ONLINE_JUDGE
	//	freopen("b.in","r",stdin);
#endif
	int T=nxi();
	while(T--){
		static int buk[N];
		memset(buk,0,sizeof(buk));
		cnd=0;
		n=nxi();
		for(int i=1;i<=n;++i){
			hx[i]=nxi();
			cf[i]=cf[i-1]^(hx[i]==-1);
			if(~hx[i]){
				if(!buk[hx[i]]) buk[hx[i]]=i;
				else dt[++cnd]=(data){buk[hx[i]],i};
			}
		}
		puts(get_ans(0)?"POSSIBLE":"IMPOSSIBLE");
	}
	return 0;
}
