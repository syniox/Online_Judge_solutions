#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
const int N=45;
const int M=1996;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cne,dgr[N],ans[M];
	bool vis[M];
	struct data{
		int to,id;
	};
	std::vector <data> lnk[N];

	bool cmp_id(const data &a,const data &b){
		return a.id<b.id;
	}

	inline void clear(){
		for(int i=1; i<N; ++i){
			lnk[i].clear();
		}
		cne=0;
		memset(dgr,0,sizeof(dgr));
		memset(vis,0,sizeof(vis));
	}

	inline void add(const int a,const int b,const int v){
		++dgr[a],++dgr[b];
		lnk[a].push_back((data){b,v});
		lnk[b].push_back((data){a,v});
	}

	inline bool jdg(){
		for(int i=1; i<N; ++i){
			if(dgr[i]&1) return 0;
		}
		return 1;
	}

	inline void sanitize(){
		for(int i=1; i<N; ++i){
			if(!lnk[i].empty()){
				std::sort(lnk[i].begin(),lnk[i].end(),cmp_id);
			}
		}
	}

	inline void dfs(const int x){
		for(std::vector <data> ::iterator it=lnk[x].begin(); it!=lnk[x].end(); ++it){
			if(vis[it->id]) continue;
			vis[it->id]=1;
			dfs(it->to);
			ans[++cne]=it->id;
		}
	}
}

int main(){
	int e_x,e_y,e_v;
	while(e_x=nxi(),e_y=nxi(),e_x&&e_y){
		G::clear();
		e_v=nxi();
		G::add(e_x,e_y,e_v);
		const int st=std::min(e_x,e_y);
		for(e_x=nxi(),e_y=nxi(); e_x&&e_y; e_x=nxi(),e_y=nxi()){
			G::add(e_x,e_y,nxi());
		}
		if(!G::jdg()){
			printf("Round trip does not exist.\n");
			continue;
		}
		G::sanitize();
		G::dfs(st);
		for(int i=G::cne; i; --i){
			printf("%d ",G::ans[i]);
		}
		puts("");
	}
	return 0;
}
