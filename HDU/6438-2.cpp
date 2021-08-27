#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
using lint=long long;

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<=y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>=y?x:y;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
	static struct{
		template <class T> operator T(){
			T x=0;
			char c;
			while(((c=getchar())>'9'||c<'0')&&c!='-');
			const bool f=c=='-'&&(c=getchar());
			while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
			return f?-x:x;
		}
	}ni;
}
using namespace utils;

int main(){
	for(int T=ni; T--; ){
		priority_queue<int> qa,qb;
		lint res=0;
		int cnt=0;
		for(int n=ni; n--; ){
			int v=ni;
			int a=qa.empty()?2e9:-qa.top();
			int b=qb.empty()?2e9:-qb.top();
			if(a<b&&v>a){
				cnt+=2;
				res+=v-a;
				qa.pop();
				qb.push(-v);
			}else if(b<=a&&v>b){
				res+=v-b;
				qb.pop();
				qa.push(-b);
				qb.push(-v);
			}else{
				qa.push(-v);
			}
		}
		printf("%lld %d\n",res,cnt);
	}
	return 0;
}
