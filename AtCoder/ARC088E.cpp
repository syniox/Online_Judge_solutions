#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
typedef long long lint;
const int N=2e5+5;
int n,lnk[N];
char str[N];
std::vector <int> cbuk[26];

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

namespace B{
	int tr[N];
	inline void add(int x,const int v){
		for(; x<=n; x+=x&-x) tr[x]+=v;
	}
	inline int ask(int x){
		int ans=0;
		for(; x; x-=x&-x) ans+=tr[x];
		return ans;
	}
}

lint solve(){
	for(int cnt=0,i=0; i<26; ++i){
		if(cbuk[i].size()&1){
			if(cnt++) return -1;
		}
		const int sz=cbuk[i].size();
		for(int j=0; j<<1<sz; ++j){
			lnk[cbuk[i][j]]=cbuk[i][sz-1-j];
		}
	}
	lint ans=0;
	for(int cnt=0,i=1; i<=n; ++i){
		//i+B::ask(i)意义不明
		if(lnk[i]==i&&cnt<n>>1){
			++lnk[i];
			std::swap(lnk[i+1],lnk[i]);
			if(lnk[i]) ++ans;
		}
		if(!lnk[i]||lnk[i]==i) continue;
		++cnt;
		int lp=i+B::ask(i),rp=lnk[i]+B::ask(lnk[i]);
		int tgt=n-lp+1;
		assert(rp<=tgt);
		B::add(lnk[i],-1);
		ans+=tgt-rp;
	}
	return ans;
}

int main(){
	scanf("%s",str+1);
	n=strlen(str+1);
	for(int i=1; i<=n; ++i){
		cbuk[str[i]-'a'].push_back(i);
	}
	printf("%lld\n",solve());
	return 0;
}
