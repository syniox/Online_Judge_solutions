#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
typedef long long lint;
const int N=70005;
int n,q,ans[N];
std::vector <int> qbuk[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

namespace U{
	int fa[N],dep[N];
	inline int find_rt(int x){
		while(fa[x]) x=fa[x];
		return x;
	}
	int merge(int x,int y){
		if(dep[x]<dep[y]){
			fa[x]=y;
			return y;
		}
		else{
			fa[y]=x,dep[x]+=dep[x]==dep[y];
			return x;
		}
	}
}

namespace G{
	int cnt,fir[N],fa[N],sz[N],son[N],top[N],dep[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs_son(const int x){
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(sz[y]) continue;
			fa[y]=x;
			dep[y]=dep[x]+1;
			dfs_son(y);
			if(sz[y]>sz[son[x]]) son[x]=y;
			sz[x]+=sz[y];
		}
	}

	void dfs_top(const int x){
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!top[y]) dfs_top(y);
		}
	}

	int get_lca(int x,int y){
		while(top[x]!=top[y]){
			if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
			else y=fa[top[y]];
		}
		return dep[x]<dep[y]?x:y;
	}

	int get_dis(const int x,const int y){
		return dep[x]+dep[y]-dep[get_lca(x,y)]*2;
	}
}

namespace T{
	int a,b,x,y,mx,p1[N],p2[N],pl[N];
	struct st{
		int a,b;
	};
	std::vector <st> tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	void init(){
		for(int i=1; i<=n; ++i){
			pl[i]=0,p1[i]=p2[i]=i;
		}
	}

	void add_t(const int l,const int r){
		if(l>=x&&r<=y){
			tr[idx(l,r)].push_back((st){a,b});
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) add_t(l,mid);
		if(y>mid) add_t(mid+1,r);
	}

	void build(const int l,const int r){
		const int mid=(l+r)>>1,old_mx=mx,k=idx(l,r),sz=tr[k].size();
		int *rp=new int[sz],*rs=new int[sz];//parent,son
		int *r1=new int[sz],*r2=new int[sz],*rl=new int[sz];//p1,p2,pl
		for(int i=0; i<sz; ++i){
			using G::get_dis;
			const int x=tr[k][i].a,y=tr[k][i].b,rx=U::find_rt(x),ry=U::find_rt(y);
			rp[i]=U::merge(rx,ry),rs[i]=rx^ry^rp[i];
			r1[i]=p1[rp[i]],r2[i]=p2[rp[i]],rl[i]=pl[rp[i]];
			const int dx=get_dis(x,p1[rx])>get_dis(x,p2[rx])?p1[rx]:p2[rx];
			const int dy=get_dis(y,p1[ry])>get_dis(y,p2[ry])?p1[ry]:p2[ry];
			const int len=get_dis(x,dx)+get_dis(y,dy)+1;
			if(len>pl[rp[i]]){
				pl[rp[i]]=len;
				p1[rp[i]]=dx,p2[rp[i]]=dy;
			}
			apx(mx,len);
		}
		if(l==r){
			for(std::vector <int> ::iterator it=qbuk[l].begin(); it!=qbuk[l].end(); ++it){
				ans[*it]=mx;
			}
		}
		else{
			build(l,mid);
			build(mid+1,r);
		}
		for(int i=sz-1; ~i; --i){
			U::fa[rs[i]]=0;
			p1[rp[i]]=r1[i],p2[rp[i]]=r2[i];
			pl[rp[i]]=rl[i];
		}
		mx=old_mx;
	}

	void add(const int a,const int b,const int l,const int r){
		T::a=a,T::b=b,T::x=l,T::y=r;
		add_t(1,n);
	}
}

int main(){
	n=nxi(),q=nxi();
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi(),l=nxi(),r=nxi();
		G::add(a,b);
		G::add(b,a);
		T::add(a,b,l,r);
	}
	G::dfs_son(1);
	G::dfs_top(1);
	for(int i=1; i<=q; ++i){
		qbuk[nxi()].push_back(i);
	}
	T::init();
	T::build(1,n);
	for(int i=1; i<=q; ++i){
		printf("%d\n",ans[i]);
	}
	return 0;
}
