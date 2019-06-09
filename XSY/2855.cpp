#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=52;
int n,ans(1e9),va[N][N],vb[N][N];

struct _pair{
	int x,y;
	friend bool operator == (const _pair &a,const _pair &b){
		return a.x==b.x&&a.y==b.y;
	}
};

namespace utils{
	template <class T> inline void apx(T &x,const T y){
		x<y?x=y:0;
	}
	template <class T> inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

namespace G{
	int cnt,fir[N<<1],dis[N<<1],pre_p[N<<1],pre_e[N<<1];
	struct edge{
		int to,wi,cs,nx;
	}eg[N*(N+2)<<1];

	inline void clear(){
		cnt=1;
		memset(fir,0,((n+1)<<1)*sizeof(int));
	}

	inline void add(const int a,const int b,const int v,const int c){
		//printf("add: %d->%d v%d c%d\n",a,b,v,c);
		eg[++cnt]=(edge){b,v,c,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,0,-c,fir[b]};
		fir[b]=cnt;
	}

	/*
	bool dij(){
		static int curd[N<<1];
		static bool vis[N<<1];
		memset(curd,8,((n+1)<<1)*sizeof(int));
		memset(vis,0,((n+1)<<1)*sizeof(bool));
		curd[0]=0;
		for(int i=1; i<=((n+1)<<1); ++i){
			int x=0;
			for(int j=1; j<=(n<<1|1); ++j){
				if(vis[x]||(!vis[j]&&curd[j]-dis[j]<curd[x]-dis[x])) x=j;
			}
			vis[x]=1;
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to,v=curd[x]+eg[i].cs;
				if(eg[i].wi&&curd[y]>v){
					curd[y]=v;
					pre_p[y]=x;
					pre_e[y]=i;
				}
			}
		}
		memcpy(dis,curd,((n+1)<<1)*sizeof(int));
		return curd[n<<1|1]>=0;
	}
	*/

	bool spfa(){
		static int que[N<<1];
		static bool vis[N<<1];
		memset(dis,8,((n+1)<<1)*sizeof(int));
		int hd=0,tl=1;
		que[0]=0;
		dis[0]=0;
		while(hd!=tl){
			const int x=que[hd++];
			if(hd==N<<1) hd=0;
			vis[x]=0;
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to,v=dis[x]+eg[i].cs;
				if(eg[i].wi&&dis[y]>v){
					pre_p[y]=x;
					pre_e[y]=i;
					dis[y]=v;
					if(!vis[y]){
						que[tl++]=y;
						if(tl==N<<1) tl=0;
						vis[y]=1;
					}
				}
			}
		}
		return dis[n<<1|1]<1e8;
	}

	_pair solve(const int mp[N][N]){
		clear();
		for(int i=1; i<=n; ++i){
			add(0,i,1,0);
			add(i+n,n<<1|1,1,0);
		}
		for(int i=1; i<=n; ++i){
			for(int j=1; j<=n; ++j){
				add(i,j+n,1,mp[i][j]);
			}
		}
		memset(dis,8,((n+1)<<1)*sizeof(int));
		for(int i=1; i<=n; ++i){
			spfa();
			for(int i=n<<1|1; i; i=pre_p[i]){
				const int e=pre_e[i];
				assert(eg[e].wi);
				--eg[e].wi;
				++eg[e^1].wi;
			}
		}
		_pair res=(_pair){0,0};
		for(int i=1; i<=n; ++i){
			for(int j=fir[i]; j; j=eg[j].nx){
				if(eg[j].wi==0){
					const int k=eg[j].to;
					assert(k>n);
					res.x+=va[i][k-n];
					res.y+=vb[i][k-n];
					break;
				}
			}
		}
		return res;
	}
}

void solve(const _pair l,const _pair r){
	//负叉积
	static int mp[N][N];
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=n; ++j){
			mp[i][j]=(l.y-r.y)*va[i][j]+(r.x-l.x)*vb[i][j];
		}
	}
	_pair mid=G::solve(mp);
	if(mid==l||mid==r) return;
	apn(ans,mid.x*mid.y);
	solve(l,mid);
	solve(mid,r);
}

int main(){
	static int mp[N][N];
	n=nxi();
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=n; ++j){
			va[i][j]=nxi();
		}
	}
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=n; ++j){
			vb[i][j]=nxi();
		}
	}
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=n; ++j){
			mp[i][j]=va[i][j];
		}
	}
	_pair x=G::solve(mp);
	apn(ans,x.x*x.y);
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=n; ++j){
			mp[i][j]=vb[i][j];
		}
	}
	_pair y=G::solve(mp);
	apn(ans,y.x*y.y);
	solve(x,y);
	printf("%d\n",ans);
	return 0;
}
