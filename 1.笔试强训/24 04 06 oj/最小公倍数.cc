#include <iostream>
using namespace std;

int main() {
    int a, b;
    while (cin >> a >> b) { // 注意 while 处理多个 case
       int i;
       for(i=1;i<=b;i++)
       {
            if(a*i%b==0)
            {
                break;
            }
       }
       cout<<a*i<<endl;
    }
}
// 64 位输出请用 printf("%lld")