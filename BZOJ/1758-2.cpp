#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
const int N=1e5+2;
const double eps=1e-5;
int n,m,ql,qr,fir[N];
struct edge{
	int to,wi,nx;
}eg[N<<1];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline void add_edge(const int a,const int b,const int v){
	static int cnt;
	eg[++cnt]=(edge){b,v,fir[a]};
	fir[a]=cnt;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace S{
	int rt,ssz,xsz,sz[N],dep[N],xdep[N];
	int dp_len,top,sque[N];
	double ans,tgt,dp[N],ndp[N],now[N];
	bool vis[N];
	inline bool cmp_xdep(const int x,const int y){
		return xdep[x]<xdep[y];
	}
	inline void init(){
		dep[0]=-1;
		memset(ndp,-63,sizeof(ndp));
		memset(dp,-63,sizeof(dp));
	}
	void get_rt(const int x,const int fa){
		sz[x]=1;
		int tsz=0;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!vis[y]&&fa!=y){
				get_rt(y,x);
				sz[x]+=sz[y];
				apx(tsz,sz[y]);
			}
		}
		apx(tsz,ssz-sz[x]);
		if(tsz<S::xsz){
			rt=x,S::xsz=tsz;
		}
	}
	void init_dfs(const int x,const int fa){
		sz[x]=1;
		dep[x]=xdep[x]=dep[fa]+1;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!vis[y]&&y!=fa){
				init_dfs(y,x);
				apx(xdep[x],xdep[y]);
				sz[x]+=sz[y];
			}
		}
	}
	void get_ndp(const int x,const int fa){
		apx(ndp[dep[x]],now[x]);
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=fa){
				dep[y]=dep[x]+1;
				now[y]=now[x]+eg[i].wi-tgt;
				get_ndp(y,x);
				apx(xdep[x],xdep[y]);
			}
		}
	}
	inline int merge(const int ln){
		static std::deque<int> dq;
		while(!dq.empty()) dq.pop_back();
		const int limit=ql-1;
		for(int i=std::min(dp_len,qr-1);i>=limit;--i){
			while(!dq.empty()&&dp[dq.front()]<dp[i]) dq.pop_front();
			dq.push_front(i);
		}
		for(int i=1;i<=ln;++i){
			if(qr-i<0) break;
			if(!dq.empty()&&dq.back()+i>qr) dq.pop_back();
			if(ql-i<=dp_len&&ql-i>=0){
				const int cur=ql-i;
				while(!dq.empty()&&dp[dq.front()]<dp[cur]) dq.pop_front();
				dq.push_front(cur);
			}
			if(!dq.empty()){
				if(dp[dq.back()]+ndp[i]>-eps) return 1;
			}
		}
		for(int i=1;i<=ln;++i){
			apx(dp[i],ndp[i]);
		}
		apx(dp_len,ln);
		return 0;
	}
	bool jdg(const int x,const double tgt){
		S::tgt=tgt;
		dp_len=dep[x]=now[x]=dp[0]=0;
		for(int i=fir[x];i;i=eg[i].nx){
			now[eg[i].to]=eg[i].wi-tgt;
		}
		for(int i=1;i<=top;++i){
			const int y=sque[i];
			if(!vis[y]){
				dep[y]=1;
				memset(ndp,-63,(xdep[x]+1)<<3);
				get_ndp(y,x);
				if(merge(xdep[y])) return 1;
			}
		}
		for(int i=ql;i<=qr;++i){
			if(dp[i]>-eps) return 1;
		}
		return 0;
	}
	void solve(const int x,const int ssz){
		if(ssz<ql) return;
		S::ssz=ssz,S::xsz=1e8;
		get_rt(x,0);
		vis[rt]=1;
		init_dfs(rt,0);
		top=0;
		for(int i=fir[rt];i;i=eg[i].nx){
			if(!vis[eg[i].to]) sque[++top]=eg[i].to;
		}
		if(top) std::sort(sque+1,sque+top,cmp_xdep);
		double l=std::max((double)0,ans-1),r=1e5,mid;
		while(r-l>eps){
			memset(dp,-63,(xdep[rt]+1)<<3);
			mid=(l+r)/2;
			if(jdg(rt,mid)) l=mid;
			else r=mid;
		}
		apx(ans,l);
		for(int i=fir[rt];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!vis[y]) solve(y,sz[y]);
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	n=nxi(),ql=nxi(),qr=nxi();
	for(int i=1;i<n;++i){
		const int a=nxi(),b=nxi(),v=nxi();
		add_edge(a,b,v);
		add_edge(b,a,v);
	}
	S::init();
	S::solve(1,n);
	printf("%.3lf\n",S::ans);
	return 0;
}