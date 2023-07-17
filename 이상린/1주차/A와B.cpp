#include <iostream>
#include <string>
#include <algorithm> // reverse 사용

using namespace std;

int rst = 0;
string S,T; 

void Func()
{
    if (T.size()==S.size())
    {
        if (S==T) rst = 1;
        return;
    }

    string now = T;
    // 마지막이 A면 제거
    if (T[T.size()-1]=='A')
    {
        T.erase(T.end()-1);
        Func();
        T=now;
    }
    // 첫글자가 B면 제거 후 reverse
    if (T[0]=='B')
    {
        T.erase(T.begin());
        reverse(T.begin(),T.end());
        Func();
    }
}

int main()
{
    cin >> S >> T;
    Func();
    cout << rst;

    return 0;
}