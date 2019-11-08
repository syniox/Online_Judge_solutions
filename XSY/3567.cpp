#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1005;
int n,m,qn,qm,lik[N][N];

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
	for(int T=1; n=nxi(),m=nxi(),n&&m; ++T){
		static bool vis[N];
		static int lst[N];
		memset(lst+1,0,n*sizeof(lst[0]));
		memset(vis+1,0,m*sizeof(vis[0]));
		printf("Case #%d: Katya's place can be ",T);
		qn=nxi(),qm=nxi();
		for(int i=1; i<=n; ++i){
			for(int j=1; j<=m; ++j){
				lik[i][j]=nxi();
			}
		}
		if(n==1){
			puts("1.");
			continue;
		}
		for(int i=1,j=0,k=0; ; i=i%n+1){
			if(i==qn){
				if(j+(++k)>=m-1){
					puts("1.");
					break;
				}
				continue;
			}
			for(++lst[i]; vis[lik[i][lst[i]]]; ++lst[i]);
			assert(lst[i]<=m);
			if(lik[i][lst[i]]==qm){
				printf("%d.\n",m-j-k);
				break;
			}
			else if(++j+k>=m-1){
				puts("1.");
				break;
			}
			vis[lik[i][lst[i]]]=1;
		}
	}
	return 0;
}
