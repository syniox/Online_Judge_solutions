#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=1e7+5;
int cnp,prm[(int)1e6];
lint phi[N];
bool npr[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	for(int i=2; i<N; ++i){
		if(!npr[i]){
			prm[++cnp]=i;
			phi[i]=i-1;
		}
		for(int j=1,tmp; j<=cnp&&(tmp=i*prm[j])<N; ++j){
			npr[tmp]=1;
			if(i%prm[j]==0){
				phi[tmp]=phi[i]*prm[j];
				break;
			}
			phi[tmp]=phi[i]*(prm[j]-1);
		}
	}
	for(int i=1; i<N; ++i){
		phi[i]+=phi[i-1];
	}
}

int main(){
	init();
	lint ans=0;
	for(int i=1,n=nxi(); prm[i]<=n; ++i){
		ans+=(phi[n/prm[i]]<<1)+1;
	}
	printf("%lld\n",ans);
	return 0;
}
