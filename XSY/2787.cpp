#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long lint;
const int N=1e5+5;
int n,q;
lint val[N],maxr,minr;

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline lint nxi(){
		lint x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

bool end2all(){
	int pl=1,pr=n,lpos=1,rpos=n;
	if(val[1]<val[n]) return 0;
	for(;;){
		bool changed=0;
		while(pr>q&&val[pr-1]<=val[lpos]){
			--pr;
			if(val[pr]<val[rpos]){
				rpos=pr;
				changed=1;
			}
		}
		while(pl<q&&val[pl+1]>=val[rpos]){
			++pl;
			if(val[pl]>val[lpos]){
				lpos=pl;
				changed=1;
			}
		}
		if(!changed||val[lpos]>=maxr) break;
	}
	return val[lpos]>=maxr;
}

bool mid2all(){
	int pl=q,pr=q,lpos=q,rpos=q;
	for(;;){
		bool changed=0;
		while(pr<n&&val[pr+1]<=val[lpos]){
			++pr;
			if(val[pr]<val[rpos]){
				rpos=pr;
				changed=1;
			}
		}
		while(pl>1&&val[pl-1]>=val[rpos]){
			--pl;
			if(val[pl]>val[lpos]){
				lpos=pl;
				changed=1;
			}
		}
		if(!changed||val[lpos]>=maxr) break;
	}
	return val[lpos]>=maxr;
}

bool all2all(){
	for(int i=1; i<=q; ++i){
		if(val[i]<minr) return 0;
	}
	return 1;
}

int main(){
	for(int T=nxi(); T--; ){
		n=nxi(),q=nxi();
		maxr=-1e18,minr=1e18;
		for(int i=1; i<=n; ++i){
			val[i]=val[i-1]+nxi();
			if(i>=q){
				apx(maxr,val[i]);
				apn(minr,val[i]);
			}
		}
		puts(end2all()&&all2all()&&mid2all()?"Yes":"No");
	}
}
