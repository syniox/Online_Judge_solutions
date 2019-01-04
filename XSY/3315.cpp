#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>
typedef long long lint;
const int N=100;
const int mod=1e9+7;
const lint mod2=(lint)mod*mod;
const lint LINT_MAX=9223372036854775807;
int n,len,q,nx[N+5],val[N+5];

struct mtrx{
	lint v[(N<<1)+5][(N<<1)+5];
	//num,len

	friend mtrx operator * (const mtrx &a,const mtrx &b){
		mtrx c;
		memset(c.v,0,sizeof(c.v));
		for(int i=0; i<n<<1; ++i){
			for(int j=0; j<n<<1; ++j){
				for(int k=0; k<n<<1; ++k){
					c.v[i][j]+=a.v[i][k]*b.v[k][j];
					if(c.v[i][j]>LINT_MAX-mod2){
						c.v[i][j]%=mod;
					}
				}
				c.v[i][j]%=mod;
			}
		}
		return c;
	}
}turn;

template <class T> inline void twk(T &x){
	if(x>=mod) x-=mod;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline T fpow(T x,int t){
	bool f=0;
	T ans;
	for(; t; t>>=1,x=x*x){
		if(t&1) ans=f?ans*x:x;
		f|=t&1;
	}
	return ans;
}

inline void get_nx(){
	for(int i=2,j=0; i<=n; ++i){
		while(j&&val[i]!=val[j+1]) j=nx[j];
		if(val[i]==val[j+1]||(j==0&&val[i]>val[1])) ++j;
		nx[i]=j;
	}
}

inline void build_mtrx(){
	std::set <int> vis;
	for(int i=0; i<n; ++i){
		vis.clear();
		int cnt=q-val[1]+1;
		int sum=((lint)(val[1]+q)*cnt>>1)%mod;
		for(int j=i; j; j=nx[j]){
			if(j+1==n||vis.find(val[j+1])!=vis.end()) continue;
			vis.insert(val[j+1]);
			if(val[j+1]>=val[1]){
				--cnt;
				twk(sum+=mod-val[j+1]);
			}
			turn.v[i][j+1]=1;
			turn.v[n+i][j+n+1]=1;
			turn.v[i][j+n+1]=val[j+1];
		}
		turn.v[i][1]=cnt;
		turn.v[i][n+1]=sum;
		turn.v[n+i][n+1]=cnt;
	}
}

inline int solve(){
	mtrx res=fpow(turn,len);
	int ans=0;
	for(int i=n+1; i<n<<1; ++i){
		twk(ans+=res.v[0][i]);
	}
	return ans;
}

int main(){
	n=nxi(),q=nxi(),len=nxi();
	++n;
	for(int i=1; i<n; ++i){
		val[i]=nxi();
	}
	for(int i=n-1; i; --i){
		val[i]-=val[i-1];
	}
	get_nx();
	build_mtrx();
	printf("%d\n",solve());
	return 0;
}
