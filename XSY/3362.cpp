#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <queue>
#include <map>
typedef long long lint;
const int N=1e5+5;
int n,val[N],c[2],ans[N];

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

void get_side(const bool v,const bool f,int *ans){
	//v=1: 搞奇下标 f=0: 奇数配奇下标
	for(int s,j,i=1; i<=n; i=j+1){
		for(s=0,j=i; s+=((j&1)==v)-((val[j]&1)==(v^f)); ){
			++j;
		}
		if(i==j){
			if((i&1)==v) ans[i]=val[i];
			continue;
		}
		std::priority_queue <int> pq;
		assert(!((i&1)==v)||!((val[i]&1)==(v^f)));
		if(((val[i]&1)==(v^f))){
			for(int k=i; k<=j; ++k){
				if((val[k]&1)==(v^f)) pq.push(-val[k]);
				if((k&1)==v){
					assert(!pq.empty());
					ans[k]=-pq.top();
					pq.pop();
				}
			}
		}
		else{
			for(int k=j; k>=i; --k){
				if((val[k]&1)==(v^f)) pq.push(val[k]);
				if((k&1)==v){
					assert(!pq.empty());
					ans[k]=pq.top();
					pq.pop();
				}
			}
		}
	}
}

int solve(const bool f,int *ans){
	get_side(1,f,ans);
	get_side(0,f,ans);
	std::map <int,int> pos;
	int res=0;
	for(int i=1; i<=n; ++i){
		pos[ans[i]]=i;
	}
	for(int i=1; i<=n; ++i){
		int p=pos[val[i]];
		res+=std::max(i-p,p-i);
	}
	return res;
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		++c[val[i]&1];
	}
	if(n&1){
		solve(c[0]>c[1],ans);
	}
	else{
		static int a0[N],a1[N];
		int res0=solve(0,a0),res1=solve(1,a1);
		if(res1!=res0){
			memcpy(ans,res0<res1?a0:a1,(n+1)*sizeof(int));
		}
		else{
			assert(a0[1]!=a1[1]);
			memcpy(ans,a0[1]<a1[1]?a0:a1,(n+1)*sizeof(int));
		}
	}
	for(int i=1; i<=n; ++i){
		printf("%d ",ans[i]);
	}
	puts("");
	return 0;
}
