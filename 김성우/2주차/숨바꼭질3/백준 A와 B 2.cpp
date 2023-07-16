#include <iostream>
#include <string>
using namespace std;

string s, t;

bool dfs(string current) {
    // 종료 조건: 현재 문자열이 목표 문자열인 t와 같은 경우
    if (current == t)
        return true;

    // 종료 조건: 현재 문자열의 길이가 t보다 큰 경우
    if (current.length() > t.length())
        return false;

    // 현재 문자열의 끝이 'A'인 경우
    if (current.back() == 'A') {
        current.pop_back(); // 마지막 문자 'A' 제거
        if (dfs(current)) // 재귀 호출
            return true;
        current.push_back('A'); // 복구
    }

    // 현재 문자열의 시작이 'B'이고, 끝이 'A'인 경우
    if (current.front() == 'B' && current.back() == 'A') {
        current.pop_back(); // 마지막 문자 'A' 제거
        reverse(current.begin(), current.end()); // 문자열 뒤집기
        if (dfs(current)) // 재귀 호출
            return true;
        reverse(current.begin(), current.end()); // 복구
        current.push_back('A'); // 복구
    }

    return false; // 위 종료 조건에 해당하지 않는 경우
}

int main() {
    cin >> s >> t;

    if (dfs(s))
        cout << "1\n";
    else
        cout << "0\n";

    return 0;
}
