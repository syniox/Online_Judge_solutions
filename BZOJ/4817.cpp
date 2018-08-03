#include<iostream>
#include<cstdio>
#include<cstring>
#include<cassert>
const int N=1e5+2;
int n,m,sz[N],fa[N],fir[N],dfn[N];
struct edge{
	int to,nx;
}eg[N<<1];

inline void apx(int &a,int b){
	if(a<b) a=b;
}
inline void add(int a,int b){
	static int cnt;
	eg[++cnt]=(edge){b,fir[a]};
	fir[a]=cnt;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace S{
	int x,y,v,cnt,son[N],dep[N],nfd[N],top[N];
	struct node{
		int f,s;
	}tr[N*3];
	inline void upd(int x){
		tr[x].s=std::max(tr[x<<1].s,tr[x<<1|1].s);
	}
	inline void psh(int k,bool f){
		if(tr[k].f){
			const int tp=tr[k].f;
			if(f){
				tr[k<<1].f+=tp;
				tr[k<<1].s+=tp;
				tr[k<<1|1].f+=tp;
				tr[k<<1|1].s+=tp;
			}
			tr[k].f=0;
		}
	}
	void dfs1(const int x){
		sz[x]=1;
		for(int i=fir[x];i;i=eg[i].nx){
			int y=eg[i].to;
			if(!sz[y]){
				dep[y]=dep[x]+1;
				fa[y]=x;
				dfs1(y);
				if(sz[S::son[x]]<sz[y]) S::son[x]=y;
				sz[x]+=sz[y];
			}
		}
	}
	void dfs2(const int x){
		dfn[x]=++cnt;
		nfd[cnt]=x;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		if(son[x]) dfs2(son[x]);
		for(int i=fir[x];i;i=eg[i].nx){
			int y=eg[i].to;
			if(!dfn[y]) dfs2(y);
		}
	}
	inline int lca(int x,int y){
		while(top[x]!=top[y]){
			if(dep[top[x]]<dep[top[y]]) std::swap(x,y);
			x=fa[top[x]];
		}
		return dep[x]<dep[y]?x:y;
	}
	void build(int k,int l,int r){
		if(l==r){
			tr[k].s=dep[nfd[l]];
			return;
		}
		int mid=(l+r)>>1;
		build(k<<1,l,mid);
		build(k<<1|1,mid+1,r);
		upd(k);
	}
	void mod(int k,int l,int r){
		psh(k,l!=r);
		if(l>=x&&r<=y){
			tr[k].f+=v;
			tr[k].s+=v;
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid) mod(k<<1,l,mid);
		if(y>mid) mod(k<<1|1,mid+1,r);
		upd(k);
	}
	inline void mod_t(const int l,const int r,const int p){
		x=l,y=r,v=p;
		mod(1,1,n);
	}
	int ask(const int k,const int l,const int r){
		if(l>=x&&r<=y) return tr[k].s;
		psh(k,l!=r);
		int mid=(l+r)>>1,ans=0;
		if(x<=mid) apx(ans,ask(k<<1,l,mid));
		if(y>mid) apx(ans,ask(k<<1|1,mid+1,r));
		return ans;
	}
	inline int ask_t(const int a,const int b){
		if(!a||!b) return 0;
		x=a,y=b;
		return ask(1,1,n);
	}
}

namespace L{
	struct node{
		int fa,s[2];
	}tr[N];
	inline bool isrt(int k){
		return tr[tr[k].fa].s[0]!=k&&tr[tr[k].fa].s[1]!=k;
	}
	inline bool son(int k){
		return tr[tr[k].fa].s[1]==k;
	}
	inline void init(){
		for(int i=1;i<=n;++i) tr[i].fa=fa[i];
	}
	inline void rot(int x){
		int f=tr[x].fa,k=son(x),p=tr[x].s[k^1];
		tr[f].s[k]=p;
		if(p) tr[p].fa=f;
		if(!isrt(f)) tr[tr[f].fa].s[son(f)]=x;
		tr[x].fa=tr[f].fa;
		tr[f].fa=x;
		tr[x].s[k^1]=f;
	}
	inline void splay(int k){
		while(!isrt(k)){
			int f=tr[k].fa;
			if(!isrt(f)) rot(son(f)==son(k)?f:k);
			rot(k);
		}
	}
	inline void acs(int x){
		int y=0;
		while(x){
			splay(x);
			if(tr[x].s[1]){
				int p=tr[x].s[1];
				while(tr[p].s[0]) p=tr[p].s[0];
				tr[x].s[1]=0;
				S::mod_t(dfn[p],dfn[p]+sz[p]-1,1);
			}
			if(y){
				int p=tr[x].s[1]=y;
				while(tr[p].s[0]) p=tr[p].s[0];
				S::mod_t(dfn[p],dfn[p]+sz[p]-1,-1);
			}
			y=x;
			x=tr[x].fa;
		}
	}
}

inline int lca(int x,int y){
	int z=S::lca(x,y),ans=S::ask_t(dfn[x],dfn[x])+S::ask_t(dfn[y],dfn[y]);
	return ans-(S::ask_t(dfn[z],dfn[z])<<1)+1;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<n;++i){
		int a=nxi(),b=nxi();
		add(a,b);
		add(b,a);
	}
	S::dfs1(1);
	S::dfs2(1);
	S::build(1,1,n);
	L::init();
	while(m--){
		int op=nxi(),x=nxi();
		switch(op){
			case 1:
				L::acs(x);
				break;
			case 2:
				printf("%d\n",lca(x,nxi()));
				break;
			case 3:
				printf("%d\n",S::ask_t(dfn[x],dfn[x]+sz[x]-1)+1);
				break;
		}
	}
	return 0;
}
