#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;
int n,cnt,pos[N];
char str[N];

namespace utils{
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
	scanf("%s",str+1);
	n=strlen(str+1);
	str[n+1]='0';
	int ans=n;
	for(int i=1; i<=n+1; ++i){
		if(str[i]!=str[i-1]){
			apn(ans,std::max(i-1,n+1-i));
		}
	}
	printf("%d\n",ans);
	return 0;
}
