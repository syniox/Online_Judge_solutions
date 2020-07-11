#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long lint;
const int N=2e5,W=24;
int n;//最高位，非个数
lint val[N*30/W];
char str[(int)2e5+5];

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
	scanf("%s",str);
	for(int i=strlen(str)-1,j=0; ~i; --i,++j){
		if(j==W) ++n,j=0;
		val[n]|=(str[i]-'0')<<j;
	}
	int ans=0;
	for(int i=0; i<n; ++i){
		static const int all=(1<<W)-1;
		lint pw3=1,sum=0;
		for(lint x=val[i]; x; ++ans){
			x=x*3+(x&-x);
			pw3*=3;
			sum=sum*3+(x>>W);
			x&=all;
		}
		ans+=W;
		int m=i+1;
		for(; m<=n||sum; ++m){
			sum+=pw3*val[m];
			val[m]=sum&all;
			sum>>=W;
		}
		apx(n,m-1);
	}
	for(; val[n]!=1; ++ans){
		if(val[n]&1) val[n]=val[n]*3+1;
		else val[n]>>=1;
	}
	printf("%d\n",ans);
	return 0;
}
