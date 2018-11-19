#include <bits/stdc++.h>
using namespace std;


int main(int argc, char const *argv[])
{
	int arr[10];
	for(int i=0;i<10;i++){
		cin>>arr[i];
	}

	sort(arr,arr+10);

	for(int i=0;i<10;i++)
		cout<<arr[i]<<endl;
	return 0;
}