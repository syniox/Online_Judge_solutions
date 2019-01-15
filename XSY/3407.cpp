#include <iostream>
#include <cstdio>
#include <cstring>
const int N=500005;
int n,m,val[N],buk[20];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int hbit(int x){
	int ans=0;
	for(int i=16; i; i>>=1){
		if(x>>i) ans+=i,x>>=i;
	}
	return ans;
}

inline int calc(){
	for(int j=19; j>=0; --j){
		if(buk[j]) return 1<<j;
	}
	return 0;
}

int main(){
	n=nxi(),m=nxi();
	for(int i=0; i<n; ++i){
		val[i]=nxi();
		if(i!=val[i]){
			++buk[hbit(i^val[i])];
		}
	}
	for(int i=1; i<=m; ++i){
		int x=nxi()-1,y=nxi()-1;
		if(x!=val[x]){
			--buk[hbit(x^val[x])];
		}
		if(y!=val[y]){
			--buk[hbit(y^val[y])];
		}
		std::swap(val[x],val[y]);
		if(x!=val[x]){
			++buk[hbit(x^val[x])];
		}
		if(y!=val[y]){
			++buk[hbit(y^val[y])];
		}
		printf("%d\n",calc());
	}
	return 0;
}
