#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
typedef long long lint;
lint fc[18];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

int dfs(int t,int lt,int tp){
	if(t>lt>>1) return tp==0;
	lint cur=fc[lt-t]-fc[t-1],p=tp/cur,ans=0;
	if(p*cur>tp) --p;
	bool f=(t!=1);
	if(abs(p)<=8+f) ans+=dfs(t+1,lt,tp-p*cur)*(9-abs(p)+f);
	if(abs(p+1)<=8+f) ans+=dfs(t+1,lt,tp-(p+1)*cur)*(9-abs(p+1)+f);
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	fc[0]=1;
	for(int i=1;i<18;++i) fc[i]=fc[i-1]*10;
	lint d=nxi(),ans=0;
	for(int i=1;i<=18;++i){
/*		int cnt=1,tp=d;
		if(i&1) cnt*=9;
		for(int j=1;j<=i>>1;++j){
			lint cur=fc[i-j]-fc[j-1],p=tp/cur;
			if(p>8+(bool)(j!=1)) break;
			cnt*=(9-p+(bool)(j!=1));
			tp-=p*cur;
		}
		if(!tp) ans+=cnt;*/
		int t=i==1?9:10;
		ans+=dfs(1,i,d)*(i&1?t:1);
	}
	printf("%lld\n",ans);
	return 0;
}
