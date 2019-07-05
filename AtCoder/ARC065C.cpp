#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <string>
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
	std::string ra="maerd",rb="remaerd",rc="esare",rd="resare";
	std::string s,t;
	std::cin>>s;
	for(int i=s.size()-1; ~i; --i){
		t+=s[i];
		if(t==ra||t==rb||t==rc||t==rd) t="";
	}
	puts(t.size()?"NO":"YES");
	return 0;
}
