#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e6+5;
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
	int n=nxi(),s=0,ans=0;
	scanf("%s",str+1);
	for(int lst,i=1; i<=n; ++i){
		if(str[i]=='('&&++s==0){
			ans+=i-lst+1;
		}
		if(str[i]==')'&&s--==0){
			lst=i;
		}
	}
	printf("%d\n",s?-1:ans);
	return 0;
}
