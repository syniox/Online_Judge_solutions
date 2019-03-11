#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
const int N=5e4+5;
const double eps=1e-9;
class _Line{
	public:
		double k,b;
		template <class T> inline double val(T x){
			return k*x+b;
		}
		friend inline double cross(const _Line &x,const _Line &y);
};

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline double cross(const _Line &x,const _Line &y){
	return (x.b-y.b)/(y.k-x.k);
}

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

namespace T{
	int x;
	_Line v,tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	double ask_t(const int l,const int r){
		double ans=tr[idx(l,r)].val(x);
		if(l==r) return ans;
		const int mid=(l+r)>>1;
		if(x<=mid) apx(ans,ask_t(l,mid));
		else apx(ans,ask_t(mid+1,r));
		return ans;
	}

	void mod_t(const int l,const int r){
		const int k=idx(l,r);
		double cur_l=tr[k].val(l),cur_r=tr[k].val(r);
		double new_l=v.val(l),new_r=v.val(r);
		if((new_l>cur_l)&&(new_r>cur_r)) tr[k]=v;
		if((new_l>cur_l)==(new_r>cur_r)) return;
		const int mid=(l+r)>>1;
		if(cross(tr[k],v)-eps<mid){
			if(tr[k].k<v.k) std::swap(tr[k],v);
			mod_t(l,mid);
		}
		else{
			if(tr[k].k>v.k) std::swap(tr[k],v);
			mod_t(mid+1,r);
		}
	}

	inline double ask(const int x){
		T::x=x;
		return ask_t(1,50000);
	}

	inline void mod(const _Line &v){
		T::v=v;
		mod_t(1,50000);
	}
}

int main(){
	static char ch[10];
	for(int q=nxi(); q; --q){
		scanf("%s",ch);
		if(ch[0]=='P'){
			double k,b;
			scanf("%lf%lf",&b,&k);
			b-=k;
			T::mod((_Line){k,b});
		}
		else printf("%d\n",(int)floor(T::ask(nxi())+eps)/100);
	}
	return 0;
}
