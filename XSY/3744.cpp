#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;
typedef long long lint;
const int N=1505,T=59049;
int h,w,q,n,tot,pw3[11];
unsigned short dp[N][T],from[N][T];
int posv[T][10];
//0: 无敲击 1: 敲击且此次敲击为该指针目前最后一次 2: 敲击且此次敲击非该指针目前最后一次

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;
struct pnt{
	int x,y;
	friend int mdis(const pnt &a,const pnt &b){
		return max(cabs(a.x-b.x),cabs(a.y-b.y));
	}
}req[N];

inline int shift(const int x){
	return x*3%pw3[tot];
}

void dfs_posv(const int t,const int scc){
	static int buk[10];
	if(t<0){
		memcpy(posv[scc],buk,tot*sizeof(int));
		return;
	}
	for(int i=0; i<3; ++i){
		buk[t]=i;
		dfs_posv(t-1,scc*3+i);
	}
}

void zy(const int t){
	static vector <int> buk[N*11];
	static bool vis[T];
	memset(vis,0,sizeof(vis));
	for(int i=0; i<N*11; ++i){
		buk[i].clear();
	}
	for(int i=0; i<pw3[tot]; ++i){
		if(dp[t][i]<30000) buk[dp[t][i]].push_back(i);
	}
	for(int i=0; i<N*11; ++i){
		for(vector<int>::iterator it=buk[i].begin(); it!=buk[i].end(); ++it){
			if(vis[*it]) continue;
			int j=shift(*it),v=dp[t][*it]+1;
			if(dp[t][j]>v){
				dp[t][j]=v;
				buk[v].push_back(j);
				from[t][j]=*it;
			}
		}
	}
}

void oput_ans(const int t,const int stat){
	static int use[N];
	static bool used[11];
	if(!t) return;
	oput_ans(t-bool(stat%3),from[t][stat]);
	if(stat%3==0) return;
	memset(used,0,sizeof(used));
	assert(stat%3==1);
	int org=shift(from[t][stat]),cur=stat-1;
	bool f=0;
	for(int cnt=0,k=1,pw=3; k<tot; ++k,pw*=3){
		cnt+=(bool)posv[cur][k];
		if(posv[cur][k]){
			used[use[t-cnt]]=1;
		}
		if(cur-org==pw){
			f=1;
			assert(posv[stat][k]==2);
			use[t]=use[t-cnt];
		}
	}
	assert(f==1||org==cur);
	if(org==cur){
		for(use[t]=1; used[use[t]]; ++use[t]);
		assert(use[t]<=q);
	}
	printf("%d %d\n",use[t],dp[t][stat]);
}

int main(){
	memset(dp,127,sizeof(dp));
	dp[0][0]=0;
	h=nxi(),w=nxi(),q=nxi(),n=nxi();
	tot=max(w,h);
	pw3[0]=1;
	for(int i=1; i<=tot; ++i){
		pw3[i]=pw3[i-1]*3;
	}
	dfs_posv(tot-1,0);
	req[0]=(pnt){1,1};
	for(int i=1; i<=n; ++i){
		req[i]=(pnt){nxi(),nxi()};
	}
	for(int i=0; i<n; ++i){
		zy(i);
		for(int j=0; j<pw3[tot]; ++j){
			const int cur=dp[i][j];
			if(cur>30000) continue;
			int cntq=0,cntv=0;
			for(int k=0; k<tot; ++k){
				if(!posv[j][k]) continue;
				cntq+=posv[j][k]==1;
				++cntv;
				assert(i-cntv+1>=0);
				if(posv[j][k]==1&&mdis(req[i-cntv+1],req[i+1])<=k){
					int tgt=shift(j+pw3[k])+1;
					if(dp[i+1][tgt]>cur+1){
						dp[i+1][tgt]=cur+1;
						from[i+1][tgt]=j;
					}
				}
			}
			if(cntq<q){
				int tgt=shift(j)+1;
				int v=max(cur,mdis(req[0],req[i+1]))+1;
				if(dp[i+1][tgt]>v){
					dp[i+1][tgt]=v;
					from[i+1][tgt]=j;
				}
			}
		}
	}
	int ans=1e9,stat=0;
	for(int i=0; i<pw3[tot]; ++i){
		if(dp[n][i]<ans){
			ans=dp[n][i],stat=i;
		}
	}
	printf("%d\n",ans);
	oput_ans(n,stat);
	return 0;
}
