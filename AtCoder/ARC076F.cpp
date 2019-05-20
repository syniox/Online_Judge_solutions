#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <queue>
const int N=2e5+5;
int n,m;
struct data{
	int l,r;
	friend bool operator < (const data &a,const data &b){
		return a.l==b.l?a.r<b.r:a.l>b.l;
	}
};

namespace utils{
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
	template <class T> inline void apx(T &x,const T y){
		x<y?x=y:0;
	}
	template <class T> inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
}
using namespace utils;

int main(){
	std::priority_queue <int> r_que;
	std::priority_queue <data> d_que;
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		data x;
		x.l=nxi(),x.r=nxi();
		d_que.push(x);
	}
	for(int i=1; i<=m; ++i){
		while(!d_que.empty()&&d_que.top().l<i){
			r_que.push(-d_que.top().r);
			d_que.pop();
		}
		if(!d_que.empty()) d_que.pop();
		else if(!r_que.empty()&&-r_que.top()<=i) r_que.pop();
	}
	printf("%d\n",(int)(d_que.size()+r_que.size()));
	return 0;
}
