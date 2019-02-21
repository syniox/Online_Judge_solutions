#include <iostream>
#include <cstdio>
#include <cstring>
const int N=105;
int n,cblk[N],cwht[N];
bool rev[N],dp[N][N],dec[N][N];//dp[i][j]: white num j;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnf,cnt,mp[N],fir[N],fa[N];
	int col[N],cnt_c[2];
	struct edge{
		int to,nx;
	}eg[N*N<<1];

	inline void init(){
		memset(col,-1,sizeof(col));
	}

	int find_rt(const int x){
		return fa[x]?fa[x]=find_rt(fa[x]):x;
	}

	inline void link(int a,int b){
		a=find_rt(a),b=find_rt(b);
		if(a!=b) fa[a]=b;
	}

	inline void add(const int a,const int b){
		//printf("add: %d - %d\n",a,b);
		link(a,b);
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,fir[b]};
		fir[b]=cnt;
	}

	inline int dfs(const int x){
		++cnt_c[col[x]];
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(col[x]==col[y]) return 0;
			else if(col[y]==-1){
				col[y]=col[x]^1;
				if(!dfs(y)) return 0;
			}
		}
		return 1;
	}

	inline bool build(){
		for(int i=1; i<=n; ++i){
			if(!fa[i]){
				cnt_c[0]=cnt_c[1]=0;
				mp[i]=++cnf;
				col[i]=0;
				if(!dfs(i)) return 0;
				cblk[cnf]=cnt_c[0];
				cwht[cnf]=cnt_c[1];
			}
		}
		return 1;
	}

	inline void oput(bool f){
		static int *pt,buk[N];
		pt=buk;
		for(int i=1; i<=n; ++i){
			if((col[i]^rev[mp[find_rt(i)]])==f){
				*pt++=i;
			}
		}
		printf("%d ",(int)(pt-buk));
		for(int *i=buk; i!=pt; ++i){
			printf("%d ",*i);
		}
		puts("");
	}
}

inline int get_ans(){
	for(int i=(n+1)>>1; i; --i){
		if(dp[G::cnf][i]) return i;
		if(dp[G::cnf][n-i]) return n-i;
	}
	return -1;
}

int main(){
	static bool vld[N][N];
	G::init();
	n=nxi();
	for(int i=1; i<=n; ++i){
		for(int j=nxi(); j; j=nxi()) vld[i][j]=1;
	}
	for(int i=1; i<n; ++i){
		for(int j=i+1; j<=n; ++j){
			if(!vld[i][j]||!vld[j][i]) G::add(i,j);
		}
	}
	if(!G::build()){
		puts("No solution");
		return 0;
	}
	dp[0][0]=1;
	for(int i=1; i<=G::cnf; ++i){
		for(int j=n; ~j; --j){
			if(j>=cblk[i]&&dp[i-1][j-cblk[i]]){
				//black
				dp[i][j]=1,dec[i][j]=1;
			}
			else if(j>=cwht[i]&&dp[i-1][j-cwht[i]]){
				//white
				dp[i][j]=1,dec[i][j]=0;
			}
		}
	}
	int tmp=get_ans();
	if(tmp==-1){
		puts("No solution");
		return 0;
	}
	for(int i=G::cnf; i; --i){
		if(dec[i][tmp]) tmp-=cblk[i];
		else rev[i]=1,tmp-=cwht[i];
	}
	G::oput(0);
	G::oput(1);
	return 0;
}
