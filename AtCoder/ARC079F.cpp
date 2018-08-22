#include<iostream>
#include<cstdio>
#include<cstring>
const int N=2e5+2;
int n,pre[N],cnc,cir[N],sg1[N],sg2[N];
struct edge{
	int to,nx;
}eg[N];

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

namespace G{
	bool vis[N];
	int fir[N];
	struct edge{
		int to,nx;
	}eg[N];
	inline void add(int a,int b){
		static int cnt;
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}
	inline void get_circle(){
		int x=1;
		while(!vis[pre[x]]){
			vis[x]=1,x=pre[x];
		}
		memset(vis,0,sizeof(vis));
		for(;!vis[x];x=pre[x]){
			vis[x]=1;
			cir[++cnc]=x;
		}
	}
	void get_sg(int x){
		static bool buk[N];
		for(int i=fir[x];i;i=eg[i].nx){
			int y=eg[i].to;
			if(!vis[y]) get_sg(y);
		}
		for(int i=fir[x];i;i=eg[i].nx){
			int y=eg[i].to;
			if(!vis[y]) buk[sg1[y]]=1;
		}
		bool exist=0;
		for(int i=0;i<=n;++i){
			if(!buk[i]){
				if(!exist){
					sg1[x]=i;
					exist=1;
				}
				else{
					sg2[x]=i;
					break;
				}
			}
		}
		for(int i=fir[x];i;i=eg[i].nx){
			int y=eg[i].to;
			if(!vis[y]) buk[sg1[y]]=0;
		}
	}
}

inline bool jdg(bool f){
	static int fhx[N];
	fhx[0]=f?sg1[cir[cnc]]:sg2[cir[cnc]];
	for(int i=1;i<=cnc;++i){
		fhx[cir[i]]=fhx[cir[i-1]]==sg1[cir[i]]?sg2[cir[i]]:sg1[cir[i]];
	}
	return fhx[0]==fhx[cir[cnc]];
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<=n;++i){
		pre[i]=nxi();
		G::add(pre[i],i);
	}
	G::get_circle();
	for(int i=1;i<=cnc;++i){
		G::get_sg(cir[i]);
	}
	puts(jdg(0)||jdg(1)?"POSSIBLE":"IMPOSSIBLE");
	return 0;
}
