#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
typedef long long lint;
const long double P=acos(-1);

int gcd(const int x,const int y){
	return y?gcd(y,x%y):x;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	const int n=nxi(),m=nxi();
	const long double r1=0.5/sin(P/n);
	lint lcm=n/gcd(n,m)*(lint)m;
	const long double r2=r1*cos(P/lcm);
	printf("%.9Lf\n",r2*tan(P/m)*2);
	return 0;
}
