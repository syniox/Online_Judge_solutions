#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=1e5+5;
int n,m,topl[N];

inline char get_c(){
	static char *h,*t,buf[20000];
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while(((c=get_c())>'9'||c<'0')&&c!='-');
	const bool f=(c=='-')&&(c=get_c());
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return f?-x:x;
}

template <class T>
inline void apx(T &x,const T y){
	x<y?x=y:0;
}

template <class T>
inline void apn(T &x,const T y){
	x>y?x=y:0;
}

struct vec{
	double k,b;
	double val(const double p){
		return k*p+b;
	}
};

namespace T{
	int x,y;
	vec tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void build(){
		for(int i=1; i<=idx(1e5,1e5); ++i){
			tr[i]=(vec){0,-1e9};
		}
	}

	void add_t(const int l,const int r,vec v){
		const int k=idx(l,r),mid=(l+r)>>1;
		if(l>=x&&r<=y){
			int flag=(tr[k].val(l)<v.val(l))+(tr[k].val(r)<v.val(r));
			if((flag&1)==0){
				if(flag) tr[k]=v;
				return;
			}
			if(tr[k].val(l)<v.val(l))
				std::swap(v,tr[k]);
			if(tr[k].val(mid)<v.val(mid)){
				std::swap(v,tr[k]);
				add_t(l,mid,v);
			}
			else{
				add_t(mid+1,r,v);
			}
			return;
		}
		if(x<=mid) add_t(l,mid,v);
		if(y>mid) add_t(mid+1,r,v);
	}

	double qmax_t(const int l,const int r){
		double ans=tr[idx(l,r)].val(x);
		if(l==r) return ans;
		const int mid=(l+r)>>1;
		if(x<=mid) apx(ans,qmax_t(l,mid));
		else apx(ans,qmax_t(mid+1,r));
		return ans;
	}

	inline void add(int l,int r,vec v){
		if(r<=0||l>1e5) return;
		apx(l,1),apn(r,(int)1e5);
		assert(l<=r);
		T::x=l,T::y=r;
		add_t(1,1e5,v);
	}

	inline double qmax(const int x){
		T::x=x;
		return qmax_t(1,1e5);
	}
}

void add_l(int x1,int y1,int x2,int y2){
	if(x1>x2){
		std::swap(x1,x2);
		std::swap(y1,y2);
	}
	if(x1==x2){
		if(x1>0&&x2<=1e5){
			apx(topl[x1],std::max(y1,y2));
		}
	}
	else{
		double k=(double)(y2-y1)/(x2-x1);
		vec v=(vec){k,y1-x1*k};
		T::add(x1,x2,v);
	}
}

int main(){
	n=nxi(),m=nxi();
	memset(topl,-10,sizeof(topl));
	T::build();
	for(int i=1; i<=n; ++i){
		int x1=nxi(),y1=nxi(),x2=nxi(),y2=nxi();
		add_l(x1,y1,x2,y2);
	}
	for(int i=1; i<=m; ++i){
		const int op=nxi();
		if(op==0){
			const int x1=nxi(),y1=nxi(),x2=nxi(),y2=nxi();
			add_l(x1,y1,x2,y2);
		}
		if(op==1){
			const int x=nxi();
			const double res=std::max(T::qmax(x),(double)topl[x]);
			printf("%.3lf\n",res<-1e7?0:res);
		}
	}
	return 0;
}
