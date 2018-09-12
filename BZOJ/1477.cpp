#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;

inline int gcd(int x,int y){
	for(;y;x%=y,std::swap(x,y));
	return x;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

lint exgcd(lint &a,lint &b,int x,int y){
	if(!y){
		a=1,b=0;
		return x;
	}
	const lint ans=exgcd(a,b,y,x%y),tp=a;
	a=b;
	b=(tp-(lint)b*(x/y));
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int x=nxi(),y=nxi(),m=nxi(),n=nxi();
	const int mod=nxi();
	if(x>y) std::swap(x,y),std::swap(m,n);
	const int step=m>n?m-n:m-n+mod;
	const int g=gcd(step,mod);
	if((y-x)%g){
		puts("Impossible");
		return 0;
	}
	lint f,tp;
	exgcd(f,tp,step,mod);
	int gfs=gcd(step,mod);
	while(f<0||tp<0){
		f+=mod/gfs,tp+=step/gfs;
	}
	printf("%lld\n",f);
	return 0;
}
