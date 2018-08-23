#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int N=1e5+2,mod=1e9+7;
int n,m,ex,ey,ans,dp[N],in[N],fir[N];
struct edge{
	int to,nx;
}eg[N<<1];

inline void add(int a,int b){
	static int cnt;
	eg[++cnt]=(edge){b,fir[a]};
	fir[a]=cnt;
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
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline lint qpow(lint x,int t){
	lint ans=1;
	for(;t;t>>=1,x=x*x%mod){
		if(t&1) ans=ans*x%mod;
	}
	return ans;
}

inline void bfs(){
	static int que[N],tx[N],xt[N],in_cp[N];
	memcpy(in_cp,in,sizeof(in));
	int hd=0,tl=1,cnt=0;
	que[0]=1;
	while(hd!=tl){
		int x=que[hd++];
		tx[++cnt]=x;
		xt[x]=cnt;
		for(int i=fir[x];i;i=eg[i].nx){
			int y=eg[i].to;
			if(!--in_cp[y]) que[tl++]=y;
		}
	}
	++in[ey];
	dp[ey]=qpow(in[ey],mod-2);
	for(int i=xt[ey];i<=xt[ex];++i){
		int x=tx[i];
		for(int j=fir[x];j;j=eg[j].nx){
			int y=eg[j].to;
			dp[y]=(dp[y]+(lint)dp[x]*qpow(in[y],mod-2))%mod;
		}
	}
	ans=dp[ex];
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
#endif
	n=nxi(),m=nxi(),ex=nxi(),ey=nxi();
	for(int i=1;i<=m;++i){
		int a=nxi(),b=nxi();
		++in[b];
		add(a,b);
	}
	bfs();
	int ytot=1;
	for(int i=2;i<=n;++i){
		ytot=(lint)ytot*in[i]%mod;
	}
	if(ey==1){
		printf("%d\n",ytot);
		return 0;
	}
	ans=(lint)ans*ytot%mod;
	printf("%lld\n",(lint)(ytot-ans+mod)%mod);
	return 0;
}
