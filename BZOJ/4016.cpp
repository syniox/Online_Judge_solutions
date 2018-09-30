#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<vector>
typedef long long lint;
const int N=3e4+2;
int n,m,ql,fir[N];
struct veg{
	int to,wi;
	bool operator < (const veg &b) const {
		return to==b.to?wi<b.wi:to<b.to;
	}
};
std::vector <veg> frm[N];
std::vector <veg> csn[N];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt,fir[N],dis[N];
	struct edge{
		int to,wi,nx;
	}eg[N<<2];
	struct node{
		int x,dis;
		bool operator < (const node &b) const {
			return dis>b.dis;
		}
	};
	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}
	inline void dijkstra(){
		static std::priority_queue <node> pq;
		static bool vis[N];
		memset(dis,31,sizeof(dis));
		dis[1]=0;
		pq.push((node){1,0});
		while(!pq.empty()){
			const node x=pq.top();
			pq.pop();
			if(vis[x.x]) continue;
			vis[x.x]=1;
			for(int i=fir[x.x];i;i=eg[i].nx){
				const int y=eg[i].to,v=x.dis+eg[i].wi;
				if(dis[y]>v){
					dis[y]=v;
					frm[y].clear();
					pq.push((node){y,v});
				}
				if(dis[y]==v) frm[y].push_back((veg){x.x,eg[i].wi});
			}
		}
	}
}

namespace T{
	int cnt,fir[N];
	bool vis[N];
	struct edge{
		int to,wi,nx;
	}eg[N<<1];

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}

	void dfs(const int x){
		std::vector <veg> ::iterator it=csn[x].begin();
		for(;it!=csn[x].end();++it){
			const int y=it->to,v=it->wi;
			if(!vis[y]){
				vis[y]=1;
				add(x,y,v);
				add(y,x,v);
				dfs(y);
			}
		}
	}
}

namespace S{
	using T::fir;
	using T::eg;
	int rt,nsz,ans,xsz_rt,dp_len,sz[N],dep[N],xdep[N];
	int dp[N],cdp[N],ndp[N],cndp[N];
	lint cnt;
	bool vis[N];

	bool cmp_xdep(const veg &a,const veg &b){
		return xdep[a.to]<xdep[b.to];
	}

	void get_rt(const int x,const int fa){
		int xsz=0;
		sz[x]=1;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=fa&&!vis[y]){
				get_rt(y,x);
				apx(xsz,sz[y]);
				sz[x]+=sz[y];
			}
		}
		apx(xsz,nsz-sz[x]);
		if(xsz_rt>xsz){
			rt=x,xsz_rt=xsz;
		}
	}

	void get_util(const int x,const int fa){
		xdep[x]=dep[x];
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=fa&&!vis[y]){
				dep[y]=dep[x]+1;
				get_util(y,x);
				apx(xdep[x],xdep[y]);
			}
		}
	}

	inline void merge(const int len){
		const int limit=std::min(len,ql-1);
		for(int i=std::max(ql-dp_len,1);i<=limit;++i){
			const int v=dp[ql-i]+ndp[i];
			if(ans<v) ans=v,cnt=0;
			if(ans==v){
				cnt+=(lint)cdp[ql-i]*cndp[i];
			}
		}
		for(int i=1;i<=len;++i){
			if(dp[i]<ndp[i]){
				dp[i]=ndp[i],cdp[i]=0;
			}
			if(dp[i]==ndp[i]){
				cdp[i]+=cndp[i];
			}
		}
		apx(dp_len,len);
	}

	inline void get_ndp(const int x,const int v){
		if(ndp[dep[x]]<v){
			ndp[dep[x]]=v;
			cndp[dep[x]]=0;
		}
		if(ndp[dep[x]]==v){
			++cndp[dep[x]];
		}
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(dep[y]>dep[x]) get_ndp(y,v+eg[i].wi);
		}
	}

	inline void calc(const int x){
		memset(dp,0,(xdep[x]+1)<<2);
		memset(cdp,0,(xdep[x]+1)<<2);
		static veg que[N];
		int top=dp_len=0;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!vis[y]) que[++top]=(veg){y,eg[i].wi};
		}
		if(top) std::sort(que+1,que+top+1,cmp_xdep);
		for(int i=1;i<=top;++i){
			const int y=que[i].to;
			memset(ndp,0,(xdep[y]+1)<<2);
			memset(cndp,0,(xdep[y]+1)<<2);
			get_ndp(y,que[i].wi);
			merge(xdep[y]);
		}
		if(xdep[x]<ql) return;
		if(dp[ql]>ans){
			ans=dp[ql],cnt=0;
		}
		if(dp[ql]==ans){
			cnt+=cdp[ql];
		}
	}

	void solve(int x,const int nsz){
		if(nsz<=ql) return;
		S::nsz=nsz;
		xsz_rt=1e8;
		get_rt(x,0);
		x=rt;
		dep[x]=0;
		get_util(x,0);
		vis[x]=1;
		calc(x);
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!vis[y]){
				solve(y,sz[y]>sz[x]?nsz-sz[x]:sz[y]);
			}
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("c.in","r",stdin);
#endif
	n=nxi(),m=nxi(),ql=nxi()-1;
	for(int i=1;i<=m;++i){
		const int a=nxi(),b=nxi(),v=nxi();
		G::add(a,b,v);
		G::add(b,a,v);
	}
	G::dijkstra();
	for(int i=1;i<=n;++i){
		std::vector <veg> ::iterator it=frm[i].begin();
		for(;it!=frm[i].end();++it){
			csn[it->to].push_back((veg){i,it->wi});
		}
	}
	for(int i=1;i<=n;++i){
		if(!csn[i].empty()){
			std::sort(csn[i].begin(),csn[i].end());
		}
	}
	T::dfs(1);
	S::solve(1,n);
	printf("%d %lld\n",S::ans,S::cnt);
	return 0;
}
