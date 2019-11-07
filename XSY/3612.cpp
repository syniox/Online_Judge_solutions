#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e6+5;
int n,ans,val[N],req[N],cnt[N];

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

void solve(const int l,const int r,int *cnt){
	int p=0,len=r-l+1;
	for(int i=0; l+i<=r-i; ++i){
		if(cnt[val[l+i]]<req[len]){
			p=l+i;
			break;
		}
		if(cnt[val[r-i]]<req[len]){
			p=r-i;
			break;
		}
	}
	if(!p){
		apx(ans,len);
		for(int i=l; i<=r; ++i){
			--cnt[val[i]];
		}
		return;
	}
	if(p-l<=r-p){
		for(int i=l; i<=p; ++i){
			--cnt[val[i]];
		}
		solve(p+1,r,cnt);
		if(p==l) return;
		for(int i=l; i<p; ++i){
			++cnt[val[i]];
		}
		solve(l,p-1,cnt);
	}
	else{
		for(int i=p; i<=r; ++i){
			--cnt[val[i]];
		}
		solve(l,p-1,cnt);
		if(p==r) return;
		for(int i=r; i>p; --i){
			++cnt[val[i]];
		}
		solve(p+1,r,cnt);
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	for(int i=1; i<=n; ++i){
		req[i]=nxi();
	}
	for(int i=1; i<=n; ++i){
		++cnt[val[i]];
	}
	solve(1,n,cnt);
	printf("%d\n",ans);
	return 0;
}
