#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
typedef long long lint;
const int N=1e5+5;
int n,m,val[N],fa[N];
std::vector <int> buk[N];

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

int find_rt(const int x){
	return fa[x]?fa[x]=find_rt(fa[x]):x;
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	for(int i=1; i<=m; ++i){
		int x=find_rt(nxi()),y=find_rt(nxi());
		if(x!=y) fa[x]=y;
	}
	for(int i=1; i<=n; ++i){
		buk[find_rt(i)].push_back(i);
	}
	int ans=0;
	for(int i=1; i<=n; ++i){
		static bool vis[N];
		if(buk[i].empty()) continue;
		for(std::vector <int> ::iterator it=buk[i].begin(); it!=buk[i].end(); ++it){
			vis[*it]=1;
		}
		for(std::vector <int> ::iterator it=buk[i].begin(); it!=buk[i].end(); ++it){
			ans+=vis[val[*it]];
		}
		for(std::vector <int> ::iterator it=buk[i].begin(); it!=buk[i].end(); ++it){
			vis[*it]=0;
		}
	}
	printf("%d\n",ans);
	return 0;
}
