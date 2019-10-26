#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
typedef long long lint;
const int N=2e5+5;
int n,q,t_h,t_r,vr[N],vh[N],ans[N];
std::vector <int> tw[N];
struct data{
	int id,v;
	friend bool operator < (const data &a,const data &b){
		return a.v<b.v;
	}
};
std::vector <data> qry[N];

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

class Disc{
	protected:
		int cnt,mp[N];
	public:
		inline void add(const int v){
			mp[++cnt]=v;
		}
		inline int build(){
			std::sort(mp+1,mp+cnt+1);
			cnt=std::unique(mp+1,mp+cnt+1)-mp-1;
			return cnt;
		}
		inline int lower_bound(const int v){
			return std::lower_bound(mp+1,mp+cnt+1,v)-mp;
		}
		inline int upper_bound(const int v){
			return std::upper_bound(mp+1,mp+cnt+1,v)-mp;
		}
}ds_h,ds_r;

namespace T{
	int x,v,tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	bool mpre_t(const int l,const int r){
		//<=
		int k=idx(l,r),tmp=0;
		if(!tr[k]) return 0;
		if(l==r) return tr[idx(l,r)]--;
		const int mid=(l+r)>>1;
		if(x>mid&&(tmp=mpre_t(mid+1,r),tr[k]-=tmp,tmp)) return 1;
		return (tmp=mpre_t(l,mid),tr[k]-=tmp,tmp);
	}

	void add_t(const int l,const int r){
		tr[idx(l,r)]+=v;
		if(l==r) return;
		const int mid=(l+r)>>1;
		if(x<=mid) add_t(l,mid);
		else add_t(mid+1,r);
	}

	int ask_t(const int l,const int r){
		if(l>=x) return tr[idx(l,r)];
		const int mid=(l+r)>>1;
		int ans=x<=mid?ask_t(l,mid):0;
		return ans+ask_t(mid+1,r);
	}

	inline void mpre(const int x){
		assert(x>=1);
		if(x<=1) return;
		T::x=x-1;
		mpre_t(1,t_r);
	}

	inline void add(const int x,const int v){
		T::x=x,T::v=v;
		add_t(1,t_r);
	}

	inline int ask(const int x){
		T::x=x;
		return ask_t(1,t_r);
	}
}

int main(){
	n=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		vr[i]=nxi(),ds_r.add(vr[i]);
		vh[i]=nxi(),ds_h.add(vh[i]);
	}
	t_r=ds_r.build();
	t_h=ds_h.build();
	for(int i=1; i<=n; ++i){
		vh[i]=ds_h.lower_bound(vh[i]);
		vr[i]=ds_r.lower_bound(vr[i]);
		tw[vh[i]].push_back(vr[i]);
	}
	for(int i=1; i<=t_h; ++i){
		if(!tw[i].empty()){
			std::sort(tw[i].begin(),tw[i].end());
		}
	}
	for(int i=1; i<=q; ++i){
		int r=ds_r.lower_bound(nxi()),h=ds_h.upper_bound(nxi())-1;
		if(h) qry[h].push_back((data){i,r});
	}
	for(int i=1; i<=t_h; ++i){
		for(std::vector <int> ::iterator it=tw[i].begin(); it!=tw[i].end(); ++it){
			T::mpre(*it);
		}
		for(std::vector <int> ::iterator it=tw[i].begin(); it!=tw[i].end(); ++it){
			T::add(*it,1);
		}
		for(std::vector <data> ::iterator it=qry[i].begin(); it!=qry[i].end(); ++it){
			ans[it->id]=T::ask(it->v);
		}
	}
	for(int i=1; i<=q; ++i){
		printf("%d\n",ans[i]);
	}
	return 0;
}
