#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
const int N=1e4+5;
int n,idx[N<<1],pos[N<<1],val[N<<1],org[N<<1];

inline int nxi(FILE *fd=stdin){
	int x=0;
	char c;
	while((c=fgetc(fd))>'9'||c<'0');
	while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
	return x;
}

inline bool cmp_org(const int a,const int b){
	return org[a]<org[b];
}

template <class T> inline void abs(const T x){
	return x<0?-x:x;
}

template <class T> inline void apn(T &x,const T y){
	x>y?x=y:0;
}

namespace G{
	int cnd,cscc,cnt,fir[N*6],bel[N*6],dfn[N*6],low[N*6];
	struct edge{
		int to,nx;
	}eg[N*126];

	void clear(){
		cnt=cscc=cnd=0;
		memset(fir,0,(n+1)*6*sizeof(int));
		memset(bel,0,(n+1)*6*sizeof(int));
		memset(dfn,0,(n+1)*6*sizeof(int));
	}

	inline void add(const int a,const int b){
		//printf("add: %d -> %d\n",a,b);
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void tarjan(const int x){
		static int top,stk[N*6];
		dfn[x]=low[x]=++cnd;
		stk[++top]=x;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!dfn[y]) tarjan(y);
			if(!bel[y]) apn(low[x],low[y]);
		}
		if(dfn[x]!=low[x]) return;
		++cscc;
		for(int i=stk[top--]; ; i=stk[top--]){
			bel[i]=cscc;
			if(i==x) break;
		}
	}
}

namespace T{
	int x,y,v;
	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	void build(const int l,const int r){
		if(l==r) return;
		const int k=idx(l,r),mid=(l+r)>>1;
		G::add(k+(n<<1),idx(l,mid)+(n<<1));
		G::add(k+(n<<1),idx(mid+1,r)+(n<<1));
		build(l,mid);
		build(mid+1,r);
	}

	void lnk_t(const int l,const int r){
		if(l>=x&&r<=y){
			G::add(v,idx(l,r)+(n<<1));
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) lnk_t(l,mid);
		if(y>mid) lnk_t(mid+1,r);
	}

	inline void lnk(const int x,const int l,const int r){
		T::x=l,T::y=r,T::v=x;
		lnk_t(1,(n<<1));
	}
}

bool jdg(const int tgt){
	G::clear();
	T::build(1,n<<1);
	for(int i=1; i<n<<1; i+=2){
		const int p1=pos[i],p2=pos[i+1];
		G::add(T::idx(p1,p1)+(n<<1),p2);
		G::add(T::idx(p2,p2)+(n<<1),p1);
	}
	for(int i=1; i<=n<<1; ++i){
		const int l=std::lower_bound(val+1,val+i+1,val[i]-tgt+1)-val;
		if(l<i) T::lnk(i,l,i-1);
		const int r=std::upper_bound(val+i,val+(n<<1)+1,val[i]+tgt-1)-val-1;
		if(r>i) T::lnk(i,i+1,r);
	}
	for(int i=1; i<=n<<1; ++i){
		if(!G::bel[i]) G::tarjan(i);
	}
	for(int i=1; i<n<<1; i+=2){
		if(G::bel[pos[i]]==G::bel[pos[i+1]]) return 0;
	}
	return 1;
}

int solve(){
	int l=0,r=1e9,mid;
	while(l!=r){
		mid=(l+r+1)>>1;
		if(jdg(mid)) l=mid;
		else r=mid-1;
	}
	return l;
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		org[(i<<1)-1]=nxi(),org[i<<1]=nxi();
	}
	for(int i=1; i<=n<<1; ++i){
		idx[i]=i;
	}
	std::sort(idx+1,idx+(n<<1)+1,cmp_org);
	for(int i=1; i<=n<<1; ++i){
		pos[idx[i]]=i;
		val[i]=org[idx[i]];
	}
	printf("%d\n",solve());
	return 0;
}
