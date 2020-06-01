#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <string>
typedef long long lint;
const int N=1e5+5;
int ls,lt,nxt[N],f[N],g[N];
char ps[N],pt[N];

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

void get_nxt(char *s,int n){
	for(int j=0,i=2; i<=n; ++i){
		while(j&&s[i]!=s[j+1]) j=nxt[j];
		if(s[i]==s[j+1]) ++j;
		nxt[i]=j;
	}
}

bool check(const int p){
	if(p<lt) return 0;
	for(int i=p-lt+1,j=1; i<=p; ++i,++j){
		if(ps[i]!='?'&&ps[i]!=pt[j]) return 0;
	}
	return 1;
}

int main(){
	scanf("%s%s",ps+1,pt+1);
	ls=strlen(ps+1);
	lt=strlen(pt+1);
	get_nxt(pt,lt);
	memset(g,-1,(ls+1)*sizeof(int));
	f[0]=0;
	for(int i=1; i<=ls; ++i){
		f[i]=f[i-1];
		if(!check(i)) continue;
		apx(g[i],f[i-lt]+1);
		for(int j=nxt[lt]; j; j=nxt[j]){
			if(~g[i-lt+j]) apx(g[i],g[i-lt+j]+1);
		}
		apx(f[i],g[i]);
	}
	printf("%d\n",f[ls]);
	return 0;
}
