#include<iostream>
#include<cstdio>
#include<cstring>
#include<bitset>
#include<cassert>
#define ni nxi<int>()
typedef unsigned long long ull;
const int N=1e5+2;
int n,m,bit,op[N],fa[N],dep[N],dfn[N],nfd[N],top[N];
ull hx[N];
//&1,|2,^3
struct node{
	//u:up d:down
	ull u0,u1,d0,d1;
};

inline char gtc(){
	static char buf[20000],*h,*t;
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
	}
	return *h++;
}

template <class T> inline T nxi(){
	T x=0;
	char c;
	while((c=gtc())>'9'||c<'0');
	while(x=x*10-48+c,(c=gtc())>='0'&&c<='9');
	return x;
}
//calc:graph
inline ull calc(const ull x,const int k){
	if(op[k]==1) return x&hx[k];
	if(op[k]==2) return x|hx[k];
	return x^hx[k];
}

inline node merge(const node x,const node y){
	node ans;
	ans.d0=(x.d0&y.d1)|(~x.d0&y.d0);
	ans.d1=(x.d1&y.d1)|(~x.d1&y.d0);
	ans.u0=(y.u0&x.u1)|(~y.u0&x.u0);
	ans.u1=(y.u1&x.u1)|(~y.u1&x.u0);
	return ans;
}

namespace G{
	int sz[N],son[N],fir[N];
	struct edge{
		int to,nx;
	}eg[N<<1];
	inline void add(int x,int y){
		static int cnt;
		eg[++cnt]=(edge){y,fir[x]};
		fir[x]=cnt;
	}
	void dfs1(int x){
		sz[x]=1;
		for(int i=fir[x];i;i=eg[i].nx){
			int y=eg[i].to;
			if(!sz[y]){
				dep[y]=dep[x]+1;
				fa[y]=x;
				dfs1(y);
				if(sz[y]>sz[son[x]]) son[x]=y;
				sz[x]+=sz[y];
			}
		}
	}
	void dfs2(int x){
		static int cnt;
		dfn[x]=++cnt;
		nfd[cnt]=x;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		if(son[x]) dfs2(son[x]);
		for(int i=fir[x];i;i=eg[i].nx){
			int y=eg[i].to;
			if(!dfn[y]) dfs2(y);
		}
	}
}

namespace T{
	int x,y;
	//0up 1down
	node tr[N*3];
	inline void upd(int k){
		tr[k]=merge(tr[k<<1],tr[k<<1|1]);
	}
	void build(int k,int l,int r){
		if(l==r){
			tr[k].u0=tr[k].d0=calc(0,nfd[l]);
			tr[k].u1=tr[k].d1=calc(~0ull,nfd[l]);
			return;
		}
		int mid=(l+r)>>1;
		build(k<<1,l,mid);
		build(k<<1|1,mid+1,r);
		upd(k);
	}
	void mod(int k,int l,int r){
		if(l==r){
			tr[k].u0=tr[k].d0=calc(0,nfd[l]);
			tr[k].u1=tr[k].d1=calc(~0ull,nfd[l]);
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid) mod(k<<1,l,mid);
		else mod(k<<1|1,mid+1,r);
		upd(k);
	}
	node ask(int k,int l,int r){
		if(l>=x&&r<=y) return tr[k];
		int mid=(l+r)>>1;
		if(x>mid) return ask(k<<1|1,mid+1,r);
		if(y<=mid) return ask(k<<1,l,mid);
//		if(!zf) return merge(ask(k<<1|1,mid+1,r),ask(k<<1,l,mid));
		return merge(ask(k<<1,l,mid),ask(k<<1|1,mid+1,r));
	}
	inline node ask_t(int a,int b){
		T::x=a,T::y=b;
		return ask(1,1,n);
	}
}

inline ull ask_G(int x,int y,ull z){
	node getx,gety;
	const ull ff=~(ull)0;
	getx=gety=(node){0,ff,0,ff};
	//upper segment always first
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]){
			getx=merge(T::ask_t(dfn[top[x]],dfn[x]),getx);
			x=fa[top[x]];
		}else{
			gety=merge(T::ask_t(dfn[top[y]],dfn[y]),gety);
			y=fa[top[y]];
		}
	}
	if(dep[x]>dep[y])
		getx=merge(T::ask_t(dfn[y],dfn[x]),getx);
	else
		gety=merge(T::ask_t(dfn[x],dfn[y]),gety);

	ull ans0=(getx.u0&gety.d1)|(~getx.u0&gety.d0);
	ull ans1=(getx.u1&gety.d1)|(~getx.u1&gety.d0);
	ull ans=0;
	bool f=0;
	for(int i=63;i>=0;--i){
		if(ans0&(1ull<<i)){
			if(z&(1ull<<i)) f=1;
			ans|=1ull<<i;
		}
		else{
			if((ans1&(1ull<<i))){
				if(f||(z&(1ull<<i))) ans|=1ull<<i;
			}
			else if(z&(1ull<<i)) f=1;
		}
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("8.in","r",stdin);
#endif
	n=ni,m=ni,bit=ni;
	for(int i=1;i<=n;++i){
		op[i]=ni,hx[i]=nxi<ull>();
	}
	for(int i=1;i<n;++i){
		int x=ni,y=ni;
		G::add(x,y);
		G::add(y,x);
	}
	G::dfs1(1);
	G::dfs2(1);
	T::build(1,1,n);
	while(m--){
		int q=ni,x=ni,y=ni;
		ull z=nxi<ull>();
		if(q==1) printf("%llu\n",ask_G(x,y,z));
		else{
			op[x]=y,hx[x]=z;
			T::x=dfn[x];
			T::mod(1,1,n);
		}
	}
	return 0;
}
