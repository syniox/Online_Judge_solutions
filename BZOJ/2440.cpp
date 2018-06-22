#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=45000;
int T,mu[N],prm[N];
bool npr[N];
inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}
inline void init(){
	mu[1]=1;
	for(int i=2;i<N;++i){
		if(!npr[i]){
			prm[++prm[0]]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=prm[0]&&i*prm[j]<N;++j){
			npr[i*prm[j]]=1;
			if(i%prm[j]==0) break;
			mu[i*prm[j]]=-mu[i];
		}
	}
}
int jdg(int t){
	int ans=t;
	for(int i=2;i*i<=t;++i){
		if(mu[i]) ans+=mu[i]*(t/(i*i));
	}
	return ans;
}
int cal(int t){
	long long l=0,r=2e9+1,mid;
	while(l!=r){
		mid=l+r>>1;
		if(jdg(mid)>=t) r=mid;
		else l=mid+1;
	}
	return l;
}
int main(){
	init();
	T=nxi();
	while(T--){
		int x=nxi();
		printf("%d\n",cal(x));
	}
	return 0;
}
