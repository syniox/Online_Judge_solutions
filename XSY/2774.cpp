 #include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long lint;
const int N=9005;
int n,m;

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
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
	vector <int> g[N];
	int vcnt,lnk[N];
	bool vis[N];

	inline void init(){
		for(int i=1; i<=vcnt; ++i) g[i].clear();
		vcnt=n;
	}
	inline void add(const int a,const int b){
		//eprintf("add: %d-%d\n",a,b);
		g[a].push_back(b);
		g[b].push_back(a);
	}
	inline void shuffle(){
		for(int i=1; i<=vcnt; ++i){
			random_shuffle(g[i].begin(),g[i].end());
		}
	}

	bool aug(const int x){
		vis[x]=1;
		for(vector<int> ::iterator it=g[x].begin(); it!=g[x].end(); ++it){
			if(!lnk[*it]){
				lnk[*it]=x,lnk[x]=*it;
				return 1;
			}
			int nx=lnk[*it];
			if(vis[nx]) continue;
			lnk[nx]=0;
			lnk[*it]=x,lnk[x]=*it;
			if(aug(nx)) return 1;
			lnk[*it]=nx,lnk[nx]=*it;
			lnk[x]=0;
		}
		return 0;
	}

	int solve(){
		memset(lnk,0,sizeof(lnk));
		int ans=0;
		for(int i=1; i<=vcnt; ++i){
			if(lnk[i]) continue;
			memset(vis,0,sizeof(vis));
			ans+=aug(i);
		}
		return ans;
	}
}

int main(){
	while(n=nxi(),m=nxi(),n&&m){
		G::init();
		int offs=0;
		for(int i=1; i<=m; ++i){
			using G::vcnt;
			static int buk[N];
			int cbuk=nxi();
			for(int i=1; i<=cbuk; ++i){
				buk[i]=nxi();
			}
			if(cbuk==1) continue;
			int clen=cbuk+(cbuk&1);
			offs+=clen>>1;
			//original circle
			for(int i=1; i<clen; ++i){
				G::add(vcnt+i,vcnt+i+1);
			}
			G::add(vcnt+clen,vcnt+1);
			for(int i=1; i<=cbuk; ++i){
				G::add(vcnt+i,buk[i]);
				if(i<clen){
					G::add(vcnt+i+1,buk[i]);
				}else{
					G::add(vcnt+1,buk[i]);
				}
			}
			vcnt+=clen;
		}
		int ans=0;
		for(int i=0; i<3; ++i){
			G::shuffle();
			apx(ans,G::solve());
		}
		printf("%d\n",ans-offs);
	}
	return 0;
}
