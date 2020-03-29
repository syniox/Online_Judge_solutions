#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
typedef long long lint;
const int N=40005;
int n,m,q,n1[N],n2[N],buk[N];
bool v1[N],v2[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
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

void getn(const bool *v,int *nx,const int n){
	nx[n+1]=n;
	for(int i=n; i>=1; --i){
		nx[i]=v[i]?nx[i+1]:i-1;
	}
}

int main(){
	n=nxi(),m=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		v1[i]=nxi();
	}
	for(int i=1; i<=m; ++i){
		v2[i]=nxi();
	}
	getn(v1,n1,n);
	getn(v2,n2,m);
	for(int i=1; i<=m; ++i){
		++buk[n2[i]-i+1];
	}
	for(int i=m-1; i; --i){
		buk[i]+=buk[i+1];
	}
	lint ans=0;
	for(int i=1; i<=sqrt(q); ++i){
		if(q%i) continue;
		int p=q/i;
		for(int j=1; j<=n; ++j){
			if(p<=m&&n1[j]-j+1>=i) ans+=buk[p];
			if(p!=i&&n1[j]-j+1>=p) ans+=buk[i];
		}
	}
	printf("%lld\n",ans);
	return 0;
}
