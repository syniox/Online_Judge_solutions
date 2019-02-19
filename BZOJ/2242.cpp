#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <cmath>
typedef long long lint;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int fpow(int x,int t,const int mod){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline void sol1(int T){
	while(T--){
		const int y=nxi(),z=nxi(),p=nxi();
		printf("%d\n",fpow(y,z,p));
	}
}

inline void sol2(int T){
	while(T--){
		int y=nxi(),z=nxi();
		const int p=nxi();
		y%=p,z%=p;
		if(!y&&z) puts("Orz, I cannot find x!");
		else printf("%lld\n",(lint)fpow(y,p-2,p)*z%p);
	}
}

inline void sol3(int T){
	std::map <int,int> mp;
	while(T--){
		int y=nxi(),z=nxi();
		const int p=nxi();
		y%=p,z%=p;
		if((y&&!z)||(!y&&z>1)||(y==1&&z!=1)){
			puts("Orz, I cannot find x!");
			continue;
		}
		mp.clear();
		const int limit=sqrt(p);
		for(int j=1,i=0; i<limit; ++i,j=(lint)j*y%p){
			mp[j]=i;
		}
		const int jmp=fpow(fpow(y,limit,p),p-2,p);
		bool flag=0;
		for(int j=1,i=0; i*limit<p-1; ++i,j=(lint)j*jmp%p){
			std::map <int,int> ::iterator it=mp.find((lint)z*j%p);
			if(it!=mp.end()){
				printf("%d\n",i*limit+it->second);
				flag=1;
				break;
			}
		}
		if(!flag){
			puts("Orz, I cannot find x!");
		}
	}
}

int main(){
	int T=nxi(),q=nxi();
	switch(q){
		case 1:
			sol1(T);
			break;
		case 2:
			sol2(T);
			break;
		case 3:
			sol3(T);
			break;
	}
	return 0;
}
