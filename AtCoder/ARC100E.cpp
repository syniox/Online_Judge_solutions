#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
using namespace std;
const int N=18;
int n,xval[1<<N][2];

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

void apl(int x[2],int v){
	if(x[0]<v) swap(x[0],v);
	if(x[1]<v) swap(x[1],v);
}

int main(){
	n=nxi();
	for(int i=0; i<1<<n; ++i){
		xval[i][0]=nxi();
	}
	for(int i=1; i<1<<n; i<<=1){
		for(int j=0; j<1<<n; j+=i<<1){
			for(int k=0; k<i; ++k){
				apl(xval[j+k+i],xval[j+k][0]);
				apl(xval[j+k+i],xval[j+k][1]);
			}
		}
	}
	int res=0;
	for(int i=1; i<1<<n; ++i){
		apx(res,xval[i][0]+xval[i][1]);
		printf("%d\n",res);
	}
	return 0;
}
