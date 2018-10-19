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
		int s;
		std::map <int,int> ch;
	};
	int rt1,rt2,cnt,cnr,top,rt[N],stk[N];
	//rt1: before
	node tr[N<<1];
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
		for(int i=1;i<=len;++i){
			if(tr[r1].s==tr[r2].s) return 0;
			if(tr[r2].ch.find(ch[i])==tr[r2].ch.end()) return 0;
			r2=tr[r2].ch[ch[i]];
			if(tr[r1].ch.find(ch[i])==tr[r1].ch.end()) r1=0;
			else r1=tr[r1].ch[ch[i]];
		}
		return tr[r2].s-tr[r1].s;
	}
}

namespace PT{
	struct node{
		int s,end;
		std::map <int,int> ch;
	};
	int cnt=1,top,stk[N];
	node tr[N];
	inline void ins(){
		const int len=strlen(ch+1);
		int p=1;
		for(int i=1;i<=len;++i){
			const int c=ch[i]-'a';
			++tr[p].s;
			if(tr[p].ch.find(c)==tr[p].ch.end()) tr[p].ch[c]=++cnt;
			p=tr[p].ch[c];
		}
		++tr[p].end;
	}
	void get_nt(const int x){
		using NT::top;
		using NT::stk;
		for(int i=1;i<=tr[x].end;++i) NT::mod();
		std::map <int,int> ::iterator it=tr[x].ch.begin();
		for(;it!=tr[x].ch.end();++it){
			stk[++top]=it->first;
			get_nt(it->second);
			--top;
		}
	}
	void get_rt(const int len){
		using NT::rt1;
		using NT::rt2;
		rt1=rt2=0;
		int p=1,res=0;
		for(int i=1;i<=len;++i){
			std::map <int,int> ::iterator it=tr[p].ch.begin();
			for(;it!=tr[p].ch.end()&&(it->first)<ch[i];++it){
				res+=tr[it->second].s;
			}
			if((it->first)==ch[i]) p=it->second;
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
	for(int i=1;i<=NT::cnr;++i){
		printf("%d ",NT::tr[NT::rt[i]].s);
	}
	puts("");
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
