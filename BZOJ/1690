#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=1002;
int n,m,cnt,f[N],fi[N],fir[N],dis[N],que[N],cvs[N];
bool vis[N];
struct edge{
	int to,wi,nx;
}og[10002],eg[10002];
inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}
inline void add(int a,int b,int v){
	eg[++cnt]=(edge){b,v,fir[a]};
	fir[a]=cnt;
}
bool spfa(){
	memset(dis,-5,sizeof(dis));
	int hd=0,tl=1;
	que[0]=1;
	dis[1]=0;
	while(hd!=tl){
		int x=que[hd];
		vis[x]=0;
		if(++hd==N) hd=0;
		for(int i=fir[x];i;i=eg[i].nx){
			int y=eg[i].to,v=eg[i].wi+dis[x];
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
bool jdg(int t){
	cnt=0;
	memset(fir,0,sizeof(fir));
	memset(cvs,0,sizeof(cvs));
	cvs[1]=1;
	for(int x=1;x<=n;++x){
		for(int i=fi[x];i;i=og[i].nx){
			int y=og[i].to,v=og[i].wi;
			add(x,y,f[y]-v*t);
		}
	}
	return spfa();
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=n;++i){
		f[i]=nxi()*1000;
	}
	for(int a,b,v;m--;){
		a=nxi(),b=nxi(),v=nxi();
		og[++cnt]=(edge){b,v,fi[a]};
		fi[a]=cnt;
	}
	int l=0,r=1e6,mid;
	while(l!=r){
		mid=(l+r+1)>>1;
		if(jdg(mid)) l=mid;
		else r=mid-1;
	}
	printf("%.2lf\n",(double)l*0.001);
	return 0;
}
