#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=1e5+5;
int n,m;

inline char get_c(){
	static char buf[20000],*h,*t;
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=get_c())>'9'||c<'0');
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return x;
}

namespace G{
	int sz[N],dep[N],fa[N],son[N],top[N];

	inline void build(){
		for(int i=2; i<=n; ++i){
			fa[i]=nxi();
		}
		for(int i=n; i>1; --i){
			sz[fa[i]]+=++sz[i];
			if(sz[son[fa[i]]]<sz[i]) son[fa[i]]=i;
		}
		for(int i=1; i<=n; ++i){
			dep[i]=dep[fa[i]]+1;
			top[i]=son[fa[i]]==i?top[fa[i]]:i;
		}
	}

	inline int get_lca(int x,int y){
		while(top[x]!=top[y]){
			dep[top[x]]>dep[top[y]]?x=fa[top[x]]:y=fa[top[y]];
		}
		return dep[x]<dep[y]?x:y;
	}
}

namespace T{//LCT节点只维护"轻"儿子信息，不维护自己
	class node{
		public:
			int col,fa,sz,c[2],val[3],sum[3];
			inline int ask(const int col){
				return (this->col==col)*(sum[col]+sz);
			}
	}tr[N];

	inline bool isrt(const int x){
		return tr[tr[x].fa].c[0]!=x&&tr[tr[x].fa].c[1]!=x;
	}

	inline bool side(const int x){
		return tr[tr[x].fa].c[1]==x;
	}

	inline void psh(const int x){
		const int ls=tr[x].c[0],rs=tr[x].c[1];
		if(ls) tr[ls].col=tr[x].col;
		if(rs) tr[rs].col=tr[x].col;
	}

	inline void add_v(const int x,const int f,const int flag){
		assert(isrt(f));
		for(int i=0; i<3; ++i){
			tr[f].val[i]+=flag*tr[x].ask(i);
			tr[f].sum[i]+=flag*tr[x].ask(i);
		}
	}

	inline void init(){
		for(int i=n; i>1; --i){
			tr[i].fa=G::fa[i];
			tr[i].sz=1;
			add_v(i,tr[i].fa,1);
		}
		tr[1].sz=1;
	}

	inline void upd(const int x){
		tr[x].sum[0]=tr[x].val[0]+tr[tr[x].c[0]].sum[0]+tr[tr[x].c[1]].sum[0];
		tr[x].sum[1]=tr[x].val[1]+tr[tr[x].c[0]].sum[1]+tr[tr[x].c[1]].sum[1];
		tr[x].sum[2]=tr[x].val[2]+tr[tr[x].c[0]].sum[2]+tr[tr[x].c[1]].sum[2];
		tr[x].sz=tr[tr[x].c[0]].sz+tr[tr[x].c[1]].sz+1;
	}

	inline void rot(const int x){
		assert(!isrt(x));
		const int f=tr[x].fa,k=side(x);
		if(!isrt(f)) tr[tr[f].fa].c[side(f)]=x;
		else tr[x].col=tr[f].col;
		int &p=tr[x].c[k^1];
		tr[x].fa=tr[f].fa;
		if(p) tr[p].fa=f;
		tr[f].fa=x;
		tr[f].c[k]=p;
		p=f;
		upd(f),upd(x);
	}

	inline void splay(const int x){
		static int stk[N];
		int *pt=stk;
		for(int f=x; !isrt(f); *pt++=(f=tr[f].fa));
		while(pt!=stk) psh(*--pt);
		while(!isrt(x)){
			const int f=tr[x].fa;
			if(!isrt(f)) rot(side(x)==side(f)?f:x);
			rot(x);
		}
	}

	inline void cut(const int x,const bool side){
		//side0: cut at the top
		splay(x);
		if(!tr[x].c[side]) return;
		psh(x);
		int k=tr[x].c[side];
		if(side==0){
			tr[k].fa=tr[x].fa;//sum does not change
			while(tr[k].c[1]) k=tr[k].c[1];
			splay(k);
			tr[x].fa=k;
			tr[x].c[side]=0;
			upd(x);
			add_v(x,k,1);
			upd(k);
		}
		else{
			add_v(k,x,1);
			tr[x].c[side]=0,upd(x);
		}
	}

	inline void merge(int x){
		for(int y=0; x; y=x,x=tr[x].fa){
			splay(x);
			if(y&&tr[x].col!=tr[y].col) break;
			cut(x,1);
			add_v(y,x,-1);
			tr[x].c[1]=y;
			upd(x);
		}
	}

	inline void acs(int x,const int tgt){
		static int org[N][3];
		assert(isrt(tgt)&&!tr[tgt].c[0]);
		for(int i=x; i; i=tr[i].fa){
			splay(i);
			if(G::dep[i]-tr[tr[i].c[0]].sz<G::dep[tgt]) break;
			org[i][0]=tr[i].ask(0);
			org[i][1]=tr[i].ask(1);
			org[i][2]=tr[i].ask(2);
		}
		for(int y=0; G::dep[x]-tr[tr[x].c[0]].sz>=G::dep[tgt]; y=x,x=tr[x].fa){
			cut(x,1);
			tr[x].sum[0]-=org[y][0],tr[x].val[0]-=org[y][0];
			tr[x].sum[1]-=org[y][1],tr[x].val[1]-=org[y][1];
			tr[x].sum[2]-=org[y][2],tr[x].val[2]-=org[y][2];
			tr[x].c[1]=y,upd(x);
		}
	}

	inline void add_delta(const int x,const int f,int org[3]){
		for(int i=0; i<3; ++i){
			int delta=tr[x].ask(i)-org[i];
			tr[f].val[i]+=delta;
			tr[f].sum[i]+=delta;
		}
	}

	inline void mod(const int x,const int f,const int v){
		static int org_f[3],org_ff[3];
		cut(f,0);
		const int ff=tr[f].fa;
		if(ff){
			merge(ff),splay(ff);
			org_f[0]=tr[f].ask(0);
			org_f[1]=tr[f].ask(1);
			org_f[2]=tr[f].ask(2);
		}
		const int fff=tr[ff].fa;
		if(fff){
			merge(fff),splay(fff);
			org_ff[0]=tr[ff].ask(0);
			org_ff[1]=tr[ff].ask(1);
			org_ff[2]=tr[ff].ask(2);
		}
		acs(x,f);
		splay(f);
		tr[f].col=v;
		if(ff){
			assert(isrt(ff));
			add_delta(f,ff,org_f);
		}
		if(fff){
			assert(isrt(fff));
			add_delta(ff,fff,org_ff);
		}
	}

	inline int ask(int x){
		merge(x),splay(x);
		return tr[x].ask(tr[x].col);
	}
}

int main(){
	n=nxi(),m=nxi();
	G::build();
	T::init();
	for(int i=1; i<=m; ++i){
		const int op=nxi();
		if(op==2) printf("%d\n",T::ask(nxi()));
		else{
			const int x=nxi(),y=nxi(),v=nxi(),lca=G::get_lca(x,y);
			T::mod(x,lca,v);
			T::mod(y,lca,v);
		}
	}
	return 0;
}
