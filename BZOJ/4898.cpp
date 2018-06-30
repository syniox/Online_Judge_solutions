#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long lint;
const int N=102;
const int P=1002;
int cnt,fir[N],cvs[N],que[N];
int n,m,p,in[N][P],ot[N][P],map[N][P];
bool vis[N];
lint vl[N][N],dis[N];
struct edge{
	int to,nx;
	lint wi;
}eg[20002];

template<class T> void apn(T &a,T b){
	if(a>b) a=b;
}

template <class T> void apx(T &a,T b){
	if(a<b) a=b;
}

inline void add(int a,int b,lint v){
	printf("add:%d %d %lld\n",a,b,v);
	eg[++cnt]=(edge){b,fir[a],v};
	fir[a]=cnt;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void floyd(){
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(i==j) continue;
			for(int k=1;k<=n;++k){
				if(j!=k&&i!=k){
					apn(map[j][k],map[j][i]+map[i][k]);
				}
			}
		}
	}
}

inline void get_v(){
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(i==j) continue;
			for(int k=1;k<=p;++k){
				if(~ot[j][k]&&~in[i][k]){
					apx(vl[i][j],(ot[j][k]-in[i][k])*100ll);
				}
			}
		}
	}
}

bool spfa(){
	memset(vis,0,sizeof(vis));
	memset(dis,0,sizeof(dis));
	memset(cvs,0,sizeof(cvs));
	int hd=0,tl=0;
	for(;tl<n;++tl) que[tl]=tl+1;
	while(hd!=tl){
		int x=que[hd];
		if(++hd==N) hd=0;
		vis[x]=0;
		for(int i=fir[x];i;i=eg[i].nx){
			int y=eg[i].to;
			lint v=eg[i].wi+dis[x];
			if(dis[y]<v){
				dis[y]=v;
				if(!vis[y]){
					if(++cvs[y]==n) return 1;
					que[tl]=y;
					if(++tl==N) tl=0;
					vis[y]=1;
				}
			}
		}
	}
	return 0;
}

inline bool jdg(lint t){
	memset(fir,0,sizeof(fir));
	cnt=0;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(map[i][j]<5e8) add(i,j,vl[i][j]-t*map[i][j]);
		}
	}
	return spfa();
}

int sol(){
	lint l=0,r=1e11,mid;
	while(l!=r){
		mid=(l+r+1)>>1;
		if(jdg(mid)) l=mid;
		else r=mid-1;
	}
	return l/100;
}

int main(){
	memset(map,31,sizeof(map));
	n=nxi(),m=nxi(),p=nxi();
	for(int i=1;i<=n;++i) map[i][i]=0;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=p;++j){
			in[i][j]=nxi(),ot[i][j]=nxi();
		}
	}
	for(int a,b,v,i=1;i<=m;++i){
		a=nxi(),b=nxi(),v=nxi();
		map[a][b]=v;
	}
	floyd();
	get_v();
	printf("%d\n",sol());
	return 0;
}
