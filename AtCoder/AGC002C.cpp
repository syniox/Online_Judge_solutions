#include <iostream>
#include <cstdio>
#include <cstring>
const int N=1e5+5;
int n,q;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int jdg(){
	int las=nxi();
	for(int x,i=2;i<=n;++i){
		x=nxi();
		if(las+x>=q) return i-1;
		las=x;
	}
	return 0;
}

int main(){
	n=nxi(),q=nxi();
	int ans=jdg();
	if(!ans) puts("Impossible");
	else{
		puts("Possible");
		for(int i=1;i<ans;++i) printf("%d\n",i);
		for(int i=n-1;i>ans;--i) printf("%d\n",i);
		printf("%d\n",ans);
	}
	return 0;
}
