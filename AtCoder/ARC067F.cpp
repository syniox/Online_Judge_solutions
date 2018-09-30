#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int N=5002,M=202;
int n,m,tl[N][M],tr[N][M];
lint ans,dis[N],vl[N][M],cf[N][N];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}	

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void get(int tt[N][M],const int step){
	static int st[N];
	int hd=1,tl=n,top=0;
	if(step<0) std::swap(hd,tl);
	const bool f=step==-1;
	for(int i=1;i<=m;++i){
		tl+=step;
		for(int j=hd;j!=tl;j+=step){
			for(;top&&(vl[st[top]][i]<vl[j][i]||(vl[st[top]][i]==vl[j][i]&&f));--top){
				tt[st[top]][i]=j-step;
			}
			st[++top]=j;
		}
		tl-=step;
		for(;top;--top) tt[st[top]][i]=tl;
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	ans=-1e8;
	n=nxi(),m=nxi();
	for(int i=2;i<=n;++i){
		dis[i]=dis[i-1]+nxi();
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			vl[i][j]=nxi();
		}
	}
	get(tr,1);
	get(tl,-1);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			const int l=tl[i][j],r=tr[i][j],cur=vl[i][j];
			cf[l][i]+=cur;
			cf[l][r+1]-=cur;
			cf[i+1][i]-=cur;
			cf[i+1][r+1]+=cur;
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			cf[i][j]+=cf[i-1][j]+cf[i][j-1]-cf[i-1][j-1];
			if(i<=j){
				apx(ans,cf[i][j]-(dis[j]-dis[i]));
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
