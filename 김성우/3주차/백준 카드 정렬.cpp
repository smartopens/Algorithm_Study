#include <iostream>
#include <queue>
using namespace std;

int main() {

    int n;
    cin >> n;

    priority_queue<int, vector<int>, greater<int>> pq; // 우선순위 큐 선언 (최소 힙)

    for (int i = 0; i < n; ++i) {
        int card;
        cin >> card;
        pq.push(card);
    }

    int result = 0;

    if (pq.size() == 1) {
        cout << result << endl;
    }
    else {
        for (int i = 0; i < n - 1; ++i) { // 2개씩 꺼내기 때문에 n-1
            int previous = pq.top();
            pq.pop();
            int current = pq.top();
            pq.pop();

            result += previous + current;
            pq.push(previous + current);
        }

        cout << result << endl;
    }

    return 0;
}
