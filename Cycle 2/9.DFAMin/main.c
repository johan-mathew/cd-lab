
#include<stdio.h>

int Node[50][26][50]={0};
int States[20];
int NewState[20];
int nscount=0;

// map characters to an index value a-1, b-2 .....
int map(char a){
	int i;
	i=a-96;
	return i;
}

int rmap(int a){
	char i;
	i = a+96;
	return i;
}

int reverse(int num){
	if( num < 0)
		return num;
	int rev =0,r;
	while( num > 0){
		r = num % 10;
		rev = rev * 10 + r;
		num = num / 10;
	}
	return rev;
	
}

int Union(int n1, int n2){
	if( n1 == -1 )
		return n2;
	int arr[10],i=0,k=0,num=0;
	n1 = reverse(n1);
	while( n1 > 0 ){
		arr[i++] = n1 % 10;
		n1 = n1 / 10;
	}
	
	n2 = reverse(n2);
	while( n2 > 0){
		int r = n2 % 10;
		int flag = 0;
		for(k=0;k<i;k++){
			if( r == arr[k] )
				flag = 1;
		}
		if( flag == 0 )
			arr[i++] = r;
		n2 = n2 / 10;	
	}
	
	for(k=0;k<i;k++)
		num = num * 10 + arr[k];
	return num;	
		
}

void CheckAndAdd(int num,int *cnt){
	int i, flag=0;
	for(i=0;i<*cnt;i++){
		if( States[i] == num)
			flag = 1;
	}
	if( flag == 0){
		States[(*cnt)++] = num;
		NewState[nscount++] = num;
	}
}


int main(){
	/*variables in main()
	 * 	INTEGERS
	 * n - no of states
	 * t - no of transitions
	 * a - no of alphabets 
	 *  -1 # indicates No transition for that input alphabet
	 * */
	 
	int n,t,a,state1,state2,i,j,k,result[10][10] = {0};
	int count=0;// count the no of newstates
	char alphabets[10],alpha;

	printf("\nEnter the no of states :");
	scanf("%d",&n);
	// assigning each state as a newstate
	for(i=1;i<=n;i++)
		States[count++] = i;
	printf("\nEnter the no of alphabets: ");
	scanf("%d",&a);
	printf("\nEnter the alphabets : \n");
	for(i=1;i<=a;i++)
		scanf(" %c",&alphabets[i]);
		
	printf("\nEnter the no of transitions: ");
	scanf("%d", &t);
	printf("\nEnter the state table:\n(States should be named as 1,2,3 ...)\nSTATE ALPHABET STATE\n");
	for(i=1;i<=t;i++){
		scanf("%d	%c	%d",&state1,&alpha,&state2);
		Node[state1][map(alpha)][state2] = 1;
	}	
	
	
	// finding the transitions
	for(i=1;i<=n;i++){
		for(j=1;j<=a;j++){
			int num=0, flag=0;
			for(k=1;k<=n;k++){
				if( Node[i][j][k] == 1){
					num = num * 10 + k;// ref eqn 1.a
					flag = 1;
				}
			}
			if( flag==1){
				result[i][j]=num; // ref eqn 1.a
				CheckAndAdd(num,&count);
			}
		}
	}
	
	// displaying the result
	for(i=1;i<=n;i++){
		for(j=1;j<=a;j++){
			printf("\nSTATE %d for ALPHABET %c >>> {",i,rmap(j));
			int temp = reverse( result[i][j] );
			while( temp > 0 ){// ref eqn 1.b
				printf(" %d  ",temp%10);
				temp = temp / 10;
			}
			printf("} ");
		}
	}
	
	// finding the transition for any new states created
	while(nscount>0){
		int st = NewState[--nscount];
		st = reverse(st);
		for(j=1;j<=a;j++){
			int new = -1, num =st;
			printf("\nSTATE %d for ALPHABET %c >>> {",NewState[nscount],rmap(j));
			while(num > 0){
				int r = num % 10;
				new = Union( new , result[r][j] );
				num = num/10;
			}
			printf("  %d } ", new);

		}
	}
				
	
}