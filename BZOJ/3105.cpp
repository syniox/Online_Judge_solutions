#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long lint;
const int N=105;
int val[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace S{
	const int P=31;
	int buk[P];
	
	inline bool insert(int x){
		for(int i=P-1; ~i; --i){
			if(x>>i&1){
				if(buk[i]) x^=i;
				else{
					buk[i]=x;
					return 1;
				}
			}
		}
		return 0;
	}
}

int main(){
	int n=nxi();
	for(int i=1; i<=n; ++i) val[i]=nxi();
	std::sort(val+1,val+n+1);
	lint ans=0;
	for(int i=n; i; --i){
		if(!S::insert(val[i])) ans+=val[i];
	}
	printf("%lld\n",ans);
	return 0;
}
