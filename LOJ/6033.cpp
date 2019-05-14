#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=105;
int n,m,tot;
char mp[N][N];
bool invld[N*N];

inline int nxi(FILE *fd=stdin){
	int x=0;
	char c;
	while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
	const bool f=(c=='-')&&(c=fgetc(fd));
	while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
	return f?-x:x;
}

template <class T>
inline void apx(T &x,const T y){
	x<y?x=y:0;
}

template <class T>
inline void apn(T &x,const T y){
	x>y?x=y:0;
}

inline int id(const int x,const int y){
	return (x-1)*m+y;
}

inline bool vldpos(const int x,const int y){
	return x>0&&y>0&&x<=n&&y<=m&&mp[x][y]=='.';
}

namespace G{
	int cnt=1,fir[N*N],cur[N*N],dep[N*N],lnk[N*N];
	struct edge{
		int to,wi,nx;
	}eg[N*N<<3];

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,0,fir[b]};
		fir[b]=cnt;
	}

	bool bfs(){
		static int que[N*N];
		memset(dep,0,(tot+2)*sizeof(int));
		dep[0]=1;
		int hd=0,tl=1;
		que[0]=0;
		while(hd!=tl){
			const int x=que[hd++];
			for(int i=cur[x]=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				if(!dep[y]&&eg[i].wi){
					dep[y]=dep[x]+1;
					que[tl++]=y;
				}
			}
		}
		return dep[tot+1];
	}

	int dfs(const int x,const int t){
		if(x==tot+1) return t;
		int tt=t,tp;
		for(int &i=cur[x]; i; i=eg[i].nx){
			const int y=eg[i].to,v=eg[i].wi;
			if(v&&dep[y]==dep[x]+1&&(tp=dfs(y,std::min(v,tt)))){
				eg[i].wi-=tp;
				eg[i^1].wi+=tp;
				if((tt-=tp)==0) break;
			}
		}
		return t-tt;
	}

	inline void dinic(){
		while(bfs()) dfs(0,1e9);
	}

	void get_lnk(){
		for(int i=1; i<=n; ++i){
			for(int j=1; j<=m; ++j){
				if((i+j)&1) continue;
				int x=id(i,j);
				for(int k=fir[x]; k; k=eg[k].nx){
					const int y=eg[k].to;
					if(y&&eg[k].wi==0){
						lnk[y]=x;
						lnk[x]=y;
						break;
					}
				}
			}
		}
	}

	void get_vld(){
		static int que[N*N];
		int hd=0,tl=0;
		for(int i=1; i<=tot; ++i){
			if(!lnk[i]) que[tl++]=i,invld[i]=1;
		}
		while(hd!=tl){
			const int x=que[hd++];
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=lnk[eg[i].to];
				if(y&&invld[y]==0){
					invld[y]=1;
					que[tl++]=y;
				}
			}
		}
	}
}

void add_eg(){
	static int cx[]={0,-1,0,1},cy[]={1,0,-1,0};
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=m; ++j){
			if(mp[i][j]=='#') continue;
			const int cur=id(i,j);
			if((i+j)&1){
				G::add(cur,tot+1,1);
				continue;
			}
			for(int k=0; k<4; ++k){
				int tx=i+cx[k],ty=j+cy[k];
				if(!vldpos(tx,ty)) continue;
				G::add(cur,id(tx,ty),1);
			}
			G::add(0,cur,1);
		}
	}
}

int main(){
	n=nxi(),m=nxi();
	tot=n*m;
	for(int i=1; i<=n; ++i){
		scanf("%s",mp[i]+1);
	}
	add_eg();
	G::dinic();
	G::get_lnk();
	G::get_vld();
	int ans=0;
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=m; ++j){
			ans+=(invld[id(i,j)]==1&&mp[i][j]=='.');
		}
	}
	printf("%d\n",ans);
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=m; ++j){
			if(invld[id(i,j)]==1&&mp[i][j]=='.'){
				printf("%d %d\n",i,j);
			}
		}
	}
	return 0;
}
