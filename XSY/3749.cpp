#include <vector>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include "perm.h"
using namespace std;
const int N=405;
int n;
bool mp[N][N];//左值右位置
vector<int> lstans,rpool,lstvec,vec;
int diff[N],lnk[N];
int oldpos[N],curpos[N];
bool checked[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
}
using namespace utils;

void setlnk(const int x,const int y){
	memset(mp[x],0,sizeof(mp[x]));
	for(int i=1; i<=n; ++i) mp[i][y]=0;
	lnk[x]=y;
	mp[x][y]=1;
	checked[x]=1;
}

namespace T{//Tarjan找交错环
	int cnd,cnt,cnf,fir[N<<1],dfn[N<<1],low[N<<1],bel[N<<1];
	struct edge{
		int to,nx;
	}eg[N*N<<1];

	inline void reset(){
		cnd=cnt=cnf=0;
		memset(dfn,0,sizeof(dfn));
		memset(bel,0,sizeof(bel));
		memset(fir,0,sizeof(fir));
	}
	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void tarjan(const int x){
		static int stk[N<<1],top;
		low[x]=dfn[x]=++cnd;
		stk[++top]=x;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!dfn[y]) tarjan(y);
			if(!bel[y]) apn(low[x],low[y]);
		}
		if(low[x]!=dfn[x]) return;
		++cnf;
		for(;;){
			bel[stk[top]]=cnf;
			if(stk[top--]==x) break;
		}
	}

	void buildscc(){
		for(int i=1; i<=n*2; ++i){
			if(!dfn[i]) tarjan(i);
		}
	}
}

namespace G{//二分图匹配
	int cnt,fir[N<<1],cur[N<<1],dep[N<<1];
	struct edge{
		int to,wi,nx;
	}eg[N*N<<2];

	inline void reset(){
		cnt=1;
		memset(fir,0,sizeof(fir));
	}
	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,0,fir[b]};
		fir[b]=cnt;
	}

	bool bfs(){
		static int que[N<<1];
		memset(dep,-1,sizeof(dep));
		int hd=0,tl=1;
		dep[0]=0;
		while(hd!=tl){
			const int x=que[hd++];
			for(int i=cur[x]=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				if(eg[i].wi&&dep[y]==-1){
					que[tl++]=y;
					dep[y]=dep[x]+1;
				}
			}
		}
		return ~dep[n*2+1];
	}
	int dfs(const int x,const int t){
		if(x==n*2+1) return t;
		int tt=t,tmp;
		for(int &i=cur[x]; i; i=eg[i].nx){
			const int y=eg[i].to,v=eg[i].wi;
			if(v&&dep[y]==dep[x]+1&&(tmp=dfs(y,min(tt,v)))){
				eg[i].wi-=tmp;
				eg[i^1].wi+=tmp;
				tt-=tmp;
				if(!tt) break;
			}
		}
		return t-tt;
	}

	void san(){
		reset();
		for(int i=1; i<=n; ++i){
			for(int j=1; j<=n; ++j){
				if(mp[i][j]) add(i,j+n,1);
			}
			add(0,i,1);
			add(i+n,n*2+1,1);
		}
		while(bfs()) dfs(0,N);
		T::reset();
		for(int e=2; e<=cnt; e+=2){
			int x=eg[e^1].to,y=eg[e].to;
			if(x==0||y==n*2+1) continue;
			if(eg[e].wi) T::add(y,x);
			else T::add(x,y);
		}
		T::buildscc();
		for(int e=2; e<=cnt; e+=2){
			int x=eg[e^1].to,y=eg[e].to;
			if(x==0||y==n*2+1||checked[x]||T::bel[x]==T::bel[y]) continue;
			assert(x<=n);
			if(!eg[e].wi) setlnk(x,y-n);
			else mp[x][y-n]=0;
		}
	}
}

int getdiff(const vector<int> &a,const vector<int> &b){
	vector<int>::const_iterator it;
	memset(diff,0,(n+1)*sizeof(int));
	for(it=a.begin(); it!=a.end(); ++it){
		--diff[*it];
	}
	for(it=b.begin(); it!=b.end(); ++it){
		++diff[*it];
	}
	int res=0;
	for(int i=0; i<=n; ++i){
		res+=cabs(diff[i]);
	}
	return res;
}

void apl_lim(const int v,const int p,const bool f){
	static bool vldpos[N];
	memset(vldpos+1,0,n*sizeof(vldpos[0]));
	for(int i=0; i<n; ++i){
		if(diff[i]&&(diff[i]>0)==f){
			if(p>i) vldpos[p-i]=1;
			if(p<=n-i) vldpos[p+i]=1;
		}
	}
	for(int i=1; i<=n; ++i){
		mp[v][i]&=vldpos[i];
	}
}

void san_rpool(){
	int cnt=0;
	for(int i=0; i<(int)rpool.size(); ++i){
		if(!checked[rpool[i]]) rpool[cnt++]=rpool[i];
	}
	rpool.resize(cnt);
}

vector<int> cuopai(vector<int> vec,const int csz){
	static bool is_shf[N];
	vector<int> res(n);
	for(;;){
		random_shuffle(rpool.begin(),rpool.end());
		memset(is_shf,0,(n+1)*sizeof(is_shf[0]));
		for(int i=0; i<csz; ++i){
			is_shf[rpool[i]]=1;
		}
		bool f=0;
		for(int i=0,cnt=0; !f&&i<n; ++i){
			if(is_shf[vec[i]]){
				if(rpool[cnt]==vec[i]) f=1;
				res[i]=rpool[cnt++];
			}
			else res[i]=vec[i];
		}
		if(!f) break;
	}
	return res;
}

vector<int> guess(int n){
	if(n==1) return (vector<int>){1};
	::n=n;
	memset(mp,1,sizeof(mp));
	rpool.reserve(n);
	vec.reserve(n);
	for(int i=1; i<=n; ++i){
		rpool.push_back(i);
		vec.push_back(i);
	}
	random_shuffle(vec.begin(),vec.end());
	lstvec=vec,lstans=query(vec);
	int globsize=max((int)sqrt(rpool.size())/2,2);
	while(san_rpool(),!rpool.empty()){
		//int csz=max(2,(int)sqrt(rpool.size())/2);
		int csz=min((int)rpool.size(),globsize);
		assert(rpool.size()!=1);
		vector<int> curans;
		for(int cnt=1; ; ++cnt){
			vec=cuopai(vec,csz);
			curans=query(vec);
			if(getdiff(lstans,curans)==csz*2){
				eprintf("%d %d\n",(int)rpool.size(),cnt);
				break;
			}
			if(cnt%5==2){
				random_shuffle(vec.begin(),vec.end());
				curans=query(vec);
			}
			lstvec=vec,lstans=curans;
		}
		for(int i=0; i<n; ++i){
			oldpos[lstvec[i]]=i+1;
			curpos[vec[i]]=i+1;
		}
		lstvec=vec,lstans=curans;
		for(int t=0; t<csz; ++t){
			const int v=rpool[t];
			assert(!checked[v]);
			apl_lim(v,oldpos[v],0);
			apl_lim(v,curpos[v],1);
			int cnt=0,y=0;
			for(int i=1; i<=n; ++i){
				if(mp[v][i]) ++cnt,y=i;
			}
			if(cnt==1){
				setlnk(v,y);
			}
		}
		G::san();
	}
	vector<int> res;
	res.resize(n);
	for(int i=1; i<=n; ++i){
		res[lnk[i]-1]=i;
	}
	return res;
}
