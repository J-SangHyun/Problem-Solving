#include <iostream>

using namespace std;
long long gcd(long long a, long long b);

int main(void) {
    int N;
    long long a, b, balance = 0, M = 0, minM = -1;
    cin >> N;
    
    for(int i = 0; i < N; i++) {
        cin >> a >> b;
        if(b - a - balance < 0) {
            M = -1;
            break;
        }
        else if(b - a - balance > 0) {
            minM = max(minM, b);
            M = gcd(b - a - balance, M);
            
            if(M <= minM) {
                M = -1;
                break;
            }
        }
        balance = b;
    }
    if(M == 0) {
        M = 1;
    }
    
    cout << M << "\n";
    return 0;
}

long long gcd(long long a, long long b) {
    return b ? gcd(b, a % b) : a;
}

