#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;
lint n,rep[N],tot_m,tot_f;
int m,len[N];
char *str[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline lint nxi(){
		lint x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=m; ++i){
		static char tmp[N*2];
		scanf("%s",tmp);
		len[i]=strlen(tmp);
		str[i]=new char[len[i]];
		memcpy(str[i],tmp,len[i]);
		rep[i]=nxi();
		int cm=0,cf=0;
		for(int j=0; j<len[i]; ++j){
			if(tmp[j]=='M') ++cm;
			else ++cf;
		}
		tot_m+=cm*rep[i];
		tot_f+=cf*rep[i];
	}
	if(tot_m>tot_f){
		puts("-1");
		return 0;
	}
	lint sum=0,ans=0;
	for(int i=m; i>=1; --i){
		int ns=0,s=0;
		for(int j=len[i]-1; ~j; --j){
			s+=str[i][j]=='F'?1:-1;
			apn(ns,s);
		}
		lint ts=s>=0?ns:s*(rep[i]-1)+ns;
		if(sum+ts>=-1) sum+=s*rep[i];
		else{
			ans+=-1-(sum+ts);
			sum+=s*rep[i]+(-1-(sum+ts));
		}
	}
	printf("%lld\n",ans);
	return 0;
}
