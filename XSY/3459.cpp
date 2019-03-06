#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <queue>
const int N=305;
int n,tgt,len[N],link[N];
char ch[N][N];
class pair{
	public:
		int x,y;
};

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	const int N=::N*::N*2;
	int cnt,end,cur[N],fir[N],dep[N];
	class edge{
		public:
			int to,wi,nx;
	}eg[N<<1];

	inline void clear(){
		cnt=1;
		memset(fir,0,sizeof(fir));
	}

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,0,fir[b]};
		fir[b]=cnt;
	}

	inline bool bfs(){
		static int que[N];
		memset(dep,0,sizeof(dep));
		int hd=0,tl=1;
		dep[0]=1;
		while(hd!=tl){
			int x=que[hd++];
			for(int i=cur[x]=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				if(eg[i].wi&&!dep[y]){
					dep[y]=dep[x]+1;
					que[tl++]=y;
				}
			}
		}
		return dep[end];
	}

	int dfs(int x,const int t){
		if(x==end) return t;
		int tt=t,tp;
		for(int &i=cur[x]; i; i=eg[i].nx){
			const int y=eg[i].to,v=eg[i].wi;
			if(dep[y]==dep[x]+1&&v&&(tp=dfs(y,std::min(v,tt)))){
				eg[i].wi-=tp;
				eg[i^1].wi+=tp;
				tt-=tp;
				if(!tt) break;
			}
		}
		return t-tt;
	}

	inline int dinic(){
		int ans=0;
		while(bfs()) ans+=dfs(0,N);
		return ans;
	}

	inline void get_link(){
		for(int x=1; x<=n; ++x){
			int to=0;
			for(int i=fir[x]; i&&!to; i=eg[i].nx){
				if(eg[i].wi==0) to=eg[i].to-n;
			}
			assert(to);
			link[x]=to;
		}
	}
}

namespace S{
	int cnt,cur_c,bel,node_s[N];
	class node{
		public:
			int fa,dep,c[26];
			bool vis[N];
			inline void clear(){
				fa=dep=0;
				memset(c,0,sizeof(c));
				memset(vis+1,0,n*sizeof(int));
			}
	}tr[N*N];

	inline void clear(){
		cnt=0;
		tr[0].clear();
		memset(node_s,0,sizeof(node_s));
	}

	inline int insert(int k,int c){
		tr[k].c[c]=++cnt;
		tr[cnt].clear();
		tr[cnt].fa=k;
		tr[cnt].dep=tr[k].dep+1;
		tr[cnt].vis[bel]=1;
		return cnt;
	}

	void dfs_g(const int k){
		if(k){
			for(int i=1; i<=n; ++i){
				if(tr[k].vis[i]) G::add(i,n+k,1);
			}
		}
		for(int i=0; i<26; ++i){
			if(tr[k].c[i]) dfs_g(tr[k].c[i]);
		}
	}

	inline void build_str(const int bel){
		static int nd[N][26],curpos[26];
		memset(curpos,0,sizeof(curpos));
		std::queue <pair> que;
		//x=node, y=pos;
		S::bel=bel;
		for(int i=len[bel]; i; --i){
			memcpy(nd[i],curpos,26*sizeof(int));
			curpos[ch[bel][i]-'a']=i;
		}
		memcpy(nd[0],curpos,26*sizeof(int));
		que.push((pair){0,0});
		int cnt=0;
		while(!que.empty()){
			pair x=que.front();
			que.pop();
			tr[x.x].vis[bel]=1;
			if(cnt>=n||tr[x.x].dep==tgt) continue;
			for(int i=0; i<26; ++i){
				if(nd[x.y][i]){
					if(!tr[x.x].c[i]) insert(x.x,i);
					que.push((pair){tr[x.x].c[i],nd[x.y][i]});
					if(++cnt==n) break;
				}
			}
		}
	}

	inline void oput_inv(int k){
		static char ch[N];
		char *pt=ch;
		for(int p=tr[k].fa; k; k=p,p=tr[k].fa){
			for(int i=0; i<26; ++i){
				if(tr[p].c[i]==k){
					*pt++=i+'a';
					break;
				}
			}
		}
		while(pt!=ch) putchar(*--pt);
		putchar('\n');
	}
}

bool jdg(int tgt){
	::tgt=tgt;
	G::clear();
	S::clear();
	for(int i=1; i<=n; ++i){
		S::build_str(i);
	}
	G::end=n+S::cnt+1;
	for(int i=1; i<=n; ++i){
		G::add(0,i,1);
	}
	for(int i=1; i<=S::cnt; ++i){
		G::add(n+i,G::end,1);
	}
	S::dfs_g(0);
	return G::dinic()==n;
}

inline int bin_search(){
	int l=1,r=n+1,mid;
	while(l!=r){
		mid=(l+r)>>1;
		if(!jdg(mid)) l=mid+1;
		else r=mid;
	}
	if(l==n+1) return -1;
	assert(jdg(l));
	return l;
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		scanf("%s",ch[i]+1);
		len[i]=strlen(ch[i]+1);
	}
	int res=bin_search();
	printf("%d\n",res);
	if(res==-1) return 0;
	G::get_link();
	for(int i=1; i<=n; ++i){
		S::oput_inv(link[i]);
	}
	return 0;
}
