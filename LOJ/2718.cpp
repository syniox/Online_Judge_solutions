#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <queue>
typedef long long lint;
const int N=2e5+5;
int n,m;
struct edge{
	int x,y,t;
	friend bool operator < (const edge &a,const edge &b){
		return a.t<b.t;
	}
}eg[N<<1];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

namespace T{
	int cnt,rt[N<<1];
	struct node{
		int l,r,v;
	}tr[N*20];

	void clear(){
		memset(tr+1,0,cnt*sizeof(tr[0]));
		memset(rt+1,0,(m+1)*sizeof(rt[0]));
		cnt=0;
	}

	void build(int &k,const int l,const int r,const int *val){
		k=++cnt;
		if(l==r){
			tr[k].v=val[l];
			return;
		}
		const int mid=(l+r)>>1;
		build(tr[k].l,l,mid,val);
		build(tr[k].r,mid+1,r,val);
	}

	void apl(const int p,int &k,const int l,const int r,const int x,const int v){
		tr[k=++cnt]=tr[p];
		if(l==r){
			tr[k].v=v;
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) apl(tr[p].l,tr[k].l,l,mid,x,v);
		else apl(tr[p].r,tr[k].r,mid+1,r,x,v);
	}

	int ask(const int t,const int x){
		int p=rt[t];
		for(int l=1,r=n; l!=r; ){
			const int mid=(l+r)>>1;
			if(x<=mid) p=tr[p].l,r=mid;
			else p=tr[p].r,l=mid+1;
		}
		assert(p);
		return tr[p].v;
	}
}

namespace U{
	int fa[N],dep[N],ct[N],ndis[N];

	inline void clear(){
		memset(ct+1,0,n*sizeof(ct[0]));
		memset(fa+1,0,n*sizeof(fa[0]));
		memset(dep+1,0,n*sizeof(dep[0]));
	}

	inline int find_rt(int x){
		while(fa[x]) x=fa[x];
		return x;
	}

	void merge(int x,int y,const int t){
		x=find_rt(x),y=find_rt(y);
		T::rt[t]=T::rt[t+1];
		if(x==y) return;
		if(dep[x]>dep[y]){
			fa[y]=x,ct[y]=t;
			if(ndis[x]>ndis[y]){
				ndis[x]=ndis[y];
				T::apl(T::rt[t+1],T::rt[t],1,n,x,ndis[x]);
			}
		}
		else{
			dep[y]+=dep[x]==dep[y];
			fa[x]=y,ct[x]=t;
			if(ndis[y]>ndis[x]){
				ndis[y]=ndis[x];
				T::apl(T::rt[t+1],T::rt[t],1,n,y,ndis[y]);
			}
		}
	}

	int get_dis(int x,const int t){
		while(fa[x]&&ct[x]>=t) 
			x=fa[x];
		return T::ask(t,x);
	}
}

namespace G{
	int cnt,fir[N],dis[N];
	struct edge{
		int to,wi,nx;
	}eg[N<<2];
	struct data{
		int x,dis;
		friend bool operator < (const data &a,const data &b){
			return a.dis>b.dis;
		}
	};

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}

	inline void clear(){
		cnt=0;
		memset(fir+1,0,n*sizeof(fir[0]));
	}

	void dij(){
		static bool vis[N];
		std::priority_queue <data> pq;
		memset(dis+1,10,n*sizeof(dis[0]));
		memset(vis+1,0,n*sizeof(vis[0]));
		dis[1]=0;
		pq.push((data){1,0});
		while(!pq.empty()){
			const int x=pq.top().x;
			pq.pop();
			if(vis[x]) continue;
			vis[x]=1;
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				if(dis[y]>dis[x]+eg[i].wi){
					dis[y]=dis[x]+eg[i].wi;
					pq.push((data){y,dis[y]});
				}
			}
		}
	}
}

int main(){
#ifndef LOCAL
	freopen("return.in","r",stdin);
	freopen("return.out","w",stdout);
#endif
	for(int cas=nxi(); cas; --cas){
		n=nxi(),m=nxi();
		U::clear();
		G::clear();
		T::clear();
		for(int i=1; i<=m; ++i){
			const int a=nxi(),b=nxi(),l=nxi(),t=nxi();
			G::add(a,b,l);
			G::add(b,a,l);
			eg[i]=(edge){a,b,t};
		}
		G::dij();
		for(int i=1; i<=n; ++i){
			U::ndis[i]=G::dis[i];
		}
		std::sort(eg+1,eg+m+1);
		T::build(T::rt[m+1],1,n,G::dis);
		for(int i=m; i>=1; --i){
			U::merge(eg[i].x,eg[i].y,i);
		}
		for(int q=nxi(),ol=nxi(),xt=nxi(),ans=0; q; --q){
			int x=nxi(),t=nxi();
			if(ol) x=(x+ans-1)%n+1,t=(t+ans)%(xt+1);
			int l=1,r=m+1,mid;
			for(; l!=r; mid=(l+r)>>1,eg[mid].t<=t?l=mid+1:r=mid);
			printf("%d\n",ans=U::get_dis(x,r));
		}
	}
	return 0;
}
