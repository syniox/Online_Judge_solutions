#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cassert>
typedef long long lint;
const int N=5e5+5;
const int mod=1e9+7;
int fac[N],ifac[N];
int n,x_tot,y_tot,type,tot_col[N];
std::vector <int> list[N];
class _Pair{
	public:
		int x,y;
}pnt[N];

inline char get_c(){
	static char *h,*t,buf[20000];
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while(((c=get_c())>'9'||c<'0')&&c!='-');
	const bool f=c=='-'&&(c=get_c());
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return f?-x:x;
}

template <class T> inline void twk(T &x){
	x<mod?0:x-=mod;
}
template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

template <class T> inline int fpow(int x,T t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline void init(){
	fac[0]=1;
	for(int i=1; i<N; ++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
	ifac[N-1]=fpow(fac[N-1],mod-2);
	for(int i=N-1; i; --i){
		ifac[i-1]=(lint)ifac[i]*i%mod;
	}
}

inline int C(const int x,const int y){
	if(x<y) return 0;
	return (lint)fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}

namespace D{
	int buk[N<<1],*pt=buk;
	inline void insert(const int x){
		*pt++=x;
	}
	inline void clear(){
		pt=buk;
	}
	inline int build(){
		std::sort(buk,pt);
		pt=std::unique(buk,pt);
		return pt-buk;
	}
	inline int ask(const int x){
		return std::lower_bound(buk,pt,x)-buk+1;
	}
}

namespace B{
	int tick,tr[N<<1],tag[N<<1];//上一次做完自动清空
	inline void add(int x,const int v){
		for(; x<=x_tot; x+=x&-x) twk(tr[x]+=v);
	}
	inline int ask(int x){
		lint ans=0;
		for(; x; x-=x&-x) ans+=tr[x];
		return (int)(ans%mod);
	}
	inline int ask(const int x,const int y){
		if(x>y) return 0;
		return (ask(y)-ask(x-1)+mod)%mod;
	}
}

namespace T{
	int x,y,v,tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	void add_t(const int l,const int r){
		if(l==r){
			tr[idx(l,r)]+=v;
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) add_t(l,mid);
		else add_t(mid+1,r);
		tr[idx(l,r)]=std::max(tr[idx(l,mid)],tr[idx(mid+1,r)]);
	}

	int ask_t(const int l,const int r){
		if(l>=x&&r<=y) return tr[idx(l,r)];
		const int mid=(l+r)>>1;
		int ans=0;
		if(x<=mid) ans=ask_t(l,mid);
		if(y>mid) apx(ans,ask_t(mid+1,r));
		return ans;
	}

	inline void add(const int x,const int v){
		T::x=x,T::v=v;
		add_t(1,x_tot);
	}

	inline int ask(const int x,const int y){
		if(x>y) return 0;
		T::x=x,T::y=y;
		return ask_t(1,x_tot);
	}
}

namespace S{
	int ans,cur_col[N],lst_col[N];

	inline void get_ans(){
		std::vector <int> ::iterator it;
		for(int i=1; i<=y_tot; ++i){
			const int sz=list[i].size();
			for(int j=0; j<sz; ++j){
				const int k=list[i][j],tot=tot_col[k],cur=cur_col[k];
				int lst=std::min(cur,tot-cur);
				int now=std::min(cur,tot-cur-1);
				if(j>ans&&sz-j>ans){//不计算等于
					const int x_lim=std::min(j,sz-j);
					const int y_lim=T::ask(list[i][j-1]+1,k-1);
					apx(ans,std::min(x_lim,y_lim));
					if(sz-j>ans){
						apx(ans,std::min(now,std::min(j,sz-j-1)));
					}
				}
				++cur_col[k];
				now=std::min(cur+1,tot-cur-1);
				if(lst!=now) T::add(k,now-lst);
			}
		}
	}

	inline void prt_ans(){
		if(!ans){
			printf(" 0");
			if(type==3) printf(" 0");
			return;
		}
		memset(cur_col,0,(x_tot+1)*sizeof(int));
		int res=0;
		for(int i=1; i<=y_tot; ++i){
			const int sz=list[i].size();
			for(int j=0; j<sz; ++j){
				const int k=list[i][j],tot=tot_col[k],cur=cur_col[k];
				int lst=std::min(cur,tot-cur);
				int now=std::min(cur,tot-cur-1);
				if(lst==ans&&now!=ans) B::add(k,-1);
			}
			for(int j=0; j<sz; ++j){
				const int k=list[i][j],tot=tot_col[k],cur=++cur_col[k];
				if(j>=ans&&sz-j>=ans){
					twk(res+=B::ask(j?list[i][j-1]+1:1,k-1));
					if(sz-j>ans) twk(res+=B::ask(k,k));
				}
				int lst=std::min(cur-1,tot-cur);
				int now=std::min(cur,tot-cur);
				if(lst!=ans&&now==ans) B::add(k,1);
			}
		}
		printf(" %d",res);
		if(type<=2) return;
		memset(cur_col,0,(x_tot+1)*sizeof(int));
		res=0;
		for(int i=1; i<=y_tot; ++i){
			const int sz=list[i].size();
			for(int j=0; j<sz; ++j){
				const int k=list[i][j],tot=tot_col[k],cur=cur_col[k];
				int lst=(lint)C(cur,ans)*C(tot-cur,ans)%mod;
				int now=(lint)C(cur,ans)*C(tot-cur-1,ans)%mod;
				++cur_col[k];
				res=(res+(lint)now*C(j,ans)%mod*C(sz-j-1,ans))%mod;
				if(j>=ans&&sz-j>=ans){
					int tmp=B::ask(list[i][j-1]+1,k-1);
					res=(res+(lint)tmp*C(j,ans)%mod*C(sz-j,ans))%mod;
				}
				now=(lint)C(cur+1,ans)*C(tot-cur-1,ans)%mod;
				if(now!=lst) B::add(k,(now-lst+mod)%mod);
			}
		}
		printf(" %d",res);
	}
}

int main(){
	init();
	n=nxi(),type=nxi();
	for(int i=1; i<=n; ++i){
		pnt[i].x=nxi(),pnt[i].y=nxi();
		D::insert(pnt[i].x);
	}
	x_tot=D::build();
	for(int i=1; i<=n; ++i){
		pnt[i].x=D::ask(pnt[i].x);
	}
	D::clear();
	for(int i=1; i<=n; ++i){
		D::insert(pnt[i].y);
	}
	y_tot=D::build();
	for(int i=1; i<=n; ++i){
		pnt[i].y=D::ask(pnt[i].y);
	}
	for(int i=1; i<=n; ++i){
		++tot_col[pnt[i].x];
		list[pnt[i].y].push_back(pnt[i].x);
	}
	for(int i=1; i<=y_tot; ++i){
		if(!list[i].empty()){
			std::sort(list[i].begin(),list[i].end());
		}
	}
	S::get_ans();
	printf("%d",S::ans);
	if(type>1) S::prt_ans();
	puts("");
	return 0;
}
