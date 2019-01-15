#include <iostream>
#include <cstdio>
#include <cstring>

int main(){
	const int n=993,m=497;
	printf("%d %d\n",n,m);
	for(int i=1; i<m; i+=2){
		printf("2 %d %d\n",i,i+1);
		printf("2 %d %d\n",i+2,i+1);
	}
	for(int i=2; i<=m; i+=2){
		printf("1 %d\n1 %d\n",i,i);
	}
	printf("1 %d\n",m);
	return 0;
}
