#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
using namespace std;

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<=y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>=y?x:y;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
	struct{
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

struct edge{
	int x,y,w;
};

int lbit(int x){
	int ans=0;
	for(int i=16; i; i>>=1){
		if(x>>i) x>>=i,ans+=i;
	}
	return ans;
}

int main(){
	int l=ni,n=20;
	l--;
	vector<edge> eg;
	for(int i=1; i<n; ++i){
		eg.push_back({i,i+1,0});
	}
	int cmax=0;
	for(int &i=cmax; l>=(1<<(i+1))-1; ++i){
		eg.push_back({n-i-1,n-i,1<<i});
	}
	cmax=(1<<cmax)-1;
	while(cmax!=l){
		int p=lbit(l-cmax);
		eg.push_back({1,n-p,cmax+1});
		cmax+=1<<p;
	}
	printf("%d %d\n",n,(int)eg.size());
	for(edge e:eg){
		printf("%d %d %d\n",e.x,e.y,e.w);
	}
	return 0;
}
