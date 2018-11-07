#include <iostream>
#include <cstdio>
#include <cstring>
const int N=1e5+5;
int n,q,s1[N],s2[N],s3[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi(),q=nxi();
	for(int i=1;i<=n;++i){
		int x=nxi();
		s1[i]=s1[i-1]+(x==1);
		s2[i]=s2[i-1]+(x==2);
		s3[i]=s3[i-1]+(x==3);
	}
	while(q--){
		const int x=nxi(),y=nxi();
		printf("%d %d %d\n",s1[y]-s1[x-1],s2[y]-s2[x-1],s3[y]-s3[x-1]);
	}
	return 0;
}
