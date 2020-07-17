#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
using namespace std;
const int N=1e5+5,logN=18;
int n,val[N];
struct data{
	lint a,b;
}dp[N][logN];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

inline int qsyl(const int x){
	return ((x-1)%n+n)%n+1;
}

inline lint qmn(const lint a,const lint b){
	return a-val[qsyl(a)]<b-val[qsyl(b)]?a:b;
}
inline lint qmx(const lint a,const lint b){
	return a+val[qsyl(a)]>b+val[qsyl(b)]?a:b;
}
data rng_mx(const data &p1,const data &p2){
	return (data){qmn(p1.a,p2.a),qmx(p1.b,p2.b)};
}

namespace T{
#define mid ((l+r)>>1)
	data tr[N<<1];//min,max
	int x,y;

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}
	void build(const int l,const int r){
		if(l==r){
			tr[idx(l,r)]=(data){l,l};
			return;
		}
		build(l,mid);
		build(mid+1,r);
		tr[idx(l,r)]=rng_mx(tr[idx(l,mid)],tr[idx(mid+1,r)]);
	}
	data qst_t(const int l,const int r){
		if(l>=x&&r<=y) return tr[idx(l,r)];
		if(y<=mid) return qst_t(l,mid);
		if(x>mid) return qst_t(mid+1,r);
		return rng_mx(qst_t(l,mid),qst_t(mid+1,r));
	}
	data qst(const int l,const int r){
		return x=l,y=r,qst_t(1,n<<1);
	}
#undef mid
}

data qdp(const lint x,const int t){
	data tmp=dp[qsyl(x)][t];
	lint offs=x-qsyl(x);
	return (data){tmp.a+offs,tmp.b+offs};
}
lint rng_len(const data &pr){
	return pr.b+val[qsyl(pr.b)]-pr.a+val[qsyl(pr.a)];
}

int main(){
	n=nxi();
	if(n==1){
		puts("0");
		return 0;
	}
	for(int i=1; i<=n; ++i) val[i]=min(n-1,nxi());
	T::build(1,n);
	for(int i=1; i<=n; ++i){
		data ans=T::qst(max(1,i-val[i]),min(n,i+val[i]));
		if(i-val[i]<1){
			data tmp=T::qst(i-val[i]+n,n);
			ans=rng_mx(ans,(data){tmp.a-n,tmp.b-n});
		}
		if(i+val[i]>n){
			data tmp=T::qst(1,i+val[i]-n);
			ans=rng_mx(ans,(data){tmp.a+n,tmp.b+n});
		}
		dp[i][0]=ans;
	}
	for(int i=1; i<logN; ++i){
		for(int j=1; j<=n; ++j){
			dp[j][i]=rng_mx(qdp(dp[j][i-1].a,i-1),qdp(dp[j][i-1].b,i-1));
		}
	}
	for(int i=1; i<=n; ++i){
		data st=(data){i,i};
		if(rng_len(st)>=n-1){
			printf("1 ");
			continue;
		}
		int res=0;
		for(int j=logN-1; ~j; --j){
			data test=rng_mx(qdp(st.a,j),qdp(st.b,j));
			if(rng_len(test)<n-1){
				st=test;
				res+=1<<j;
			}
		}
		printf("%d ",res+2);
	}
	puts("");
	return 0;
}
