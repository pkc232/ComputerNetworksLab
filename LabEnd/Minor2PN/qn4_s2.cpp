#include <iostream>
#include <fstream>
using namespace std;
int main()
{
  
  while(!feof(stdin))
  {
     char buff[50];
     cin>>buff;
     cout<<buff<<endl;  
  }


 return 0;
}
