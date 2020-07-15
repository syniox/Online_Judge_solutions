#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
using namespace std;
const int N=755;
const int L=1e7+5;
int n;
bool lnk[N][N];
char str[L];

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

namespace S{
	int cnt,pos[N];
	struct node{
		int fa,lk,rlk,id,c[2];
	}tr[L];

	void insert(const char *s,const int len,const int id){
		int p=0;
		for(int i=0; i<len; ++i){
			int &q=tr[p].c[s[i]-'a'];
			if(!q) q=++cnt;
			tr[q].fa=p,p=q;
		}
		pos[id]=p;
		tr[p].id=id;
	}

	void build(){
		static int que[L];
		int hd=0,tl=1;
		while(hd!=tl){
			const int x=que[hd++],lk=tr[x].lk;
			tr[x].rlk=tr[lk].id?lk:tr[lk].rlk;
			for(int i=0; i<2; ++i){
				int &y=tr[x].c[i];
				if(!y) y=tr[lk].c[i];
				else{
					if(x!=lk) tr[y].lk=tr[lk].c[i];
					que[tl++]=y;
				}
			}
		}
		for(int i=1; i<=n; ++i){
			for(int j=pos[i]; j; j=tr[j].fa){
				if(tr[j].id) lnk[i][tr[j].id]=1;
				for(int k=tr[j].rlk; tr[k].id&&!lnk[i][tr[k].id]; k=tr[k].rlk){
					lnk[i][tr[k].id]=1;
				}
			}
		}
	}
}

namespace G{
	int cnt=1,fir[N*2],cur[N*2],dep[N*2];
	struct edge{
		int to,wi,nx;
	}eg[N*N*2];

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,0,fir[b]};
		fir[b]=cnt;
	}

	bool dinic_bfs(){
		static int que[N*2];
		memset(dep,-1,sizeof(dep));
		int hd=0,tl=1;
		dep[0]=0;
		while(hd!=tl){
			const int x=que[hd++];
			for(int i=cur[x]=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				if(dep[y]==-1&&eg[i].wi){
					que[tl++]=y;
					dep[y]=dep[x]+1;
				}
			}
		}
		return ~dep[n*2+1];
	}

	int dinic_dfs(const int x,const int t){
		if(x==n*2+1) return t;
		int tt=t,tmp;
		for(int &i=cur[x]; i; i=eg[i].nx){
			const int y=eg[i].to,v=eg[i].wi;
			if(dep[y]==dep[x]+1&&v&&(tmp=dinic_dfs(y,std::min(tt,v)))){
				eg[i].wi-=tmp;
				eg[i^1].wi+=tmp;
				tt-=tmp;
				if(!tt) break;
			}
		}
		return t-tt;
	}

	void solve(){
		for(int i=1; i<=n; ++i){
			add(0,i,1);
			for(int j=1; j<=n; ++j){
				if(lnk[i][j]&&i!=j) add(i,j+n,1);
			}
			add(i+n,n*2+1,1);
		}
		int ans=n;
		while(dinic_bfs()){
			ans-=dinic_dfs(0,N);
		}
		printf("%d\n",ans);
		for(int i=1; i<=n; ++i){
			//从所有链底出发，能够到达的点均不合法，删掉后形成的新链底也同样处理
			//最后得到的图的链底集合一定两两无边，而且个数依然为ans
			//遍历过程形如dinic_bfs，显然左边遍历到的点成为过链底，右边没被遍历到的点一定没被删
			if(dep[i]!=-1&&dep[i+n]==-1) printf("%d ",i);
		}
		puts("");
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		scanf("%s",str);
		S::insert(str,strlen(str),i);
	}
	S::build();
	G::solve();
	return 0;
}
