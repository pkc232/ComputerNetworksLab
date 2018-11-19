#include <bits/stdc++.h>
#include <semaphore.h>
using namespace std;

sem_t s1,s2;
int x,y;


void *p1(void *n){
	while(1){
		sem_wait(s2);
		x=y+1;
		cout<<" Current x "<<x<<endl;
		sem_post(s1);
	}
}


void *p2(void *n){
	while(1){
		sem_wait(s1);
		y=x+1;
		cout<<"Current y "<<y<<endl;
		sem_post(s2);
	}
}

int main(int argc, char const *argv[])
{
	sem_init(&s1,0,0);
	sem_init(&s2,0,1);
	x=0,y=0;

	



	return 0;
}

