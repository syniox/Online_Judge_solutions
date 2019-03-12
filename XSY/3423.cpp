#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
const int N=1e5+5;
const int eps=1e-8;
typedef long long lint;
int n,ans;
struct _pep{
	int l,r,v;
}pep[2][N];
class _Line{
	public:
		lint k,b;
		inline lint val(const int x){
			return k*x+b;
		}
};

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}
template <class T> inline void apn(T &x,const T y){
	x>y?x=y:0;
}

inline bool cmp_r(const _pep &a,const _pep &b){
	return a.r<b.r;
}
inline bool cmp_l(const _pep &a,const _pep &b){
	return a.l<b.l;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline double get_crs(const _Line &a,const _Line &b){
	return (double)(a.b-b.b)/(double)(b.k-a.k);
}

namespace B{
	int tick,tag[N];
	lint tr[N];
	inline void clear(){
		++tick;
	}
	inline void upd(const int x){
		if(tag[x]<tick) tag[x]=tick,tr[x]=-1e12;
	}
	inline void mod(int x,const lint v){
		for(; x<=n; x+=x&-x) upd(x),apx(tr[x],v);
	}
	inline lint ask(int x){
		lint ans=-1e12;
		for(; x; x-=x&-x) upd(x),apx(ans,tr[x]);
		return ans;
	}
}

namespace T{
	_Line tr[N<<1];
	int x,y,tick,tag[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void clear(){
		++tick;
	}

	inline void upd(const int k){
		if(tag[k]!=tick){
			tr[k].k=tr[k].b=0;
			tag[k]=tick;
		}
	}

	lint ask_t(const int l,const int r){
		upd(idx(l,r));
		lint ans=tr[idx(l,r)].val(x);
		if(l==r) return ans;
		const int mid=(l+r)>>1;
		if(x<=mid) apx(ans,ask_t(l,mid));
		else apx(ans,ask_t(mid+1,r));
		return ans;
	}

	void mod_t(const int l,const int r,_Line v){
		upd(idx(l,r));
		const int mid=(l+r)>>1;
		if(l>=x&&r<=y){
			const int k=idx(l,r);
			const lint cur_l=tr[k].val(l),cur_r=tr[k].val(r);
			const lint new_l=v.val(l),new_r=v.val(r);
			if((cur_l<=new_l)&&(cur_r<=new_r)) tr[k]=v;
			if((cur_l<=new_l)==(cur_r<=new_r)) return;
			const double crs=get_crs(tr[k],v);
			if(crs+eps<(double)mid){
				if(tr[k].k<v.k) std::swap(tr[k],v);
				mod_t(l,mid,v);
			}
			else{
				if(tr[k].k>v.k) std::swap(tr[k],v);
				mod_t(mid+1,r,v);
			}
		}
		if(x<=mid) mod_t(l,mid,v);
		if(y>mid) mod_t(mid+1,r,v);
	}

	inline lint ask(const int x){
		T::x=x;
		return ask_t(1,N-1);
	}

	inline void mod(const int l,const int r,const _Line v){
		T::x=l,T::y=r;
		mod_t(1,N-1,v);
	}
}

inline lint solve_bel(){
	std::sort(pep[0]+1,pep[0]+n+1,cmp_r);
	std::sort(pep[1]+1,pep[1]+n+1,cmp_r);
	B::clear();
	lint ans=0;
	for(int i=n,j=n; i; --i){
		for(; j&&pep[1][j].r>=pep[0][i].r; --j){
			B::mod(pep[1][j].l,pep[1][j].v);
		}
		lint tmp=B::ask(pep[0][i].l);
		if(tmp<=-1e12) tmp=0;
		apx(ans,(lint)(pep[0][i].r-pep[0][i].l+1)*pep[0][i].v*tmp);
	}
	return ans;
}

inline lint solve_crs(){
	std::sort(pep[0]+1,pep[0]+n+1,cmp_l);
	std::sort(pep[1]+1,pep[1]+n+1,cmp_l);
	T::clear();
	lint ans=0;
	for(int i=n,j=n; ~i; --i){
		for(; j&&pep[0][j].l>=pep[1][i].l; --j){
			_Line tmp=(_Line){pep[0][j].v,-(lint)(pep[0][j].l-1)*pep[0][j].v};
			T::mod(pep[0][j].l,pep[0][j].r,tmp);
		}
		apx(ans,T::ask(pep[1][i].r)*pep[1][i].v);
	}
	return ans;
}

int main(){
	n=nxi();
	for(int i=0; i<2; ++i){
		for(int j=1; j<=n; ++j){
			pep[i][j].l=nxi();
			pep[i][j].r=nxi();
			pep[i][j].v=nxi();
		}
	}
	lint ans=0;
	apx(ans,solve_bel());
	std::swap(pep[0],pep[1]);
	apx(ans,solve_bel());
	apx(ans,solve_crs());
	std::swap(pep[0],pep[1]);
	apx(ans,solve_crs());
	printf("%lld\n",ans);
	return 0;
}
