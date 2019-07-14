#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;
int n,m,sz[N*3],rm_c[N*3];
lint rm_d[N*3];

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

void add(const int fr,const int to){
	++sz[fr+1];
	++rm_c[to];
	rm_d[to]+=to-fr-1;
}

int main(){
	m=nxi(),n=nxi();
	lint tot=0,ans=1e15;
	for(int lst=nxi(),cur=0,i=2; i<=m; ++i,lst=cur){
		cur=nxi();
		if(lst<cur){
			add(lst+n,cur+n);
			tot+=cur-lst;
		}
		else{
			add(lst,cur+n);
			add(lst+n,cur+(n<<1));
			tot+=cur+n-lst;
		}
	}
	for(int i=1,s=0; i<=n*2; ++i){
		tot-=s;
		tot+=rm_d[i-1];
		s+=sz[i]-rm_c[i];
		apn(ans,tot);
	}
	printf("%lld\n",ans);
	return 0;
}
