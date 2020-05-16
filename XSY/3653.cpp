#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
typedef long long lint;
const int N=2e5+5;
int n,q,ans[N],valx[N];
struct opt{
	int type,tick,v,x;
};
std::vector <opt> op_b[N];

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

namespace T{
	int cnt,x,v;
	struct node{
		int sum,vpre,ppre;//sum,min_presum,min_presum_pos(right)
		inline void set(const int v){
			ppre=0;
			sum=vpre=v;
		}
	}tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void upd(const int l,const int r){
		const int k=idx(l,r),mid=(l+r)>>1;
		const int ls=idx(l,mid),rs=idx(mid+1,r);
		tr[k].sum=tr[ls].sum+tr[rs].sum;
		if(tr[ls].vpre<tr[ls].sum+tr[rs].vpre){
			tr[k].ppre=tr[ls].ppre;
			tr[k].vpre=tr[ls].vpre;
		}
		else{
			tr[k].ppre=(mid-l+1)+tr[rs].ppre;
			tr[k].vpre=tr[ls].sum+tr[rs].vpre;
		}
	}

	int getsum_t(const int l,const int r){
		const int mid=(l+r)>>1;
		if(r<=x) return tr[idx(l,r)].sum;
		int ans=getsum_t(l,mid);
		if(x>mid) ans+=getsum_t(mid+1,r);
		return ans;
	}

	int find_x_t(const int l,const int r,const int v){
		//从后往前第一个前缀和<=v的数的位置(0-index)
		const int k=idx(l,r),mid=(l+r)>>1;
		if(tr[k].vpre>v) return -1;
		if(l==r) return 0;
		int ans=-1;
		if(x>mid&&~(ans=find_x_t(mid+1,r,v-tr[idx(l,mid)].sum))) return ans+mid-l+1;
		return find_x_t(l,mid,v);
	}

	void set_v_t(const int l,const int r){
		if(l==r){
			tr[idx(l,r)].set(v);
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) set_v_t(l,mid);
		else set_v_t(mid+1,r);
		upd(l,r);
	}

	int getsum(const int x){
		T::x=x;
		return getsum_t(0,q);
	}

	int find_x(const int x,const int v){
		//第一个前缀和<=sum[x]-v的数
		T::x=x-1;
		return find_x_t(0,q,getsum(x)-v);
	}

	void set_v(const int x,const int v){
		T::x=x,T::v=v;
		set_v_t(0,q);
	}
}

int main(){
	n=nxi(),q=nxi();
	for(int i=1; i<=q; ++i){
		const int op=nxi(),l=nxi(),r=nxi();
		if(op==1){
			int x=nxi();
			op_b[l].push_back((opt){1,i,1,x});
			op_b[r+1].push_back((opt){1,i,0,x});
			valx[i]=x;
		}else if(op==2){
			op_b[l].push_back((opt){2,i,-1,0});
			op_b[r+1].push_back((opt){2,i,0,0});
		}else{
			op_b[l].push_back((opt){3,i,r,r});
		}
	}
	for(int i=1; i<=n; ++i){
		for(std::vector <opt> ::iterator it=op_b[i].begin(); it!=op_b[i].end(); ++it){
			if(it->type==1||it->type==2){
				T::set_v(it->tick,it->v);
			}
		}
		for(std::vector <opt> ::iterator it=op_b[i].begin(); it!=op_b[i].end(); ++it){
			if(it->type==3){
				int p=T::find_x(it->tick,it->v);
				if(p==-1) ans[it->tick]=-1;
				else{
					assert(valx[p+1]);
					ans[it->tick]=valx[p+1];
				}
			}
		}
	}
	for(int i=1; i<=q; ++i){
		if(!ans[i]) continue;
		if(ans[i]==-1) puts("Error");
		else printf("%d\n",ans[i]);
	}
	return 0;
}
