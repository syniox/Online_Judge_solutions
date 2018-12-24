#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cstdlib>
typedef long long lint;
const int N=505;
int n,m,hx[N],list[N];

bool cmp_hx(const int a,const int b){
	return hx[a]<hx[b];
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace S{
	//alway take down the smallest node on the route
	int down_node,tick,tag[N],lnk[N];
	bool take_down;
	class Graph{
		protected:
			std::vector <int> to[N];

			bool dfs(const int x){
				if(take_down){
					if(down_node==x) return 1;
				}
				else if(hx[x]<hx[down_node]){
					down_node=x;
				}
				for(std::vector <int> ::iterator it=to[x].begin(); it!=to[x].end(); ++it){
					const int y=*it;
					if(!lnk[y]){
						lnk[y]=x,lnk[x]=y;
						return 1;
					}
					else if(tag[y]<tick){
						tag[y]=tick;
						const int z=lnk[y];
						lnk[y]=x,lnk[x]=y,lnk[z]=0;
						if(dfs(z)) return 1;
						lnk[y]=z,lnk[x]=0,lnk[z]=y;
					}
				}
				return 0;
			}

		public:
			inline void add(const int a,const int b){
				to[a].push_back(b);
				to[b].push_back(a);
			}

			friend lint solve(Graph &G);
	}G;

	inline lint solve(Graph &G){
		lint ans=0;
		memset(lnk,0,sizeof(lnk));
		for(int i=1; i<=n; ++i){
			std::random_shuffle(G.to[i].begin(),G.to[i].end());
		}
		for(int i=n; i; --i){
			const int x=list[i];
			if(lnk[x]) continue;
			++tick;
			take_down=0,down_node=x;
			if(G.dfs(x)) continue;
			++tick;
			take_down=1;
			G.dfs(x);
		}
		for(int i=1; i<=n; ++i){
			if(lnk[i]) ans+=hx[i];
		}
		return ans;
	}
}

int main(){
	srand(19260817);
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		hx[i]=nxi(),list[i]=i;
	}
	std::sort(list+1,list+n+1,cmp_hx);
	for(int i=1; i<=m; ++i){
		S::G.add(nxi(),nxi());
	}
	printf("%lld\n",std::max(S::solve(S::G),S::solve(S::G)));
	return 0;
}
