#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1005;
int n,m,p,cnt,que[N],fir[N],dp[N][1<<10];
int sp[11],hx[1<<10];
bool vis[N],ipt[N];
struct pnt{
	int x,bel;
	bool operator < (const pnt b) const {
		return x<b.x;
	}
}pt[11];
struct edge{
	int to,wi,nx;
}eg[6005];
inline void apn(int &a,int b){
	if(a>b) a=b;
}
inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-48;
	return x;
}
inline void add(int a,int b,int v){
	eg[++cnt]=(edge){b,v,fir[a]};
	fir[a]=cnt;
}
void spfa(int lt){
	int hd=0,tl=0,cnt=0;
	for(int i=1;i<=n;++i){
		if(ipt[i]){
			if(1<<cnt&lt){
				apn(dp[i][lt],dp[i][lt^(1<<cnt)]);
			}
			++cnt;
		}
		que[tl++]=i;
	}
	memset(vis,1,sizeof(vis));
	while(hd!=tl){
		int x=que[hd++];
		if(hd==N) hd=0;
		vis[x]=0;
		int q=dp[x][lt];
		for(int i=fir[x];i;i=eg[i].nx){
			int y=eg[i].to,v=q+eg[i].wi;
			if(dp[y][lt]>v){
				dp[y][lt]=v;
				if(!vis[y]){
					que[tl++]=y;
					if(tl==N) tl=0;
					vis[y]=1;
				}
			}
		}
	}
}
void init(){
	for(int i=1;i<=p;++i){
		sp[pt[i].bel]+=1<<(i-1);
	}
	for(int i=1;i<1<<p;++i){
		int tp=0;
		for(int j=0;j<p;++j){
			if((1<<j)&i) tp|=sp[j+1];
		}
		for(int j=1;j<=p;++j){
			if(i&(1<<(pt[j].bel-1))){
				hx[i]=dp[pt[j].x][tp];
				break;
			}
		}
	}
}
int calc(){
	for(int i=1;i<1<<p;++i){
		for(int j=(i-1)&i;j>((j-1)&j);j=(j-1)&i){
			apn(hx[i],hx[j]+hx[j^i]);
		}
	}
	int ans=0;
	for(int i=1;i<=p;++i){
		if(sp[i]) ans|=sp[i];
	}
	return hx[ans];
}

//---------------main---------------//

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi(),m=nxi(),p=nxi();
	for(int a,b,v,i=1;i<=m;++i){
		a=nxi(),b=nxi(),v=nxi();
		add(a,b,v);
		add(b,a,v);
	}
	for(int i=1;i<=p;++i){
		pt[i].bel=nxi();
		pt[i].x=nxi();
		ipt[pt[i].x]=1;
	}
	sort(pt+1,pt+p+1);
	memset(dp,31,sizeof(dp));
	for(int i=1;i<1<<p;++i) dp[i][0]=0;
	for(int i=1;i<1<<p;++i){
		for(int j=1;j<=n;++j){
			for(int k=(i-1)&i;k;k=(k-1)&i){
				apn(dp[j][i],dp[j][k]+dp[j][i^k]);
			}
		}
		spfa(i);
	}
	init();
	printf("%d\n",calc());
	return 0;
}
