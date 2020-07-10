#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
using namespace std;
const int N=8e5+5;
int n,q,tot;

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
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
	int cnt=1,fir[N],pre[N],dis[N];
	struct edge{
		int to,wi,cs,nx;
	}eg[N*10<<1];

	inline void add(const int a,const int b,const int v,const int c){
		//eprintf("add: %d->%d\n",a,b);
		eg[++cnt]=(edge){b,v,c,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,0,-c,fir[b]};
		fir[b]=cnt;
	}

	bool spfa(const int offs){
		static int que[N];
		static bool vis[N];
		memset(dis+offs,-10,(N-offs)*sizeof(int));
		dis[0]=0;
		int hd=0,tl=1,cnt=0;
		while(hd!=tl){
			int x=que[hd++];
			if(hd==N) hd=0;
			vis[x]=0;
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to,v=dis[x]+eg[i].cs;
				if(eg[i].wi&&dis[y]<v){
					dis[y]=v,pre[y]=i;
					if(!vis[y]){
						vis[y]=1;
						assert(++cnt<=tot*20);
						que[tl++]=y;
						if(tl==N) tl=0;
					}
				}
			}
		}
		return dis[tot*2+1]>0;
	}

	int solve(const int t){
		static int ans,cnt,rbuk[N];
		if(t==1){
			for(int i=1; i<=q; ++i) add(0,i,1,0);
		}else{
			for(int i=fir[0]; i; i=eg[i].nx){
				eg[i].to+=q*2;
				eg[i].wi=1,eg[i^1].wi=0;
			}
		}
		cnt-=rbuk[t-1];
		ans-=cnt;
		while(spfa((t-1)*q*2)){
			ans+=dis[tot*2+1];
			++rbuk[t+dis[tot*2+1]];
			++cnt;
			for(int x=tot*2+1; x; x=eg[pre[x]^1].to){
				--eg[pre[x]].wi;
				++eg[pre[x]^1].wi;
			}
		}
		//assert(ans>=0);
		return ans;
	}
}

int main(){
	n=nxi(),q=nxi();
	tot=n*q;
	for(int i=1; i<n; ++i){
		for(int j=1; j<=q; ++j){
			static char str[12];
			scanf("%s",str+1);
			for(int k=1; k<=q; ++k){
				if(str[k]=='1') G::add(tot+(i-1)*q+j,i*q+k,1,1);
			}
			G::add(tot+i*q+j,tot*2+1,1,0);//第一层没必要加
		}
	}
	for(int i=1; i<=tot; ++i){
		G::add(i,tot+i,1,0);
	}
	lint ans=0;
	for(int i=1; i<=n; ++i){
		ans+=G::solve(i);
	}
	printf("%lld\n",ans);
	return 0;
}
