#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=102;
typedef long long lint;
int n,cnt,pre[N<<1],fir[N<<1],w[N][N],que[N<<1];
lint v[N][N],dis[N<<1];
bool vis[N<<1];
struct edge{
	int fr,to,wi,nx;
	lint cs;
}eg[20405];
inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}
inline void add(int a,int b,int w,lint c){
	eg[++cnt]=(edge){a,b,w,fir[a],c};
	fir[a]=cnt;
	eg[++cnt]=(edge){b,a,0,fir[b],-c};
	fir[b]=cnt;
}
bool spfa(){
	memset(dis,-2,sizeof(dis));
	int hd=0,tl=1;
	dis[0]=0;
	que[0]=0;
	while(hd!=tl){
		int x=que[hd++];
		vis[x]=0;
		if(hd==N<<1) hd=0;
		for(int i=fir[x];i;i=eg[i].nx){
			int y=eg[i].to;
			lint v=dis[x]+eg[i].cs;
			if(eg[i].wi&&dis[y]<v){
				dis[y]=v;
				pre[y]=i;
				if(!vis[y]){
					que[tl++]=y;
					if(tl==N<<1) tl=0;
					vis[y]=1;
				}
			}
		}
	}
	return dis[(N<<1)-1]>-1e16;
}
bool jdg(lint t){
	cnt=1;
	memset(fir,0,sizeof(fir));
	for(int i=1;i<=n;++i){
		add(0,i,1,0);
		add(i+N,(N<<1)-1,1,0);
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			add(i,j+N,1,v[i][j]-t*w[i][j]);
		}
	}
	lint ans=0;
	if(!spfa()) return 0;
	if(spfa()){
		do{
			int x=(N<<1)-1;
			while(x){
				int q=pre[x];
				--eg[q].wi;
				++eg[q^1].wi;
				ans+=eg[q].cs;
				x=eg[q].fr;
			}
		}while(spfa());
	}
	return ans>=0;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			v[i][j]=nxi()*10000000ll;
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			w[i][j]=nxi();
		}
	}
	lint l=0,r=1e11,mid;
	while(l<r){
		mid=(l+r+1)>>1;
		if(jdg(mid)) l=mid;
		else r=mid-1;
	}
	printf("%.6lf\n",double(l)*0.0000001);
	return 0;
}
