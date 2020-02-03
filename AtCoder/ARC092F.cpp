#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
typedef long long lint;
const int N=1005;
const int M=2e5+5;
int n,m;
bool irp[N][N],lnk[N][N];

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
	int rt,cnt,fir[N];
	bool col[N];
	std::vector <int> g[N];
	struct edge{
		int fr,to;
	}eg[M];

	inline void add(const int a,const int b){
		g[a].push_back(b);
		eg[++cnt]=(edge){a,b};
	}

	void dfs(const int x){
		col[x]=lnk[rt][x]=1;
		for(std::vector <int> ::iterator it=g[x].begin(); it!=g[x].end(); ++it){
			if(!col[*it]) dfs(*it);
		}
	}

	void set(const int x){
		rt=x;
		memset(col+1,0,n*sizeof(col[0]));
		col[x]=1;
		for(std::vector <int> ::iterator it=g[x].begin(); it!=g[x].end(); ++it){
			if(col[*it]) irp[x][*it]=1;
			else dfs(*it);
		}
		std::reverse(g[x].begin(),g[x].end());
		memset(col+1,0,n*sizeof(col[0]));
		col[x]=1;
		for(std::vector <int> ::iterator it=g[x].begin(); it!=g[x].end(); ++it){
			if(col[*it]) irp[x][*it]=1;
			else dfs(*it);
		}
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=m; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
	}
	for(int i=1; i<=n; ++i){
		G::set(i);
	}
	for(int i=1; i<=m; ++i){
		int x=G::eg[i].fr,y=G::eg[i].to;
		puts(irp[x][y]^lnk[y][x]?"diff":"same");
	}
	return 0;
}
