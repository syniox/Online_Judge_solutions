#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
typedef long long lint;
const int N=2005;
int n,m;
char mp[N][N];

namespace utils{
	template <class T> inline void apx(T &x,const T y){
		x<y?x=y:0;
	}
	template <class T> inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

template <class T>
class mque{
	protected:
		T que[N];
		int hd,tl;
	public:
		mque():hd(0),tl(0){}
		inline T front(){
			return que[hd];
		}
		inline void pop(){
			++hd;
		}
		inline void push(const T &v){
			que[tl++]=v;
		}
};
mque <int> lim[N];

int solve(const int st){
	static int buk[N],stk[N];
	for(int i=1; i<m; ++i){
		while(lim[i].front()<=st) lim[i].pop();
		buk[i]=lim[i].front();
	}
	buk[m]=st-1;
	int ans=0,top=0;
	for(int i=1; i<=m; ++i){
		for(; top&&buk[stk[top]]>buk[i]; --top){
			apx(ans,(i-stk[top-1])*(buk[stk[top]]-st));
		}
		stk[++top]=i;
	}
	return ans;
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		assert(scanf("%s",mp[i]+1)==1);
	}
	for(int i=1; i<n; ++i){
		for(int j=1; j<m; ++j){
			if((mp[i][j]==mp[i][j+1])!=(mp[i+1][j]==mp[i+1][j+1])){
				lim[j].push(i+1);
			}
		}
	}
	for(int j=1; j<=m; ++j){
		lim[j].push(n+1);
	}
	int ans=0;
	for(int i=1; i<=n; ++i){
		apx(ans,solve(i));
	}
	printf("%d\n",std::max(std::max(n,m),ans));
	return 0;
}
