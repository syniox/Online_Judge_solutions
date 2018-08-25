#include<iostream>
#include<cstdio>
#include<cstring>
const int N=402,M=1e5+2;
int n,m,ans,qa[M],qb[M];
bool vld[N],mp[N][N];

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

inline bool jdg(const int x){
	mp[x][x]=1;
	for(int i=m;i;--i){
		const int a=qa[i],b=qb[i];
		if(mp[x][a]&&mp[x][b]) return 0;
		if(mp[x][a]||mp[x][b]) mp[x][a]=mp[x][b]=1;
	}
	return 1;
}

inline bool getand(const int x,const int y){
	for(int i=1;i<=n;++i){
		if(mp[x][i]&mp[y][i]) return 1;
	}
	return 0;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=m;++i){
		qa[i]=nxi(),qb[i]=nxi();
	}
	for(int i=1;i<=n;++i){
		vld[i]=jdg(i);
	}
	for(int i=1;i<n;++i){
		if(!vld[i]) continue;
		for(int j=i+1;j<=n;++j){
			if(!vld[j]) continue;
			if(!getand(i,j)) ++ans;
		}
	}
	printf("%d\n",ans);
	return 0;
}
