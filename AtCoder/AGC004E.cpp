#include<iostream>
#include<cstdio>
#include<cstring>
const int N=102;
int H,W,hcnt[N][N],wcnt[N][N];
char mp[N][N];
short dp[N][N][N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T1,class T2> inline void apx(T1 &x,const T2 y){
	if(x<y) x=y;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	H=nxi(),W=nxi();
	int ex,ey;
	for(int i=1;i<=H;++i){
		scanf("%s",mp[i]+1);
	}
	for(int i=1;i<=H;++i){
		for(int j=1;j<=W;++j){
			if(mp[i][j]=='E') ex=i,ey=j;
			bool f=mp[i][j]=='o';
			hcnt[i][j]=hcnt[i][j-1]+f;
			wcnt[i][j]=wcnt[i-1][j]+f;
		}
	}
	int ans=0;
	for(int i=0;i<ex;++i){
		for(int j=0;j<=H-ex;++j){
			int nh=std::max(ex-i,j+1),xh=std::min(ex+j,H-i);
			if(xh<nh) continue;
			for(int k=0;k<ey;++k){
				for(int l=0;l<=W-ey;++l){
					int nw=std::max(ey-k,l+1),xw=std::min(ey+l,W-k);
					if(xw<nw) continue;
					int cur=dp[j][k][l];
					apx(ans,cur);
					if(k+l+1<ey){
						apx(dp[j][k+1][l],cur+wcnt[xh][ey-k-1]-wcnt[nh-1][ey-k-1]);
					}
					if(k+l+1<W-ey+1){
						apx(dp[j][k][l+1],cur+wcnt[xh][ey+l+1]-wcnt[nh-1][ey+l+1]);
					}
					if(i+j+1<H-ex+1){
						apx(dp[j+1][k][l],cur+hcnt[ex+j+1][xw]-hcnt[ex+j+1][nw-1]);
					}
					if(i+j+1<ex){
						apx(dp[j][k][l],cur+hcnt[ex-i-1][xw]-hcnt[ex-i-1][nw-1]);
					}
				}
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
