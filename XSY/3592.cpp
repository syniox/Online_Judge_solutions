#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;
int n,q,m,val[N*5];

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

namespace G{
	int cnt,fir[N*5],ind[N*5];
	struct edge{
		int to,wi,nx;
	}eg[(int)5e6+N*3];

	inline void add(const int a,const int b,const int v){
		//printf("add: %d->%d v%d\n",a,b,v);
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
		++ind[b];
	}

	bool getans(){
		static int que[N],req_v[N*5];
		static bool vis[N];
		memset(req_v,63,sizeof(req_v));
		int hd=0,tl=0;
		for(int i=1; i<n*3+m; ++i){
			if(!ind[i]){
				if(!val[i]) val[i]=1e9;
				que[tl++]=i;
			}
		}
		while(hd!=tl){
			const int x=que[hd++];
			if(req_v[x]<val[x]) return 0;
			if(!val[x]) val[x]=req_v[x];
			if(x<=n) vis[x]=1;
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				apn(req_v[y],val[x]-eg[i].wi);
				if(!--ind[y]) que[tl++]=y;
			}
		}
		for(int i=1; i<=n; ++i){
			if(!vis[i]) return 0;
		}
		return 1;
	}
}

namespace T{
	int x,y,t;
	inline int idx(const int l,const int r){
		return ((l+r)|(l!=r))-1;
	}
	void build(const int l,const int r){
		if(l==r){
			G::add(idx(l,r)+n+m,l,0);
			return;
		}
		const int mid=(l+r)>>1;
		G::add(idx(l,r)+n+m,idx(l,mid)+n+m,0);
		G::add(idx(l,r)+n+m,idx(mid+1,r)+n+m,0);
		build(l,mid);
		build(mid+1,r);
	}
	inline void add_t(const int l,const int r){
		if(l>=x&&r<=y){
			G::add(t,idx(l,r)+n+m,0);
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) add_t(l,mid);
		if(y>mid) add_t(mid+1,r);
	}
	inline void add(const int x,const int l,const int r){
		T::x=l,T::y=r,T::t=x;
		add_t(1,n);
	}
}

int main(){
	n=nxi(),q=nxi(),m=nxi();
	for(int i=1; i<=q; ++i){
		int x=nxi();
		val[x]=nxi();
	}
	T::build(1,n);
	for(int i=1; i<=m; ++i){
		static int buk[N];
		const int l=nxi(),r=nxi(),t=nxi();
		for(int j=1; j<=t; ++j){
			buk[j]=nxi();
			G::add(buk[j],n+i,1);
		}
		for(int lst=l-1,j=1; j<=t; lst=buk[j++]){
			if(lst<buk[j]-1){
				T::add(n+i,lst+1,buk[j]-1);
			}
		}
		if(buk[t]<r){
			T::add(n+i,buk[t]+1,r);
		}
	}
	if(!G::getans()) puts("Impossible");
	else{
		puts("Possible");
		for(int i=1; i<=n; ++i){
			printf("%d ",val[i]);
		}
		puts("");
	}
	return 0;
}
