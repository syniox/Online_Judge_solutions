#include <iostream>
#include <cstdio>
#include <cstring>
const int N=5e5+5;
int n;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void bigmul(int *a,int &len,int b){
	int p=0;
	for(int i=0; i<len; ++i){
		a[i]=a[i]*b+p;
		p=a[i]/10;
		if(p) a[i]-=p*10;
	}
	if(p) a[len++]=p;
}

int main(){
	static char ch[N];
	static int s[N];
	scanf("%s",ch+1);
	n=strlen(ch+1);
	for(int i=0; i<n; ++i){
		s[i]=ch[n-i]-'0';
	}
	bigmul(s,n,9);
	int cbit=0;
	for(int i=0; i<n; ++i){
		cbit+=s[i];
	}
	for(int i=1; i<=n; ++i){
		cbit+=9;
		int p=9;
		for(int j=0; p; ++j){
			s[j]+=p;
			p=s[j]/10;
			if(p){
				s[j]-=p*10;
				cbit-=9;
			}
		}
		if(cbit<=i*9){
			printf("%d\n",i);
			break;
		}
	}
	return 0;
}
