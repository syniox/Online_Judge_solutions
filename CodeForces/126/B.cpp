#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e6+5;
int n,nxt[N],psum[N];
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
	for(int j=0,i=2; i<=n; ++i){
		while(j&&str[j+1]!=str[i]) j=nxt[j];
		nxt[i]=j+=str[j+1]==str[i];
		++psum[nxt[i]];
	}
	for(int i=n; i; --i){
		psum[nxt[i]]+=psum[i];
	}
	for(int i=n; i; i=nxt[i]){
		if(psum[i]>1){
			str[i+1]='\0';
			printf("%s\n",str+1);
			return 0;
		}
	}
	puts("Just a legend");
	return 0;
}
