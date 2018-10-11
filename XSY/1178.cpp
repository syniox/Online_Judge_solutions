#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int N=1e5+2;
int n,sz[N],dfn[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt,cnd,fir[N];
	struct edge{
		int to,nx;
	}eg[N<<1];
	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}
}

namespace BIT{
	int tr1[N],tr2[N];
	inline void mod(const int x,const int v){
		const int tp=x*v;
		for(int p=x;p<=n;p+=p&-p){
			tr1[p]+=v;
			tr2[p]+=tp;
		}
	}
	inline void mod(const int x,const int y,const int v){
		mod(x,v);
		mod(y+1,-v);
	}
	inline int ask(const int x){
		int p=x,p1=0,p2=0;
		for(;p;p-=p&-p){
			p1+=tr1[p];
			p2+=tr2[p];
		}
		return (x+1)*p1-p2;
	}
	inline int ask(const int x,const int y){
		return ask(y)-ask(x-1);
	}
}

namespace T{
	struct node{
		int f,c[2];
	}tr[N];
	inline bool isrt(const int k){
		return tr[tr[k].f].c[0]!=k&&tr[tr[k].f].c[1]!=k;
	}
	inline bool side(const int k){
		return tr[tr[k].f].c[1]==k;
	}
	inline int get_top(int k){
		while(tr[k].c[0]) k=tr[k].c[0];
		return k;
	}
	inline void rot(const int k){
		const int f=tr[k].f,ff=tr[f].f;
		const bool sid=side(k);
		int &p=tr[k].c[sid^1];
		tr[k].f=ff;
		if(!isrt(f)) tr[ff].c[side(f)]=k;
		tr[f].f=k;
		tr[f].c[sid]=p;
		tr[p].f=f;
		p=f;
	}
	inline void splay(int x){
		while(!isrt(x)){
			const int f=tr[x].f;
			if(!isrt(f)){
				rot(side(f)==side(x)?f:x);
			}
			rot(x);
		}
	}
	inline void acs(int x){
		for(int y=0;x;y=x,x=tr[x].f){
			splay(x);
			const int tp=get_top(tr[x].c[1]);
			if(tp) BIT::mod(dfn[tp],dfn[tp]+sz[tp]-1,1);
			tr[x].c[1]=y;
			if(y){
				const int tp2=get_top(y);
				BIT::mod(dfn[tp2],dfn[tp2]+sz[tp2]-1,-1);
			}
		}
	}
}

inline void dfs(const int x){
	using namespace G;
	dfn[x]=++cnd;
	sz[x]=1;
	for(int i=fir[x];i;i=eg[i].nx){
		const int y=eg[i].to;
		if(!dfn[y]){
			T::tr[y].f=x;
			dfs(y);
			BIT::mod(dfn[y],dfn[y]+sz[y]-1,1);
			sz[x]+=sz[y];
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<n;++i){
		const int x=nxi()+1,y=nxi()+1;
		G::add(x,y);
		G::add(y,x);
	}
	dfs(1);
	int q=nxi();
	while(q--){
		char op;
		while((op=getchar())!='q'&&op!='O');
		const int x=nxi()+1;
		if(op=='O') T::acs(x);
		else{
			printf("%.9lf\n",BIT::ask(dfn[x],dfn[x]+sz[x]-1)/(double)sz[x]);
		}
	}
	return 0;
}
