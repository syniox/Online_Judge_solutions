#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <deque>
typedef long long lint;
const int N=1e5+5;
int n;

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x<y?y:x;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

namespace G{
	int cnt,fir[N],dis[N];
	struct edge{
		int to,wi,nx;
	}eg[N<<1];

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}

	int bfs(){
		static bool vis[N];
		memset(dis,10,(n+1)*sizeof(dis[0]));
		dis[1]=0;
		std::deque <int> dq;
		dq.push_back(1);
		while(!dq.empty()){
			const int x=dq.front();
			dq.pop_front();
			if(vis[x]) continue;
			vis[x]=1;
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to,v=eg[i].wi;
				if(dis[y]>dis[x]+v){
					dis[y]=dis[x]+v;
					if(v) dq.push_back(y);
					else dq.push_front(y);
				}
			}
		}
		return dis[0];
	}
}

int main(){
#ifdef LOCAL
	freopen("multiple.in","r",stdin);
	freopen("multiple.out","w",stdout);
#endif
	n=nxi();
	for(int i=0; i<n; ++i){
		G::add(i,i*10%n,0);
		G::add(i,(i+1)%n,1);
	}
	printf("%d\n",G::bfs()+1);
	return 0;
}
