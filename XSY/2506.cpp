#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
typedef long long lint;
const int N=1e5+5;
int n,m,id[N];
bool odd_cir[N];

class _Pair{
	public:
		int x,y;
}eg[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace D{
	lint buk[N],*pt=buk;

	inline void insert(const lint x){
		*pt++=x;
	}
	inline void build(){
		std::sort(buk,pt);
		pt=std::unique(buk,pt);
	}
	inline int ask(const lint x){
		return std::lower_bound(buk,pt,x)-buk;
	}
}

namespace U{
	int fa[N<<1],sz[N<<1];
	int find_rt(int x){
		while(fa[x]) x=fa[x];
		return x;
	}
	inline int link(const int x,const int y){
		if(x==y) return 0;
		if(sz[x]<sz[y]){
			fa[x]=y,sz[y]+=sz[x];
			return x;
		}
		else{
			fa[y]=x,sz[y]+=sz[x];
			return y;
		}
	}
}

namespace T{
	std::vector <_Pair> tr[N<<1];
	int x,y;
	_Pair v;

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	void mod_t(const int l,const int r){
		if(l>=x&&r<=y){
			tr[idx(l,r)].push_back(v);
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_t(l,mid);
		if(y>mid) mod_t(mid+1,r);
	}

	void solve(const int l,const int r){
		static int stkx[N],stkto[N],top;
		const int k=idx(l,r);
		int lst=top;
		for(std::vector <_Pair> ::iterator it=tr[k].begin(); it!=tr[k].end(); ++it){
			int x1=U::find_rt(it->x),x2=U::find_rt(it->x+n);
			int y1=U::find_rt(it->y),y2=U::find_rt(it->y+n);
			if(x1==y1||x2==y2){
				memset(odd_cir+l,1,r-l+1);
				for(; top>lst; --top){
					U::fa[stkx[top]]=0;
					U::sz[stkto[top]]-=U::sz[stkx[top]];
				}
				return;
			}
			int linked=U::link(x1,y2);
			if(linked) stkx[++top]=linked,stkto[top]=linked^x1^y2;
			x2=U::find_rt(it->x+n),y1=U::find_rt(it->y);
			linked=U::link(x2,y1);
			if(linked) stkx[++top]=linked,stkto[top]=linked^x2^y1;
		}
		if(l<r){
			const int mid=(l+r)>>1;
			solve(l,mid);
			solve(mid+1,r);
		}
		for(; top>lst; --top){
			U::fa[stkx[top]]=0;
			U::sz[stkto[top]]-=U::sz[stkx[top]];
		}
	}

	inline void mod(const int x,const int y,const _Pair &v){
		T::x=x,T::y=y,T::v=v;
		mod_t(1,m);
	}
}

int main(){
	static int pos[N];
	n=nxi(),m=nxi();
	for(int i=1; i<=m; ++i){
		int x=nxi(),y=nxi();
		if(x>y) std::swap(x,y);
		D::insert((lint)x*n+y);
		eg[i].x=x,eg[i].y=y;
	}
	D::build();
	for(int i=1; i<=m; ++i){
		id[i]=D::ask((lint)eg[i].x*n+eg[i].y);
		if(pos[id[i]]) T::mod(pos[id[i]],i-1,eg[i]),pos[id[i]]=0;
		else pos[id[i]]=i;
	}
	for(int i=1; i<=m; ++i){
		if(pos[id[i]]) T::mod(pos[id[i]],m,eg[i]);
	}
	T::solve(1,m);
	for(int i=1; i<=m; ++i){
		puts(odd_cir[i]?"NO":"YES");
	}
	return 0;
}
