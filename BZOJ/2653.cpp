#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
const int N=20005;
int n,hx[N];
struct data{
	int s,ls,rs;
}dt_null;

inline data merge(const data &l,const data &r){
	return (data){l.s+r.s,std::max(l.ls,l.s+r.ls),std::max(r.rs,r.s+l.rs)};
}

bool hx_cmp(const int a,const int b){
	return hx[a]<hx[b];
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace D{
	int pt,mp[N];

	inline void build(){
		std::sort(mp+1,mp+n+1);
		pt=std::unique(mp+1,mp+n+1)-mp-1;
	}

	inline int get_val(int x){
		return std::lower_bound(mp+1,mp+pt+1,x)-mp;
	}
}

namespace T{
	int x,y,v,cnt,rt[N];
	struct node{
		int l,r;
		data x;
	}tr[N*30];

	inline int build(const int l,const int r){
		int k=++cnt;
		if(l==r){
			tr[k].x.s=-1;
			return k;
		}
		const int mid=(l+r)>>1;
		tr[k].l=build(l,mid);
		tr[k].r=build(mid+1,r);
		tr[k].x=merge(tr[tr[k].l].x,tr[tr[k].r].x);
		return k;
	}

	void mod_t(const int p,int &k,const int l,const int r){
		k=++cnt;
		tr[k]=tr[p];
		if(l==r){
			tr[k].x.s=v;
			tr[k].x.ls=tr[k].x.rs=std::max(v,0);
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_t(tr[p].l,tr[k].l,l,mid);
		else mod_t(tr[p].r,tr[k].r,mid+1,r);
		tr[k].x=merge(tr[tr[k].l].x,tr[tr[k].r].x);
	}

	data ask_t(const int k,const int l,const int r){
		if(l>=x&&r<=y) return tr[k].x;
		int mid=(l+r)>>1;
		data ans=dt_null;
		if(x<=mid) ans=ask_t(tr[k].l,l,mid);
		if(y>mid) ans=merge(ans,ask_t(tr[k].r,mid+1,r));
		return ans;
	}

	inline void mod(const int p,int &k,const int x,const int v){
		T::x=x,T::v=v;
		mod_t(p,k,1,n);
	}

	inline data ask(const int p,int x,int y){
		if(!x) ++x;
		if(x>y) return dt_null;
		T::x=x,T::y=y;
		return ask_t(rt[p],1,n);
	}

	inline void init(){
		rt[0]=build(1,n);
		static int que[N];
		for(int i=1; i<=n; ++i){
			que[i]=i;
		}
		std::sort(que+1,que+n+1,hx_cmp);
		rt[D::pt+1]=rt[0];
		for(int i=D::pt,j=n; i; --i){
			rt[i]=rt[i+1];
			for(; hx[que[j]]==D::mp[i]; --j){
				mod(rt[i],rt[i],que[j],1);
			}
		}
	}
}

inline int jdg(int tgt,int a[]){
	const data l=T::ask(tgt,a[1],a[2]-1);
	const data r=T::ask(tgt,a[3]+1,a[4]);
	const data mid=T::ask(tgt,a[2],a[3]);
	return mid.s+l.rs+r.ls;
}

inline int solve(){
	static int ans=0,a[5];
	for(int i=1; i<5; ++i){
		a[i]=(nxi()+ans)%n+1;
	}
	std::sort(a+1,a+5);
	int l=1,r=D::pt,mid;
	while(l!=r){
		mid=(l+r+1)>>1;
		if(jdg(mid,a)<0) r=mid-1;
		else l=mid;
	}
	return ans=D::mp[l];
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		hx[i]=D::mp[i]=nxi();
	}
	D::build();
	T::init();
	for(int q=nxi(); q; --q){
		printf("%d\n",solve());
	}
	return 0;
}
