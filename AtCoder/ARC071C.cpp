#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;

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
	static int buk[26];
	memset(buk,10,sizeof(buk));
	for(int i=nxi(); i; --i){
		static char str[51];
		static int tmp[26];
		memset(tmp,0,sizeof(tmp));
		scanf("%s",str);
		for(int j=strlen(str)-1; j>=0; --j){
			++tmp[str[j]-'a'];
		}
		for(int j=0; j<26; ++j){
			apn(buk[j],tmp[j]);
		}
	}
	for(int i=0; i<26; ++i){
		for(int j=0; j<buk[i]; ++j){
			putchar('a'+i);
		}
	}
	puts("");
	return 0;
}
