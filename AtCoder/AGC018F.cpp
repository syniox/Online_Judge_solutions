#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=1e5+5;
int n,rt1,rt2,fa1[N],fa2[N],col[N];
bool dgr1[N],dgr2[N];

inline int nxi(FILE *fd=stdin){
	int x=0;
	char c;
	while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
	const bool f=(c=='-')&&(c=fgetc(fd));
	while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
	return f?-x:x;
}

bool able(){
	for(int i=1; i<=n; ++i){
		if(dgr1[i]!=dgr2[i]) return 0;
	}
	return 1;
}

namespace G{
	int cnt=1,fir[N<<1],cur[N<<1];
	bool vis[N*6];
	struct edge{
		int to,nx;
	}eg[N*6];

	inline void add(const int a,const int b){
		//printf("add: %d - %d\n",a,b);
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,fir[b]};
		fir[b]=cnt;
	}

	void dfs(const int x){
		for(int i=cur[x]; i; i=cur[x]){
			cur[x]=eg[i].nx;
			if(vis[i]||vis[i^1]) continue;
			vis[i]=1;
			dfs(eg[i].to);
		}
	}

	bool jdg(){
		for(int i=2; i<=cnt; i+=2){
			if(vis[i]==vis[i+1]) return 0;
		}
		return 1;
	}

	void paint(){
		for(int i=1; i<=n; ++i){
			for(int j=fir[i]; j; j=eg[j].nx){
				if(eg[j].to==i+n) col[i]=vis[j]?-1:1;
			}
		}
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		fa1[i]=nxi();
		if(fa1[i]==-1) rt1=i;
		else dgr1[fa1[i]]^=1;
	}
	for(int i=1; i<=n; ++i){
		fa2[i]=nxi();
		if(fa2[i]==-1) rt2=i;
		else dgr2[fa2[i]]^=1;
	}
	if(!able()){
		puts("IMPOSSIBLE");
		return 0;
	}
	for(int i=1; i<=n; ++i){
		if(fa1[i]==-1) G::add(0,i);
		else G::add(fa1[i],i);
		if(fa2[i]==-1) G::add(0,i+n);
		else G::add(fa2[i]+n,i+n);
		if(!dgr1[i]) G::add(i,i+n);
	}
	memcpy(G::cur,G::fir,(n<<1|1)*sizeof(int));
	G::dfs(0);
	assert(G::jdg());
	G::paint();
	puts("POSSIBLE");
	for(int i=1; i<=n; ++i){
		printf("%d ",col[i]);
	}
	puts("");
	return 0;
}
