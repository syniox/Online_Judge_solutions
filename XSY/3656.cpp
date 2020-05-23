#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <vector>
typedef long long lint;
const int N=1e5+5;
int S;
int n,m,cnq,val[N],bel[N];
lint spre[N],ans[N];
bool asked[N];
std::vector <std::pair <int,int> > obuk[N];//time,value
struct _qry{
	int l,r,t;
	friend bool operator < (const _qry &a,const _qry &b){
		return bel[a.l]==bel[b.l]?(bel[a.l]&1?a.r<b.r:a.r>b.r):a.l<b.l;
	}
}qry[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

namespace T{
	int x,v;
	struct node{
		lint sum,npre;
	}tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void upd(const int l,const int r){
		const int mid=(l+r)>>1,k=idx(l,r);
		const int ls=idx(l,mid),rs=idx(mid+1,r);
		tr[k].sum=tr[ls].sum+tr[rs].sum;
		tr[k].npre=std::min(tr[ls].npre,tr[ls].sum+tr[rs].npre);
	}

	void add_t(const int l,const int r){
		const int mid=(l+r)>>1,k=idx(l,r);
		if(l==r){
			tr[k].sum+=v;
			tr[k].npre=std::min(0ll,tr[k].sum);
			return;
		}
		if(x<=mid) add_t(l,mid);
		if(x>mid) add_t(mid+1,r);
		upd(l,r);
	}

	lint ask_t(const int l,const int r){
		const int mid=(l+r)>>1;
		if(r<=x) return tr[idx(l,r)].npre;
		lint ans=ask_t(l,mid);
		if(x>mid) apn(ans,tr[idx(l,mid)].sum+ask_t(mid+1,r));
		return ans;
	}

	inline void add(const int x,const int v){
		T::x=x,T::v=v;
		add_t(1,m);
	}

	inline lint ask(const int x){
		T::x=x;
		return ask_t(1,m);
	}
}

int __cnt;

void setv(const int p,const int f){
	//if(obuk[p].empty()) return;
	std::vector <std::pair <int,int> > ::iterator it;
	int lst=val[p];
	for(it=obuk[p].begin(); it!=obuk[p].end(); ++it){
		++__cnt;
		T::add(it->first,f*(it->second-lst));
		lst=it->second;
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		spre[i]=spre[i-1]+(val[i]=nxi());
	}
	for(int i=1; i<=m; ++i){
		int p=nxi(),a=nxi(),b=nxi();
		if(p==1) obuk[a].push_back(std::make_pair(i,b));
		else asked[i]=1,qry[++cnq]=(_qry){a,b,i};
	}
	S=sqrt((lint)(m-cnq)*(m-cnq)/cnq)*1.25+1;
	//S=sqrt(m-cnq)+1;
	fprintf(stderr,"cntq: %d S: %d\n",cnq,S);
	for(int i=1,j=1,s=0; i<=n; ++i){
		int w=((i&15)==0);//防卡莫队
		if((s+=obuk[i].size()+w)>=S) ++j,s=obuk[i].size()+w;
		bel[i]=j;
	}
	std::sort(qry+1,qry+cnq+1);
	for(int i=1,l=1,r=0; i<=cnq; ++i){
		int qr=qry[i].r,ql=qry[i].l;
		while(r<qr) setv(++r,1);
		while(l>ql) setv(--l,1);
		while(r>qr) setv(r--,-1);
		while(l<ql) setv(l++,-1);
		ans[qry[i].t]=spre[qr]-spre[ql-1]+T::ask(qry[i].t);
	}
	for(int i=1; i<=m; ++i){
		if(asked[i]) printf("%lld\n",ans[i]);
	}
	fprintf(stderr,"cnt: %d\n",__cnt);
	return 0;
}
