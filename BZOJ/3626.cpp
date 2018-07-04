#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long lint;
const int N=50002;
int n,q,cnt,fz[N],fa[N],fir[N];
int sz[N],top[N],son[N],dfn[N];
lint ans[N];
struct edge{
	int to,nx;
}eg[N];
struct node{
	int l,r,s,f;
}tr[N<<2];
struct qry{
	int r,id;
	bool z;
	bool operator < (const qry b) const {
		return r<b.r;
	}
}qy[N<<1];

inline void add(int a,int b){
	eg[++cnt]=(edge){b,fir[a]};
	fir[a]=cnt;
}

inline void upd(int k){
	tr[k].s=tr[k<<1].s+tr[k<<1|1].s;
}

inline void p_ad(int k,int f){
	tr[k].f+=f;
	tr[k].s+=f*(tr[k].r-tr[k].l+1);
}

inline void psh(int k){
	int &f=tr[k].f;
	if(f&&tr[k].l!=tr[k].r){
		p_ad(k<<1,f);
		p_ad(k<<1|1,f);
		f=0;
	}
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

void dfs1(int x){
	sz[x]=1;
	for(int i=fir[x];i;i=eg[i].nx){
		int y=eg[i].to;
		if(fa[x]!=y){
			dfs1(y);
			if(sz[son[x]]<sz[y]) son[x]=y;
			sz[x]+=sz[y];
		}
	}
}

void dfs2(int x){
	dfn[x]=++cnt;
	top[x]=son[fa[x]]==x?top[fa[x]]:x;
	if(son[x]) dfs2(son[x]);
	for(int i=fir[x];i;i=eg[i].nx){
		int y=eg[i].to;
		if(!dfn[y]) dfs2(y);
	}
}

void build(int k,int l,int r){
	tr[k]=(node){l,r,0,0};
	if(l==r) return;
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
}

void mod(int k,int x,int y){
	psh(k);
	int l=tr[k].l,r=tr[k].r,mid=(l+r)>>1;
	if(l>=x&&r<=y){
		tr[k].s+=r-l+1;
		++tr[k].f;
		return;
	}
	if(x<=mid) mod(k<<1,x,y);
	if(y>mid) mod(k<<1|1,x,y);
	upd(k);
}

lint ask(int k,int x,int y){
	psh(k);
	int l=tr[k].l,r=tr[k].r,mid=(l+r)>>1;
	if(l>=x&&r<=y) return tr[k].s;
	if(y<=mid) return ask(k<<1,x,y);
	if(x>mid) return ask(k<<1|1,x,y);
	return ask(k<<1,x,y)+ask(k<<1|1,x,y);//
}

inline void mod_t(int x){
	while(x){
		mod(1,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
}

inline lint ask_t(int x){
	lint ans(0);
	while(x){
		ans+=ask(1,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	return ans;
}
int main(){
	n=nxi(),q=nxi();
	for(int a,i=2;i<=n;++i){
		a=nxi()+1;
		fa[i]=a;
		add(a,i);
	}
	dfs1(1);
	cnt=0;
	dfs2(1);
	cnt=0;
	for(int l,r,z,i=1;i<=q;++i){
		l=nxi()+1,r=nxi()+1,z=nxi()+1;
		fz[i]=z;
		qy[++cnt]=(qry){r,i,1};
		if(l-1) qy[++cnt]=(qry){l-1,i,0};
	}
	sort(qy+1,qy+cnt+1);
	build(1,1,n);
	for(int i=1,j=1;i<=n;++i){
		mod_t(i);
		for(;qy[j].r==i;++j){
			lint t=ask_t(fz[qy[j].id]);
			ans[qy[j].id]+=qy[j].z?t:-t;
		}
	}
	for(int i=1;i<=q;++i){
		printf("%lld\n",ans[i]%201314);
	}
	return 0;
}
