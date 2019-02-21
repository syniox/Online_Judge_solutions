#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long lint;
const int N=1e5+5;
int n,m,q;
lint seq[N],ans[N],buk[N];

template <class T> inline T nxi(){
	T x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

int main(){
	n=nxi<int>(),q=nxi<int>();
	seq[++m]=n;
	for(int i=1; i<=q; ++i){
		lint x=nxi<lint>();
		while(m&&seq[m]>x) --m;
		seq[++m]=x;
	}
	buk[m]=1;
	for(int i=m; i; --i){
		if(!buk[i]) continue;
		lint tmp=seq[i];
		for(int j=i; tmp>seq[1]; ){
			j=std::lower_bound(seq+1,seq+j,tmp)-seq-1;
			lint f=tmp/seq[j];
			tmp-=f*seq[j];
			buk[j]+=buk[i]*f;
		}
		ans[tmp]+=buk[i];
	}
	for(int i=seq[1]; i; --i){
		ans[i-1]+=ans[i];
	}
	for(int i=1; i<=n; ++i){
		printf("%lld\n",ans[i]);
	}
	return 0;
}
