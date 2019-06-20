#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
typedef long long lint;
const int N=1e7+5;
lint phi[N];

namespace utils{
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	inline lint nxi(FILE *fd=stdin){
		lint x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

void init(const int n){
	static int prm[N];
	static bool npr[N];
	int cnp=0;
	phi[1]=1;
	for(int i=2; i<=n; ++i){
		if(!npr[i]){
			prm[++cnp]=i;
			phi[i]=i-1;
		}
		for(int j=1; j<=cnp&&i*prm[j]<=n; ++j){
			npr[i*prm[j]]=1;
			if(i%prm[j]==0){
				phi[i*prm[j]]=phi[i]*prm[j];
				break;
			}
			phi[i*prm[j]]=phi[i]*(prm[j]-1);
		}
	}
	for(int i=2; i<=n; ++i){
		phi[i]=phi[i-1]+phi[i];
	}
}

int main(){
	lint n=nxi();
	init(sqrt(n));
	lint ans=0;
	for(lint i=1,j; i<=n; i=j+1){
		lint t=sqrt(n/i);
		j=n/(t*t);
		ans+=(phi[t]*2-1)*(j-i+1);
	}
	printf("%lld\n",ans);
	return 0;
}
