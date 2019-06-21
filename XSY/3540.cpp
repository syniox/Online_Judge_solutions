#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
typedef long long lint;
const int N=3e5+5;
int n,q,to_l[N];
lint ans[N];
char str[N];
std::vector <int> endp[N];
struct _qry{
	int x,y,id;
	friend bool operator < (const _qry &a,const _qry &b){
		return a.y<b.y;
	}
}qry[N];

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

int ask_endp(const int *sum,int *stk,const int x,int &top,const int f){
	if((str[x]==')')==(f==-1)){
		while(sum[stk[top]]>=sum[x]) --top;
		stk[++top]=x;
		return x;
	}
	//1-top递增,最后一个小于
	int l=1,r=top,mid;
	while(l!=r){
		mid=(l+r+1)>>1;
		if(sum[stk[mid]]<sum[x+f]) l=mid;
		else r=mid-1;
	}
	return stk[r];
}

void get_endp(){
	static int sum[N],stk[N];
	int top=0;
	for(int i=1; i<=n; ++i){
		sum[i]=sum[i-1]+(str[i]=='('?2:-1);
	}
	stk[++top]=n+1;
	sum[n+1]=-1e9;
	for(int i=n; i>=1; --i){
		int p=ask_endp(sum,stk,i,top,-1);
		if(str[i]=='('&&p<=n){
			endp[p].push_back(i);
		}
	}
	top=0;
	sum[n+1]=0;
	for(int i=n; i>=1; --i){
		sum[i]=sum[i+1]+(str[i]==')'?2:-1);
	}
	stk[++top]=0;
	sum[0]=-1e9;
	for(int i=1; i<=n; ++i){
		to_l[i]=ask_endp(sum,stk,i,top,1)+1;
	}
}

namespace T{
	int x,y;
	struct node{
		int sz,dlt;
		lint ans;
		inline void add(const int v){
			dlt+=v;
			ans+=(lint)v*sz;
		}
	}tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	void upd(const int l,const int r){
		const int k=idx(l,r),mid=(l+r)>>1;
		tr[k].sz=tr[idx(l,mid)].sz+tr[idx(mid+1,r)].sz;
		tr[k].ans=tr[idx(l,mid)].ans+tr[idx(mid+1,r)].ans;
	}

	void psh(const int l,const int r){
		if(l==r) return;
		const int mid=(l+r)>>1;
		int &d=tr[idx(l,r)].dlt;
		tr[idx(l,mid)].add(d);
		tr[idx(mid+1,r)].add(d);
		d=0;
	}

	void build(const int l,const int r){
		if(l==r){
			tr[idx(l,r)].sz=str[l]=='(';
			return;
		}
		const int mid=(l+r)>>1;
		build(l,mid);
		build(mid+1,r);
		upd(l,r);
	}

	void rem_t(const int l,const int r){
		if(l==r){
			tr[idx(l,r)].sz=0;
			return;
		}
		psh(l,r);
		const int mid=(l+r)>>1;
		if(x<=mid) rem_t(l,mid);
		else rem_t(mid+1,r);
		upd(l,r);
	}

	void add_t(const int l,const int r){
		if(l>=x&&r<=y){
			tr[idx(l,r)].add(1);
			return;
		}
		psh(l,r);
		const int mid=(l+r)>>1;
		if(x<=mid) add_t(l,mid);
		if(y>mid) add_t(mid+1,r);
		upd(l,r);
	}

	lint qsum_t(const int l,const int r){
		if(l>=x&&r<=y) return tr[idx(l,r)].ans;
		psh(l,r);
		const int mid=(l+r)>>1;
		lint ans=0;
		if(x<=mid) ans+=qsum_t(l,mid);
		if(y>mid) ans+=qsum_t(mid+1,r);
		return ans;
	}

	inline void rem(const int x){
		T::x=x;
		rem_t(1,n);
	}

	inline void add(const int l,const int r){
		assert(l&&r);
		T::x=l,T::y=r;
		add_t(1,n);
	}

	inline lint qsum(const int l,const int r){
		T::x=l,T::y=r;
		return qsum_t(1,n);
	}
}

int main(){
	n=nxi(),q=nxi();
	scanf("%s",str+1);
	for(int i=1; i<=q; ++i){
		qry[i].id=i;
		qry[i].x=nxi(),qry[i].y=nxi();
	}
	get_endp();
	std::sort(qry+1,qry+q+1);
	T::build(1,n);
	for(int i=1,j=1; i<=n; ++i){
		for(std::vector <int> ::iterator it=endp[i].begin(); it!=endp[i].end(); ++it){
			T::rem(*it);
		}
		if(str[i]==')'&&to_l[i]<i){
			T::add(to_l[i],i-1);
		}
		for(; qry[j].y==i; ++j){
			ans[qry[j].id]=T::qsum(qry[j].x,qry[j].y);
		}
	}
	for(int i=1; i<=q; ++i){
		printf("%lld\n",ans[i]);
	}
	return 0;
}
