#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=2e5+5;
int n,va[N],vb[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

inline int san(const int x,const int b){
	return x&((1<<b)-1);
}

void upd(int *id,int *v,const int t){
	static int buk[2][N];
	int c[2]={0};
	for(int i=1; i<=n; ++i){
		int p=v[id[i]]>>t&1;
		buk[p][++c[p]]=id[i];
	}
	memcpy(id+1,buk[0]+1,c[0]*sizeof(id[0]));
	memcpy(id+c[0]+1,buk[1]+1,c[1]*sizeof(id[0]));
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		va[i]=nxi();
	}
	for(int i=1; i<=n; ++i){
		vb[i]=nxi();
	}
	int ans=0;
	for(int i=0; i<=28; ++i){
		static int la[N],lb[N];
		bool res=0;
		int c[2]={0,0};
		for(int j=1; j<=n; ++j){
			++c[vb[j]>>i&1];
		}
		for(int j=1; j<=n; ++j){
			res^=c[(va[j]>>i&1)^1]&1;
		}
		if(i==0){
			for(int j=1; j<=n; ++j) la[j]=j;
			for(int j=1; j<=n; ++j) lb[j]=j;
		}
		else{
			for(int j=1,k=n; j<=n; ++j){
				for(; k&&san(va[la[j]],i)+san(vb[lb[k]],i)>=1<<i; --k);
				res^=(n-k)&1;
			}
		}
		ans|=res<<i;
		upd(la,va,i);
		upd(lb,vb,i);
	}
	printf("%d\n",ans);
	return 0;
}
