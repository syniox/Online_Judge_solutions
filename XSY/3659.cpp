#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1005;
int lg2[N];

namespace utils{
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
	for(int i=2; i<N; ++i){
		lg2[i]=lg2[i>>1]+1;
	}
	int n=nxi(),ub=lg2[n]+1-(n==(n&-n));
	if(n<=2){
		printf("%d\n",1-n);
		return 0;
	}
	if(n&1){
		printf("%d\n",ub);
		for(int i=0; 1<<i<n; ++i){
			for(int j=1; j<=n; ++j){
				printf("%d ",(j+(1<<i)-1)%n+1);
			}
			puts("");
		}
	}
	else{
		printf("%d\n",ub+((n&3)==2));
		if((n&3)==2){
			printf("%d %d ",n-1,1);
			for(int i=3; i<=n-2; ++i){
				printf("%d ",i);
			}
			printf("%d %d\n",n,2);
		}
		for(int i=1; i+3<=n; i+=4){
			printf("%d %d %d %d ",i+2,i,i+3,i+1);
		}
		if((n&3)==2) printf("%d %d\n",n-1,n);
		else puts("");
		for(int i=1; i<<1<n; i<<=1){
			for(int j=1; j<=n; ++j){
				printf("%d ",(j+i-1)%n+1);
			}
			puts("");
		}
	}
	return 0;
}
