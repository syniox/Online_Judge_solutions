#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
typedef long long lint;
const int N=2e5+5;
int n,m1,m2,ans[N];
std::vector <int> buk[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
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

class _ufs{
	protected:
		int fa[N];
	public:
		int find_rt(const int x){
			return fa[x]?fa[x]=find_rt(fa[x]):x;
		}
		void link(int x,int y){
			x=find_rt(x),y=find_rt(y);
			if(x!=y) fa[x]=y;
		}
}u1,u2;

void solve(const int r){
	static int cnt[N];
	for(std::vector <int> ::iterator it=buk[r].begin(); it!=buk[r].end(); ++it){
		++cnt[u2.find_rt(*it)];
	}
	for(std::vector <int> ::iterator it=buk[r].begin(); it!=buk[r].end(); ++it){
		ans[*it]=cnt[u2.find_rt(*it)];
	}
	for(std::vector <int> ::iterator it=buk[r].begin(); it!=buk[r].end(); ++it){
		cnt[u2.find_rt(*it)]=0;
	}
}

int main(){
	n=nxi(),m1=nxi(),m2=nxi();
	while(m1--) u1.link(nxi(),nxi());
	while(m2--) u2.link(nxi(),nxi());
	for(int i=1; i<=n; ++i){
		buk[u1.find_rt(i)].push_back(i);
	}
	for(int i=1; i<=n; ++i){
		if(!buk[i].empty()) solve(i);
	}
	for(int i=1; i<=n; ++i){
		printf("%d ",ans[i]);
	}
	puts("");
	return 0;
}
