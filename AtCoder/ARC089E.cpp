#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=101;
int qa,qb,qr[11][11],mp[N+1][N+1];

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

bool jdg(){
	for(int i=1; i<=qa; ++i){
		for(int j=1; j<=qb; ++j){
			int res=1e9;
			for(int k=1; k<=N; ++k){
				for(int l=1; l<=N; ++l){
					apn(res,(k-1)*i+(N-l)*j+mp[k][l]);
				}
			}
			assert(res>=qr[i][j]);
			if(res>qr[i][j]) return 0;
		}
	}
	return 1;
}

int main(){
	qa=nxi(),qb=nxi();
	for(int i=1; i<=qa; ++i){
		for(int j=1; j<=qb; ++j){
			const int v=qr[i][j]=nxi();
			for(int k=1; k<=N; ++k){
				for(int l=1; l<=N; ++l){
					apx(mp[k][l],v-i*(k-1)-j*(N-l));
				}
			}
		}
	}
	if(!jdg()){
		puts("Impossible");
		return 0;
	}
	puts("Possible");
	printf("%d %d\n",N<<1,N*N+2*(N-1));
	for(int i=1; i<N; ++i){
		printf("%d %d X\n",i,i+1);
		printf("%d %d Y\n",i+N,i+N+1);
	}
	for(int i=1; i<=N; ++i){
		for(int j=1; j<=N; ++j){
			printf("%d %d %d\n",i,j+N,mp[i][j]);
		}
	}
	printf("%d %d\n",1,N*2);
	return 0;
}
