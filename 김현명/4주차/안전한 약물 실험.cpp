#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <iostream>

using namespace std;

int n, k;
int nums[10];
string poison[10];
int path[10];
int safe_num;

void dfs(int depth, int max_depth, int idx) {
    // 탐색하려는 약품 개수가 되었을 경우
    if (depth >= max_depth) {

        // 약품이 안전한지를 본다.
        bool is_safe = true;

        // k개의 독극물을 탐색한다.
        for (int i = 0; i < k; i++) {
            int p_num = 0;

            // 독극물의 각 요소가 약품조합(path)에 부합할 경우 p_num += 1을 해준다.
            for (int s = 0; s < poison[i].length(); s++) {
                for (int j = 0; j < max_depth; j++) {
                    if ((int)(poison[i][s]-'0') == path[j]) {
                        p_num += 1;
                        break;
                    }
                }
            }
            // 독극물의 조합이 있는 경우 안전하지 않다.
            if (p_num == poison[i].length()) {
                is_safe = false;
            }
        }

        // 안전하다면 개수를 센다.
        if (is_safe) {
            safe_num += 1;
        }

        return;
    }

    // 3 5 7

    // 약물 조합 만들기
    for (int i = idx; i < n; i++) {
        path[depth] = nums[i];
        dfs(depth + 1, max_depth, i + 1);
    }
}

int main() {
    cin >> n;

    // 약물 정보 입력하기
    for (int i = 0; i < n; i++) {
        nums[i] = i+1;
    }

    cin >> k;

    // 독 정보 입력하기
    for (int i = 0; i < k; i++) {
        string tmp;
        cin >> tmp;
        poison[i] = tmp;
    }

    // 안전한지 탐색하기
    // 약품개수: 1 ~ n 개
    // 모든 약물 조합의 경우를 본다.
    for (int i = 1; i < n + 1; i++) {
        dfs(0,i,0);
    }

    cout << safe_num << endl;

    return 0;
}