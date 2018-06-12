#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int N=55;
int n,m,cnt,sum,at[N],hp[N],cur[N<<1],fir[N<<1],dep[N<<1];
bool map[N][N];
struct edge{
	int to;
	double wi;
	int nx;
}eg[5200];
inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-48;
	return x;
}
inline void add(int a,int b,double v){
	eg[++cnt]=(edge){b,v,fir[a]};
	fir[a]=cnt;
	eg[++cnt]=(edge){a,0,fir[b]};
	fir[b]=cnt;
}
void init(double t){
	cnt=0;
	memset(fir,0,sizeof(fir));
	for(int i=1;i<=n;++i){
		add(0,i,at[i]*t);
	}
	for(int i=1;i<=m;++i){
		add(i+N,(N<<1)-1,hp[i]);
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(map[i][j]){
				add(i,j,1000);
			}
		}
	}
}
bool bfs(){
	static int que[N<<1];
	memset(dep,0,sizeof(dep));
	dep[0]=1;
	int hd=0,tl=1;
	while(hd!=tl){
		int x=que[hd++];
		for(int i=cur[x]=fir[x];i;i=eg[i].nx){
			int y=eg[i].to;
			if(!dep[y]){
				dep[y]=dep[x]+1;
				que[tl++]=x;
			}
		}
	}
	return dep[(N<<1)-1];
}
double dfs(int x,double t){
	if(x==(N<<1)-1) return t;
	double tp,tt=t;
	for(int &i=cur[x];i;i=eg[i].nx){
		int y=eg[i].to;
		double &v=eg[i].wi;
		if(dep[y]==dep[x]+1&&v&&tt&&(tp=dfs(y,min(v,tt)))){
			v-=tp;
			eg[i^1].wi+=tp;
			tt-=tp;
		}
	}
	return tt-t;
}
inline bool jdg(double t){
	double ans=0;
	init(t);
	while(bfs()) ans+=dfs(0,50005);
	return fabs(ans-sum)<1e6;
}
int main(){
	m=nxi(),n=nxi();
	for(int i=1;i<=n;++i){
		at[i]=nxi();
	}
	for(int i=1;i<=m;++i){
		sum+=hp[i]=nxi();
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			map[i][j]=nxi();
		}
	}
	double l=0,r=50001,mid;
	while(r-1e-4>l){
		mid=(l+r)/2;
		if(jdg(mid)) r=mid;
		else l=mid+1;
	}
	printf("%lf\n",l);
	return 0;
}
