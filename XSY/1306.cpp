#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <map>
#include <vector>
typedef long long lint;
using namespace std;
const int N=1e5+5;
int n,ans1,ans2;
lint q,val[N],xv[N];
map<lint,vector<int> > mp;

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline lint nxi(){
		lint x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

lint gcd(const lint x,const lint y){
	return y?gcd(y,x%y):x;
}

void san(int *q,lint *g,int &n,const lint v){
	int cnt=0;
	for(int i=1; i<=n; ++i){
		if(i==1||gcd(g[i],v)!=g[cnt])
			q[++cnt]=q[i],g[cnt]=gcd(g[i],v);
	}
	n=cnt;
}

void solve(){
	static int blk[N];
	static lint gb[N];
	int cnt=0;
	ans1=1e9;
	for(int i=1; i<=n; ++i){
		blk[++cnt]=i,gb[cnt]=val[i];
		san(blk,gb,cnt,val[i]);
		blk[cnt+1]=i+1;
		for(int j=1; j<=cnt; ++j){
			if(q%gb[j]) break;
			map<lint,vector<int> >::iterator it=mp.find(q/gb[j]^xv[i]);
			if(it==mp.end()) continue;
			vector<int>::iterator pos=lower_bound(it->second.begin(),it->second.end(),blk[j]-1);
			if(pos!=it->second.end()&&*pos+1<blk[j+1]&&*pos+1<ans1){
				ans1=*pos+1,ans2=i;
			}
		}
	}
}

signed main(){
	n=nxi();
	mp[0].push_back(0);
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		xv[i]=xv[i-1]^val[i];
		mp[xv[i]].push_back(i);
	}
	q=nxi();
	for(map<lint,vector<int> >::iterator it=mp.begin(); it!=mp.end(); ++it){
		sort(it->second.begin(),it->second.end());
	}
	solve();
	if(ans1==1e9) puts("no solution");
	else printf("%d %d\n",ans1,ans2);
	return 0;
}
