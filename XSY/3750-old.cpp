#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long lint;
const int N=3e5+5;
const double eps=1e-8;
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
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
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

double crs(double x1,double y1,double x2,double y2){
	return x1*y2-x2*y1;
}
lint crs(const vec &a,const vec &b){
	return (lint)a.x*b.y-a.y*b.x;
}
double ln_s::qval(const int x){
	return (double)k*x+b;
}
double crspt(const ln_s &a,const ln_s &b){
	assert(a.k!=b.k);
	return (a.b-b.b)/(b.k-a.k);
}
bool operator<(const ln_s &a,const ln_s &b){
	if(cabs(a.k-b.k)<eps) return a.b<b.b;
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
		if(l==r) return;
		if(x<=mid) ins_t(tr[k].ls,l,mid);
		else ins_t(tr[k].rs,mid+1,r);
	}
	int qpos_t(const int k,const int l,const int r,const int rk){
		if(l==r) return l;
		if(tr[tr[k].ls].sz>=rk) return qpos_t(tr[k].ls,l,mid,rk);
		return qpos_t(tr[k].rs,mid+1,r,rk-tr[tr[k].ls].sz);
	}
	void ins(int &k,int pos){
		assert(pos>0&&pos<=n);
		x=pos;
		ins_t(k,1,n);
	}
#undef mid
}

namespace CH{//Convex Hull
	vec vc[N];
	int fi[N];//first invalid point
	bool need_pop(const ln_s &a,const ln_s &b,const ln_s &c){
		assert(a.k-eps<b.k&&b.k-eps<c.k);
		double tp1=crspt(a,b),tp2=crspt(a,c);
		return tp1+eps>tp2;
	}

	void ef(const int l1,const int r1,const int l2,const int r2){
		static vec v1[N],v2[N];
		static ln_s ln[N];
		if(l2>r2) return;
		const int mid=(l1+r1+1)>>1;
		int cnt=0;
		for(int i=mid; i<=r1; ++i){
			ln[++cnt]=(ln_s){(double)fk[i].y/fk[i].x,(double)w/fk[i].x};
		}
		sort(ln+1,ln+cnt+1);
		for(int i=1,top=0; i<=cnt; ++i){
			if(top&&cabs(ln[top].k-ln[i].k)<eps) --top;
			for(; top>1&&need_pop(ln[top-1],ln[top],ln[i]); --top);
			ln[++top]=ln[i];
			if(i==cnt) cnt=top;
		}
		int p1=0,p2=0;
		for(int i=l2; i<=r2; ++i){
			int l=1,r=cnt;
			while(l<r){//最后一个左端点在他前面的数
				int tmp=(l+r+1)>>1;
				if(crspt(ln[tmp],ln[tmp-1])<vc[i].x) l=tmp;
				else r=tmp-1;
			}
			bool f=cnt?vc[i].y+eps<ln[l].qval(vc[i].x):0;
			if(l1==r1){
				fi[vc[i].id]=l1-1+f;
			}else{
				if(f) v2[++p2]=vc[i];
				else v1[++p1]=vc[i];
			}
		}
		if(l1==r1) return;
		memcpy(vc+l2,v1+1,p1*sizeof(vc[0]));
		memcpy(vc+l2+p1,v2+1,p2*sizeof(vc[0]));
		ef(l1,mid-1,l2,l2+p1-1);
		ef(mid,r1,l2+p1,r2);
	}
}

void cdq(const int l,const int r){
	using CH::vc;
	if(l==r) return;
	const int mid=(l+r)>>1;
	cdq(l,mid);
	cdq(mid+1,r);
	memcpy(vc+l,fk+l,(r-l+1)*sizeof(fk[0]));
	CH::ef(l,mid,mid+1,r);
	int tmp=l;
	for(int i=l,j=mid+1; i<=mid+1; ++i){
		for(; j<=r&&CH::fi[fk[j].id]<i; ++j){
			fk[tmp++]=fk[j];
		}
		if(i<=mid) fk[tmp++]=vc[i];
	}
	assert(tmp==r+1);
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
			printf("%d %d\n",fk[res].y,fk[res].x);
		}
	}
	return 0;
}
