#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
using namespace std;
const int N=10005,C=1005;
const int mod=1e9+7;
int n,q,pv[N][C],ipv[N][C];

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

void apl(int *v,const int d){
	for(int i=C-1; i>=d; --i)
		v[i]=(v[i]-v[i-d]+mod)%mod;
}
void aplinv(int *v,const int d){
	for(int i=d; i<C; ++i)
		v[i]=(v[i]+v[i-d])%mod;
}

int qans(const int l,const int r,const int c){
	static int v[N];
	memcpy(v,pv[r],(c+1)*sizeof(int));
	aplinv(v,1);
	int ans=0;
	for(int i=0; i<=c; ++i)
		ans=(ans+(lint)v[i]*ipv[l-1][c-i])%mod;
	return ans;
}

int main(){
	n=nxi(),q=nxi();
	pv[0][0]=ipv[0][0]=1;
	for(int i=1; i<=n; ++i){
		int va=nxi(),vb=nxi();
		memcpy(pv[i],pv[i-1],sizeof(pv[i]));
		memcpy(ipv[i],ipv[i-1],sizeof(ipv[i]));
		apl(pv[i],(va+1)*vb);
		aplinv(pv[i],vb);
		aplinv(ipv[i],(va+1)*vb);
		apl(ipv[i],vb);
	}
	for(int ans=0; q--; ){
		int l=(nxi()+ans)%n+1,r=(nxi()+ans)%n+1;
		if(l>r) swap(l,r);
		printf("%d\n",ans=qans(l,r,nxi()));
	}
	return 0;
}
