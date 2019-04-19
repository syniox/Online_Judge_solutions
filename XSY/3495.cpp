#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <map>
typedef long long lint;
const int mod=998244353;
lint n;
struct _data{
	lint t,sl,sr;
	friend _data operator + (const _data &a,const _data &b){
		return (_data){a.t+b.t,a.sl+b.sl,a.sr+b.sr};
	}
};
std::map <lint,_data> mp;

template <class T> inline T nxi(){
	T x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	n=nxi<lint>();
	int ans=1;
	mp[-n]=(_data){1,1,1};
	for(std::map <lint,_data> ::iterator it=mp.begin(); it!=mp.end(); mp.erase(it++)){
		_data cur=it->second;
		lint n=-it->first,l=(n+1)/2,r=n-l;
		if(n==1) break;
		lint res_l=r%mod*cur.sl;//覆盖左区间
		lint res_r=l%mod*cur.sr;//覆盖右区间
		ans=(ans+res_l+res_r)%mod;
		mp[-l]=mp[-l]+cur;
		mp[-r]=mp[-r]+cur;
		mp[-l].sr=(mp[-l].sr+cur.t*(r%mod))%mod;
		mp[-r].sl=(mp[-r].sl+cur.t*(l%mod))%mod;
	}
	printf("%d\n",ans);
	return 0;
}
