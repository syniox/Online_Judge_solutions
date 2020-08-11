#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef unsigned long long ull;
const int N=5e6+5,V=2e7+5;
int n,q,pa[N],pb[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
	static struct{
		template <class T> operator T(){
			T x=0;
			char c;
			while(((c=getchar())>'9'||c<'0')&&c!='-');
			const bool f=c=='-'&&(c=getchar());
			while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
			return f?-x:x;
		}
	}ni;
}
using namespace utils;

ull xsp(ull &k1,ull &k2){
	ull k3=k1,k4=k2;
	k1=k4,k3^=k3<<23;
	k2=k3^k4^(k3>>17)^(k4>>26);
	return k2+k4;
}

void gen(){
	static const int threshold=1e7;
	n=ni,q=ni;
	ull k1=ni,k2=ni;
	for(int i=1; i<=n; ++i){
		pa[i]=xsp(k1,k2)%threshold+1;
		pb[i]=xsp(k1,k2)%threshold+1;
	}
}

void buk_sort(int v[],const int n){
	static int buk[V];
	int cnt=0,mx=0;
	for(int i=1; i<=n; ++i){
		++buk[v[i]];
		apx(mx,v[i]);
	}
	for(int i=mx; i; --i){
		for(; buk[i]; --buk[i]) v[++cnt]=i;
	}
	//assert(cnt==n);
}

int main(){
	gen();
	for(int i=1; i<=n; ++i){
		pb[i]+=pa[i];
	}
	buk_sort(pa,n);
	buk_sort(pb,n);
	lint ans=0,s=0;
	for(int i=1,t1=0,t2=0; i<=q; ++i){
		s+=pa[++t1];
		if(t1>=2&&pb[t2+1]>=pa[t1]+pa[t1-1]){
			s+=pb[t2+1]-pa[t1]-pa[t1-1];
			++t2,t1-=2;
		}
		ans^=s;
	}
	printf("%lld\n",ans);
	return 0;
}
