#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <bitset>
typedef long long lint;
const int N=1e5+5;
const int B=33500;
int n,m,val[N],bel[N],cnt[N];
struct _qry{
	int l1,r1,l2,r2,l3,r3;
}qry[B+5];
struct _srq{
	int l,r,id;
	friend bool operator < (const _srq &a,const _srq &b){
		return bel[a.l]==bel[b.l]?(bel[a.l]&1?a.r<b.r:a.r>b.r):a.l<b.l;
	}
}srq[B*3+5];

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

void san_val(){
	static int buk[N];
	memcpy(buk+1,val+1,n*sizeof(buk[0]));
	std::sort(buk+1,buk+n+1);
	for(int i=1; i<=n; ++i){
		val[i]=std::lower_bound(buk+1,buk+n+1,val[i])-buk;
	}
}

void add(std::bitset <N> &bs,const int x){
	bs[val[x]+cnt[val[x]]++]=1;
}
void rem(std::bitset <N> &bs,const int x){
	bs[val[x]+--cnt[val[x]]]=0;
}

void solve(const int n){
	static std::bitset <N> res[B+5],cur;
	memset(cnt+1,0,::n*sizeof(int));
	for(int i=1; i<=n; ++i){
		res[i].set();
	}
	for(int i=1; i<=n; ++i){
		srq[i*3-2]=(_srq){qry[i].l1,qry[i].r1,i};
		srq[i*3-1]=(_srq){qry[i].l2,qry[i].r2,i};
		srq[i*3-0]=(_srq){qry[i].l3,qry[i].r3,i};
	}
	std::sort(srq+1,srq+n*3+1);
	cur.reset();
	for(int l=1,r=0,i=1; i<=n*3; ++i){
		while(r<srq[i].r) add(cur,++r);
		while(l>srq[i].l) add(cur,--l);
		while(r>srq[i].r) rem(cur,r--);
		while(l<srq[i].l) rem(cur,l++);
		res[srq[i].id]&=cur;
	}
	for(int i=1; i<=n; ++i){
		_qry* q=&qry[i];
		printf("%d\n",q->r1-q->l1+q->r2-q->l2+q->r3-q->l3+3-3*(int)res[i].count());
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int s=sqrt(n)+1,i=1; i<=n; ++i){
		val[i]=nxi();
		bel[i]=(i-1)/s+1;
	}
	san_val();
	for(int i=1; i<=m; ++i){
		int p=(i-1)%B+1;
		qry[p].l1=nxi(),qry[p].r1=nxi();
		qry[p].l2=nxi(),qry[p].r2=nxi();
		qry[p].l3=nxi(),qry[p].r3=nxi();
		if(i==m||p==B) solve((i-1)%B+1);
	}
	return 0;
}
