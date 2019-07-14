#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=2e5+5;
int n,nxt[N],len[N],ed[N];
char str[N];

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
	static int tr[26];
	scanf("%s",str+1);
	n=strlen(str+1);
	for(int i=0; i<26; ++i)
		tr[i]=n+1;
	for(int i=n; i>=0; --i){
		int nlen=n+2,nc=0;
		for(int j=0; j<26; ++j){
			if(len[tr[j]]<nlen){
				nlen=len[tr[j]],nc=j;
			}
		}
		len[i]=nlen+1;
		ed[i]=nc;
		nxt[i]=tr[nc];
		if(i){
			tr[str[i]-'a']=i;
		}
	}
	for(int i=0; i<=n; i=nxt[i]){
		putchar(ed[i]+'a');
	}
	puts("");
	return 0;
}
