#include <iostream>
#include <cstdio>
#include <cstring>
const int M=305;
const int N=3005;
//f[i][j]表示第i个物品恰好有j个人喜欢的概率
//dp[i][j]表示第i个物品选j个时的期望利益
//dp[i][j]=sum{min(j,k)*f[i][k]}(1<=k<=n)
//dp[i][j+1]-dp[i][j]=sum{f[i][k]}(j+1<=k<=n);
int n,m;
double lk[M][N];

inline char get_c(){
	static char *h,*t,buf[20000];
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=get_c())>'9'||c<'0');
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return x;
}

namespace S{
	//fp[i][j]: 第i个物品在在j个人选了$个的概率
	double pcnt[M],fp[M][N];

	inline void init(){
		for(int i=1; i<=m; ++i){
			fp[i][0]=1;
			for(int j=1; j<=n; ++j){
				fp[i][j]=fp[i][j-1]*(1-lk[i][j]);
			}
			pcnt[i]=fp[i][n];
		}
	}

	inline void upd(const int x){
		static double tp[N];
		memcpy(tp,fp[x],sizeof(fp[0]));
		fp[x][0]=0;
		for(int i=1; i<=n; ++i){
			fp[x][i]=tp[i-1]*lk[x][i]+fp[x][i-1]*(1-lk[x][i]);
		}
		pcnt[x]+=fp[x][n];
	}

	inline double solve(){
		double ans=0;
		for(int x,i=1; i<=n; ++i){
			x=1;
			for(int j=2; j<=m; ++j){
				if(pcnt[j]<pcnt[x]) x=j;
			}
			ans+=1-pcnt[x];
			upd(x);
		}
		return ans;
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=m; ++j){
			lk[j][i]=(double)nxi()/1000;
		}
	}
	S::init();
	printf("%.12lf\n",S::solve());
	return 0;
}
