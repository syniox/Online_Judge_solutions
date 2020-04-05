#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
typedef long long lint;
const int N=5e5+5;
int n,m,id[N];
lint val[N];
std::vector <int> eg[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline lint nxi(){
		lint x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

inline bool cmp_id(const int x,const int y){
	return eg[x]<eg[y];
}

inline lint gcd(const lint a,const lint b){
	return b?gcd(b,a%b):a;
}

int main(){
	for(int T=nxi(); T; --T){
		n=nxi(),m=nxi();
		for(int i=1; i<=n; ++i){
			val[i]=nxi();
			eg[i].clear();
			id[i]=i;
		}
		for(int i=1; i<=m; ++i){
			int p=nxi();
			eg[nxi()].push_back(p);
		}
		for(int i=1; i<=n; ++i){
			std::sort(eg[i].begin(),eg[i].end());
		}
		std::sort(id+1,id+n+1,cmp_id);
		lint ans=0;
		for(int i=1; i<=n; ++i){
			if(eg[id[i]].empty()) continue;
			int j=i+1;
			for(; j<=n&&eg[id[i]]==eg[id[j]]; ++j);
			lint res=0;
			for(int k=i; k<j; ++k) res+=val[id[k]];
			i=j-1;
			ans=gcd(ans,res);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
