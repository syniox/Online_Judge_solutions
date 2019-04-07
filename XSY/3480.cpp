#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
const int N=205;
const int M=(N>>1)*(N>>1);
int n,m,q,ans[M];
struct edge{
	int x,y;
}eg[M];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

namespace G{
	int cnt=1,cur[N],fir[N],dep[N];
	std::vector <int> eg_list;
	bool vld[N],eof[M+N];//end of life
	struct edge{
		int to,wi,nx;
	}eg[(M<<1)+(N<<1)];

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,0,fir[b]};
		fir[b]=cnt;
	}

	inline void add_side_edge(const int q){
		for(int i=1; i<=n>>1; ++i){
			if(vld[i]) G::add(0,i,q);
		}
		for(int i=(n>>1)+1; i<=n; ++i){
			if(vld[i]) G::add(i,n+1,q);
		}
	}

	bool bfs(){
		static int que[N];
		memset(dep,0,(n+2)*sizeof(int));
		dep[0]=1;
		int hd=0,tl=1;
		while(hd!=tl){
			const int x=que[hd++];
			for(int i=cur[x]=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				//assert(vld[y]);
				if(!eof[i>>1]&&eg[i].wi&&!dep[y]){
					dep[y]=dep[x]+1;
					que[tl++]=y;
				}
			}
		}
		return dep[n+1];
	}

	int dfs(const int x,const int t){
		if(x==n+1) return t;
		int tt=t,tp;
		for(int &i=cur[x]; i; i=eg[i].nx){
			const int y=eg[i].to,v=eg[i].wi;
			//assert(vld[y]);
			if(!eof[i>>1]&&v&&dep[y]==dep[x]+1&&(tp=dfs(y,std::min(v,tt)))){
				eg[i].wi-=tp;
				eg[i^1].wi+=tp;
				if((tt-=tp)==0) break;
			}
		}
		return t-tt;
	}

	void get_vld(){
		for(int x=1; x<=n>>1; ++x){
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				if(!eg[i].wi&&y>n>>1&&y<=n){
					//assert((i&1)==0);
					eg_list.push_back(i>>1);
					vld[x]=vld[y]=1;
				}
			}
		}
		int vld_l=0,vld_r=0;
		for(int i=1; i<=n>>1; ++i){
			vld_l+=vld[i];
		}
		for(int i=(n>>1)+1; i<=n; ++i){
			vld_r+=vld[i];
		}
		for(int i=1; i<=n>>1; ++i){
			if(vld_l<vld_r&&!vld[i]){
				++vld_l,vld[i]=1;
			}
		}
		for(int i=(n>>1)+1; i<=n; ++i){
			if(vld_l>vld_r&&!vld[i]){
				++vld_r,vld[i]=1;
			}
		}
		vld[0]=vld[n+1]=1;
		std::sort(eg_list.begin(),eg_list.end());
	}

	int rebuild(){
		static int dgr[N];
		memset(fir,0,(n+2)*sizeof(int));
		cnt=1;
		for(std::vector <int> ::iterator it=eg_list.begin(); it!=eg_list.end(); ++it){
			++dgr[::eg[*it].x];
			++dgr[::eg[*it].y];
			add(::eg[*it].x,::eg[*it].y,1);
		}
		add_side_edge(1);
		int x_dgr=0;
		for(int i=1; i<=n; ++i){
			if(!vld[i]) assert(dgr[i]==0);
		}
		for(int i=1; i<=n; ++i){
			apx(x_dgr,dgr[i]);
		}
		for(int i=1,j=(n>>1)+1; i<=n>>1; ++i){
			if(!vld[i]) continue;
			while(dgr[i]<x_dgr){
				while(j<=n&&(!vld[j]||dgr[j]==x_dgr)) ++j;
				assert(j<=n);
				add(i,j,1);
				++dgr[i],++dgr[j];
			}
		}
		return x_dgr;
	}

	void resolve(const int col){
		//while(bfs()) dfs(0,1e9);
		int tmp=0;
		while(bfs()) tmp+=dfs(0,1e9);
		//assert(tmp==n>>1);
		const int sz=eg_list.size();
		for(int i=1; i<=n>>1; ++i){
			for(int j=fir[i]; j; j=eg[j].nx){
				if(!eof[j>>1]&&eg[j].wi==0){
					eof[j>>1]=1;
					if(j>>1<=sz) ans[eg_list[(j>>1)-1]]=col;
					break;
				}
			}
		}
		for(int i=fir[0]; i; i=eg[i].nx){
			if(eof[i>>1]) continue;
			assert(eg[i].wi==0);
			eg[i].wi=1,eg[i^1].wi=0;
		}
		for(int i=fir[n+1]; i; i=eg[i].nx){
			if(eof[i>>1]) continue;
			assert(eg[i].wi==1);
			eg[i].wi=0,eg[i^1].wi=1;
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	//freopen("d.in","r",stdin);
#endif
	n=nxi(),m=nxi(),q=nxi();
	bool odd=0;
	if(n&1) ++n,odd=1;
	for(int i=1; i<=m; ++i){
		const int a=nxi(),b=nxi()+odd;
		eg[i].x=a,eg[i].y=b;
		G::add(a,b,1);
	}
	memset(G::vld,1,(n+2)*sizeof(bool));
	G::add_side_edge(q);
	int res=0;
	while(G::bfs()) res+=G::dfs(0,1e9);
	printf("%d\n",res);
	memset(G::vld+1,0,n*sizeof(bool));
	G::get_vld();
	for(int i=G::rebuild(); i; --i){
		G::resolve(i);
	}
	for(int i=1; i<=m; ++i){
		if(ans[i]) printf("%d %d\n",i,ans[i]);
	}
	return 0;
}
