#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
typedef long long lint;
const int N=5e5+2;
int n,q,ql,qr,pre_s[N],st1[20][N],st2[20][N];
lint ans;
struct data{
	int x,l,r,v,pos;
	//x:left endpiont,pos: best right endpoint
	bool operator < (const data &b) const {
		return v<b.v;
	}
};
std::priority_queue <data> pq;

inline int highbit(int x){
	int ans=0;
	for(int i=16;i;i>>=1){
		if(x>>i) x>>=i,ans+=i;
	}
	return ans;
}

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
	const bool f=c=='-'&&(c=get_c());
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return f?-x:x;
}

inline void push_q(const int x,const int l,const int r){
	const int hbit=highbit(r-l+1),p1=st1[hbit][l],p2=st2[hbit][r];
	const int pos=pre_s[p1]>pre_s[p2]?p1:p2;
	pq.push((data){x,l,r,pre_s[pos]-pre_s[x-1],pos});
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
#endif
	n=nxi(),q=nxi(),ql=nxi(),qr=nxi();
	for(int i=1;i<=n;++i){
		pre_s[i]=pre_s[i-1]+nxi();
		st1[0][i]=st2[0][i]=i;
	}
	const int hbit=highbit(n);
	for(int i=1;i<=hbit;++i){
		for(int j=1;j<=n;++j){
			st1[i][j]=st1[i-1][j];
			int k=j+(1<<(i-1));
			if(k<=n&&pre_s[st1[i-1][k]]>pre_s[st1[i-1][j]]){
				st1[i][j]=st1[i-1][k];
			}
			st2[i][j]=st2[i-1][j];
			k=j-(1<<(i-1));
			if(k>0&&pre_s[st2[i-1][k]]>pre_s[st2[i-1][j]]){
				st2[i][j]=st2[i-1][k];
			}
		}
	}
	for(int i=1;i+ql-1<=n;++i){
		push_q(i,i+ql-1,std::min(n,i+qr-1));
	}
	while(q--){
		const data cur=pq.top();
		pq.pop();
		ans+=cur.v;
		if(cur.l<cur.pos) push_q(cur.x,cur.l,cur.pos-1);
		if(cur.r>cur.pos) push_q(cur.x,cur.pos+1,cur.r);
	}
	printf("%lld\n",ans);
	return 0;
}
