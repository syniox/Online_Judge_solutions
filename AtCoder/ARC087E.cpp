#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;
int n;
lint q;

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline lint nxi(){
		lint x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

namespace S{
	int cnt,tr[N][2];
	lint ans;

	void insert(const char *str,const int len){
		int p=0;
		for(int i=1; i<=len; ++i){
			int &c=tr[p][str[i]-'0'];
			if(!c) c=++cnt;
			p=c;
		}
	}

	void dfs_sg(const int x,const int dep){
		if((bool)tr[x][0]^(bool)tr[x][1]){
			ans^=(q-dep+1)&-(q-dep+1);
		}
		if(tr[x][0]) dfs_sg(tr[x][0],dep+1);
		if(tr[x][1]) dfs_sg(tr[x][1],dep+1);
	}

	bool get_sg(){
		dfs_sg(0,1);
		return (bool)ans;
	}
}

int main(){
	n=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		static char str[N];
		scanf("%s",str+1);
		int l=strlen(str+1);
		S::insert(str,l);
	}
	puts(S::get_sg()?"Alice":"Bob");
	return 0;
}
