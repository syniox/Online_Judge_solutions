#include<iostream>
#include<cstdio>
#include<cstring>
const int N=1e5+2;
int n,m,xdep,cnt[N],dep[N];

inline void apx(int &x,const int y){
	if(x<y) x=y;
}

inline char get_c(){
	static char *h,*t,buf[20000];
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=get_c())>'9'||c<'0');
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return x;
}

namespace T{
	int x,y,v;
	struct node{
		int s,f;
	}tr[N*3];
	inline void upd(const int k){
		tr[k].s=std::max(tr[k<<1].s,tr[k<<1|1].s);
	}
	inline void psh(const int k){
		if(tr[k].f){
			const int tp=tr[k].f;
			tr[k<<1].s+=tp;
			tr[k<<1].f+=tp;
			tr[k<<1|1].s+=tp;
			tr[k<<1|1].f+=tp;
			tr[k].f=0;
		}
	}
	void mod(const int k,const int l,const int r){
		if(l!=r) psh(k);
		if(l>=x&&r<=y){
			tr[k].s+=v;
			tr[k].f+=v;
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod(k<<1,l,mid);
		if(y>mid)  mod(k<<1|1,mid+1,r);
		upd(k);
	}
	inline void mod_t(const int x,const int y,const int v){
		T::x=x,T::y=y,T::v=v;
		mod(1,1,xdep);
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=2;i<=n;++i){
		dep[i]=dep[nxi()]+1;
		apx(xdep,dep[i]);
	}
	while(m--){
		const int op=3-(nxi()<<1),x=dep[nxi()];
		if(x){
			T::mod_t(1,x,op);
			if(op==1&&++cnt[x]==1) T::mod_t(x,x,x);
			if(op==-1&&--cnt[x]==0) T::mod_t(x,x,-x);
		}
		printf("%d\n",T::tr[1].s);
	}
	return 0;
}
