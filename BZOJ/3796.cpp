#include<iostream>
#include<cstdio>
#include<cstring>
#include<cassert>
const int N=50005;
char s1[N],s2[N],s3[10005];
int l1,l2,l3,tpr[N],sub[N];
//tpr[i]:(s3:end,i]
inline void apx(int &a,int b){
	if(a<b) a=b;
}
inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace SAM{
	int lst,cnt;
	struct node{
		int lk,len,s[26];
	}tr[N<<1];
	inline void init(){
		tr[0].lk=-1;
	}
	inline void add(int c){
		int p=lst,x=lst=++cnt;
		tr[x].len=tr[p].len+1;
		for(;~p&&!tr[p].s[c];p=tr[p].lk){
			tr[p].s[c]=x;
		}
		if(p==-1) return;
		int q=tr[p].s[c];
		if(tr[q].len==tr[p].len+1) tr[x].lk=q;
		else{
			tr[++cnt]=tr[q];
			tr[cnt].len=tr[p].len+1;
			for(;~p&&tr[p].s[c]==q;p=tr[p].lk){
				tr[p].s[c]=cnt;
			}
			tr[q].lk=tr[x].lk=cnt;
		}
	}
	inline void get_sub(){
		int x=0,len=0;
		for(int i=1;i<=l2;++i){
			int c=s2[i]-'a';
			if(!tr[x].s[c]){
				while(x&&!tr[x].s[c]) x=tr[x].lk;
				len=tr[x].len;
			}
			if(tr[x].s[c]){
				x=tr[x].s[c];
				sub[i]=++len;
			}
		}
	}
}

namespace KMP{
	int nx[10005];
	inline void init(){
		for(int i=2,j=0;i<=l3;++i){
			while(j&&s3[i]!=s3[j+1]) j=nx[j];
			if(s3[j+1]==s3[i]) ++j;
			nx[i]=j;
		}
	}
	inline void work(){
		tpr[0]=-l3+1;
		for(int i=1,j=0;i<=l2&&j<=l3;++i){
			while(j&&s2[i]!=s3[j+1]) j=nx[j];
			if(s2[i]==s3[j+1]) ++j;
			if(j==l3){
				tpr[i]=0,j=nx[j];
			}
			else tpr[i]=tpr[i-1]+1;
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	SAM::init();
	scanf("%s%s%s",s1+1,s2+1,s3+1);
	l1=strlen(s1+1),l2=strlen(s2+1),l3=strlen(s3+1);
	KMP::init();
	for(int i=1;i<=l1;++i){
		SAM::add(s1[i]-'a');
	}
	KMP::work();
	SAM::get_sub();

	int ans=0;
	for(int i=1;i<=l2;++i){
		apx(ans,std::min(sub[i],tpr[i]+l3-1));
	}
	printf("%d\n",ans);

	return 0;
}
