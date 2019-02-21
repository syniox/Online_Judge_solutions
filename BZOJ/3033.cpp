#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
const int N=2050;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt=1,fir[N];
	int cne,stk[N];
	bool vis[N];
	struct data{
		int to,id;
		friend bool operator < (const data &a,const data &b){
			return a.id<b.id;
		}
	};
	std::vector <data> vt[N];

	inline void add(const int a,const int b,const int v){
		vt[a].push_back((data){b,v});
	}

	void dfs(const int x){
		for(std::vector <data> ::iterator it=vt[x].begin(); it!=vt[x].end(); ++it){
			if(vis[it->id]) continue;
			vis[it->id]=1;
			dfs(it->to);
			stk[++cne]=it->id;
		}
	}
}

int main(){
	int q=nxi();
	for(int i=0; i<1<<(q-1); ++i){
		G::add(i,(i<<1&((1<<(q-1))-1))|1,i<<1|1);
		G::add(i,(i<<1&((1<<(q-1))-1))|0,i<<1|0);
	}
	for(int i=0; i<1<<(q-1); ++i){
		std::sort(G::vt[i].begin(),G::vt[i].end());
	}
	G::dfs(0);
	printf("%d ",1<<q);
	for(int i=G::cne; i; --i){
		printf("%d",G::stk[i]>>(q-1)&1);
	}
	puts("");
	return 0;
}
