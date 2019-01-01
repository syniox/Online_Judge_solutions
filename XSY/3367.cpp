#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
typedef long long lint;
const int N=120005;
int n,q,val[N];
lint ans[N];
struct query{
	int x,y,id;
	friend bool cmp_y(const query &a,const query &b){
		return a.y<b.y;
	}
}qry[N];

bool cmp_y(const query &a,const query &b);

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace T{
	int x,y,v;
	struct node{
		//min: max-min-(r-l)
		int delta,min,mincnt,hitcnt;
		lint s;
		inline void get_psh(int v,int hit){
			min+=v,delta+=v;
			s+=hit*mincnt;
			hitcnt+=hit;
		}
	}tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void upd(const int l,const int r){
		const int mid=(l+r)>>1;
		int k=idx(l,r),ls=idx(l,mid),rs=idx(mid+1,r);
		tr[k].s=tr[ls].s+tr[rs].s;
		tr[k].min=std::min(tr[ls].min,tr[rs].min);
		tr[k].mincnt=0;
		if(tr[ls].min==tr[k].min) tr[k].mincnt+=tr[ls].mincnt;
		if(tr[rs].min==tr[k].min) tr[k].mincnt+=tr[rs].mincnt;
	}

	inline void psh(const int l,const int r){
		int k=idx(l,r),mid=(l+r)>>1;
		int ls=idx(l,mid),rs=idx(mid+1,r);
		if(!(tr[k].delta||tr[k].hitcnt)) return;
		tr[ls].get_psh(tr[k].delta,0);
		if(tr[ls].min==tr[k].min) tr[ls].get_psh(0,tr[k].hitcnt);
		tr[rs].get_psh(tr[k].delta,0);
		if(tr[rs].min==tr[k].min) tr[rs].get_psh(0,tr[k].hitcnt);
		tr[k].delta=tr[k].hitcnt=0;
	}

	inline void build(const int l,const int r){
		tr[idx(l,r)].mincnt=(r-l+1);
		if(l==r) return;
		const int mid=(l+r)>>1;
		build(l,mid);
		build(mid+1,r);
	}

	void mod_min_t(const int l,const int r){
		if(l!=r) psh(l,r);
		if(l>=x&&r<=y){
			tr[idx(l,r)].get_psh(v,0);
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_min_t(l,mid);
		if(y>mid) mod_min_t(mid+1,r);
		upd(l,r);
	}

	void mod_hit_t(const int l,const int r){
		if(l!=r) psh(l,r);
		if(l>=x&&r<=y){
			if(tr[idx(l,r)].min==0) tr[idx(l,r)].get_psh(0,1);
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_hit_t(l,mid);
		if(y>mid) mod_hit_t(mid+1,r);
		upd(l,r);
	}

	inline lint ask_t(const int l,const int r){
		if(l!=r) psh(l,r);
		if(l>=x&&r<=y) return tr[idx(l,r)].s;
		lint ans=0,mid=(l+r)>>1;
		if(x<=mid) ans+=ask_t(l,mid);
		if(y>mid) ans+=ask_t(mid+1,r);
		return ans;
	}

	inline void mod_min(const int x,const int y,const int v){
		if(x>y) return;
		T::x=x,T::y=y,T::v=v;
		T::mod_min_t(1,n);
	}

	inline void mod_hit(const int x,const int y){
		if(x>y) return;
		T::x=x,T::y=y;
		T::mod_hit_t(1,n);
	}

	inline lint ask(const int x,const int y){
		if(x>y) return 0;
		T::x=x,T::y=y;
		return T::ask_t(1,n);
	}
}

inline void ins_stk(int st[],int &pt,int pos,bool f){
	//need: max-min-(r-l)
	for(; pt&&(val[st[pt]]==val[pos]||(val[st[pt]]<val[pos])==f); --pt){
		T::mod_min(st[pt-1]+1,pos-1,abs(val[pos]-val[st[pt]]));
	}
	st[++pt]=pos;
}

inline void solve(){
	static int q_min[N],q_max[N];
	int ptmin=0,ptmax=0;
	T::build(1,n);
	for(int i=1,j=1; i<=q; ++i){
		for(; j<=qry[i].y; ++j){
			ins_stk(q_min,ptmin,j,0);
			ins_stk(q_max,ptmax,j,1);
			T::mod_min(1,j-1,-1);
			T::mod_hit(1,j);
		}
		ans[qry[i].id]=T::ask(qry[i].x,qry[i].y);
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	q=nxi();
	for(int i=1; i<=q; ++i){
		qry[i].id=i;
		qry[i].x=nxi(),qry[i].y=nxi();
	}
	std::sort(qry+1,qry+q+1,cmp_y);
	solve();
	for(int i=1; i<=q; ++i){
		printf("%lld\n",ans[i]);
	}
	return 0;
}
