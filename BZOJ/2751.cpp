#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long lint;
const int ha=1e9+7;
const int K=100005;
int n,m,k;
struct data{
	int x,t;
	bool operator < (const data b) const {
		return x==b.x?t<b.t:x<b.x;
	}
	bool operator == (const data b) const {
		return (x==b.x)&&(t==b.t);
	}
}xz[K];

inline int nxi(){
	int x(0);
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

lint qmi(int x,int t){
	if(!t) return 1;
	lint q=qmi(x,t>>1);
	return q*q%ha*(t&1?x:1)%ha;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	n=nxi(),m=nxi(),k=nxi();
	for(int i=1;i<=k;++i){
		xz[i].x=nxi(),xz[i].t=nxi();
	}
	sort(xz+1,xz+k+1);
	lint ans=1,dy=n*(n+1)%ha*qmi(2,1e9+5)%ha;
	for(int j=0,i=1;i<=k;){
		ans=ans*qmi(dy,xz[i].x-j-1)%ha;
		lint tp=0;
		j=xz[i].x;
		while(xz[i].x==j){
			if(xz[i]==xz[i++]) continue;
			tp+=xz[i-1].t;
		}
		j=xz[i-1].x;
		ans=ans*(dy-tp)%ha;
	}
	ans=ans*qmi(dy,m-xz[k].x)%ha;
	printf("%lld\n",ans);
}
