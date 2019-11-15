#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=2e5+5;
const int mod=1e9+7;
int n,ans,tsum,inv[N],req[N],val[N],pm1[N],ipm[N],invld[N];

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

inline int fpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

bool get_val(){
	for(int i=1; i<=n; ++i){
		++val[req[i]];
	}
	for(int i=n-1; i; --i){
		val[i]+=val[i+1];
	}
	for(int i=n; i; --i){
		if((val[i]=val[i]-(n-i))<=0) return 0;
		invld[i]=val[i]==1;
	}
	return 1;
}

void get_pm1(){
	static int buk[N];
	for(int i=1; i<=n; ++i){
		++buk[req[i]];
	}
	tsum=1;
	for(int i=1; i<=n; ++i){
		pm1[i]=(lint)inv[val[i]]*(val[i]-1)%mod;
		ans=(ans+(lint)(buk[i])*(buk[i]-1)%mod*inv[2])%mod;
		if(!invld[i]) assert(pm1[i]);
		tsum=(lint)tsum*val[i]%mod;
	}
	ans=(lint)ans*tsum%mod;
	for(int i=1; i<=n; ++i){
		if(i>1&&!invld[i-1]&&!invld[i]){
			pm1[i]=(lint)pm1[i]*pm1[i-1]%mod;
		}
		if(invld[i]) ipm[i]=1;
		else ipm[i]=fpow(pm1[i],mod-2);
	}
	for(int i=2; i<=n; ++i){
		invld[i]+=invld[i-1];
	}
}

void solve(int l1,int r1,int l2,int r2,int &tsz,int &res){
	tsz=res=0;
	int sum=0;
	for(int i=r1,j=r2; i>=l1; --i){
		for(; j>=l2&&req[j]>req[i]; --j){
			if(j<r2){
				if(invld[req[j+1]]!=invld[req[j]]){
					sum=0;
				}
				else{
					sum=(lint)sum*pm1[req[j+1]]%mod*ipm[req[j]]%mod;
				}
			}
			sum=(sum+tsum)%mod;
		}
		tsz=(tsz+r2-j)%mod;
		if(sum&&invld[req[i]]==invld[req[j+1]]){
			res=(res+(lint)pm1[req[j+1]]*ipm[req[i]]%mod*sum)%mod;
		}
	}
}

void bsolve(const int l,const int r){
	const int mid=(l+r)>>1;
	if(l<mid) bsolve(l,mid);
	if(r>mid+1) bsolve(mid+1,r);
	int sz1,res1,sz2,res2;
	solve(l,mid,mid+1,r,sz1,res1);
	solve(mid+1,r,l,mid,sz2,res2);
	ans=(ans+res1)%mod;
	ans=(ans+2ll*sz2*tsum-res2)%mod;
	std::inplace_merge(req+l,req+mid+1,req+r+1);
}

int main(){
	n=nxi();
	inv[1]=1;
	for(int i=1; i<=n; ++i){
		req[i]=nxi();
		if(i>1){
			inv[i]=(mod-(lint)inv[mod%i]*(mod/i)%mod)%mod;
		}
	}
	if(!get_val()){
		puts("0");
		return 0;
	}
	get_pm1();
	bsolve(1,n);
	printf("%lld\n",(lint)ans*inv[2]%mod);
	return 0;
}
