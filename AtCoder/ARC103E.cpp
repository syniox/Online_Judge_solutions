#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
using lint=long long;

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<=y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>=y?x:y;}
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

int main(){
	string str;
	cin>>str;
	int n=str.length(),invld=0;
	invld=str[n-1]=='1'||str[0]=='0';
	for(int i=2; i<=n-i&&!invld; ++i){
		invld|=str[i-1]!=str[n-i-1];
	}
	if(invld){
		puts("-1");
		return 0;
	}
	for(int cc=1,i=2; i<=n; ++i){
		printf("%d %d\n",cc,i);
		if(str[i-2]=='1') cc=i;
	}
	return 0;
}
