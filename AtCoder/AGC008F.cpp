#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int N=2e5+2;
int n,m,fa[N],cntok[N],fir[N],fr1[N],fr2[N],dep1[N],dep2[N];
lint ans;
char quanlike[N];
struct edge{
	int to,nx;
}eg[N<<1];

inline void apn(int &x,const int y){
	if(x>y) x=y;
}

inline void add(const int a,const int b){
	static int cnt=0;
	eg[++cnt]=(edge){b,fir[a]};
	fir[a]=cnt;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void updep(const int x,const int y,int caly[]){
	if(dep1[x]<caly[y]+1){
		dep2[x]=dep1[x];
		fr2[x]=fr1[x];
		dep1[x]=caly[y]+1;
		fr1[x]=y;
	}
	else if(dep2[x]<caly[y]+1){
		dep2[x]=caly[y]+1;
		fr2[x]=y;
	}
}

inline int upcnt(const int x,const int y){
	return fr1[y]==x?dep2[y]:dep1[y];
}

void init(int x){
	for(int i=fir[x];i;i=eg[i].nx){
		int y=eg[i].to;
		if(y!=fa[x]){
			fa[y]=x;
			init(y);
			cntok[x]+=cntok[y];
			updep(x,y,dep1);
		}
	}
}

void dfs(int x){
	int min_sdep=quanlike[x]=='1'?0:1e9;
	if(fa[x]){
		if(m-cntok[x]) apn(min_sdep,upcnt(x,fa[x])+1);
		if(fr1[fa[x]]!=x) updep(x,fa[x],dep1);
		else updep(x,fa[x],dep2);
	}
	for(int i=fir[x];i;i=eg[i].nx){
		int y=eg[i].to;
		if(y!=fa[x]){
			if(cntok[y]) apn(min_sdep,upcnt(x,y)+1);
			dfs(y);
		}
	}
	ans+=std::max(0,std::min(dep1[x]-1,dep2[x]+1)-min_sdep+1);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<n;++i){
		const int a=nxi(),b=nxi();
		add(a,b);
		add(b,a);
	}
	scanf("%s",quanlike+1);
	for(int i=1;i<=n;++i){
		m+=cntok[i]=quanlike[i]=='1';
	}
	init(1);
	dfs(1);
	printf("%lld\n",ans+1);
	return 0;
}
