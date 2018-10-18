#include<iostream>
#include<cstdio>
#include<cstring>
const int N=505;
int n,m;
char mp[N][N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=n;++i){
		scanf("%s",mp[i]+1);
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			putchar(j!=m&&(j==1||i&1||mp[i][j]=='#')?'#':'.');
		}
		puts("");
	}
	puts("");
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			putchar(j!=1&&(j==m||(i&1)==0||mp[i][j]=='#')?'#':'.');
		}
		puts("");
	}
	return 0;
}
