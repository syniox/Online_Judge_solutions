#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e6+5;

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
const int mod=nxi();

struct data{
	static int idx[N];
	int st,x,y,tgt;
	inline void read(){
		st=nxi(),tgt=nxi(),x=nxi(),y=nxi();
	}
	bool solve(int &tot,int &p,int &add){
		memset(idx,0,(mod+1)*sizeof(idx[0]));
		tot=p=0;
		for(int i=st,tp; !idx[i]; i=tp){
			//printf("%d ",i);
			idx[i]=++tot;
			if(i==tgt) p=tot;
			if(idx[tp=((lint)i*x+y)%mod]){
				add=idx[tp];
				tot-=idx[tp]-1;
				break;
			}
		}
		//puts("");
		return (bool)p;
	}
}d1,d2;
int data::idx[N];

int gcd(const int x,const int y){
	return y?gcd(y,x%y):x;
}

int main(){
	int tot1,p1,add1,tot2,p2,add2;
	d1.read();
	d2.read();
	if(!d1.solve(tot1,p1,add1)||!d2.solve(tot2,p2,add2)){
		puts("-1");
		return 0;
	}
	if(p1<add1&&p2<add2){
		printf("%d\n",p1==p2?p1-1:-1);
		return 0;
	}
	if(p1<add1||p2<add2){
		if(p1<add1){
			std::swap(p1,p2);
			std::swap(tot1,tot2);
		}
		lint ans=p1;
		while(ans<p2) ans+=tot1;
		printf("%lld\n",ans==p2?ans-1:-1);
		return 0;
	}
	if((p1-p2)%gcd(tot1,tot2)){
		puts("-1");
		return 0;
	}
	lint ans=p1;
	for(; ans%tot2!=p2%tot2||(ans<p2); ans+=tot1);
	printf("%lld\n",ans-1);
	return 0;
}
