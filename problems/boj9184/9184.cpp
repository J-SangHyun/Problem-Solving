#include <iostream>
#include <stdio.h>

using namespace std;
int w_dp[21][21][21];
int w(int a, int b, int c);

int main(void) {
    int a, b, c;
    for(a = 0; a <= 20; a++) {
        for(b = 0; b <= 20; b++) {
            for(c = 0; c <= 20; c++) {
                if(a < b && b < c) {
                    w_dp[a][b][c] = w(a, b, c-1) + w(a, b-1, c-1) - w(a, b-1, c);
                }
                else{
                     w_dp[a][b][c] = w(a-1, b, c) + w(a-1, b-1, c) + w(a-1, b, c-1) - w(a-1, b-1, c-1);
                }
            }
        }
    }
    
    while(true) {
        cin >> a >> b >> c;
        if(a == -1 && b == -1 && c == -1) {
            break;
        }
        printf("w(%d, %d, %d) = %d\n", a, b, c, w(a, b, c));
    }
    return 0;
}

int w(int a, int b, int c) {
    if(a <= 0 || b <= 0 || c <= 0) {
        return 1;
    }
    if(a > 20 || b > 20 || c > 20) {
        return w_dp[20][20][20];
    }
    return w_dp[a][b][c];
}

