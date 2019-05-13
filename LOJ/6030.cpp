#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=1005;
int n,cntx[N],cnty[N];

template <class T> inline void apn(T &x,const T y){
	x>y?x=y:0;
}

inline int nxi(FILE *fd=stdin){
	int x=0;
	char c;
	while((c=fgetc(fd))>'9'||c<'0');
	while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
	return x;
}

int main(){
	n=nxi();
	bool vld=0;
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=n; ++j){
			char c;
			while((c=getchar())!='#'&&c!='.');
			if(c=='.') continue;
			vld=1;
			++cntx[i];
			++cnty[j];
		}
	}
	if(!vld){
		puts("-1");
		return 0;
	}
	int ans=n;
	for(int i=1; i<=n; ++i){
		apn(ans,n-cntx[i]+(cnty[i]==0));
	}
	fprintf(stderr,"ans: %d\n",ans);
	for(int i=1; i<=n; ++i){
		ans+=cnty[i]!=n;
	}
	printf("%d\n",ans);
	return 0;
}
