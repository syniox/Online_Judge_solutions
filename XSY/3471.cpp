#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <sys/mman.h>
#include <unistd.h>
const int N=2e5+5;
int n,tot,val[N];

template <class T> inline void apn(T &x,const T y){
	x>y?x=y:0;
}

namespace IO{
	char *ibuf;
	struct _Init{
		_Init(){ibuf=(char*)mmap(0,lseek(0,0,SEEK_END),PROT_READ,MAP_PRIVATE,0,0);}
	}_init;
	inline int nxi(){
		int x=0;
		char c;
		while((c=*ibuf++)>'9'||c<'0');
		while(x=x*10-48+c,(c=*ibuf++)>='0'&&c<='9');
		return x;
	}
}
using IO::nxi;

namespace G{
	int cnt,fir[N*3],dfn[N*3];
	int c_scc,nval[N*3],bel[N*3];
	struct edge{
		int to,nx;
	}eg[N*30];

	inline void add(const int a,const int b){
		//printf("add: %d->%d\n",a,b);
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
		assert(cnt<N*20);
	}

	void tarjan(const int x){
		static int cnd,low[N*3],top,stk[N*3];
		stk[++top]=x;
		dfn[x]=low[x]=++cnd;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!dfn[y]){
				tarjan(y);
				apn(low[x],low[y]);
			}
			else{
				if(!bel[y]) apn(low[x],dfn[y]);
			}
		}
		if(low[x]<dfn[x]) return;
		++c_scc;
		for(int j=stk[top--]; ; j=stk[top--]){
			bel[j]=c_scc;
			if(j==x) break;
		}
	}

	inline int get_ans(){
		memset(nval+1,10,n*sizeof(int));
		int ans=0;
		for(int i=1; i<=tot; ++i){
			for(int j=fir[i]; j; j=eg[j].nx){
				if(bel[eg[j].to]!=bel[i]) nval[bel[i]]=0;
			}
		}
		for(int i=1; i<=n; ++i){
			ans+=val[i];
			apn(nval[bel[i]],val[i]);
		}
		for(int i=1; i<=n; ++i){
			if(nval[bel[i]]!=-1) ans-=nval[bel[i]];
			nval[bel[i]]=-1;
		}
		return ans;
	}
}

namespace T{
	int x,y,v,tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	void build(const int l,const int r){
		const int k=idx(l,r);
		if(l==r){
			G::add(n+k-1,l);
			return;
		}
		const int mid=(l+r)>>1;
		G::add(n+k-1,n+idx(l,mid)-1);
		G::add(n+k-1,n+idx(mid+1,r)-1);
		build(l,mid);
		build(mid+1,r);
	}

	inline void mod_t(const int l,const int r){
		assert(l<=r);
		if(l>=x&&r<=y){
			G::add(v,n+idx(l,r)-1);
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_t(l,mid);
		if(y>mid) mod_t(mid+1,r);
	}

	inline void link(const int l,const int r,const int v){
		assert(l<=r);
		T::x=l,T::y=r,T::v=v;
		mod_t(1,n);
	}
}

int main(){
	n=nxi();
	T::build(1,n);
	tot=n*3-1;
	for(int i=1; i<=n; ++i){
		const int l=nxi(),r=nxi();
		val[i]=nxi();
		T::link(l,r,i);
	}
	for(int i=1; i<=tot; ++i){
		if(!G::dfn[i]) G::tarjan(i);
	}
	printf("%d\n",G::get_ans());
	return 0;
}
