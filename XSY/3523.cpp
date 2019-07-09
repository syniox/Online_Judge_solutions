#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
typedef long long lint;
const int N=1e5+5;
const double eps=1e-12;
int n;
lint pv[N];
double sum[N];
struct data{
	int v,id;
	double h;
	friend bool operator < (const data &a,const data &b){
		return a.h<b.h;
	}
}dt[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
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

double getsum(const double x){
	int p=std::lower_bound(pv+1,pv+n+1,x)-pv;
	assert(p<=n);
	return sum[p-1]+dt[p].h*(x-pv[p-1]);
}

void oput(const double x1,const double x2){
	int p1=std::lower_bound(pv+1,pv+n+1,x1)-pv;
	int p2=std::lower_bound(pv+1,pv+n+1,x2)-pv;
	if(p1==p2){
		puts("2");
		printf("%d %.12lf\n",dt[p1].id,(x1-pv[p1-1])/dt[p1].v);
		printf("%d %.12lf\n",dt[p1].id,(x2-x1)/(dt[p1].v-(pv[p1]-x1)));
		puts("1");
		printf("%d\n",n+1);
	}
	else{
		puts("2");
		printf("%d %.12lf\n",dt[p1].id,(x1-pv[p1-1])/dt[p1].v);
		printf("%d %.12lf\n",dt[p2].id,(pv[p2]-x2)/dt[p2].v);
		printf("%d\n",p2-p1+1);
		printf("%d %d ",n+1,n+2);
		for(int i=p1+1; i<p2; ++i){
			printf("%d ",dt[i].id);
		}
		puts("");
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		dt[i].id=i;
		dt[i].v=nxi(),dt[i].h=(double)nxi()/dt[i].v;
	}
	std::sort(dt+1,dt+n+1);
	for(int i=1; i<=n; ++i){
		sum[i]=sum[i-1]+dt[i].v*dt[i].h;
		pv[i]=pv[i-1]+dt[i].v;
	}
	double l=0,r=pv[n]/2.0,mid;
	for(int i=1; i<=100; ++i){
		mid=(l+r)/2;
		if(getsum(mid+pv[n]/2.0)-getsum(mid)<sum[n]/2.0) l=mid;
		else r=mid;
	}
	oput(l,l+pv[n]/2.0);
	return 0;
}
