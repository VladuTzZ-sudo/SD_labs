#include <stdio.h>
#include <stdlib.h>

void hanoi(int n,char A,char B,char C){
	if ( n == 1 ){
		printf("Discul 1 s-a mutat de pe %c pe %c\n", A,B);
		return;
	}
	hanoi(n-1, A,C,B);
		printf("Discul %d s-a mutat de pe %c pe %c\n", n,A,B);
	hanoi(n-1, C,B,A);
}

int main(){
int n;
char A;
char B;
char C;
scanf("%d", &n);
A = 'A';
B = 'B';
C = 'C';
//printf("%c %c %c", A,B,C);
hanoi(n,A,B,C);
return 0;
}
