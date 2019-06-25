#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
typedef long long lint;
const int N=5e5+5;
int n,q,ans[N];
char str[N];
struct _qry{
	int l,id;
};
std::vector <_qry> qbuk[N];

namespace utils{
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

namespace T{
	int x,y,v;
	struct node{
		int v,dlt;
		inline void getv(const int v){
			this->v+=v;
			dlt+=v;
		}
	}tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void psh(const int l,const int r){
		int &d=tr[idx(l,r)].dlt;
		if(l==r||!d) return;
		const int mid=(l+r)>>1;
		tr[idx(l,mid)].getv(d);
		tr[idx(mid+1,r)].getv(d);
		d=0;
	}

	inline void upd(const int l,const int r){
		const int mid=(l+r)>>1;
		tr[idx(l,r)].v=std::min(tr[idx(l,mid)].v,tr[idx(mid+1,r)].v);
	}

	void add_t(const int l,const int r){
		if(l>=x&&r<=y){
			tr[idx(l,r)].getv(v);
			return;
		}
		psh(l,r);
		const int mid=(l+r)>>1;
		if(x<=mid) add_t(l,mid);
		if(y>mid) add_t(mid+1,r);
		upd(l,r);
	}

	int qmin_t(const int l,const int r){
		if(l>=x&&r<=y) return tr[idx(l,r)].v;
		psh(l,r);
		const int mid=(l+r)>>1;
		int ans=N;
		if(x<=mid) apn(ans,qmin_t(l,mid));
		if(y>mid) apn(ans,qmin_t(mid+1,r));
		return ans;
	}

	inline void add(const int l,const int r,const int v){
		T::x=l,T::y=r,T::v=v;
		add_t(1,n);
	}

	inline int qmin(const int l,const int r){
		T::x=l,T::y=r;
		return qmin_t(1,n);
	}
}

void solve(){
	static int stk[N];
	int top=0;
	for(int i=1; i<=n; ++i){
		if(str[i]=='C'){
			if(top){
				T::add(stk[top--],i-1,-1);
			}
		}
		else{
			stk[++top]=i;
		}
		T::add(i,i,(i-1?T::qmin(i-1,i-1):0)+(str[i]=='C'));
		for(std::vector <_qry> ::iterator it=qbuk[i].begin(); it!=qbuk[i].end(); ++it){
			const int l=it->l;
			int res=top-(std::lower_bound(stk+1,stk+top+1,l)-stk)+1;
			if(it->l==1){
				ans[it->id]=res-std::min(0,T::qmin(l,i));
			}
			else{
				ans[it->id]=res+T::qmin(l-1,l-1)-T::qmin(l-1,i);
			}
		}
	}
}

int main(){
	n=nxi();
	scanf("%s",str+1);
	q=nxi();
	for(int i=1; i<=q; ++i){
		const int l=nxi(),r=nxi();
		qbuk[r].push_back((_qry){l,i});
	}
	solve();
	for(int i=1; i<=q; ++i){
		printf("%d\n",ans[i]);
	}
	return 0;
}
