#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
typedef long long lint;
const int N=1e5+5;
int n;

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

namespace G{
	int dis[N];
	bool vis[N];
	struct edge{
		int to,wi;
	};
	std::vector <edge> g[N],vg[N];

	inline void add(const int a,const int b,const int v){
		g[a].push_back((edge){b,v});
		vg[b].push_back((edge){a,v});
	}

	bool dfs(const int x){
		vis[x]=1;
		for(std::vector <edge> ::iterator it=g[x].begin(); it!=g[x].end(); ++it){
			const int y=it->to,d=dis[x]+it->wi;
			if(!vis[y]&&!(dis[y]=d,dfs(y))) return 0;
			if(dis[y]!=d) return 0;
		}
		for(std::vector <edge> ::iterator it=vg[x].begin(); it!=vg[x].end(); ++it){
			const int y=it->to,d=dis[x]-it->wi;
			if(!vis[y]&&!(dis[y]=d,dfs(y))) return 0;
			if(dis[y]!=d) return 0;
		}
		return 1;
	}

	bool build(){
		for(int i=1; i<=n; ++i){
			if(!vis[i]&&!dfs(i)) return 0;
		}
		return 1;
	}
}

int main(){
	n=nxi();
	for(int i=nxi(); i; --i){
		const int a=nxi(),b=nxi();
		G::add(a,b,nxi());
	}
	puts(G::build()?"Yes":"No");
	return 0;
}
