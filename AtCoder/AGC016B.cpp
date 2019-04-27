#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=1e5+5;
int n,nval,xval,val[N];

inline int nxi(){
	int x=0;
	char c;
	while(((c=getchar())>'9'||c<'0')&&c!='-');
	const bool f=(c=='-')&&(c=getchar());
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return f?-x:x;
}

bool solve(){
	if(xval==nval) return xval==n-1||xval<=n>>1;
	if(xval-nval>1) return 0;
	int clow=0;
	for(int i=1; i<=n; ++i){
		clow+=val[i]==nval;
	}
	if(clow>=xval) return 0;
	if(clow+((n-clow)>>1)<xval) return 0;
	return 1;
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		nval=i==1?val[i]:std::min(nval,val[i]);
		xval=i==1?val[i]:std::max(xval,val[i]);
	}
	puts(solve()?"Yes":"No");
	return 0;
}
