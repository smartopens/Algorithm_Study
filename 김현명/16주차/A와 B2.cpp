#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

string s_word;
string t_word;

int s_n;
int t_n;

bool can_con;

// t문자에서 시작해서 한단계씩 내려간다.
// 마지막 문자가 A인 경우:
// 처음 문자가 A: now_t의 마지막 문자를 제거한다.
// 처음 문자가 B: 이전 단계에서 두가지 명령의 경우로 오는것이 가능하므로 둘다 넘겨준다.

// 마지막 문자가 B인 경우:
// 처음 문자가 A: 이런 경우가 올 수 없다. 그러므로 고려하지 않는다.
// 처음 문자가 B: 이전 단계에서 B를 붙이는 경우로 오는것이 가능하므로 문자 변환 후 넘겨준다.

void is_con(int tid, string now_t) {
    // S문자와 길이가 같아지는 경우
    // 같은지를 비교한다.
    if (tid == s_n-1)
    {
     
        if (s_word == now_t)
        {
            can_con = true;
        }
        return;
    }

    if (now_t[tid] == 'A') {
        if (now_t[0] == 'A') {
            is_con(tid - 1, now_t.substr(0, now_t.length() - 1));
        }
        else if (now_t[0] == 'B') {
            is_con(tid - 1, now_t.substr(0, now_t.length() - 1));
            string tmp1 = now_t.substr(1, now_t.length());
            string tmp2 = "";

            for (int i = 0; i < tmp1.length(); i++) {
                tmp2 += tmp1[tmp1.length() - i - 1];
            }
            is_con(tid - 1, tmp2);
        }
    }
    else if (now_t[tid] == 'B') {

        if (now_t[0] == 'B') {
            string tmp1 = now_t.substr(1, now_t.length());
            string tmp2 = "";

            for (int i = 0; i < tmp1.length(); i++) {
                tmp2 += tmp1[tmp1.length() - i - 1];
            }
            is_con(tid - 1, tmp2);
        }
    }
    return;
}

int main() {
    // s문자와 t문자 입력
    cin >> s_word;
    cin >> t_word;

    s_n = s_word.length();
    t_n = t_word.length();

    // t문자에서 한단계씩 돌아오면서 판단한다. 
    is_con(t_word.length()-1,t_word);

    // 전환 가능 여부 출력하기
    if (can_con) {
        cout << 1 << endl;
    }
    else {
        cout << 0 << endl;
    }
    return 0;
};