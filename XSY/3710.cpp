#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <cmath>
typedef long long lint;
const int N=7000;
int n,xval,nval(1e5),val[N];
double wp[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
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

double qmean(const double lambda){
	double ans=0,_exp=(double)1/(n-1);
	for(int i=1; i<=n; ++i){
		ans+=wp[i]=std::max(0.,1-pow(lambda/(n*val[i]),_exp));
	}
	return ans;
}

template <class T>
inline T fpow(T x,int t){
	T ans;
	for(bool f=0; t; x=x*x,t>>=1){
		if(t&1) ans=f?ans*x:x;
		f|=t&1;
	}
	return ans;
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		apx(xval,val[i]=nxi());
		apn(nval,val[i]);
	}
	{
		double l=0,r=(double)xval*n,mid;
		for(int i=1; i<=40; ++i){
			mid=(l+r)/2;
			if(qmean(mid)>1) l=mid;
			else r=mid;
		}
	}
	double ans=0;
	for(int i=1; i<=n; ++i){
		ans+=val[i]*(1-fpow(1-wp[i],n));
	}
	printf("%.9lf\n",ans/n);
	return 0;
}
