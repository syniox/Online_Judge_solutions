#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
typedef long long lint;
const int N=1005;
int n,val[N];
bool use[N];

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
	std::vector <int> step;
	n=nxi();
	{
		lint v[2]={0};
		bool all_neg=1;
		int xpos=1;
		for(int i=1; i<=n; ++i){
			val[i]=nxi();
			if(val[i]>0) v[i&1]+=val[i];
			all_neg&=val[i]<0;
			if(val[xpos]<val[i]) xpos=i;
		}
		bool p=v[1]>v[0];
		printf("%lld\n",all_neg?(lint)val[xpos]:v[p]);
		for(int i=1; i<=n; ++i){
			use[i]=(i&1)==p&&val[i]>=0;
		}
		if(all_neg) use[xpos]=1;
	}
	while(n>1){
		int x=n;
		for(; x&&(use[x]||(x!=1&&x!=n&&use[x-1]!=use[x+1])); --x);
		assert(x);
		step.push_back(x);
		if(x==1||x==n){
			n-=1;
			for(int i=x; i<=n; ++i) use[i]=use[i+1];
		}
		else{
			n-=2;
			for(int i=x; i<=n; ++i) use[i]=use[i+2];
		}
	}
	printf("%d\n",(int)step.size());
	for(std::vector <int> ::iterator it=step.begin(); it!=step.end(); ++it){
		printf("%d\n",*it);
	}
	return 0;
}
