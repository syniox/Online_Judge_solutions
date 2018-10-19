#include<iostream>
#include<cstdio>
#include<cstring>
const int N=102;
int n,m,sg[N],limit[N],cbit[1<<17];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int highbit(int x){
	int ans=0;
	for(int i=16;i;i>>=1){
		if(x>>i) x>>=i,ans+=i;
	}
	return ans;
}

namespace G{
	int cnt,ind[N],fir[N],topo[N],que[N];
	bool vis[1<<17];
	struct edge{
		int to,nx;
	}eg[1502];
	inline void init(){
		cnt=0;
		memset(ind,0,sizeof(ind));
		memset(fir,0,sizeof(fir));
	}
	inline void add(const int a,const int b){
		++ind[b];
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}
	inline void get_topo(){
		int hd=0,tl=0,cnd=0;
		for(int i=1;i<=n;++i){
			if(!ind[i]) que[tl++]=i;
		}
		while(hd!=tl){
			const int x=que[hd++];
			topo[++cnd]=x;
			for(int i=fir[x];i;i=eg[i].nx){
				const int y=eg[i].to;
				if(!--ind[y]) que[tl++]=y;
			}
		}
	}
	inline void get_sg(){
		static int buk[1<<17];
		for(int it=n;it;--it){
			memset(vis,0,sizeof(vis));
			memset(buk,0,sizeof(buk));
			const int x=topo[it];
			int top=0;
			bool to_end=0;
			for(int i=fir[x];i;i=eg[i].nx){
				que[++top]=eg[i].to;
				to_end|=!fir[eg[i].to];
			}
			vis[0]=fir[x]&&((limit[x]&1)==0||to_end);
			for(int i=1;i<1<<top;++i){
				buk[i]=buk[i^(i&-i)]^sg[que[highbit(i&-i)+1]];
				if(cbit[i]<=limit[x]&&(((limit[x]-cbit[i])&1)==0)){
					vis[buk[i]]=1;
				}
			}
			for(int i=0;i<1<<top;++i){
				if(!vis[i]){
					sg[x]=i;
					break;
				}
			}
		}
	}
}

inline bool solve(){
	int ans=0;
	for(int i=1;i<=n;++i){
		if(nxi()&1) ans^=sg[i];
	}
	return (bool)ans;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("d.in","r",stdin);
#endif
	const int T=nxi();
	for(int i=1;i<1<<17;++i){
		cbit[i]=cbit[i>>1]+(i&1);
	}
	for(int cas=1;cas<=T;++cas){
		n=nxi(),m=nxi();
		G::init();
		for(int i=1;i<=m;++i){
			const int x=nxi()+1,y=nxi()+1;
			G::add(x,y);
		}
		for(int i=1;i<=n;++i){
			limit[i]=nxi();
		}
		G::get_topo();
		G::get_sg();
//		printf("sg:");
//		for(int i=1;i<=n;++i){
//			printf("%d ",sg[i]);
//		}
//		puts("");
		printf("Game#%d:\n",cas);
		const int R=nxi();
		for(int i=1;i<=R;++i){
			printf("Round#%d: ",i);
			puts(solve()?"WINNING":"LOSING");
		}
		puts("");
	}
	return 0;
}
