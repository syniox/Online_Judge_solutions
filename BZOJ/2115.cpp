#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=50005;
const int M=1e5+5;
int n,m;

template <class T> inline T nxi(){
	T x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace S{
	const int P=62;
	lint buk[P];

	inline void insert(lint x){
		for(int i=P-1; ~i; --i){
			if(x>>i&1){
				if(buk[i]) x^=buk[i];
				else{
					buk[i]=x;
					break;
				}
			}
		}
	}

	inline lint get_max(lint x){
		for(int i=P-1; ~i; --i){
			if(!(x>>i&1)&&buk[i]) x^=buk[i];
		}
		return x;
	}
}

namespace G{
	int cnt=1,fir[N];
	lint dep[N];
	bool vis[N],is_tr[M];
	struct edge{
		int to;
		lint wi;
		int nx;
	}eg[M<<1];

	inline void add(const int a,const int b,const lint v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}

	void dfs_tr(const int x){
		vis[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!vis[y]){
				is_tr[i>>1]=1;
				dep[y]=dep[x]^eg[i].wi;
				dfs_tr(y);
			}
		}
	}
}

inline void build(){
	using namespace G;
	for(int x=1; x<=n; ++x){
		for(int i=fir[x]; i; i=eg[i].nx){
			if(i&1&&!is_tr[i>>1]){
				S::insert(dep[x]^dep[eg[i].to]^eg[i].wi);
			}
		}
	}
}

int main(){
	n=nxi<int>(),m=nxi<int>();
	for(int i=1; i<=m; ++i){
		const int a=nxi<int>(),b=nxi<int>();
		const lint v=nxi<lint>();
		G::add(a,b,v);
		G::add(b,a,v);
	}
	G::dfs_tr(1);
	build();
	printf("%lld\n",S::get_max(G::dep[n]));
	return 0;
}
