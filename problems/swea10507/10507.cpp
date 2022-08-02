#include <iostream>
#include <queue>

using namespace std;

int main(void) {
    int T, N, P, n, p, max_days;
    queue<int> Q;
    cin >> T;
    
    for(int t = 0; t < T; t++) {
        Q = queue<int>();
        cin >> N >> P;
        max_days = P;
        
        for(int i = 0; i < N; i++) {
            cin >> n;
            if(Q.size() == 0) {
                Q.push(n);
                p = P;
            }
            else {
                if(n - Q.back() - 1 > P) {
                    Q = queue<int>();
                    Q.push(n);
                    p = P;
                }
                else {
                    int front;
                    while(p < n - Q.back() - 1) {
                        front = Q.front();
                        Q.pop();
                        p += Q.front() - front - 1;
                    }
                    p -= n - Q.back() - 1;
                    Q.push(n);
                }
            }
            max_days = max(max_days, (int)Q.size() + P);
        }
        cout << "#" << t+1 << " " << max_days << "\n";
    }
    return 0;
}

