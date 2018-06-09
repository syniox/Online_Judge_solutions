#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=2005;
int n,cnt,st[N];
struct pnt{
	double x,y;
	bool operator < (const pnt &b) const {
		return x==b.x?y<b.y:x<b.x;
	}
	double operator * (const pnt &b) const{
		return x*b.y-y*b.x;
	}
	pnt operator - (const pnt &b) const {
		return (pnt){x-b.x,y-b.y};
	}
}pt[N];
inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-48;
	return x;
}
inline double jdg(pnt &a,pnt &b,pnt &c){
	pnt x=(pnt){a.x-b.x,a.y-b.y};
	pnt y=(pnt){b.x-c.x,b.y-c.y};
	return x*y;
}
double solve(){
	double ans=0;
	for(int i=1;i<n-2;++i){
		int k=i+1,l=i+3;
		pnt &x=pt[st[i]];
		for(int j=1;j<n;++j){
			pnt &y=pt[st[j]];
			while(k<j&&(pt[st[k]]-x)*(y-x)<(pt[st[k+1]]-x)*(y-x)) ++k;
			while(l<cnt&&(y-x)*(pt[st[l]]-x)<(y-x)*(pt[st[l+1]]-x)) ++l;
			ans=max(ans,((y-x)*(pt[st[k]]-x)+(y-x)*(pt[st[l]]-x))/2);
		}
	}
	return ans;
}
int main(){
	n=nxi();
	for(int i=1;i<=n;++i){
		scanf("%lf%lf",&pt[i].x,&pt[i].y);
	}
	sort(pt+1,pt+n+1);
	st[++cnt]=1;
	st[++cnt]=2;
	for(int i=3;i<=n;++i){
		while(cnt>1&&jdg(pt[cnt-1],pt[cnt],pt[i])<0) --cnt;
		st[++cnt]=i;
	}
	int tp=cnt;
	st[++cnt]=n-1;
	for(int i=n-2;i;--i){
		while(cnt>tp&&jdg(pt[cnt-1],pt[cnt],pt[i])<0) --cnt;
		st[++cnt]=i;
	}
	printf("%.3lf\n",solve());
	return 0;
}
