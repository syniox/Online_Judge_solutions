#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cassert>
typedef long long lint;
const int N=5e5+5;
const int mod=998244353;
int n,inv[N],preinv[N],pre2inv[N];
std::vector <int> buk[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	pre2inv[1]=preinv[1]=inv[1]=1;
	for(int i=2; i<=n+1; ++i){
		inv[i]=(lint)(mod-mod/i)*inv[mod%i]%mod;
		preinv[i]=(preinv[i-1]+inv[i])%mod;
		pre2inv[i]=(pre2inv[i-1]+preinv[i])%mod;
	}
}

namespace T{
	int x,y,v;
	class node{
		public:
			int v,npos,tag;
	}tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void upd(const int l,const int r){
		const int k=idx(l,r),mid=(l+r)>>1;
		tr[k].v=(tr[idx(l,mid)].v+tr[idx(mid+1,r)].v)%mod;
		tr[k].npos=tr[idx(l,mid)].npos;
	}

	inline void get_psh(const int l,const int r,const int v){
		const int k=idx(l,r);
		tr[k].tag=tr[k].npos=v;
		tr[k].v=(pre2inv[v-l]-pre2inv[v-r-1]+mod)%mod;
	}

	inline void psh(const int l,const int r){
		const int k=idx(l,r),mid=(l+r)>>1;
		if(l==r||!tr[k].tag) return;
		get_psh(l,mid,tr[k].tag);
		get_psh(mid+1,r,tr[k].tag);
		tr[k].tag=0;
	}

	void init(const int l,const int r){
		tr[idx(l,r)].npos=l;
		if(l==r) return;
		const int mid=(l+r)>>1;
		init(l,mid);
		init(mid+1,r);
	}

	int ask_pos_t(const int l,const int r){
		if(l==r) return l;
		psh(l,r);
		const int mid=(l+r)>>1;
		if(tr[idx(mid+1,r)].npos<x) return ask_pos_t(mid+1,r);
		return ask_pos_t(l,mid);
	}

	void mod_t(const int l,const int r){
		psh(l,r);
		if(l>=x&&r<=y){
			get_psh(l,r,v);
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_t(l,mid);
		if(y>mid) mod_t(mid+1,r);
		upd(l,r);
	}

	inline int ask_pos(const int x){
		T::x=x;
		return ask_pos_t(1,n+1);
	}

	inline void mod(const int l,const int r,const int v){
		T::x=l,T::y=r,T::v=v;
		mod_t(1,n+1);
	}
}

inline int ask(const int t){
	if(buk[t].empty()) return 0;
	int lst=0;
	for(std::vector <int> ::iterator it=buk[t].begin(); it!=buk[t].end(); lst=*it,++it){
		int pos=T::ask_pos(*it);//最后一个link小于*it的位置
		//if(lst) assert(pos>=lst);
		if(T::tr[T::idx(pos,pos)].npos>=*it) continue;
		T::mod(lst+1,pos,*it);
	}
	if(lst<n) T::mod(lst+1,n,n+1);
	return pre2inv[n]-T::tr[T::idx(1,n+1)].v;
}

int main(){
	n=nxi();
	init();
	T::init(1,n+1);
	for(int i=1; i<=n; ++i){
		const int x=nxi();
		if(x<=n) buk[x].push_back(i);
	}
	int ans=0;
	for(int i=0; i<=n; ++i){
		int tmp=ask(i);
		if(!tmp) break;
		ans=(ans+tmp)%mod;
	}
	printf("%d\n",ans<0?ans+mod:ans);
	return 0;
}
