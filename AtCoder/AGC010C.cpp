#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=1e5+5;
typedef long long lint;
int n,val[N];

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
	int rt,cnt,dgr[N],fir[N];
	lint req[N];
	class edge{
		public:
			int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		++dgr[a],++dgr[b];
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,fir[b]};
		fir[b]=cnt;
	}

	inline void get_rt(){
		for(; dgr[rt]<2; ++rt);
		assert(rt<=n);
	}

	bool dfs(const int x,const int fa){
		if(dgr[x]==1){
			req[x]=val[x];
			return 1;
		}
		lint mx_req=0,req_sum=0;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=fa){
				if(!dfs(y,x)||req[y]>val[x]) return 0;
				req_sum+=req[y];
				apx(mx_req,req[y]);
			}
		}
		if(req_sum<val[x]) return 0;
		lint link_need=req_sum-val[x];
		lint link_able=std::min(req_sum>>1,req_sum-mx_req);
		if(link_need>link_able) return 0;
		req[x]=req_sum-(link_need<<1);
		return 1;
	}
}

int main(){
	n=nxi();
	if(n==2){
		puts(nxi()==nxi()?"YES":"NO");
		nxi(),nxi();
		return 0;
	}
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
	}
	G::get_rt();
	if(!G::dfs(G::rt,0)) puts("NO");
	else puts(G::req[G::rt]?"NO":"YES");
	return 0;
}
