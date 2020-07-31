#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long lint;
const int N=3e5+5;
int n,q,w,qry[N],tpos[N];
struct vec{
	int x,y,id,t;//m->x,h->y
	//b后加入，且不能超过a时crs(a,b)<w
	//h_b>=w/m_a+h_a/m_a*m_b时会交换
	//二分时构建右下凸包看b是否在凸包外
	//半平面交？
}fk[N];
struct ln_s{
	double k,b;
	double qval(const int x);
	friend double crspt(const ln_s &a,const ln_s &b);
	friend bool operator<(const ln_s &a,const ln_s &b);
};

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline lint nxi(){
		lint x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

inline lint crs(const vec &a,const vec &b){
	return (lint)a.x*b.y-a.y*b.x;
}
inline lint ln_s::qval(const int x){
	return (lint)k*x+b;
}
double crspt(const ln_s &a,const ln_s &b){
	assert(a.k!=b.k);
	return (a.b-b.b)/(b.k-a.k);
}
bool operator<(const ln_s &a,const ln_s &b){
	return a.k<b.k;
}

namespace T{
#define mid ((l+r)>>1)
	int cnt,x,rt[N];
	struct node{
		int ls,rs,sz;
	}tr[N*20];
	void ins_t(int &k,const int l,const int r){
		tr[++cnt]=tr[k];
		k=cnt;
		++tr[k].sz;
		if(x<=mid) ins_t(tr[k].ls,l,mid);
		else ins_t(tr[k].rs,mid+1,r);
	}
	int qpos_t(const int k,const int l,const int r,const int rk){
		if(l==r) return l;
		if(tr[tr[k].ls].sz>=rk) return qpos_t(tr[k].ls,l,mid,rk);
		return qpos_t(tr[k].rs,mid+1,r,rk-tr[tr[k].ls].sz);
	}
	void ins(int &k,int pos){
		x=pos;
		ins_t(k,1,n);
	}
#undef mid
}

int fi[N];//first invalid point
void ef(const int l1,const int r1,const int l2,const int r2){
	static ln_s ln[N];
	const int mid=(l1+r1+1)>>1;
	int cnt=0;
	for(int i=mid; i<=r1; ++i){
		ln[++cnt]=(ln_s){(double)fk[i].y/fk[i].x,(double)w/fk[i].x};
	}
	sort(ln+1,ln+cnt+1);
}

void cdq(const int l,const int r){
	if(l==r) return;
	const int mid=(l+r)>>1;
	cdq(l,mid);
	cdq(mid+1,r);
}

int main(){
	q=nxi(),w=nxi();
	for(int i=1; i<=q; ++i){
		if(nxi()==1){
			fk[++n].t=i;
			fk[n].y=nxi(),fk[n].x=nxi();
			fk[n].id=n;
		}else{
			qry[i]=nxi();
		}
	}
	cdq(1,n);
	for(int i=1; i<=n; ++i){
		tpos[fk[i].t]=i;
	}
	for(int i=1; i<=q; ++i){
		T::rt[i]=T::rt[i-1];
		if(tpos[i]) T::ins(T::rt[i],tpos[i]);
		if(qry[i]){
			int res=T::qpos_t(T::rt[i],1,n,qry[i]);
			printf("%d\n",fk[res].y,fk[res].x);
		}
	}
	return 0;
}
