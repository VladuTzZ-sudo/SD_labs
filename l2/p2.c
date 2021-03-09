#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sir(char *s,char c){
	char *p;
	p = strchr(s,c);
	//printf("%s", p+1);
	if ( p!= NULL ){
		return p-s + sir(p+1,c)+1;
	}
	else{
		return -1;
	}
}

int main(){
	char s[100];
	char c;
	fgets(s, 100,stdin);
	scanf("%c", &c);
	int k;
	k = sir(s, c);
	printf("%d\n", k);
return 0;
}
