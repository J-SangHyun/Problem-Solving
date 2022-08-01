#include <iostream>
#include <vector>

using namespace std;
long long power_2(int sumAB, int K);

int main(void) {
    int T, A, B, K;
    long long pow, minAB;
    cin >> T;
    
    for(int i = 0; i < T; i++) {
        cin >> A >> B >> K;
        minAB = min(A, B);
        pow = power_2(A+B, K);
        minAB = (minAB * pow) % (A+B);
        cout << "#" << i+1 << " " << min(minAB, A+B-minAB) <<  "\n";
    }
    
    return 0;
}

long long power_2(int sumAB, int K) {
    if(K == 0) {
        return 1;
    }
    long long half, mult;
    half = power_2(sumAB, K/2);
    mult = (half * half) % sumAB;
    if(K % 2 == 0) {
        return mult;
    }
    else {
        mult = (2 * mult) % sumAB;
        return mult;
    }
}

