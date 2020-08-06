#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <set>
#include <map>
typedef long long lint;
using namespace std;
const int N=5005;
const int mod=998244353;
int n,p,val[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
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

namespace S1{
	const int N=11;
	int dp[1<<N],st[N];
	void main(){
		map<int,int> mp;
		memset(dp,10,sizeof(dp));
		for(int i=1; i<=n; ++i){
			mp[val[i]]=i;
		}
		for(int i=1; i<=n; ++i){
			set<int> vis;
			for(int w=val[i]; ; w=(lint)w*val[i]%p){
				if(vis.find(w)!=vis.end()) break;
				map<int,int>::iterator it=mp.find(w);
				if(it==mp.end()) continue;
				st[i]|=1<<(it->second-1);
				vis.insert(w);
			}
		}
		int ans=0;
		for(int i=1; i<1<<n; ++i){
			memset(dp,10,sizeof(dp));
			for(int j=1; j<=n; ++j){
				if(!(i>>(j-1)&1)) continue; 
				for(int k=st[j]; k; k=(k-1)&st[j]){
					dp[k]=1;
				}
			}
			for(int j=1; j<=i; ++j){
				for(int k=(j-1)&j; k>(j^k); k=(k-1)&j){
					apn(dp[j],dp[k]+dp[j^k]);
				}
			}
			ans=(ans+dp[i])%mod;
		}
		printf("%d\n",ans);
	}
}

int main(){
	n=ni,p=ni;
	for(int i=1; i<=n; ++i){
		val[i]=ni;
	}
	if(n<=10) S1::main();
	return 0;
}
