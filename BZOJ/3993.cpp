#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long lint;
const int N=55;
int n,m,cnt,at[N],hp[N],cur[N<<1],fir[N<<1],dep[N<<1];
bool map[N][N];
lint sum;
struct edge{
	int to;
	lint wi;
	int nx;
}eg[5200];
inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-48;
	return x;
}
inline void add(int a,int b,lint v){
	eg[++cnt]=(edge){b,v,fir[a]};
	fir[a]=cnt;
	eg[++cnt]=(edge){a,0,fir[b]};
	fir[b]=cnt;
}
void init(lint t){
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
				add(i,j+N,1e9);
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
			if(!dep[y]&&eg[i].wi){
				dep[y]=dep[x]+1;
				que[tl++]=y;
			}
		}
	}
	return dep[(N<<1)-1];
}
lint dfs(int x,lint t){
	if(x==(N<<1)-1) return t;
	lint tp,tt=t;
	for(int &i=cur[x];i&&tt;i=eg[i].nx){
		int y=eg[i].to;
		lint &v=eg[i].wi;
		if(dep[y]==dep[x]+1&&v&&(tp=dfs(y,min(v,tt)))){
			v-=tp;
			eg[i^1].wi+=tp;
			tt-=tp;
		}
	}
	return t-tt;
}
inline bool jdg(int t){
	lint ans=0;
	init(t);
	while(bfs()) ans+=dfs(0,1e16);
	return ans>=sum;
}
int main(){
	m=nxi(),n=nxi();
	for(int i=1;i<=n;++i){
		at[i]=nxi();
	}
	for(int i=1;i<=m;++i){
		sum+=hp[i]=nxi()*10000;
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			map[i][j]=nxi();
		}
	}
	int l=0,r=500000005,mid;
	while(l<r){
		mid=l+r>>1;
		if(jdg(mid)) r=mid;
		else l=mid+1;
	}
	printf("%lf\n",(double)l*0.0001);
	return 0;
}
