#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
const double P=acos(-1);
const int N=2e5+2;
int n,sx,tx,sy,ty;
struct pnt{
	int x,y;
}pt[N];

bool cmp_x(const pnt &a,const pnt &b){
	return a.x<b.x;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline double solve(){
	static int buk[N];
	const double cost=2-P*0.5;
	const int disx=abs(sx-tx),disy=abs(sy-ty);
	int top=0;
	for(int i=1;i<=n;++i){
		if(!top||(pt[i].y>buk[top])==(ty>sy)){
			buk[++top]=pt[i].y;
		}
		else{
			int l=1,r=top,mid;
			while(l!=r){
				mid=(l+r)>>1;
				if((pt[i].y>buk[mid])==(ty>sy)) l=mid+1;
				else r=mid;
			}
			buk[l]=pt[i].y;
		}
	}
	return ((disx+disy)*10-top*cost+(top==disx+1||top==disy+1)*(P*0.5))*10;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	sx=nxi(),sy=nxi(),tx=nxi(),ty=nxi();
	n=nxi();
	if(sx>tx){
		std::swap(sx,tx);
		std::swap(sy,ty);
	}
	const int miny=std::min(sy,ty);
	const int maxy=std::max(sy,ty);
	for(int i=1;i<=n;++i){
		pt[i].x=nxi(),pt[i].y=nxi();
		if(pt[i].x<sx||pt[i].x>tx||pt[i].y<miny||pt[i].y>maxy) --i,--n;
	}
	std::sort(pt+1,pt+n+1,cmp_x);
	printf("%.15lf\n",solve());
	return 0;
}
