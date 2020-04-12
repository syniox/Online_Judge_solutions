#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=505;
int n,val[N],dp[N][N];
bool vld[N][N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
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

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	for(int i=1; i<=n; ++i){
		static int stk[N];
		int top=0;
		for(int j=i; j<=n; ++j){
			if(top&&val[j]>stk[top]) break;
			stk[++top]=val[j];
			while(top>1&&stk[top]==stk[top-1]) ++stk[--top];
			if(top==1) vld[i][j]=1;
		}
	}
	for(int i=1; i<=n; ++i){
		for(int j=i; j>=1; --j){
			int res=N;
			for(int k=i; k>=j; --k){
				if(vld[k][i]) apn(res,dp[j][k-1]+1);
			}
			dp[j][i]=res;
		}
	}
	printf("%d\n",dp[1][n]);
	return 0;
}
