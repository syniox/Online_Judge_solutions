#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
using namespace std;
const int N=2e5+5;
int h,w,n;
char st1[N],st2[N];
char mp[126];

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
			const bool f=(c=='-')&&(c=getchar());
			while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
			return f?-x:x;
		}
	}ni;
}
using namespace utils;

bool onbrd(const int st){
	int l=1,r=w;
	for(int i=n; i>=1; --i){
		if(st2[i]=='R'){
			l=max(1,l-1);
		}else if(st2[i]=='L'){
			r=min(w,r+1);
		}
		if(st1[i]=='R'){
			if(--r<l) return 0;
		}else if(st1[i]=='L'){
			if(++l>r) return 0;
		}
	}
	return st>=l&&st<=r;
}

int main(){
	mp['L']='U',mp['R']='D',mp['U']='L',mp['D']='R';
	h=ni,w=ni,n=ni;
	int sr=ni,sc=ni;
	scanf("%s",st1+1);
	scanf("%s",st2+1);
	if(!onbrd(sc)) puts("NO");
	else{
		swap(w,h);
		for(int i=1; i<=n; ++i){
			st1[i]=mp[st1[i]];
			st2[i]=mp[st2[i]];
		}
		puts(onbrd(sr)?"YES":"NO");
	}
	return 0;
}
