#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long lint;
const int N=1.5e5+5;
int n,q,m;

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
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

struct pdt{
	int cnt,id[5],vl[5];
	inline void reset(){
		cnt=0;
		memset(id,0,sizeof(id));
		memset(vl,0,sizeof(vl));
	}
	pdt(){reset();}
	void psh(int tid,int tcnt){
		int ncnt=1e9,npos=-1;
		for(int i=0; i<cnt; ++i){
			if(vl[i]<ncnt) ncnt=vl[i],npos=i;
			if(id[i]==tid){
				vl[i]+=tcnt;
				return;
			}
		}
		if(cnt<m){
			id[cnt]=tid;
			vl[cnt++]=tcnt;
		}else{
			int rx=min(ncnt,tcnt);
			for(int i=0; i<cnt; ++i){
				vl[i]-=rx;
			}
			if(ncnt-rx==0){
				id[npos]=tid;
				vl[npos]=tcnt-rx;
			}
		}
	}
	void oput(){
		printf("%d ",cnt);
		for(int i=0; i<cnt; ++i){
			printf("%d ",id[i]);
		}
		puts("");
	}
	friend pdt operator*(const pdt &a,const pdt &b){
		pdt c=a;
		for(int i=0; i<b.cnt; ++i){
			c.psh(b.id[i],b.vl[i]);
		}
		return c;
	}
};

namespace T{
#define mid ((l+r)>>1)
	int x,y,id;
	struct node{
		int tag;
		pdt dt;
		void getpsh(const int t,const int cnt){
			dt.reset();
			dt.psh(t,cnt);
			tag=t;
		}
	}tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}
	inline void upd(const int l,const int r){
		assert(l!=r);
		tr[idx(l,r)].dt=tr[idx(l,mid)].dt*tr[idx(mid+1,r)].dt;
	}
	inline void psh(const int l,const int r){
		assert(l!=r);
		int &t=tr[idx(l,r)].tag;
		if(!t) return;
		tr[idx(l,mid)].getpsh(t,mid-l+1);
		tr[idx(mid+1,r)].getpsh(t,r-mid);
		t=0;
	}

	void build(const int l,const int r){
		if(l==r){
			tr[idx(l,r)].dt.psh(nxi(),1);
			return;
		}
		build(l,mid);
		build(mid+1,r);
		upd(l,r);
	}

	void set_t(const int l,const int r){
		if(l>=x&&r<=y){
			tr[idx(l,r)].getpsh(id,r-l+1);
			return;
		}
		psh(l,r);
		if(x<=mid) set_t(l,mid);
		if(y>mid) set_t(mid+1,r);
		upd(l,r);
	}
	pdt ask_t(const int l,const int r){
		if(l>=x&&r<=y) return tr[idx(l,r)].dt;
		psh(l,r);
		pdt ans;
		if(x<=mid) ans=ans*ask_t(l,mid);
		if(y>mid) ans=ans*ask_t(mid+1,r);
		return ans;
	}

	void set(const int l,const int r,const int id){
		x=l,y=r,T::id=id;
		set_t(1,n);
	}
	pdt ask(const int l,const int r){
		return x=l,y=r,ask_t(1,n);
	}
#undef mid
}

int main(){
	n=nxi(),q=nxi(),m=nxi();
	m=100/m;
	T::build(1,n);
	while(q--){
		const int op=nxi(),l=nxi(),r=nxi();
		if(op==1){
			T::set(l,r,nxi());
		}else{
			T::ask(l,r).oput();
		}
	}
	return 0;
}
