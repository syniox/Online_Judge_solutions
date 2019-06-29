#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e4+5;
int n,q;

namespace utils{
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
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
	int cnt,fir[N],sz[N],fa[N];
	short dp[N][501][3],bot[N][501],dc_k[N][501][3];
	__int8_t dc_b[N][501][3];
	int cans,rot1[N],rot2[N];
	bool vis[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void clear(){
		cnt=cans=0;
		memset(fir+1,0,n*sizeof(fir[0]));
		memset(vis+1,0,n*sizeof(vis[0]));
	}

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs_dp(const int x,const int f){
		static short fr_k[N][501][3],use_k[N][501][3];
		static __int8_t fr_b[N][501][3],use_b[N][501][3];
		static short buk[N],fp[N][501][3];
		int cnt=0;
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==f) continue;
			fa[y]=x;
			dfs_dp(y,x);
			sz[x]+=sz[y];
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=f) buk[++cnt]=y;
		}
		buk[0]=x;
		memset(fp[0],-10,sizeof(fp[0]));
		fp[0][0][0]=0;
		fp[0][1][1]=1;
		for(int i=1,s=1; i<=cnt; ++i){
			const int y=buk[i];
			const int lim=std::min(q,s+sz[y]);
			memset(fp[i],-10,(lim+1)*sizeof(fp[i][0]));
			for(int j=0; j<=s; ++j){
				//不对接
				for(int k=0; k<=std::min(q-j,sz[y]); ++k){
					int use=0;
					if(dp[y][k][1]>dp[y][k][use]) use=1;
					if(dp[y][k][2]>dp[y][k][use]) use=2;
					const short v=dp[y][k][use];
					for(int l=0; l<3; ++l){
						if(fp[i][j+k][l]<fp[i-1][j][l]+v){
							fp[i][j+k][l]=fp[i-1][j][l]+v;
							use_k[i][j+k][l]=k;
							use_b[i][j+k][l]=use;
							fr_k[i][j+k][l]=j;
							fr_b[i][j+k][l]=l;
						}
					}
				}
				//对接
				for(int k=0; k<=std::min(q-j+1,sz[y]); ++k){
					if(fp[i][j+k-1][2]<fp[i-1][j][1]+dp[y][k][1]){
						fp[i][j+k-1][2]=fp[i-1][j][1]+dp[y][k][1];
						use_k[i][j+k-1][2]=k;
						use_b[i][j+k-1][2]=1;
						fr_k[i][j+k-1][2]=j;
						fr_b[i][j+k-1][2]=1;
					}
					if(fp[i][j+k][1]<fp[i-1][j][0]+dp[y][k][1]+1){
						fp[i][j+k][1]=fp[i-1][j][0]+dp[y][k][1]+1;
						use_k[i][j+k][1]=k;
						use_b[i][j+k][1]=1;
						fr_k[i][j+k][1]=j;
						fr_b[i][j+k][1]=0;
					}
				}
			}
			s=std::min(q,s+sz[y]);
		}
		memcpy(dp[x],fp[cnt],(std::min(q,sz[x])+1)*sizeof(dp[x][0]));
		for(int i=1; i<=std::min(q,sz[x]); ++i){
			for(int j=0; j<3; ++j){
				for(int c=cnt,k=i,l=j; c; --c){
					dc_k[buk[c]][i][j]=use_k[c][k][l];
					dc_b[buk[c]][i][j]=use_b[c][k][l];
					int pre_k=fr_k[c][k][l];
					int pre_l=fr_b[c][k][l];
					k=pre_k,l=pre_l;
				}
			}
		}
		for(int i=1; i<=std::min(q,sz[x]); ++i){
			int j=1;
			while(j<=cnt&&dc_b[buk[j]][i][1]!=1) ++j;
			if(j>cnt){
				bot[x][i]=x;
			}
			else{
				bot[x][i]=bot[buk[j]][dc_k[buk[j]][i][1]];
			}
		}
	}

	void dfs_rot(const int x,const int f,const int k,const int b){
		int p1=b==1?x:0,p2=0;
		if(vis[x]) assert(b==1);
		if(b&&!vis[x]){
			for(int i=fir[x]; i&&!p2; i=eg[i].nx){
				const int y=eg[i].to;
				if(y==f||dc_b[y][k][b]!=1) continue;
				vis[y]=1;
				for(int j=bot[y][dc_k[y][k][b]]; j!=y; j=fa[j]){
					vis[j]=1;
				}
				if(p1) p2=bot[y][dc_k[y][k][b]];
				else p1=bot[y][dc_k[y][k][b]];
			}
			if(!p2){
				assert(b==1&&p1==x&&bot[x][k]==x);
				p2=x;
			}
			++cans;
			rot1[cans]=p1,rot2[cans]=p2;
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=f){
				dfs_rot(y,x,dc_k[y][k][b],dc_b[y][k][b]);
			}
		}
	}

	void oput(){
		int res_k=1,res_c=0;
		for(int i=1; i<=q; ++i){
			for(int j=0; j<3; ++j){
				if(dp[1][i][j]>dp[1][res_k][res_c]){
					res_k=i,res_c=j;
				}
			}
		}
		printf("%d\n",dp[1][res_k][res_c]);
		dfs_rot(1,0,res_k,res_c);
		printf("%d\n",cans);
		for(int i=1; i<=cans; ++i){
			printf("%d %d\n",rot1[i],rot2[i]);
		}
	}
}

int main(){
	while(n=nxi(),q=nxi(),n&&q){
		G::clear();
		for(int i=1; i<n; ++i){
			const int a=nxi(),b=nxi();
			G::add(a,b);
			G::add(b,a);
		}
		for(int i=1; i<=n; ++i){
			memset(G::dp[i],-10,sizeof(G::dp[i]));
		}
		G::dfs_dp(1,0);
		G::oput();
	}
	return 0;
}
