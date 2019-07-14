#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=55;
const int mod=1e9+7;
int n;
char str[2][N];

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

int main(){
	n=nxi();
	scanf("%s%s",str[0]+1,str[1]+1);
	int s0,s1;
	if(str[0][1]!=str[1][1]) s0=0,s1=6;
	else s0=3,s1=0; 
	for(int i=2+(str[0][1]!=str[1][1]); i<=n; ++i){
		if(str[0][i]!=str[1][i]){
			s1=(s0*2ll+s1*3ll)%mod;
			s0=0;
			++i;
		}
		else{
			s0=(s1+s0*2ll)%mod;
			s1=0;
		}
	}
	printf("%d\n",s0+s1);
	return 0;
}
