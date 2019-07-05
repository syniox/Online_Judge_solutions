#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;
int n;
char str[N];
bool wlf[N];

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

bool jdg(const int v1,const int v2){
	wlf[1]=v1,wlf[2]=v2;
	for(int i=3; i<=n; ++i){
		wlf[i]=wlf[i-2]^(wlf[i-1]^(str[i-1]=='x'));
	}
	if((wlf[n]^wlf[2])!=(wlf[1]^(str[1]=='x'))) return 0;
	if((wlf[1]^wlf[n-1])!=(wlf[n]^(str[n]=='x'))) return 0;
	return 1;
}

void oput(){
	for(int i=1; i<=n; ++i){
		putchar(wlf[i]?'W':'S');
	}
	puts("");
}

int main(){
	n=nxi();
	scanf("%s",str+1);
	if(jdg(0,0)) oput();
	else if(jdg(0,1)) oput();
	else if(jdg(1,0)) oput();
	else if(jdg(1,1)) oput();
	else puts("-1");
	return 0;
}
