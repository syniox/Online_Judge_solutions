#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
typedef long long lint;
using namespace std;
const int N=105,V=1e5+5;
int n,val[N],sum[V];
vector<bool> dp[V],vis[V];
vector<double> fp[V];
/*
   sum[i]表示能被i整除的数有多少个
   dp[i][j]表示当前gcd为i且取了j次时先手是否能赢
   fp[i][j]表示当前gcd为i且取了j次时先手赢的概率
 */

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
	static struct{
		template <class T> operator T(){
			T x=0;
			char c;
			while(((c=getchar())>'9'||c<'0')&&c!='-');
			const bool f=c=='-'&&(c=getchar());
			while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
			return f?-x:x;
		}
	}ni;
}
using namespace utils;

int gcd(const int x,const int y){
	return y?gcd(y,x%y):x;
}

bool qdp(const int i,const int j){
	if(i==1||j==n) return i==1;
	assert(j<=sum[i]);
	if(vis[i][j]) return dp[i][j];
	vis[i][j]=1;
	bool f=0;
	for(int cnt=j,k=1; !f&&k<=n; ++k){
		if(i&&val[k]%i==0&&cnt-->0) continue;
		f|=!qdp(gcd(i,val[k]),j+1);
	}
	return dp[i][j]=f;
}

double qfp(const int i,const int j){
	if(i==1||j==n) return i==1;
	assert(j<=sum[i]);
	if(vis[i][j]) return fp[i][j];
	vis[i][j]=1;
	double res=0;
	for(int cnt=j,k=1; k<=n; ++k){
		if(i&&val[k]%i==0&&cnt-->0) continue; 
		res+=(1-qfp(gcd(i,val[k]),j+1));
	}
	return fp[i][j]=res/(n-j);
}

int main(){
	for(int T=ni; T--; ){
		memset(sum,0,sizeof(sum));
		n=ni;
		for(int i=1; i<=n; ++i){
			val[i]=ni;
			++sum[val[i]];
		}
		sort(val+1,val+n+1);
		sum[0]=1;
		vis[0].resize(1);
		dp[0].resize(1);
		fp[0].resize(1);
		for(int i=2; i<V; ++i){//!!
			for(int j=2; i*j<V; ++j){
				sum[i]+=sum[i*j];
			}
			vis[i].resize(sum[i]+1);
			dp[i].resize(sum[i]+1);
			fp[i].resize(sum[i]+1);
		}
		for(int i=0; i<V; ++i){
			fill(vis[i].begin(),vis[i].end(),0);
		}
		qdp(0,0);
		for(int i=0; i<V; ++i){
			fill(vis[i].begin(),vis[i].end(),0);
		}
		qfp(0,0);
		printf("%d %.4lf\n",(int)dp[0][0],fp[0][0]);
	}
	return 0;
}
