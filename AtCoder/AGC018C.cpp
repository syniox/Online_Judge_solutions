#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <queue>
typedef long long lint;
const int N=1e5+5;
int n,qx,qy,qz;
lint sum_z,cx[N],cy[N];
struct _pair{
	int x,y;
}pep[N];

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

inline int nxi(FILE *fd=stdin){
	int x=0;
	char c;
	while((c=fgetc(fd))>'9'||c<'0');
	while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
	return x;
}

inline bool _pr_cmp_dif(const _pair &a,const _pair &b){
	return (a.x-a.y)<(b.x-b.y);
}

void solve(){
	static std::priority_queue <int> pq;
	lint sum=0;
	for(int i=1; i<=qy; ++i){
		sum+=pep[i].y;
		pq.push(-pep[i].y);
	}
	cy[qy]=sum;
	for(int i=qy+1; i<=n-qx; ++i){
		if(pep[i].y>-pq.top()){
			sum+=pep[i].y;
			pq.push(-pep[i].y);
			sum+=pq.top();
			pq.pop();
		}
		cy[i]=sum;
	}
	while(!pq.empty()) pq.pop();
	sum=0;
	for(int i=n-qx+1; i<=n; ++i){
		sum+=pep[i].x;
		pq.push(-pep[i].x);
	}
	cx[n-qx+1]=sum;
	for(int i=n-qx; i>qy; --i){
		if(pep[i].x>-pq.top()){
			sum+=pep[i].x;
			pq.push(-pep[i].x);
			sum+=pq.top();
			pq.pop();
		}
		cx[i]=sum;
	}
}

int main(){
	qx=nxi(),qy=nxi(),qz=nxi();
	n=qx+qy+qz;
	for(int i=1; i<=n; ++i){
		const int x=nxi(),y=nxi(),z=nxi();
		sum_z+=z;
		pep[i]=(_pair){x-z,y-z};
	}
	std::sort(pep+1,pep+n+1,_pr_cmp_dif);
	solve();
	lint ans=-1e16;
	for(int i=qy; i<=n-qx; ++i){
		apx(ans,cy[i]+cx[i+1]);
	}
	printf("%lld\n",ans+sum_z);
	return 0;
}
