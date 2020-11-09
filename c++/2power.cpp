#include <iostream>
using namespace std;
int power_of_two_ceil(int a)
{
    if(a < 1){
      cout <<"7th" << endl;
      return 0; 
    }
    else{
        int i ;
        int j;
        for(i=0; i<=30; i++ ){
            j = 1 << i;
            if(j >= a){
                return j;
            }
        }
        return 0;
    }  
}    


int main()   
{             
    cout << power_of_two_ceil((int)(1 << 30)) << endl;    
}