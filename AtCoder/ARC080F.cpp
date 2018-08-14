#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
const int N=102;
int n,cnp,cnj,cnt,og[N],hx[N<<1],fir[N<<1],prm[460];
bool npr[3200];
struct edge{
	int to,wi,nx;
}eg[N*N];

inline void add(int a,int b,int v){
	static int cnt=1;
	eg[++cnt]=(edge){b,v,fir[a]};
	fir[a]=cnt;
	eg[++cnt]=(edge){a,0,fir[b]};
	fir[b]=cnt;
}

inline char get_c(){
	static char buf[20000],*h,*t;
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
	}
	return h==t?EOF:*h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=get_c())>'9'||c<'0');
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return x;
}

inline void init(){
	npr[1]=1;
	for(int i=2;i<3200;++i){
		if(!npr[i]) prm[++cnp]=i;
		for(int j=1;j<=cnp&&i*prm[j]<3200;++j){
			npr[i*prm[j]]=1;
			if(i%prm[j]==0) break;
		}
	}
}

inline bool ispr(int x){
	if(x<3200) return !npr[x];
	int sq=sqrt(x)+1;
	for(int i=1;prm[i]<=sq;++i){
		if(x%prm[i]==0) return 0;
	}
	return 1;
}

namespace F{
	int dep[N<<1],que[N<<1],cur[N<<1];

	inline bool bfs(){
		memset(dep,0,sizeof(dep));
		int hd=0,tl=1;
		dep[0]=1;
		while(hd!=tl){
			int x=que[hd++];
			for(int i=cur[x]=fir[x];i;i=eg[i].nx){
				int y=eg[i].to;
				if(eg[i].wi&&!dep[y]){
					dep[y]=dep[x]+1;
					que[tl++]=y;
				}
			}
		}
		return dep[(N<<1)-1];
	}

	int dfs(int x,int t){
		if(x==(N<<1)-1) return t;
		int tp,tt=t;
		for(int &i=cur[x];i;i=eg[i].nx){
			int y=eg[i].to,v=eg[i].wi;
			if(v&&tt&&dep[x]+1==dep[y]&&(tp=dfs(y,std::min(v,tt)))){
				eg[i].wi-=tp;
				eg[i^1].wi+=tp;
				tt-=tp;
				if(!tt) break;
			}
		}
		return t-tt;
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("c.in","r",stdin);
#endif
	init();
	n=nxi();
	for(int i=1;i<=n;++i){
		og[i]=nxi();
	}
	std::sort(og+1,og+n+1);
	og[0]=-1;
	for(int i=1;i<=n;++i){
		if(og[i]-og[i-1]>1){
			if(og[i-1]+1) hx[++cnt]=og[i-1]+1;
			hx[++cnt]=og[i];
		}
	}
	hx[++cnt]=og[n]+1;
	for(int i=1;i<=cnt;++i){
		if(hx[i]&1) ++cnj;
		if(hx[i]&1) add(0,i,1);
		else add(i,(N<<1)-1,1);
		for(int j=i+1;j<=cnt;++j){
			int p=hx[j]-hx[i];
			if((p&1)&&ispr(p)){
				if(hx[i]&1) add(i,j,1);
				else add(j,i,1);
			}
		}
	}
	int ans=0;
	while(F::bfs()){
		ans+=F::dfs(0,N);
	}
	printf("%d\n",cnt-ans+(cnj&1));
	return 0;
}
