#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=1e5+5;
int n,m;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
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
		if(rs) tr[ls].col=tr[x].col;
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
		tr[p].fa=f;
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
		int k=tr[x].c[side];
		if(side==0){
			tr[k].fa=tr[x].fa;//sum does not change
			while(tr[k].c[side^1]) k=tr[k].c[side^1];
			splay(k);
			tr[x].fa=k;
			add_v(x,k,1);
			tr[x].c[side]=0,upd(x);
			upd(k);
		}
		else{
			add_v(k,x,1);
			tr[x].c[side]=0,upd(x);
		}
	}

	inline void acs(int x,const int tgt){
		assert(isrt(tgt)&&!tr[tgt].c[0]);
		for(int y=0; G::dep[x]-tr[tr[x].c[0]].sz>=G::dep[tgt]; y=x,x=tr[x].fa){
			cut(x,1);
			add_v(y,x,-1);
			tr[x].c[1]=y,upd(x);
		}
	}

	inline void mod(const int x,const int f,const int v){
		static int org_v[N][3];
		cut(f,0);
		for(int i=f,j=tr[i].fa; j; i=j,j=tr[j].fa){
			splay(i);
			org_v[i][0]=tr[i].ask(0);
			org_v[i][1]=tr[i].ask(1);
			org_v[i][2]=tr[i].ask(2);
		}
		acs(x,f);
		splay(f);
		tr[f].col=v;
		int top=f;
		for(int i=f,j=tr[i].fa,delta; j; top=i,i=j,j=tr[j].fa){
			assert(isrt(i));
			for(int k=0; k<3; ++k){
				delta=tr[i].ask(k)-org_v[i][k];
				tr[j].val[k]+=delta;
				tr[j].sum[k]+=delta;
			}
			if(tr[j].col!=tr[i].col) break;
		}
		while(tr[top].c[0]) top=tr[top].c[0];
		splay(top);
		acs(x,top);
	}

	inline int ask(int x){
		splay(x);
		for(int y=tr[x].fa; y; x=y,y=tr[y].fa){
			splay(y);
			if(tr[x].col!=tr[y].col) break;
			cut(y,1);
			tr[y].c[1]=x;
			add_v(x,y,-1);
			upd(y);
		}
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
