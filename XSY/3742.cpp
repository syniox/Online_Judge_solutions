#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
using namespace std;
const int N=3050;
int n,m,cbit[1<<14],val[N],lg2[1<<14];
char str[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
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
	n=nxi(),m=min(14,nxi());
	for(int i=1,j=1; j<=n; ++i){
		cbit[i]=cbit[i>>1]+(i&1);
		if(cbit[i]==m>>1) val[j++]=i;
	}
	for(int i=1; i<14; ++i){
		lg2[1<<i]=i;
	}
	for(int i=2; i<=n; ++i){
		scanf("%s",str+1);
		for(int j=1; j<i; ++j){
			bool f=str[j]-'0';
			int dis=(val[i]^val[j])&(f?val[i]:val[j]);
			putchar(lg2[dis&-dis]+'a');
		}
		puts("");
	}
	return 0;
}
