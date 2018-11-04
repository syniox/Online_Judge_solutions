#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>
const int N=1e5+2;
int n,q;

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

struct pnt{
	int sz,n[6],x[6];
	bool operator < (const pnt &b) const {
		for(int i=1;i<=q;++i){
			if(n[i]>b.n[i]) return 0;
		}
		return 1;
	}
	void operator += (const pnt &b){
		for(int i=1;i<=q;++i){
			apn(n[i],b.n[i]);
			apx(x[i],b.x[i]);
		}
		sz+=b.sz;
	}
	bool canb(const pnt &b) const {
		for(int i=1;i<=q;++i){
			if(x[i]>b.n[i]) return 1;
		}
		return 0;
	}
};
std::set <pnt> st;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
#endif
	n=nxi(),q=nxi();
	for(int i=1;i<=n;++i){
		pnt pt;
		pt.sz=1;
		for(int j=1;j<=q;++j){
			pt.n[j]=pt.x[j]=nxi();
		}
		std::set <pnt> ::iterator it=st.upper_bound(pt),it2;
		while(it2=it,it2!=st.begin()&&(*--it2).canb(pt)){
			pt+=(*it2);
			st.erase(it2);
		};
		st.insert(pt);
		printf("%d ",st.rbegin()->sz);
	}
	puts("");
	return 0;
}
