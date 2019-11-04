#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=55;
int n,val[N],mx,mn;

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
	mn=mx=1;
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		if(val[mx]<val[i]) mx=i;
		if(val[mn]>val[i]) mn=i;
	}
	if(val[mx]>0&&val[mn]<0){
		printf("%d\n",n*2-2);
		if(val[mx]>-val[mn]){
			for(int i=1; i<=n; ++i){
				if(i!=mx) printf("%d %d\n",mx,i);
			}
		}
		else{
			for(int i=1; i<=n; ++i){
				if(i!=mn) printf("%d %d\n",mn,i);
			}
			val[mx]=-1;
		}
	}
	else printf("%d\n",n-1);
	if(val[mx]>0){
		for(int i=2; i<=n; ++i){
			printf("%d %d\n",i-1,i);
		}
	}
	else{
		for(int i=n-1; i; --i){
			printf("%d %d\n",i+1,i);
		}
	}
	return 0;
}
