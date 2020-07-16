#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
using namespace std;
const int N=2e5+5;
int n,val[N],buk[N];

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

namespace D{
	int cnt,v[N];
	inline void add(const int x){
		v[++cnt]=x;
	}
	inline void build(){
		sort(v+1,v+cnt+1);
		cnt=unique(v+1,v+cnt+1)-v-1;
	}
	inline int ask(const int x){
		return lower_bound(v+1,v+cnt+1,x)-v;
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		D::add(val[i]);
	}
	D::build();
	for(int i=1; i<=n; ++i){
		++buk[D::ask(val[i])];
	}
	sort(buk+1,buk+D::cnt+1);
	int ans=0;
	for(int i=1; i<=n; ++i){
		int res=0;
		for(int pos=0,ap=i; ; ap*=2){
			pos=lower_bound(buk+pos+1,buk+D::cnt+1,ap)-buk;
			if(pos>D::cnt) break;
			res+=ap;
		}
		apx(ans,res);
	}
	printf("%d\n",ans);
	return 0;
}
