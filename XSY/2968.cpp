#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=2e5+5;
int n,chl,chr;
char ch[N<<1];
lint ans;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace AM{
	int ptl,ptr,cnt=1;
	struct node{
		int s[4],lk,len,dep;
	}tr[N];

	inline int get_fail(const int chp,int pt,int op){
		while(ch[chp-op*tr[pt].len-op]!=ch[chp]) pt=tr[pt].lk;
		return pt;
	}

	inline void ins(int c,const int chp,int &pt,int op){
		const int p=get_fail(chp,pt,op);
		if(!tr[p].s[c]){
			tr[++cnt].lk=tr[get_fail(chp,tr[p].lk,op)].s[c];
			tr[p].s[c]=cnt;
			tr[cnt].len=tr[p].len+2;
			tr[cnt].dep=tr[tr[cnt].lk].dep+1;
		}
		pt=tr[p].s[c];
		ans+=tr[pt].dep;
		if(tr[pt].len==chr-chl+1) ptl=ptr=pt;
	}
}

inline void init(){
	chl=N,chr=N-1;
	AM::tr[0].lk=AM::tr[1].lk=1;
	AM::tr[1].len=-1;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	n=nxi();
	init();
	for(int i=1;i<=n;++i){
		static char c,op[20];
		scanf("%s",op+1);
		while((c=getchar())>'d'||c<'a');
		if(op[1]=='l'){
			ch[--chl]=c;
			AM::ins(c-'a',chl,AM::ptl,-1);
		}
		else{
			ch[++chr]=c;
			AM::ins(c-'a',chr,AM::ptr,1);
		}
		printf("%lld %d\n",ans,AM::cnt-1);
	}
	return 0;
}
