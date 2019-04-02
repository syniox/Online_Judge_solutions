#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <sys/mman.h>
#include <unistd.h>
typedef long long lint;
const int N=1e5+5;
const int mod=323232323;
int m,n,q,val[N];

namespace IO{
	char *ibuf;
	struct _Init{
		_Init(){ibuf=(char*)mmap(0,lseek(0,0,SEEK_END),PROT_READ,MAP_PRIVATE,0,0);}
	}_init;
	inline int nxi(){
		int x=0;
		char c;
		while((c=*ibuf++)>'9'||c<'0');
		while(x=x*10-48+c,(c=*ibuf++)>='0'&&c<='9');
		return x;
	}
}
using IO::nxi;

int gcd(const int x,const int y){
	return y?gcd(y,x%y):x;
}

struct mtrx{
	int n[2][2];
	friend mtrx operator * (const mtrx &a,const mtrx &b){
		mtrx c;
		c.n[0][0]=((lint)a.n[0][0]*b.n[0][0]+(lint)a.n[0][1]*b.n[1][0])%mod;
		c.n[0][1]=((lint)a.n[0][0]*b.n[0][1]+(lint)a.n[0][1]*b.n[1][1])%mod;
		c.n[1][0]=((lint)a.n[1][0]*b.n[0][0]+(lint)a.n[1][1]*b.n[1][0])%mod;
		c.n[1][1]=((lint)a.n[1][0]*b.n[0][1]+(lint)a.n[1][1]*b.n[1][1])%mod;
		return c;
	}
};

inline mtrx fpow(mtrx x,int t){
	mtrx ans;
	ans.n[0][1]=ans.n[1][0]=0;
	ans.n[0][0]=ans.n[1][1]=1;
	for(; t; x=x*x,t>>=1){
		if(t&1) ans=ans*x;
	}
	return ans;
}

inline int ask_per(const int t){
	mtrx res;
	res.n[0][0]=0,res.n[1][0]=1;
	res.n[0][1]=m-1,res.n[1][1]=m-2;
	res=fpow(res,t-1);
	return (lint)(m-1)*res.n[1][0]%mod;
}

namespace T{
	int rt;
	struct node{
		//l,r表示区间端点的值
		int ls,rs,l,r,v,sz,gcd,delta,rnk;
		bool rev,zero;
	}tr[N];

	inline void upd(const int k){
		const int ls=tr[k].ls,rs=tr[k].rs;
		tr[k].l=ls?tr[ls].l:tr[k].v;
		tr[k].r=rs?tr[rs].r:tr[k].v;
		tr[k].sz=tr[ls].sz+tr[rs].sz+1;
		tr[k].gcd=gcd(tr[ls].gcd,tr[rs].gcd);
		if(ls) tr[k].gcd=gcd(tr[k].gcd,abs(tr[k].v-tr[ls].r));
		if(rs) tr[k].gcd=gcd(tr[k].gcd,abs(tr[k].v-tr[rs].l));
		tr[k].zero=(tr[k].v==-1)|tr[ls].zero|tr[rs].zero;
	}

	inline void add(const int k,const int delta){
		tr[k].delta+=delta;
		tr[k].v+=delta,tr[k].l+=delta,tr[k].r+=delta;
		tr[k].zero=0;
	}

	inline void rev(const int k){
		tr[k].rev^=1;
		std::swap(tr[k].ls,tr[k].rs);
		std::swap(tr[k].l,tr[k].r);
	}

	inline void psh(const int k){
		if(tr[k].delta){
			if(tr[k].ls) add(tr[k].ls,tr[k].delta);
			if(tr[k].rs) add(tr[k].rs,tr[k].delta);
			tr[k].delta=0;
		}
		if(tr[k].rev){
			if(tr[k].ls) rev(tr[k].ls);
			if(tr[k].rs) rev(tr[k].rs);
			tr[k].rev=0;
		}
	}

	void build(int &k,const int l,const int r){
		k=0;
		for(int i=l; i<=r; ++i){
			if(tr[i].rnk>tr[k].rnk) k=i;
		}
		if(l<k) build(tr[k].ls,l,k-1);
		if(r>k) build(tr[k].rs,k+1,r);
		upd(k);
	}

	void split(const int k,int &lf,int &rf,const int sum){
		if(!k){
			lf=rf=0;
			return;
		}
		psh(k);
		const int sz=tr[tr[k].ls].sz+1;
		if(sz>sum){
			rf=k;
			split(tr[k].ls,lf,tr[k].ls,sum);
		}
		else{
			lf=k;
			split(tr[k].rs,tr[k].rs,rf,sum-sz);
		}
		if(lf) upd(lf);
		if(rf) upd(rf);
	}

	void merge(int &k,const int lf,const int rf){
		if(!lf||!rf){
			k=lf+rf;
			return;
		}
		if(tr[lf].rnk>tr[rf].rnk){
			k=lf,psh(lf);
			merge(tr[lf].rs,tr[lf].rs,rf);
		}
		else{
			k=rf,psh(rf);
			merge(tr[rf].ls,lf,tr[rf].ls);
		}
		upd(k);
	}
}

int main(){
#ifndef ONLINE_JUDGE
	//freopen("d.in","r",stdin);
#endif
	srand(19491001);
	nxi();
	m=nxi(),n=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi()-1;
		T::tr[i].v=T::tr[i].l=T::tr[i].r=val[i];
		T::tr[i].sz=1;
		T::tr[i].rnk=rand();
	}
	T::build(T::rt,1,n);
	for(int i=1; i<=q; ++i){
		const int op=nxi(),l=nxi(),r=nxi();
		int rt1,rt2,rt3;
		T::split(T::rt,rt1,rt3,r);
		T::split(rt1,rt1,rt2,l-1);
		switch(op){
			case 1:
				if(T::tr[rt2].zero) puts("1");
				else printf("%d\n",ask_per(gcd(T::tr[rt2].gcd,T::tr[rt2].l)+1));
				break;
			case 2:
				T::rev(rt2);
				break;
			case 3:
				T::add(rt2,nxi());
				break;
		}
		T::merge(rt1,rt1,rt2);
		T::merge(T::rt,rt1,rt3);
	}
	return 0;
}
