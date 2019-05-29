#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
//const int N=3e4+5;
//const int S=175;
const int N=1e5+5;
const int S=320;
int n,m,val[N],bel[N];
int b_que[S][S+5],b_len[S],b_dlt[N];

namespace utils{
	template <class T> inline void apx(T &x,const T y){
		x<y?x=y:0;
	}
	template <class T> inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

namespace G{
	int cnt=1,fir[N],dfn[N],sz[N],dep[N];
	struct edge{
		int to,wi,nx;
	}eg[N];

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}

	void dfs(const int x){
		static int cnd;
		dfn[x]=++cnd;
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			dep[y]=dep[x]+eg[i].wi;
			dfs(y);
			sz[x]+=sz[y];
		}
	}
}

int getsum(int *a,int len,int v){
	//小于等于的个数
	return std::upper_bound(a+1,a+len+1,v)-a-1;
}

void build(const int p){
	int l=(p-1)*S+1,r=std::min(n,p*S);
	int cnt=0;
	int *que=b_que[p];
	for(int i=l; i<=r; ++i){
		que[++cnt]=val[i];
	}
	std::sort(que+1,que+cnt+1);
	b_len[p]=cnt;
}

void add(const int l,const int r,const int v){
	if(bel[l]==bel[r]){
		for(int i=l; i<=r; ++i){
			val[i]+=v;
		}
		build(bel[l]);
		return;
	}
	for(int i=bel[l]+1; i<bel[r]; ++i){
		b_dlt[i]+=v;
	}
	for(int i=l; bel[i]==bel[l]; ++i){
		val[i]+=v;
	}
	for(int i=r; bel[i]==bel[r]; --i){
		val[i]+=v;
	}
	build(bel[l]);
	build(bel[r]);
}

int ask(const int x,const int y,const int k){
	static int que[S<<1];
	if(y-x+1<k) return -1;
	int cnt=0;
	if(bel[x]==bel[y]){
		for(int i=x; i<=y; ++i){
			que[++cnt]=val[i]+b_dlt[bel[i]];
		}
	}
	else{
		for(int i=x; bel[i]==bel[x]; ++i){
			que[++cnt]=val[i]+b_dlt[bel[i]];
		}
		for(int i=y; bel[i]==bel[y]; --i){
			que[++cnt]=val[i]+b_dlt[bel[i]];
		}
	}
	std::sort(que+1,que+cnt+1);
	int l=0,r=n*20,mid;
	while(l!=r){
		mid=(l+r)>>1;
		int res=getsum(que,cnt,mid);
		for(int i=bel[x]+1; i<bel[y]; ++i){
			res+=getsum(b_que[i],b_len[i],mid-b_dlt[i]);
		}
		if(res>=k) r=mid;
		else l=mid+1;
	}
	return l;
}

int main(){
	n=nxi(),m=nxi();
	nxi();
	for(int i=2; i<=n; ++i){
		int f=nxi(),v=nxi();
		G::add(f,i,v);
	}
	G::dfs(1);
	for(int i=1; i<=n; ++i){
		bel[i]=(i-1)/S+1;
		val[G::dfn[i]]=G::dep[i];
	}
	for(int i=1; i<=bel[n]; ++i){
		build(i);
	}
	for(int i=1; i<=m; ++i){
		const int op=nxi(),x=nxi(),y=nxi();
		if(op==2){
			add(G::dfn[x],G::dfn[x]+G::sz[x]-1,y);
		}
		else{
			printf("%d\n",ask(G::dfn[x],G::dfn[x]+G::sz[x]-1,y));
		}
	}
	return 0;
}
