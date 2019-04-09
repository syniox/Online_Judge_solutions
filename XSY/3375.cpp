#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <map>
typedef long long lint;
const int N=2e5+5;
int n;
lint val[N];
std::map <lint,lint> stat;

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

template <class T> inline T nxi(){
	T x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	n=nxi<int>();
	val[1]=nxi<lint>();
	for(int i=2; i<=n; ++i){
		val[i]=std::min(val[i-1],nxi<lint>());
	}
	stat[val[1]-1]=0;
	for(int i=1; i<n; ++i){
		std::map <lint,lint> ::iterator it=stat.lower_bound(val[i+1]);
		for(; it!=stat.end(); stat.erase(it++)){
			lint wgt=it->first/val[i+1];
			lint rest=it->first%val[i+1];
			apx(stat[rest],it->second+i*(it->first-(lint)rest));
			apx(stat[val[i+1]-1],it->second+i*val[i+1]*(wgt-1));
		}
	}
	lint ans=0;
	for(std::map <lint,lint> ::iterator it=stat.begin(); it!=stat.end(); ++it){
		apx(ans,it->second+it->first*n);
	}
	printf("%lld\n",ans);
	return 0;
}
