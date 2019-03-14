/**
 *          f[i+1][j+b[i]],max(f[i+1][k](0<=k<b[i]))+j  if j<a[i]
 * f[i][j]= f[i+1][j-a[i]]+a[i]                         if a[i]<=j<a[i]+b[i]
 *          f[i+1][j]                                   if j>=a[i]+b[i]
 *
 * (Though unnecessary)
 * Define g[i][j]=f[i][j]-j;
 *
 *          g[i+1][j+b[i]]+b[i],max(g[i+1][k]+k)        if j<a[i]
 * g[i][j]= g[i+1][j-a[i]]                              if a[i]<=j<a[i]+b[i]
 *          g[i+1][j]                                   if j>=a[i]+b[i]
 *
 * Treap(区间apmax,区间+index求max,区间交换，区间加)
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
const int N=1005;
const int M=20005;
int n,m,lim_m,va[N],vb[N];

class _Trans{
	public:
		int apx,dlt;//apply max first

		inline void clear(){
			apx=dlt=0;
		}
		friend _Trans operator + (const _Trans &a,const _Trans &b){
			return (_Trans){std::max(a.apx,b.apx-a.dlt),a.dlt+b.dlt};
		}
		void operator += (const _Trans &b){
			(*this)=(*this)+b;
		}
};

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace T{
	int rt;
	class node{
		public:
			int val,sz,mx,rnk,ls,rs;
			_Trans tag;

			inline void upd();
			inline void aply(_Trans trs);
			inline void psh();

	}tr[20005];//大根堆,i节点对应g[][i-1]?

	inline void node::upd(){
		sz=tr[ls].sz+tr[rs].sz+1;
		mx=val+tr[ls].sz;
		if(ls) apx(mx,tr[ls].mx);
		if(rs) apx(mx,tr[rs].mx+tr[ls].sz+1);
	}

	inline void node::aply(_Trans trs){
		apx(mx,sz-1+trs.apx);
		apx(val,trs.apx);
		mx+=trs.dlt;
		val+=trs.dlt;
		tag+=trs;
	}

	inline void node::psh(){
		if(tag.apx||tag.dlt){
			if(ls) tr[ls].aply(tag);
			if(rs) tr[rs].aply(tag);
			tag.clear();
		}
	}

	void build(){
		static int top,stk[M];
		for(int i=1; i<=lim_m; ++i){
			tr[i].rnk=rand();
			tr[i].sz=1;
			if(tr[stk[top]].rnk<tr[i].rnk){
				for(; top&&tr[stk[top]].rnk<tr[i].rnk; --top){
					tr[i].ls=stk[top];
					tr[stk[top]].upd();
				}
			}
			tr[stk[top]].rs=i;
			stk[++top]=i;
		}
		for(; top; --top) tr[stk[top]].upd();
		rt=stk[1];
	}

	void split(const int k,int &lf,int &rf,int rk){
		if(!k){
			lf=0,rf=0;
			return;
		}
		tr[k].psh();
		const int sum=tr[tr[k].ls].sz+1;
		if(sum<=rk){
			lf=k;
			split(tr[k].rs,tr[k].rs,rf,rk-sum);
		}
		else{
			rf=k;
			split(tr[k].ls,lf,tr[k].ls,rk);
		}
		tr[k].upd();
	}

	void merge(int &k,const int lf,const int rf){
		if(!lf||!rf){
			k=lf|rf;
			return;
		}
		tr[lf].psh(),tr[rf].psh();
		if(tr[lf].rnk>tr[rf].rnk){
			k=lf;
			merge(tr[k].rs,tr[k].rs,rf);
		}
		else{
			k=rf;
			merge(tr[k].ls,lf,tr[k].ls);
		}
		tr[k].upd();
	}
}

int main(){
	srand(19491001);
	n=nxi(),m=nxi();
	lim_m=m;
	for(int i=1; i<n; ++i){
		va[i]=nxi(),vb[i]=nxi();
		apx(lim_m,va[i]+vb[i]);
	}
	T::build();
	for(int i=n; i; --i){
		int rt1,rt2,rt3;
		T::split(T::rt,rt1,rt3,va[i]+vb[i]);
		T::split(rt1,rt1,rt2,vb[i]);
		int tmp_mx=T::tr[rt1].mx;
		T::tr[rt2].aply((_Trans){0,vb[i]});
		T::tr[rt2].aply((_Trans){tmp_mx,0});
		T::merge(rt1,rt2,rt1);
		T::merge(T::rt,rt1,rt3);
	}
	int rt1;
	T::split(T::rt,rt1,T::rt,m);
	printf("%d\n",T::tr[rt1].mx);
	return 0;
}
