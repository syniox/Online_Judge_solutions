#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=55;
int n,m,sum,at[N],hp[N],fir[N<<1];
struct edge{
	int to,wi,nx;
}eg[5200];
inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9;||c<'0');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-48;
	return x;
}
inline void init(){
	for(int i=1;i<=n;++i){
		add(0,i,0);
	}
	for(int i=1;i<=m;++i){
		add(i+N,(N<<1)-1,hp[i]);
	}
}
inline bool jdg(int t){

}
int main(){
	m=nxi(),n=nxi();
	for(int i=1;i<=n;++i){
		at[i]=nxi();
	}
	for(int i=1;i<=m;++i){
		sum+=hp[i]=nxi();
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			map[i][j]=nxi();
		}
	}
	init();
	double l=0,r=50001,mid;
	while(r-1e-4>l){
		mid=l+r>>1;
		if(jdg(mid)) r=mid;
		else l=mid+1;
	}
	printf("%lf\n",l);
	return 0;
}
