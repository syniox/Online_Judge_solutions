#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>
typedef long long lint;
const int N=1e5+5;
int n,ans=1,val[N];

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
	int cnt,fir[N],son[N],dep[N],xdep[N];
	std::vector <int> cu[N],cd[N];//与深度同向增长，与深度反向增长
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	inline void ins(const int x,const int v){
		std::vector <int> ::iterator pos;
		pos=std::lower_bound(cu[x].begin(),cu[x].end(),v,std::greater <int> ());
		if(pos==cu[x].end()){
			cu[x].push_back(v);
		}
		else *pos=v;
		pos=std::lower_bound(cd[x].begin(),cd[x].end(),v);
		if(pos==cd[x].end()){
			cd[x].push_back(v);
		}
		else *pos=v;
	}

	void dfs_son(const int x,const int f){
		xdep[x]=dep[x];
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==f) continue;
			dep[y]=dep[x]+1;
			dfs_son(y,x);
			if(xdep[x]<xdep[y]){
				son[x]=y;
				xdep[x]=xdep[y];
			}
		}
	}

	void dfs_ans(const int x){
		if(!son[x]){
			ins(x,val[x]);
			return;
		}
		dfs_ans(son[x]);
		std::swap(cu[x],cu[son[x]]);
		std::swap(cd[x],cd[son[x]]);
		ins(x,val[x]);
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(dep[y]<dep[x]||y==son[x]) continue;
			dfs_ans(y);
			for(int i=0; i!=(int)cu[y].size(); ++i){
				std::vector <int> ::iterator pos;
				int v=cu[y][i];
				pos=std::lower_bound(cd[x].begin(),cd[x].end(),v);
				apx(ans,(int)(pos-cd[x].begin())+i+2-1);
			}
			for(int i=0; i!=(int)cd[y].size(); ++i){
				std::vector <int> ::iterator pos;
				int v=cd[y][i];
				pos=std::lower_bound(cu[x].begin(),cu[x].end(),v,std::greater<int>());
				apx(ans,(int)(pos-cu[x].begin())+i+2-1);
			}
			ins(y,val[x]);
			for(int i=0; i!=(int)cu[y].size(); ++i){
				if((int)cu[x].size()<=i) cu[x].push_back(cu[y][i]);
				else apx(cu[x][i],cu[y][i]);
			}
			for(int i=0; i!=(int)cd[y].size(); ++i){
				if((int)cd[x].size()<=i) cd[x].push_back(cd[y][i]);
				else apn(cd[x][i],cd[y][i]);
			}
		}
		apx(ans,(int)cu[x].size());
		apx(ans,(int)cd[x].size());
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	G::dfs_son(1,1);
	G::dfs_ans(1);
	printf("%d\n",ans);
	return 0;
}
