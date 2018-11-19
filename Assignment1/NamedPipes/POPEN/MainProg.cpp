#include <bits/stdc++.h>
#include <stdio.h>
#include <sys/types.h>
using namespace std;


int main(int argc, char const *argv[])
{
	char buff[BUFSIZ];
	FILE *fp = popen("ls","r");
	while ( fgets( buff, BUFSIZ, fp ) != NULL ) {
  		printf("LS->%s", buff );
	}
	pclose(fp);

	return 0;
}



