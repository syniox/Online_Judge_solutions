#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
typedef long long lint;
const int N=1e5+5;
int n,m;
lint dis[N];
bool vis[N];
struct data{
	int p;
	lint v;
	friend bool operator < (const data &a,const data &b){
		return a.v<b.v;
	}
};
struct edge{
	int l,r,s,d;
};
std::vector <edge> ebuk[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=y<x?x:y;}
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

namespace T{
	int x,y;
	struct line{
		int k;
		lint b;
		inline lint val(const int x){
			return (lint)x*k+b;
		}
	};
	struct node{
		line l;
		data res;
		lint s;
		int pt_l,pt_r;
		node(){
			l=(line){0,(lint)1e15};
		}
	}tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void upd(const int l,const int r){
		const int k=idx(l,r),mid=(l+r)>>1;
		int &pl=tr[k].pt_l,&pr=tr[k].pt_r;
		while(pl<=r&&vis[pl]) ++pl;
		while(pr>=l&&vis[pr]) --pr;
		data self=(data){0,(lint)1e15};
		if(pl<=pr){
			if(tr[k].l.k>=0) self=(data){pl,tr[k].l.val(pl)};
			else self=(data){pr,tr[k].l.val(pr)};
		}
		if(l!=r){
			apn(self,tr[idx(l,mid)].res);
			apn(self,tr[idx(mid+1,r)].res);
		}
		tr[k].res=self;
	}

	void build(const int l,const int r){
		const int k=idx(l,r),mid=(l+r)>>1;
		tr[k].pt_l=l,tr[k].pt_r=r;
		tr[k].res.v=1e15;
		if(l==r) return;
		build(l,mid);
		build(mid+1,r);
	}

	void mod_all_t(const int l,const int r,line t){
		const int mid=(l+r)>>1;
		line &p=tr[idx(l,r)].l;
		if(p.val(l)<t.val(l)&&p.val(r)<t.val(r)){
			return;
		}
		if(p.val(mid)>t.val(mid)){
			std::swap(p,t);
		}
		if(l==r){
			upd(l,r);
			return;
		}
		if(p.val(l)>t.val(l)) mod_all_t(l,mid,t);
		else mod_all_t(mid+1,r,t);
		upd(l,r);
	}

	void mod_t(const int l,const int r,const line t){
		if(l>=x&&r<=y){
			mod_all_t(l,r,t);
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_t(l,mid,t);
		if(y>mid) mod_t(mid+1,r,t);
		upd(l,r);
	}

	void clr_t(const int l,const int r,const int p){
		const int mid=(l+r)>>1;
		if(l!=r){
			if(p<=mid) clr_t(l,mid,p);
			else clr_t(mid+1,r,p);
		}
		upd(l,r);
	}

	void mod(const int l,const int r,const int d,const int s){
		T::x=l,T::y=r;
		mod_t(1,n,(line){d,s-l*d});
	}

	inline data ask(){
		return tr[idx(1,n)].res;
	}
}

int main(){
	n=nxi(),m=nxi();
	memset(dis,10,sizeof(dis));
	for(int i=1; i<=m; ++i){
		int x=nxi(),l=nxi(),r=nxi(),s=nxi(),d=nxi();
		ebuk[x].push_back((edge){l,r,s,d});
	}
	T::build(1,n);
	T::mod(1,1,0,0);
	dis[1]=0;
	for(int i=1; i<=n; ++i){
		data tmp=T::ask();
		const int p=tmp.p;
		dis[p]=tmp.v;
		if(i==n) break;
		vis[p]=1;
		T::clr_t(1,n,p);
		for(std::vector <edge> ::iterator it=ebuk[p].begin(); it!=ebuk[p].end(); ++it){
			T::mod(it->l,it->r,it->d,dis[p]+it->s);
		}
	}
	for(int i=1; i<=n; ++i){
		printf("%lld ",dis[i]<=1e13?dis[i]:-1);
	}
	puts("");
	return 0;
}
