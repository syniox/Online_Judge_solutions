#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
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

//RULD
const int cx[]={1,0,-1,0},cy[]={0,1,0,-1};
const char cc[]={'R','U','L','D'};

int get_dr(const int x,const int y){
	if(cabs(x)>cabs(y)) return x>0?0:2;
	return y>0?1:3;
}

int main(){
	int n=ni;
	vector<pair<int,int>> vt;
	vector<int> vl;
	int d;
	for(int i=1; i<=n; ++i){
		int a=ni,b=ni;
		vt.push_back({a,b});
		if(i==1) d=(a&1)^(b&1);
		else if(((a&1)^(b&1))!=d){
			puts("-1");
			return 0;
		}
	}
	for(int i=30; i>=0; --i){
		vl.push_back(1ll<<i);
	}
	if((d&1)==0) vl.push_back(1);
	printf("%d\n",(int)vl.size());
	for(int l:vl) printf("%d ",l);
	puts("");
	for(auto pr:vt){
		int tx=pr.first,ty=pr.second,x=0,y=0;
		for(int l:vl){
			int dr=get_dr(tx-x,ty-y);
			x+=cx[dr]*l,y+=cy[dr]*l;
			putchar(cc[dr]);
		}
		puts("");
		assert(x==tx&&y==ty);
	}
	return 0;
}
