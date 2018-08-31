#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int N=202,mod=1e9+7;
char ch[N][N];
int zf,n,m,cn,tp[N*N],vis[N*N],bel[N*N],mp[302][302];
int px[27],py[27];

inline bool vld(int x,int y){
	return x>0&&y>0&&x<=n&&y<=m;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int fbel(int x){
	if(++vis[x]>n*m) return -1;
	return bel[x]==x?x:bel[x]=fbel(bel[x]);
}

inline int qpow(int x,int t){
	int ans=1;
	for(;t;t>>=1,x=(lint)x*x%mod){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline void upd(int x,int ty){
//	printf("%d->%d(%d from %d)\n",x,tp[fbel(ty)],fbel(ty),ty);
	--mp[x][tp[fbel(ty)]];
}

inline void gauss_init(){
	memset(mp,0,sizeof(mp));
	int cur=0;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			//we don't need to consider root
			if(ch[i][j]=='.'){
				++cur;
				mp[cur][cur]+=4;
				const int tp=(i-1)*m+j;
				if(i>1) upd(cur,tp-m);
				if(j>1) upd(cur,tp-1);
				if(i<n) upd(cur,tp+m);
				if(j<m) upd(cur,tp+1);
			}
		}
	}
//	printf("cn:%d\n",cn);
	for(int i=1;i<=cn;++i){
		for(int j=1;j<=cn;++j){
			if(mp[i][j]<0) mp[i][j]+=mod;
//			printf("%d ",mp[i][j]);
		}
//		puts("");
	}
}

inline bool gauss(){
	for(int i=1;i<=cn;++i){
		int j=i;
		while(j<=cn&&mp[j][i]==0) ++j;
		if(j>cn) return 0;
		if(i!=j) zf*=-1;
		std::swap(mp[i],mp[j]);
		const int cur=qpow(mp[i][i],mod-2);
		for(int k=i+1;k<=cn;++k){
			const int p=(lint)mp[k][i]*cur%mod;
			for(int l=1;l<=cn;++l){
				mp[k][l]=(mp[k][l]+(lint)mp[i][l]*(mod-p))%mod;
			}
		}
	}
	return 1;
}

inline bool jdg(){
	for(int i=1;i<=n*m;++i){
		if(fbel(i)==-1){
			puts("0");
			return 0;
		}
	}
	memset(vis,128,sizeof(vis));
	return 1;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	px['U'-'A']=py['L'-'A']=-1;
	px['D'-'A']=py['R'-'A']=1;
	int T=nxi();
	while(T--){
		memset(tp,0,sizeof(tp));
		memset(vis,0,sizeof(vis));
		zf=1,cn=0;
		n=nxi(),m=nxi();
		for(int i=1;i<=n*m;++i) bel[i]=i;
		for(int i=1;i<=n;++i){
			scanf("%s",ch[i]+1);
			for(int j=1;j<=m;++j){
				const int cur=(i-1)*m+j;
				if(ch[i][j]=='.') tp[cur]=++cn;
				else{
					const int tx=i+px[ch[i][j]-'A'];
					const int ty=j+py[ch[i][j]-'A'];
					if(vld(tx,ty)) bel[cur]=(tx-1)*m+ty;
					else bel[cur]=0;
				}
			}
		}
		if(!jdg()) continue;
		gauss_init();
		if(!gauss()){
			puts("0");
			continue;
		}
		lint ans=1;
		for(int i=1;i<=cn;++i){
			ans=ans*mp[i][i]%mod;
		}
		printf("%lld\n",(ans*zf+mod)%mod);
	}
	return 0;
}
