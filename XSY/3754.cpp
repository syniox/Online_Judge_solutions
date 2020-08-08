#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <bitset>
typedef long long lint;
using namespace std;
const int N=1e5+5,S=320,T=1.45e4;
int n,m,q,bel[N],idx[N],ans[N],val[N],np2[S][N];
bool vis[N];
bitset<T> bs[N];
struct opt_s{
	int op,x,v;
	friend bool operator<(const opt_s &a,const opt_s &b);
}opt[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
	static struct{
		template <class T> operator T(){
			T x=0;
			char c;
			while(((c=getchar())>'9'||c<'0')&&c!='-');
			const bool f=c=='-'&&(c=getchar());
			while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
			return f?-x:x;
		}
	}ni;
}
using namespace utils;

bool operator<(const opt_s &a,const opt_s &b){
	return a.v<b.v;
}

namespace G{
	int cnt,fir[N];
	struct edge{
		int to,nx;
	}eg[N];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void cover(const int x,const int v,int *dp,const int t){
		if(vis[x]) return;
		vis[x]=1;
		idx[x]=t;
		if(!t) apn(dp[x],v);
		else dp[x]=v;
		for(int i=fir[x]; i; i=eg[i].nx){
			cover(eg[i].to,v,dp,t);
		}
	}

	void dfs_bs(const int x,const int l,const int r){
		if(vis[x]) return;
		vis[x]=1;
		if(x>=l&&x<=r) bs[x][x-l]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			dfs_bs(eg[i].to,l,r);
			bs[x]|=bs[eg[i].to];
		}
	}
}

int qmin(const int l,const int r,const int x,const int cl){
	int ans=1e9;
	if(bel[l]==bel[r]||l>r){
		for(int i=l; i<=r; ++i){
			if(opt[i].op==2&&bs[opt[i].x][x])
				apn(ans,opt[i].v);
		}
	}else{
		for(int i=bel[l]+1; i<bel[r]; ++i){
			apn(ans,np2[i][x+cl]);
		}
		for(int i=l; bel[i]==bel[l]; ++i){
			if(opt[i].op==2&&bs[opt[i].x][x])
				apn(ans,opt[i].v);
		}
		for(int i=r; bel[i]==bel[r]; --i){
			if(opt[i].op==2&&bs[opt[i].x][x])
				apn(ans,opt[i].v);
		}
	}
	return ans;
}

void solve(const int l,const int r){
	static int buk[N];
	memset(vis+1,0,n*sizeof(vis[0]));
	memset(val+1,0,n*sizeof(val[0]));
	for(int i=1; i<=n; ++i){
		bs[i].reset();
	}
	for(int i=1; i<=n; ++i){
		G::dfs_bs(i,l,r);
	}
	for(int cnt=0,i=1; i<=q; ++i){
		if(opt[i].op==3&&opt[i].x>=l&&opt[i].x<=r){
			int pl=idx[opt[i].x]+1,pr=i-1,v=val[opt[i].x];
			for(int j=cnt; j; --j){
				if(bs[opt[buk[j]].x][opt[i].x-l]){
					pl=buk[j]+1;
					v=opt[buk[j]].v;
					break;
				}
			}
			ans[i]=min(v,qmin(pl,pr,opt[i].x-l,l));
		}else if(opt[i].op==1){
			buk[++cnt]=i;
		}
		if(bel[i]!=bel[i+1]){
			memset(vis+1,0,n*sizeof(vis[0]));
			for(; cnt; --cnt){
				G::cover(opt[buk[cnt]].x,opt[buk[cnt]].v,val,buk[cnt]);
			}
		}
	}
}

int main(){
	n=ni,m=ni,q=ni;
	memset(ans+1,-1,q*sizeof(ans[0]));
	for(int i=1; i<=m; ++i){
		int x=ni,y=ni;
		G::add(x,y);
	}
	for(int i=1; i<=q; ++i){
		opt[i].op=ni,opt[i].x=ni;
		if(opt[i].op!=3) opt[i].v=ni;
		bel[i]=(i-1)/S+1;
	}
	for(int cnt=0,i=1; i<=q; ++i){
		static opt_s buk[S];
		if(opt[i].op==2) buk[++cnt]=opt[i];
		if(i%S) continue;
		sort(buk+1,buk+cnt+1);
		memset(np2[bel[i]]+1,63,n*sizeof(int));
		memset(vis,0,sizeof(vis));
		for(int j=1; j<=cnt; ++j){
			G::cover(buk[j].x,buk[j].v,np2[bel[i]],0);
		}
		cnt=0;
	}
	for(int i=1; i<=n; i+=T){
		solve(i,min(i+T-1,n));
	}
	for(int i=1; i<=q; ++i){
		if(~ans[i]) printf("%d\n",ans[i]);
	}
	return 0;
}
