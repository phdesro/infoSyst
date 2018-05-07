int main(arg)   {
	//int i, j,k ,r;
	int i;
		
	/* ---- test if ----
	if (i==j)
		printf("dansif");
	else
		printf("danselse");
	printf("horsif");

	if(i<3)	{
		printf("dansif");	
		printf("dansif");
		printf("dansif");
	} else {
		printf("danselse");
		printf("danselse");
	}
	printf("horsif");
	*/
	
	/* --- test operation ---
	j=4 ;
	k=8 ;
	
	r=(i+j)*(i+k/j) ;
	*/

	/* ---- test asm if ----
	if(i>= 0)
		i=3;
	else
		i = 5;
	i = i + 1;
 	*/

	/* ---- test asm while ---- */

	while(i < 5) {
		i = i + 1;
	}
}
