#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=32;
int n,m,q;
bool hole[N][N];
struct data{
	double r,d,l,u,s;
}dp[N][N][N][N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

void solve(const int x1,const int x2,const int y1,const int y2){
	double res=0,sr=0,sd=0,sl=0,su=0;
	int cnt=0;
	for(int i=x1+1; i<x2; ++i){
		for(int j=y1+1; j<y2; ++j){
			if(!hole[i][j]) continue;
			++cnt;
			data d;

			d=dp[x1][i][y1][j];
			res+=d.s+d.r*(y2-j)+d.d*(x2-i+j-y1)+d.l*(i-x1);
			sr+=d.r,sl+=d.d;
			su+=d.l+d.u;

			d=dp[x1][i][j][y2];
			res+=d.s+d.d*(x2-i)+d.l*(j-y1+i-x1)+d.u*(y2-j);
			sd+=d.d,su+=d.l;
			sr+=d.u+d.r;

			d=dp[i][x2][j][y2];
			res+=d.s+d.l*(j-y1)+d.u*(i-x1+y2-j)+d.r*(x2-i);
			sl+=d.l,sr+=d.u;
			sd+=d.r+d.d;

			d=dp[i][x2][y1][j];
			res+=d.s+d.u*(i-x1)+d.r*(y2-j+x2-i)+d.d*(j-y1);
			su+=d.u,sd+=d.r;
			sl+=d.d+d.l;
		}
	}
	if(!cnt) return;
	sr=sr/cnt+1,sd=sd/cnt+1;
	sl=sl/cnt+1,su=su/cnt+1;
	res=res/cnt+(x2-x1+y2-y1)*2;
	dp[x1][x2][y1][y2]=(data){sr,sd,sl,su,res};
}

int main(){
	n=nxi(),m=nxi(),q=nxi();
	for(int i=1; i<=q; ++i){
		const int x=nxi(),y=nxi();
		hole[x][y]=1;
	}
	for(int i=n; i>=0; --i){
		for(int j=i+2; j<=n; ++j){
			for(int k=m; k>=0; --k){
				for(int l=k+2; l<=m; ++l){
					solve(i,j,k,l);
				}
			}
		}
	}
	printf("%.9lf\n",dp[0][n][0][m].s);
	return 0;
}
