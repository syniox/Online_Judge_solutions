#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
typedef long long lint;
const int N=1e6+5;
int n,m;

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
	int cnt=1,cnf,fir[N],ex[N],ey[N],bel[N],cnt_p[N];
	std::vector <int> buk[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,fir[b]};
		fir[b]=cnt;
	}

	void tarjan(const int x,const int f){
		static int cnd,top,dfn[N],low[N],stk[N];
		static bool vis[N];
		low[x]=dfn[x]=++cnd;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(vis[i>>1]) continue;
			vis[i>>1]=1;
			stk[++top]=i>>1;
			if(!dfn[y]){
				if(tarjan(y,x),low[y]>=dfn[x]){
					++cnf;
					for(int j=stk[top--]; ; j=stk[top--]){
						bel[j]=cnf;
						buk[cnf].push_back(j);
						if(j==i>>1) break;
					}
				}
				else apn(low[x],low[y]);
			}
			else apn(low[x],dfn[y]);
		}
		if(x==f) assert(!top);
	}

	inline void solve(){
		static bool vis[N];
		for(int i=1; i<=cnf; ++i){
			int ans=0;
			for(std::vector <int> ::iterator it=buk[i].begin(); it!=buk[i].end(); ++it){
				int x=eg[*it<<1].to,y=eg[*it<<1|1].to;
				ans+=(int)(!vis[x])+(!vis[y]);
				vis[x]=vis[y]=1;
			}
			for(std::vector <int> ::iterator it=buk[i].begin(); it!=buk[i].end(); ++it){
				int x=eg[*it<<1].to,y=eg[*it<<1|1].to;
				vis[x]=vis[y]=0;
			}
			cnt_p[i]=ans;
		}
	}

	inline int getans(){
		int ans=0;
		for(int i=1; i<=m; ++i){
			ans^=i*((int)buk[bel[i]].size()==cnt_p[bel[i]]);
		}
		return ans;
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=m; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
	}
	G::tarjan(1,1);
	G::solve();
	printf("%d\n",G::getans());
	return 0;
}
