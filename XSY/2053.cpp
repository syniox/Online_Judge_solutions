#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=5e4+5;
int n,m,val[N];

template <class T> inline T nxi(){
	T x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

const lint q=nxi<lint>();
const int mod=nxi<int>();

struct data{
	lint p;
	int v;
	friend bool operator < (const data &a,const data &b){
		return a.p<b.p;
	}
}cn[N];

struct mtrx{
	int n[2][2];
	friend inline mtrx operator * (const mtrx &a,const mtrx &b){
		mtrx c;
		c.n[0][0]=((lint)a.n[0][0]*b.n[0][0]+(lint)a.n[0][1]*b.n[1][0])%mod;
		c.n[0][1]=((lint)a.n[0][0]*b.n[0][1]+(lint)a.n[0][1]*b.n[1][1])%mod;
		c.n[1][0]=((lint)a.n[1][0]*b.n[0][0]+(lint)a.n[1][1]*b.n[1][0])%mod;
		c.n[1][1]=((lint)a.n[1][0]*b.n[0][1]+(lint)a.n[1][1]*b.n[1][1])%mod;
		return c;
	}
}pvl[N],nvl[N],lvl[60];

struct vec{
	int n[2];
	friend inline vec operator * (const vec &a,const mtrx &b){
		vec c;
		c.n[0]=((lint)a.n[0]*b.n[0][0]+(lint)a.n[1]*b.n[1][0])%mod;
		c.n[1]=((lint)a.n[0]*b.n[0][1]+(lint)a.n[1]*b.n[1][1])%mod;
		return c;
	}
};

template <class T> inline int hbit(T x){
	int ans=0;
	for(int i=32; i; i>>=1){
		if(x>>i) x>>=i,ans+=i;
	}
	return ans;
}

void san_n(){
	if(n>2) return;
	int org_n=n;
	for(; n<=2; n+=org_n){
		memcpy(val+n,val,org_n*sizeof(int));
	}
}

mtrx mat_step(const int a,const int b){
	mtrx x;
	x.n[0][0]=0,x.n[1][0]=1;
	x.n[0][1]=a,x.n[1][1]=b;
	return x;
}

namespace T{
	mtrx *vl,tr[N<<1];
	int x,y;

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void build(const int l,const int r){
		if(l==r){
			tr[idx(l,r)]=vl[l];
			return;
		}
		const int mid=(l+r)>>1;
		build(l,mid);
		build(mid+1,r);
		tr[idx(l,r)]=tr[idx(l,mid)]*tr[idx(mid+1,r)];
	}

	mtrx ask_t(const int l,const int r){
		if(l>=x&&r<=y) return tr[idx(l,r)];
		const int mid=(l+r)>>1;
		if(y<=mid) return ask_t(l,mid);
		if(x>mid) return ask_t(mid+1,r);
		return ask_t(l,mid)*ask_t(mid+1,r);
	}

	inline mtrx ask(const int l,const int r){
		assert(l<n&&r<n);
		assert(l<=r);
		T::x=l,T::y=r;
		return ask_t(0,n-1);
	}
}

void build_vl(){
	static mtrx vl[N];
	vl[0]=mat_step(val[n-2],val[n-1]);
	vl[1]=mat_step(val[n-1],val[0]);
	for(int i=2; i<n; ++i){
		vl[i]=mat_step(val[i-2],val[i-1]);
	}
	pvl[0]=vl[0];
	for(int i=1; i<n; ++i){
		pvl[i]=pvl[i-1]*vl[i];
	}
	nvl[n-1]=vl[n-1];
	for(int i=n-1; ~i; --i){
		nvl[i]=vl[i]*nvl[i+1];
	}
	lvl[0]=pvl[n-1];
	for(int i=1; i<60; ++i){
		lvl[i]=lvl[i-1]*lvl[i-1];
	}
	T::vl=vl;
	T::build(0,n-1);
}

vec jmp(vec res,lint fr,lint to){
	//fr已经到过
	if(fr>=to) return res;
	lint bel_fr=fr/n,bel_to=to/n;
	if(bel_fr==bel_to){
		return res*T::ask((fr+1)%n,to%n);
	}
	if(fr%n<n-1) res=res*T::ask((fr+1)%n,n-1);
	lint jmp_blk=bel_to-bel_fr-1;
	for(int t=hbit(jmp_blk); ~t; --t){
		if(jmp_blk>>t&1) res=res*lvl[t];
	}
	return res*T::ask(0,to%n);
}

vec wlk(vec res,int fp,int tp){
	//res.n[1]在cn[fp].p上
	static int cv[N*3];
	const lint st=cn[fp].p,ed=cn[tp].p+1+(cn[tp].p<q-1);
	for(lint i=st; i<=ed; ++i){
		cv[i-st]=val[i%n];
	}
	for(int i=fp; i<=tp; ++i){
		cv[cn[i].p-st]=cn[i].v;
	}
	res=res*mat_step(val[(st-1)%n],cv[0]);
	for(int i=2; i<=ed-st; ++i){
		res=res*mat_step(cv[i-2],cv[i-1]);
	}
	return res;
}

int main(){
	n=nxi<int>();
	for(int i=0; i<n; ++i){
		val[i]=nxi<int>();
	}
	san_n();
	build_vl();
	m=nxi<int>();
	for(int i=1; i<=m; ++i){
		cn[i].p=nxi<lint>(),cn[i].v=nxi<int>();
	}
	std::sort(cn+1,cn+m+1);
	for(; cn[m].p>=q; --m);
	lint curpos=1;
	vec res((vec){0,1});
	for(int i=1,j; i<=m; i=j+1){
		res=jmp(res,curpos,cn[i].p);
		for(j=i; j<m&&cn[j+1].p-cn[j].p<=2; ++j);
		res=wlk(res,i,j);
		curpos=cn[j].p+2;
	}
	res=jmp(res,curpos,q);
	printf("%d\n",res.n[1]);
	return 0;
}
