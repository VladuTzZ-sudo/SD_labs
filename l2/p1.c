#include <stdio.h>
#include <stdlib.h>

int perfect(int n,int k){
	if ( k >= 1 ){
	if ( n % k == 0 ){
		return k + perfect(n,k-1);
	}
	else{
		return perfect(n,k-1);
	}
	}
	else{
		return 0; 
	}
}

int main(){
	int n;
	scanf("%d", &n);
	int k;
	k = perfect(n,n-1);
	//printf("%d", k);
	if ( k == n ){
		printf("Numarul este perfect!\n");
	}
	else{
		printf("Numarul nu este perfect!\n");
	}
}

