#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
const int N=1e6+5;
int n;

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
	int cnt=1,sum[N<<1],fir[N],dp[N<<1];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs_dn(const int x,const int e){
		static int buk[N];
		int cnt=0;
		sum[e]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			if(i==(e^1)) continue;
			const int y=eg[i].to;
			dfs_dn(y,i);
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			if(i==(e^1)) continue;
			sum[e]+=sum[i];
			dp[e]+=dp[i];
			buk[++cnt]=sum[i];
		}
		std::sort(buk+1,buk+cnt+1);
		for(int i=cnt; i&&sum[e]>n>>1; --i){
			++dp[e];
			sum[e]-=buk[i];
		}
	}

	void dfs_up(const int x,const int e){
		static int buk[N],psum[N];
		int cnt=0,base=0;
		for(int i=fir[x]; i; i=eg[i].nx){
			base+=dp[i];
			buk[++cnt]=sum[i];
		}
		std::sort(buk+1,buk+cnt+1);
		for(int i=1; i<=cnt; ++i){
			psum[i]=psum[i-1]+buk[i];
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			if(i==(e^1)) continue;
			int l=1,r=cnt,mid;
			while(l!=r){
				mid=(l+r+1)>>1;
				if(psum[mid]-sum[i]*(sum[i]<=buk[mid])+1>n>>1) r=mid-1;
				else l=mid;
			}
			const bool inq=(sum[i]<=buk[l]);
			dp[i^1]=base-dp[i]+cnt-l-(inq^1);
			sum[i^1]=psum[l]-sum[i]*inq+1;
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			if(i!=(e^1)) dfs_up(eg[i].to,i);
		}
	}

	int getans(const int x){
		int res=0;
		for(int i=fir[x]; i; i=eg[i].nx){
			res+=dp[i];
		}
		return res;
	}
}

int main(){
	n=nxi();
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	G::dfs_dn(1,0);
	G::dfs_up(1,0);
	for(int i=1; i<=n; ++i){
		printf("%d\n",G::getans(i));
	}
	return 0;
}
