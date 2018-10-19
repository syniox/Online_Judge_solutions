#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
const int N=2e6+5;
char ch[N];
int n,m;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace NT{
	struct node{
		int s,ch[26];
	};
	int rt1,rt2,cnt,cnr,top,rt[N],stk[N];
	node tr[N+2010];
	inline void init(){
		rt[0]=cnt=1;
	}
	inline void mod(){
		++cnr;
		int p=rt[cnr]=++cnt,fp=rt[cnr-1];
		for(int i=top;i;--i){
			const int c=stk[i];
			tr[p]=tr[fp];
			++tr[p].s;
			tr[p].ch[c]=++cnt;
			p=cnt;
			fp=tr[fp].ch[c];
		}
		++tr[p].s;
	}
	inline int ask(const int len){
		int r1=rt[rt1],r2=rt[rt2];
		for(int i=len;i;--i){
			if(!r2) return 0;
			r2=tr[r2].ch[(int)ch[i]];
			r1=tr[r1].ch[(int)ch[i]];
		}
		return tr[r2].s-tr[r1].s;
	}
}

namespace PT{
	struct node{
		int s,end,ch[26];
	};
	int cnt=1,top,stk[N];
	node tr[N];
	inline void ins(){
		const int len=strlen(ch+1);
		int p=1;
		for(int i=1;i<=len;++i){
			const int c=ch[i]-'a';
			++tr[p].s;
			if(!tr[p].ch[c]) tr[p].ch[c]=++cnt;
			p=tr[p].ch[c];
		}
		++tr[p].end;
	}
	void get_nt(const int x){
		using NT::top;
		using NT::stk;
		for(int i=1;i<=tr[x].end;++i) NT::mod();
		for(int i=0;i<26;++i){
			if(tr[x].ch[i]){
				stk[++top]=i;
				get_nt(tr[x].ch[i]);
				--top;
			}
		}
	}
	void get_rt(const int len){
		using NT::rt1;
		using NT::rt2;
		rt1=rt2=0;
		int p=1,res=0;
		for(int i=1;i<=len;++i){
			for(int j=0;j<ch[i];++j){
				res+=tr[tr[p].ch[j]].s;
			}
			if(tr[p].ch[(int)ch[i]]) p=tr[p].ch[(int)ch[i]];
			else return;
		}
		rt1=res;
		rt2=res+tr[p].s;
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<=n;++i){
		scanf("%s",ch+1);
		PT::ins();
	}
	NT::init();
	PT::get_nt(1);
	int ans=0;
	m=nxi();
	for(int i=1;i<=m;++i){
		scanf("%s",ch+1);
		int len=strlen(ch+1);
		for(int i=1;i<=len;++i){
			ch[i]=(ans+ch[i]-'a')%26;
		}
		PT::get_rt(len);
		scanf("%s",ch+1);
		len=strlen(ch+1);
		for(int i=1;i<=len;++i){
			ch[i]=(ans+ch[i]-'a')%26;
		}
		printf("%d\n",ans=NT::ask(len));
	}
	return 0;
}
