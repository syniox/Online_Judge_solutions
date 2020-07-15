#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long lint;
int n,q;

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

template <class T> T fpow(T x,int t){
	assert(t);
	T ans;
	bool f=0;
	for(; t; x=x*x,t>>=1){
		if(t&1) ans=f?ans*x:x;
		f|=t&1;
	}
	return ans;
}

vector <int> qinv(const vector <int> &vt){
	vector <int> res(n);
	for(int i=0; i<n; ++i){
		res[vt[i]]=i;
	}
	return res;
}
vector <int> operator*(const vector <int> &v1,const vector <int> &v2){
	vector <int> res(n);
	for(int i=0; i<n; ++i){
		res[i]=v2[v1[i]];
	}
	return res;
}

void oput(const vector <int> &vt){
	for(int i=0; i<n; ++i){
		printf("%d ",vt[i]+1);
	}
	puts("");
}

vector <int> bf(vector <int> v1,vector <int> v2,const int t){
	if(t==1) return v1;
	for(int i=3; i<=t; ++i){
		vector <int> tmp=qinv(v1)*v2;
		swap(v2,tmp),swap(v1,tmp);
	}
	return v2;
}

//t=q^-1*p*q*p^-1
int main(){
	n=nxi(),q=nxi();
	vector<int> v1(n),v2(n);
	for(int i=0; i<n; ++i) v1[i]=nxi()-1;
	for(int i=0; i<n; ++i) v2[i]=nxi()-1;
	if(q<=12) return oput(bf(v1,v2,q)),0;
	int rpow=(q-1)/6;
	vector <int> t=qinv(v2)*v1*v2*qinv(v1);
	oput(fpow(t,rpow)*bf(v1,v2,q-6*rpow)*fpow(qinv(t),rpow));
	return 0;
}
