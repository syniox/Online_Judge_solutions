#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
using namespace std;
const int N=2e5+5;
int n,val[N],divp[N],divn[N];
lint pval[N];

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

inline lint diffv(int s1,int s2,int s3){
	lint v1=pval[s2]-pval[s1-1];
	lint v2=pval[s3]-pval[s2];
	return v1<v2?v2-v1:v1-v2;
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		pval[i]=val[i]+pval[i-1];
	}
	divp[2]=1;
	for(int i=3; i<n; ++i){
		divp[i]=divp[i-1];
		while(diffv(1,divp[i],i)>diffv(1,divp[i]+1,i)){
			++divp[i];
			assert(divp[i]<i);
		}
	}
	divn[n-2]=n-1;
	for(int i=n-3; i>1; --i){
		divn[i]=divn[i+1];
		while(diffv(i+1,divn[i],n)>diffv(i+1,divn[i]-1,n)){
			--divn[i];
			assert(divn[i]>i);
		}
	}
	lint ans=1e12;
	for(int i=2; i<n-1; ++i){
		lint v[4]={pval[divp[i]],pval[i]-pval[divp[i]],
			pval[divn[i]]-pval[i],pval[n]-pval[divn[i]]};
		sort(v,v+4);
		apn(ans,v[3]-v[0]);
	}
	printf("%lld\n",ans);
	return 0;
}
