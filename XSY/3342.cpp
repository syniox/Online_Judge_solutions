#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long lint;
const int N=1e5+5;
const int M=19;
int n,m,hx[M],bel[N],sz[1<<18],mp[M][M];

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

bool cmp_hx(const int a,const int b){
	return hx[a]<hx[b];
}

inline void get_mp(){
	memset(mp,120,sizeof(mp));
	static bool link[1<<18];
	for(int i=1; i<=n; ++i){
		link[bel[i]]=1;
	}
	for(int i=(1<<m)-1; i; --i){
		if(!link[i]) continue;
		for(int j=i,k=j&-j; j; j^=k,k=j&-j){
			link[i^k]=1;
		}
	}
	for(int i=1; i<=m; ++i){
		for(int j=1; j<=m; ++j){
			if(link[1<<(i-1)|1<<(j-1)]) mp[i][j]=hx[j];
		}
		mp[i][i]=0;
	}
}

inline void get_sz(){
	int full_st=(1<<m)-1;
	for(int i=1; i<=n; ++i){
		++sz[full_st^bel[i]];
	}
	for(int i=1; i<=m; ++i){
		int state=full_st^1<<(i-1);
		for(int j=state; j; j=(j-1)&state){
			sz[j]+=sz[j|1<<(i-1)];
		}
	}
	for(int i=1; i<1<<m; ++i){
		sz[i]=n-sz[i];
	}
}

inline lint dij(const int stp){
	static int dis[M];
	memset(dis,120,sizeof(dis));
	int cur_sz=1,cur_st=0;
	lint ans=0;
	for(int i=1; i<=m; ++i){
		if(bel[stp]&1<<(i-1)) dis[i]=hx[i];
	}
	for(int i=1; i<=m; ++i){
		int nx_cir=0;
		for(int j=1; j<=m; ++j){
			if((cur_st&1<<(j-1))==0&&dis[j]<dis[nx_cir]) nx_cir=j;
		}
		for(int j=1; j<=m; ++j){
			apn(dis[j],dis[nx_cir]+mp[nx_cir][j]);
		}
		cur_st|=1<<(nx_cir-1);
		ans+=(lint)(sz[cur_st]-cur_sz)*dis[nx_cir];
		cur_sz=sz[cur_st];
	}
	return ans;
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=m; ++i){
		hx[i]=nxi();
		int k=nxi();
		for(int j=1; j<=k; ++j){
			bel[nxi()]|=1<<(i-1);
		}
	}
	get_mp();
	get_sz();
	lint ans=0;
	for(int i=1; i<=n; ++i){
		ans+=dij(i);
	}
	printf("%lld\n",ans>>1);
	return 0;
}
