#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
int n,sum;
bool vld[(int)1e4+5];

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
	vld[0]=1;
	for(int i=nxi(); i; --i){
		int x=nxi();
		for(int j=sum; ~j; --j){
			vld[j+x]|=vld[j];
		}
		sum+=x;
	}
	int ans=sum;
	while(ans>0&&(ans%10==0||!vld[ans])) --ans;
	printf("%d\n",ans);
	return 0;
}
