#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long lint;
const int N=3005;
int n,pos[2][N],nx[N*2],id[N*2];
string str,dp[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

int main(){
	cin>>n>>str;
	assert((int)str.length()==n*2);
	for(int i=0,c[2]={0}; i<n*2; ++i){
		const int f=str[i]-'a';
		pos[f][++c[f]]=i,id[i]=c[f];
	}
	pos[0][n+1]=pos[1][n+1]=n*2+1,id[n*2+1]=n+1;
	for(int i=1,j=0; i<=n+1; ++i){
		for(; j<=n*2&&pos[0][i]>=j&&pos[1][i]>=j; ++j)
			nx[j]=i;
	}
	for(int i=n; i; --i){
		if(pos[0][i]<pos[1][i])
			dp[i]="ab"+dp[nx[pos[1][i]+1]];
		else{
			int j=pos[1][i];
			for(; id[j]<=i||pos[1][id[j]]<=pos[0][id[j]-1]; ++j){
				if(id[j]>=i) dp[i]+=str[j];
			}
			dp[i]+=dp[nx[j]];
		}
		apx(dp[i],dp[i+1]);
	}
	cout<<dp[1]<<endl;
	return 0;
}
