#include <iostream>
#include <cstdio>
#include <cstring>
const int N=105;
int n,psum,val[N];

inline int nxi(){
	int x=0;
	char c;
	while(((c=getchar())>'9'||c<'0')&&c!='-');
	const bool f=(c=='-')&&(c=getchar());
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return f?-x:x;
}

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

namespace G{
#define S (n)
#define T (n+1)
	int cnt,fir[N],cur[N],dep[N];
	class edge{
		public:
			int to,wi,nx;
	}eg[N<<3];

	inline void clear(){
		cnt=1;
		memset(fir,0,(n+2)*sizeof(int));
	}

	inline void add_edge(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,0,fir[b]};
		fir[b]=cnt;
	}

	inline void init(){
		clear();
		for(int i=0; i<n; ++i){
			if(val[i]<0) add_edge(i,T,-val[i]);
			else add_edge(S,i,val[i]);
		}
	}

	bool bfs(){
		static int que[N];
		memset(dep,0,(n+2)*sizeof(int));
		dep[S]=1;
		int hd=0,tl=1;
		que[0]=S;
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
		return dep[T];
	}

	int dfs(const int x,const int t){
		if(x==T) return t;
		int tt=t,tp;
		for(int &i=cur[x]; i&&tt; i=eg[i].nx){
			const int y=eg[i].to,v=eg[i].wi;
			if(v&&dep[y]==dep[x]+1&&(tp=dfs(y,std::min(v,tt)))){
				eg[i].wi-=tp;
				eg[i^1].wi+=tp;
				tt-=tp;
			}
		}
		return t-tt;
	}

	inline int solve(){
		int ans=psum;
		while(bfs()) ans-=dfs(S,1e6);
		return ans;
	}
#undef S
#undef T
}

class _Tree{
	protected:
		int cnt,fir[N];
		class edge{
			public:
				int to,nx;
		}eg[N<<1];

		inline void add_edge(const int a,const int b){
			eg[++cnt]=(edge){b,fir[a]};
			fir[a]=cnt;
		}
	public:
		inline void build(){
			memset(fir,0,n*sizeof(int));
			cnt=0;
			for(int i=1; i<n; ++i){
				const int a=nxi()-1,b=nxi()-1;
				add_edge(a,b);
				add_edge(b,a);
			}
		}

		inline void dfs(const int x,const int fa){
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				if(y==fa) continue;
				G::add_edge(y,x,1e6);
				dfs(y,x);
			}
		}
}t1,t2;

int main(){
	for(int cas=nxi(); cas; --cas){
		n=nxi();
		psum=0;
		for(int i=0; i<n; ++i){
			val[i]=nxi();
			if(val[i]>0) psum+=val[i];
		}
		t1.build();
		t2.build();
		int ans=0;
		for(int i=0; i<n; ++i){
			G::init();
			t1.dfs(i,i);
			t2.dfs(i,i);
			apx(ans,G::solve());
		}
		printf("%d\n",ans);
	}
	return 0;
}
