#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <queue>
#include <algorithm>
typedef long long lint;
const int N=2e5+5;
int n,q;
lint ans[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

struct _pair{
	int x,y;
	friend bool operator < (const _pair &a,const _pair &b){
		return a.x==b.x?a.y<b.y:a.x<b.x;
	}
	friend lint area(const _pair &a,const _pair &b){
		return (lint)cabs(a.y-b.y)*cabs(a.x-b.x);
	}
}seg[N];
struct _qry{
	int id,x,y;
	friend bool operator < (const _qry &a,const _qry &b){
		return a.x<b.x;
	}
};
struct _data{
	int x;
	double rm_t;
	friend bool operator < (const _data &a,const _data &b){
		return a.rm_t<b.rm_t;
	}
	friend bool operator > (const _data &a,const _data &b){
		return a.rm_t>b.rm_t;
	}
};

lint get_area(const _pair &a,const _pair &b){
	if(a.x>b.x||a.y<b.y) return -1;
	return area(a,b);
}

namespace T{
	int x,n;
	_pair *v,p;
	bool f;
	struct node{
		int l,r;
	}tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void upd(const int l,const int r){
		const int k=idx(l,r),mid=(l+r)>>1;
		const int ls=idx(l,mid),rs=idx(mid+1,r);
		tr[k].l=std::min(tr[ls].l,tr[rs].l);
		tr[k].r=std::max(tr[ls].r,tr[rs].r);
	}

	void init_dfs(const int l,const int r){
		if(f==0){
			tr[idx(l,r)]=(node){n,-1};
		}
		else{
			tr[idx(l,r)]=(node){l,r};
		}
		if(l==r) return;
		const int mid=(l+r)>>1;
		init_dfs(l,mid);
		init_dfs(mid+1,r);
	}

	int qlst_t(const int l,const int r,const int x){
		if(l==r) return l;
		const int mid=(l+r)>>1;
		if(tr[idx(mid+1,r)].l<x){
			return qlst_t(mid+1,r,x);
		}
		return qlst_t(l,mid,x);
	}

	int qnxt_t(const int l,const int r,const int x){
		if(l==r) return l;
		const int mid=(l+r)>>1;
		if(tr[idx(l,mid)].r>x){
			return qnxt_t(l,mid,x);
		}
		return qnxt_t(mid+1,r,x);
	}

	void rm_t(const int l,const int r){
		if(l==r){
			const int k=idx(l,r);
			assert(tr[k].l==l&&tr[k].r==r);
			tr[k].l=n,tr[k].r=-1;
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) rm_t(l,mid);
		else rm_t(mid+1,r);
		upd(l,r);
	}

	void add_t(const int l,const int r){
		if(l==r){
			const int k=idx(l,r);
			assert(tr[k].l==n&&tr[k].r==-1);
			tr[k].l=l,tr[k].r=r;
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) add_t(l,mid);
		else add_t(mid+1,r);
		upd(l,r);
	}

	lint qmax_t(const int l,const int r){
		if(l==r){
			if(tr[idx(l,r)].l!=l) return -1;
			//assert(tr[idx(l,r)].l==l&&tr[idx(l,r)].r==r);
			return get_area(v[l],p);
		}
		const int mid=(l+r)>>1;
		if(tr[idx(mid+1,r)].l==n) return qmax_t(l,mid);
		if(tr[idx(l,mid)].r==-1) return qmax_t(mid+1,r);
		if(get_area(v[tr[idx(l,mid)].r],p)>get_area(v[tr[idx(mid+1,r)].l],p)){
			return qmax_t(l,mid);
		}
		return qmax_t(mid+1,r);
	}

	void init(_pair *v,const int n,const bool f){
		T::n=n,T::v=v,T::f=f;
		init_dfs(0,n-1);
	}

	void rm(const int x){
		T::x=x;
		rm_t(0,n-1);
	}

	void add(const int x){
		T::x=x;
		add_t(0,n-1);
	}

	lint qmax(const int x,const int y){
		T::p=(_pair){x,y};
		return qmax_t(0,n-1);
	}
}

double crsp(double k1,double b1,double k2,double b2){
	if(k1==k2) return 2e9;
	return (b2-b1)/(k1-k2);
}

double get_rm_t(const _pair a,const _pair b,const _pair c){
	assert(a.x!=b.x&&b.x!=c.x);
	double k1=-(double)(b.y-a.y)/(b.x-a.x);
	double k2=-(double)(c.y-b.y)/(c.x-b.x);
	double b1=(double)((lint)b.x*b.y-(lint)a.x*a.y)/(b.x-a.x);
	double b2=(double)((lint)c.x*c.y-(lint)b.x*b.y)/(c.x-b.x);
	return crsp(k1,b1,k2,b2);
}

_data get_data(const _pair* v,const int n,const int p,int lst,int nxt){
	if(lst==-1) lst=T::qlst_t(0,n-1,p);
	if(nxt==-1) nxt=T::qnxt_t(0,n-1,p);
	assert(lst>=0&&lst<p&&nxt<n&&nxt>p);
	return (_data){p,get_rm_t(v[lst],v[p],v[nxt])};
}

void solve(std::vector <_pair> &seg,std::vector <_qry> &qry){
	static double rm_tm[N];
	std::priority_queue <_data,std::vector <_data> ,std::greater <_data> > pq;
	if(qry.empty()||seg.empty()) return;
	std::sort(seg.begin(),seg.end());
	int cnt=0;
	for(int i=0; i<(int)seg.size(); ++i){
		if(i==(int)seg.size()-1||seg[i].x!=seg[i+1].x){
			seg[cnt++]=seg[i];
		}
	}
	seg.resize(cnt);
	cnt=0;
	for(int i=0; i<(int)seg.size(); ++i){
		if(i==0||seg[i].y>seg[cnt-1].y){
			seg[cnt++]=seg[i];
		}
	}
	for(int i=0; i<cnt; ++i){
		rm_tm[i]=2e9;
	}
	seg.resize(cnt);
	T::init(seg.data(),cnt,1);
	for(int i=1; i<cnt-1; ++i){
		double r=get_rm_t(seg[i-1],seg[i],seg[i+1]);
		pq.push((_data){i,r});
	}
	while(!pq.empty()){
		_data dt=pq.top();
		pq.pop();
		int p1=T::qlst_t(0,cnt-1,dt.x);
		int p2=T::qnxt_t(0,cnt-1,dt.x);
		if(dt.rm_t<seg[dt.x].x||get_rm_t(seg[p1],seg[dt.x],seg[p2])!=dt.rm_t){
			continue;
		}
		rm_tm[dt.x]=dt.rm_t;
		T::rm(dt.x);
		if(p1!=0){
			pq.push(get_data(seg.data(),cnt,p1,-1,p2));
		}
		if(p2!=cnt-1){
			pq.push(get_data(seg.data(),cnt,p2,p1,-1));
		}
	}
	for(int i=1; i<cnt-1; ++i){
		assert(rm_tm[i]>seg[i].x);
	}
	while(!pq.empty()) pq.pop();
	T::init(seg.data(),cnt,0);
	for(int i=0,j=0; i<(int)qry.size(); ++i){
		for(; seg[j].x<=qry[i].x&&j<cnt; ++j){
			T::add(j);
			if(j&&j!=cnt-1){
				pq.push((_data){j,rm_tm[j]});
			}
		}
		while(!pq.empty()){
			_data dt=pq.top();
			if(dt.rm_t>qry[i].x) break;
			pq.pop();
			T::rm(dt.x);
		}
		apx(ans[qry[i].id],T::qmax(qry[i].x,qry[i].y));
	}
}

namespace Q{
	std::vector <_pair> seg[N<<1];
	std::vector <_qry> qry[N<<1];
	int x,y;
	_pair v;

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	void adds_t(const int l,const int r){
		if(l>=x&&r<=y){
			seg[idx(l,r)].push_back(v);
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) adds_t(l,mid);
		if(y>mid) adds_t(mid+1,r);
	}

	void adds(const int x,const int y,const _pair v){
		assert(x<=y);
		Q::x=x,Q::y=y,Q::v=v;
		adds_t(1,n);
	}

	void addq(const int x,const _qry v){
		qry[idx(x,x)].push_back(v);
	}

	void build(const int l,const int r){
		const int k=idx(l,r),mid=(l+r)>>1;
		if(l!=r){
			const int ls=idx(l,mid),rs=idx(mid+1,r);
			build(l,mid);
			build(mid+1,r);
			qry[k].resize(qry[ls].size()+qry[rs].size());
			std::merge(qry[ls].begin(),qry[ls].end(),
					qry[rs].begin(),qry[rs].end(),qry[k].begin());
			std::vector <_qry> ().swap(qry[ls]);
			std::vector <_qry> ().swap(qry[rs]);
		}
		solve(seg[k],qry[k]);
	}
}

int main(){
	static int pos[N];
	n=nxi();
	int cnts=0;
	for(int i=1; i<=n; ++i){
		const int op=nxi();
		if(op==1){
			const int x=nxi(),y=nxi();
			seg[++cnts]=(_pair){x,y};
			pos[cnts]=i;
		}
		if(op==2){
			const int x=nxi()+1;
			assert(pos[x]);
			Q::adds(pos[x],i-1,seg[x]);
			pos[x]=0;
		}
		if(op==3){
			const int x=nxi(),y=nxi();
			Q::addq(i,(_qry){++q,x,y});
		}
	}
	memset(ans+1,-1,q*sizeof(ans[0]));
	for(int i=1; i<=cnts; ++i){
		if(pos[i]){
			Q::adds(pos[i],n,seg[i]);
			pos[i]=0;
		}
	}
	Q::build(1,n);
	for(int i=1; i<=q; ++i){
		printf("%lld\n",ans[i]);
	}
	return 0;
}
