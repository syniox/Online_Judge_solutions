#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
const int N=1e5+2;
int n;
char qa[N],qb[N];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline bool vld(){
	bool f1=0,f2=0;
	for(int i=0;i<n;++i){
		f1|=(qa[i]=='1');
		f2|=(qb[i]=='1');
	}
	if(f2==0) puts(f1?"-1":"0");
	return f2;
}

inline int get_ans(){
	static int to_l[N],to_r[N],maxr[N];
	memset(to_l,0,sizeof(to_l));
	memset(to_r,0,sizeof(to_r));
	for(int i=0;i<n;++i){
		while(qb[(i-to_l[i]+n)%n]=='0') ++to_l[i];
		while(qb[(i+to_r[i])%n]=='0') ++to_r[i];
	}
	int ans=1e9;
	for(int s=0;s<n;++s){
		memset(maxr,0,sizeof(maxr));
		int xr=0,cturn=0;
		for(int i=0;i<n;++i){
			if(qa[i]!=qb[(i+s)%n]){
				++cturn;
				apx(maxr[to_l[i]],to_r[i]-s);

			}
		}
		for(int i=n-1;i>=0;--i){
			apn(ans,((i+xr)<<1)+s+cturn);
			apx(xr,maxr[i]);
		}
	}
	return ans;
}

inline int solve(){
	int ans=1e9;
	apn(ans,get_ans());
	std::reverse(qa,qa+n);
	std::reverse(qb,qb+n);
	apn(ans,get_ans());
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	scanf("%s%s",qa,qb);
	n=strlen(qa);
	if(!vld()) return 0;
	printf("%d\n",solve());
	return 0;
}
