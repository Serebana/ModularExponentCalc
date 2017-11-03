#include <iostream>
#include "time.h"
#include <fstream>
#include <math.h>
#include "RSA.h"
using namespace std;
int main() {
    RSA a,b,c,z;
    a.Input();
    b.Input();
    c.Input(1);
    int t=clock();
    z=a.PowMod(b,c);
    t=clock()-t;
    cout<<"\n time="<<dec<<(float)t/CLOCKS_PER_SEC<<"\n Exit"<<endl;
    z.Output('z');
    return 0;
}