#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstdlib>
const int N=305;
int n,m;

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int tick,tag[N],lnk[N];

	std::vector <int> eg[N];

	inline void add_edge(const int a,const int b){
		eg[a].push_back(b);
		eg[b].push_back(a);
	}

	bool dfs(const int x){
		tag[x]=tick;
		for(std::vector <int> ::iterator it=eg[x].begin(); it!=eg[x].end(); ++it){
			if(!lnk[*it]){
				lnk[x]=*it,lnk[*it]=x;
				return 1;
			}
			else if(tag[*it]!=tick){
				tag[*it]=tick;
				int z=lnk[*it];
				lnk[*it]=x,lnk[x]=*it,lnk[z]=0;
				if(dfs(z)) return 1;
				lnk[*it]=z,lnk[z]=*it,lnk[x]=0;
			}
		}
		return 0;
	}

	int solve(){
		memset(lnk+1,0,(n+n+m)*sizeof(int));
		for(int i=1; i<=n+n+m; ++i){
			std::random_shuffle(eg[i].begin(),eg[i].end());
		}
		int ans=0;
		for(int i=1; i<=n+n+m; ++i){
			if(!lnk[i]) ++tick,ans+=dfs(i);
		}
		return ans;
	}
}

int main(){
#ifndef ONLINE_JUDGE
	//freopen("d.in","r",stdin);
#endif
	srand(19260817);
	static char ch[N];
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		G::add_edge(i,i+n);
		scanf("%s",ch+1);
		for(int j=1; j<=m; ++j){
			if(ch[j]=='1'){
				G::add_edge(i,j+(n<<1));
				G::add_edge(i+n,j+(n<<1));
			}
		}
	}
	int ans=0;
	for(int i=1; i<=20; ++i){
		apx(ans,G::solve());
	}
	printf("%d\n",ans-n);
	return 0;
}
