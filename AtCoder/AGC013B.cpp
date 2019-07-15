#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <deque>
typedef long long lint;
const int N=1e5+5;
int n,m;

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
	int cnt,fir[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void solve(){
		static bool vis[N];
		std::deque <int> dq;
		vis[1]=1;
		dq.push_back(1);
		{
			int tmp=eg[fir[1]].to;
			vis[tmp]=1;
			dq.push_back(tmp);
		}
		for(;;){
			const int x=dq.front();
			int fr=0;
			for(int i=fir[x]; !fr&&i; i=eg[i].nx){
				if(!vis[eg[i].to]) fr=eg[i].to;
			}
			if(!fr) break;
			vis[fr]=1;
			dq.push_front(fr);
		}
		for(;;){
			const int x=dq.back();
			int to=0;
			for(int i=fir[x]; !to&&i; i=eg[i].nx){
				if(!vis[eg[i].to]) to=eg[i].to;
			}
			if(!to) break;
			vis[to]=1;
			dq.push_back(to);
		}
		printf("%d\n",(int)dq.size());
		while(!dq.empty()){
			printf("%d ",dq.front());
			dq.pop_front();
		}
		puts("");
	}
}

int main(){
#ifdef LOCAL
	freopen("path.in","r",stdin);
	freopen("path.out","w",stdout);
#endif
	n=nxi(),m=nxi();
	for(int i=1; i<=m; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	G::solve();
	return 0;
}
