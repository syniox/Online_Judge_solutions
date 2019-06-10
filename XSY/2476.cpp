#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>
typedef long long lint;
const int N=3e5+5;
int n,q,val[N];
lint ans[N];
bool vis[N];
struct _pair{
	int x,y;
	friend _pair operator - (const _pair &a,const _pair &b){
		return (_pair){a.x-b.x,a.y-b.y};
	}
	friend lint crs(const _pair &a,const _pair &b){
		return (lint)a.x*b.y-(lint)a.y*b.x;
	}
	lint qans(const int q){
		return (lint)x*q+y;
	}
}pr[N];

namespace utils{
	template <class T> inline void apx(T &x,const T y){
		x<y?x=y:0;
	}
	template <class T> inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

template <class T>
std::vector <T> merge(const std::vector <T> &x,const std::vector <T> y,bool (*cmp)(T,T)){
	const int s1=x.size(),s2=y.size();
	int p1=0,p2=0;
	std::vector <T> res;
	while(p1<s1&&p2<s2){
		if(cmp(x[p1],y[p2])){
			res.push_back(x[p1++]);
		}
		else{
			res.push_back(y[p2++]);
		}
	}
	while(p1<s1){
		res.push_back(x[p1++]);
	}
	while(p2<s2){
		res.push_back(y[p2++]);
	}
	return res;
}

inline bool cmp_x(const _pair a,const _pair b){
	return a.x<b.x;
}
inline bool cmp_v(const int x,const int y){
	return val[x]<val[y];
}

namespace T{
	int x,y;
	std::vector <_pair> tr[N<<1];
	std::vector <int> qry[N<<1];
	_pair v;

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	void ins_t(const int l,const int r){
		if(l>=x&&r<=y){
			tr[idx(l,r)].push_back(v);
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) ins_t(l,mid);
		if(y>mid) ins_t(mid+1,r);
	}

	void ins(const int l,const int r,const _pair pr){
		T::v=pr,T::x=l,T::y=r;
		ins_t(1,n);
	}

	void ask(const int p,const int x){
		T::qry[idx(p,p)].push_back(x);
	}

	void ansqry(const std::vector <int> &qry,std::vector <_pair> &pr){
		static _pair buk[N];
		if(pr.empty()) return;
		std::sort(pr.begin(),pr.end(),cmp_x);
		int pt=0;
		for(int i=0; i<(int)pr.size(); ++i){
			while(pt>1&&crs(buk[pt]-buk[pt-1],pr[i]-buk[pt-1])>=0){
				--pt;
			}
			buk[++pt]=pr[i];
		}
		for(int i=0,j=1; i<(int)qry.size(); ++i){
			const int c=qry[i];
			while(j<pt&&buk[j].qans(val[c])<buk[j+1].qans(val[c])){
				++j;
			}
			apx(ans[c],buk[j].qans(val[c]));
		}
	}

	void build(const int l,const int r){
		const int k=idx(l,r),mid=(l+r)>>1;
		if(l==r){
			if(qry[k].empty()||tr[k].empty()) return;
			ansqry(qry[k],tr[k]);
			return;
		}
		const int ls=idx(l,mid),rs=idx(mid+1,r);
		build(l,mid);
		build(mid+1,r);
		qry[k]=merge(qry[ls],qry[rs],cmp_v);
		ansqry(qry[k],tr[k]);
	}
}

int main(){
	memset(ans,-60,sizeof(ans));
	n=nxi();
	for(int i=1; i<=n; ++i){
		const int op=nxi();
		if(op==1){
			pr[i].x=nxi(),pr[i].y=nxi();
		}
		if(op==2){
			const int p=nxi();
			vis[i]=vis[p]=1;
			T::ins(p,i-1,pr[p]);
		}
		if(op==3){
			val[++q]=nxi();
			vis[i]=1;
			T::ask(i,q);
		}
	}
	for(int i=1; i<=n; ++i){
		if(!vis[i]) T::ins(i,n,pr[i]);
	}
	T::build(1,n);
	for(int i=1; i<=q; ++i){
		if(ans[i]<-2e18) puts("EMPTY SET");
		else printf("%lld\n",ans[i]);
	}
	return 0;
}
