#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <set>
typedef long long lint;
const int N=3e5+5;
const int mod=998244353;
std::set <int> nbr[N];
int n;

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

int main(){
	n=nxi();
	for(int i=nxi(); i; --i){
		const int a=nxi(),b=nxi();
		nbr[std::min(a,b)].insert(std::max(a,b));
	}
	int ans=1;
	for(int i=1; i<=n; ++i){
		ans=(lint)ans*(n-nbr[i].size())%mod;
		if(nbr[i].empty()) continue;
		int j=*nbr[i].begin();
		nbr[i].erase(nbr[i].begin());
		if(nbr[i].size()>nbr[j].size()){
			std::swap(nbr[i],nbr[j]);
		}
		for(std::set <int> ::iterator it=nbr[i].begin(); it!=nbr[i].end(); ++it){
			nbr[j].insert(*it);
		}
	}
	printf("%d\n",ans);
	return 0;
}
