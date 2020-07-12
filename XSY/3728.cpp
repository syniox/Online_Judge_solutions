#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long lint;
const int N=1e6+5;
int n,m;
char str[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
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

namespace S{
	int cnt;
	struct node{
		int lk,c[26];
		lint s,dp;
	}tr[N<<1];

	void add(const char *str,const int len,const int v){
		int p=0;
		for(int i=1; i<=len; ++i){
			int &k=tr[p].c[str[i]-'a'];
			p=k?k:k=++cnt;
		}
		tr[p].s+=v;
	}
	void build(){
		static int que[N<<1];
		int hd=0,tl=1;
		while(hd!=tl){
			int x=que[hd++],lk=tr[x].lk;
			for(int i=0; i<26; ++i){
				int &y=tr[x].c[i];
				if(!y) continue;
				lint res=tr[x].dp;
				int j=lk;
				for(; j&&!tr[j].c[i]; j=tr[j].lk){
					apx(res,tr[j].dp);
				}
				if(x!=j){
					tr[y].s+=tr[tr[j].c[i]].s;
					tr[y].lk=tr[j].c[i];
					res+=tr[tr[j].c[i]].s;
				}
				tr[y].dp=res;
				que[tl++]=y;
			}
		}
		hd=0,tl=1;
		while(hd!=tl){
			int x=que[hd++],lk=tr[x].lk;
			apx(tr[x].dp,tr[lk].dp);
			for(int i=0; i<26; ++i){
				int &y=tr[x].c[i];
				if(!y) y=tr[lk].c[i];
				else que[tl++]=y;
			}
		}
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		scanf("%s",str+1);
		int len=strlen(str+1);
		S::add(str,len,nxi());
	}
	scanf("%s",str+1);
	S::add(str,m,0);
	S::build();
	lint ans=0,res=0;
	for(int p=0,i=1; i<=m; ++i){
		using S::tr;
		p=tr[p].c[str[i]-'a'];
		res+=tr[p].s;
		apx(ans,std::max(tr[p].dp,res));
	}
	printf("%lld\n",ans);
	return 0;
}
