#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long lint;
const int N=524290;
int n,q;
struct piece{
	int b,st;
	bool k;
	friend piece operator*(const piece &a,const piece &b);
	friend piece operator<(const piece &a,const piece &b);
	int opt(const int x) const;
};

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
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

piece operator*(const piece &a,const piece &b){
	int p=max(a.st,b.st);
	return (piece){b.opt(a.opt(p)),p,a.k&b.k};
}
piece operator<(const piece &a,const piece &b){
	return assert(a.k==b.k),a.b<b.b;
}
int piece::opt(const int x)const{
	return k*x+b;
}

int main(){
	n=ni,q=ni;
	for(int i=1; i<=n; ++i){

	}
	return 0;
}
