#include <stdio.h>


int printer(int toReturn)
{
	printf("Build version is ");
	
#ifdef BX_VERSION
	printf(BX_VERSION);
#else
	printf("undefined");
#endif
	printf("\n");
	
	
	printf("Build time is ");
	
#ifdef BX_TIME
	printf(BX_TIME);
#else
	printf("undefined");
#endif
	printf("\n");

  return toReturn;
  
}
