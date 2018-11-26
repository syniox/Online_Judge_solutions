#include <iostream>
#include <cstdio>
#include <cstring>
const int N=1e5+2;
int n,val[N];
bool mr[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

int main(){
	n=nxi();
	for(int i=1;i<=n;++i) val[i]=1;
	mr[1]=1;
	for(int q=nxi();q;--q){
		const int x=nxi(),y=nxi();
		mr[y]|=mr[x];
		if(!--val[x]) mr[x]=0;
		++val[y];
	}
	int ans=0;
	for(int i=1;i<=n;++i){
		ans+=mr[i];
	}
	printf("%d\n",ans);
	return 0;
}
