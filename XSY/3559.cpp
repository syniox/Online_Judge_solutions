#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;
const int mod=1e9+7;
int n,q,val[3][N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
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

struct data{
	int len;
	int gc,gd,ga;//产生： 毒雾，毒，伤害
	int ab,sb,pb,b2;//b的乘积，乘积后缀和，乘积前缀和，子区间乘积和
	int cd,ca;//毒雾->毒,伤
	int fd,fa;//区间增毒雾->毒，伤
	int dd,da;//毒->毒，伤
	data(){
		memset(this,0,sizeof(*this));
		len=0;
		dd=ab=pb=sb=1;
	}
	inline void set(const int a,const int b,const int c){
		len=1;
		gc=c,gd=((lint)a*b-1)%mod,ga=(gd+1)%mod;
		ab=sb=pb=b2=b,cd=ca=b,dd=da=b;
		fd=fa=0;
	}
	friend data operator + (const data &a,const data &b){
		data c;
		c.len=a.len+b.len;
		c.gc=(a.gc+b.gc)%mod;
		c.ab=(lint)a.ab*b.ab%mod;
		c.sb=((lint)a.sb*b.ab+b.sb)%mod;
		c.pb=(a.pb+(lint)a.ab*b.pb)%mod;
		c.b2=(a.b2+b.b2+(lint)b.pb*a.sb)%mod;
		c.cd=((lint)a.cd*b.dd+b.cd)%mod;
		c.ca=(a.ca+b.ca+(lint)a.cd*b.da)%mod;
		c.fd=((lint)a.fd*b.dd+b.fd+(lint)a.len*b.cd)%mod;
		c.fa=(a.fa+b.fa+(lint)a.fd*b.da+(lint)a.len*b.ca)%mod;
		c.dd=(lint)a.dd*b.dd%mod;
		c.da=(a.da+(lint)a.dd*b.da)%mod;
		c.gd=((lint)a.gd*b.dd+(lint)a.gc*b.cd+b.gd)%mod;
		c.ga=(a.ga+b.ga+(lint)a.gd*b.da+(lint)a.gc*b.ca)%mod;
		return c;
	}
};

namespace T{
	data tr[N<<1];
	int x,y,v,dlt_a[N<<1],dlt_c[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void upd(const int l,const int r){
		const int mid=(l+r)>>1;
		tr[idx(l,r)]=tr[idx(l,mid)]+tr[idx(mid+1,r)];
	}

	void get_a(const int l,const int r,const int v){
		const int k=idx(l,r);
		dlt_a[k]=(dlt_a[k]+v)%mod;
		tr[k].gd=(tr[k].gd+(lint)v*tr[k].sb)%mod;
		tr[k].ga=(tr[k].ga+(lint)v*tr[k].b2)%mod;
	}

	void get_c(const int l,const int r,const int v){
		const int k=idx(l,r);
		dlt_c[k]=(dlt_c[k]+v)%mod;
		tr[k].gc=(tr[k].gc+(lint)v*tr[k].len)%mod;
		tr[k].gd=(tr[k].gd+(lint)v*tr[k].fd)%mod;
		tr[k].ga=(tr[k].ga+(lint)v*tr[k].fa)%mod;
	}

	void psh(const int l,const int r){
		if(l==r) return;
		const int mid=(l+r)>>1;
		int &da=dlt_a[idx(l,r)],&dc=dlt_c[idx(l,r)];
		if(da){
			get_a(l,mid,da);
			get_a(mid+1,r,da);
			da=0;
		}
		if(dc){
			get_c(l,mid,dc);
			get_c(mid+1,r,dc);
			dc=0;
		}
	}

	inline void build(const int l,const int r){
		const int k=idx(l,r);
		if(l==r){
			tr[k].set(val[0][l],val[1][l],val[2][l]);
			return;
		}
		const int mid=(l+r)>>1;
		build(l,mid);
		build(mid+1,r);
		upd(l,r);
	}

	data ask_t(const int l,const int r){
		if(l>=x&&r<=y) return tr[idx(l,r)];
		psh(l,r);
		const int mid=(l+r)>>1;
		if(y<=mid) return ask_t(l,mid);
		if(x>mid) return ask_t(mid+1,r);
		return ask_t(l,mid)+ask_t(mid+1,r);
	}

	void add_a_t(const int l,const int r){
		if(l>=x&&r<=y){
			get_a(l,r,v);
			return;
		}
		psh(l,r);
		const int mid=(l+r)>>1;
		if(x<=mid) add_a_t(l,mid);
		if(y>mid) add_a_t(mid+1,r);
		upd(l,r);
	}

	void add_c_t(const int l,const int r){
		if(l>=x&&r<=y){
			get_c(l,r,v);
			return;
		}
		psh(l,r);
		const int mid=(l+r)>>1;
		if(x<=mid) add_c_t(l,mid);
		if(y>mid) add_c_t(mid+1,r);
		upd(l,r);
	}

	data ask(const int l,const int r){
		x=l,y=r;
		return ask_t(1,n);
	}

	void add_a(const int l,const int r,const int v){
		x=l,y=r,T::v=v;
		add_a_t(1,n);
	}

	void add_c(const int l,const int r,const int v){
		x=l,y=r,T::v=v;
		add_c_t(1,n);
	}
}

int main(){
	n=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		val[0][i]=nxi(),val[1][i]=nxi(),val[2][i]=nxi();
	}
	T::build(1,n);
	for(int i=1; i<=q; ++i){
		const int op=nxi(),l=nxi(),r=nxi();
		if(op!=3){
			data res=T::ask(l,r);
			printf("%d\n",op==1?res.gd:res.ga);
		}
		else if(nxi()==1){
			T::add_a(l,r,nxi());
		}
		else{
			T::add_c(l,r,nxi());
		}
	}
	return 0;
}
