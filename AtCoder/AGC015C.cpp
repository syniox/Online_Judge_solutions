#include<iostream>
#include<cstdio>
#include<cstring>
const int N=2002;
int n,m,q,pre_p[N][N],pre_e[N][N],prl_e[N][N],prc_e[N][N];
char mp[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int get_p(const int x1,const int y1,const int x2,const int y2){
	return pre_p[x2][y2]-pre_p[x1-1][y2]-pre_p[x2][y1-1]+pre_p[x1-1][y1-1];
}

inline int get_e(const int x1,const int y1,const int x2,const int y2){
	const int fc=prc_e[x2][y1]-prc_e[x1][y1];
	const int fl=prl_e[x1][y2]-prl_e[x1][y1];
	return pre_e[x2][y2]-pre_e[x1][y2]-pre_e[x2][y1]+fc+fl+pre_e[x1][y1];
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	n=nxi(),m=nxi(),q=nxi();
	for(int i=1;i<=n;++i){
		scanf("%s",mp+1);
		for(int j=1;j<=m;++j){
			if(mp[j]=='1'){
				pre_p[i][j]=1;
				prc_e[i][j]=pre_p[i-1][j];
				prl_e[i][j]=pre_p[i][j-1];
				pre_e[i][j]=pre_p[i-1][j]+pre_p[i][j-1];
			}
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			pre_p[i][j]+=pre_p[i][j-1];
			pre_e[i][j]+=pre_e[i][j-1];
			prl_e[i][j]+=prl_e[i][j-1];
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			pre_p[i][j]+=pre_p[i-1][j];
			pre_e[i][j]+=pre_e[i-1][j];
			prc_e[i][j]+=prc_e[i-1][j];
		}
	}
	while(q--){
		const int x1=nxi(),y1=nxi(),x2=nxi(),y2=nxi();
		printf("%d\n",get_p(x1,y1,x2,y2)-get_e(x1,y1,x2,y2));
	}
	return 0;
}
