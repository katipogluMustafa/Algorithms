#include<stdio.h>

int GCD(int x, int y){

	int remainder;

	while( y ){
		remainder = x % y;
		//GCD(x,y) = GCD(y, remainder)
		x = y;
		y = remainder;
	}
	return x;
}

int main(){
	
	printf("GCD(25,5) = %d\n", GCD(25,5) );
	printf("GCD(17,2) = %d\n", GCD(17,2) );
	printf("GCD(12,4) = %d\n", GCD(12,4) );
	printf("GCD(65,13) = %d\n", GCD(65,13) );

return 0;
}
