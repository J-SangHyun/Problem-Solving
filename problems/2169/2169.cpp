#include <iostream>
#include <vector>

using namespace std;
typedef vector<int> vint;

int main(void) {
    int N, M, v_from_up, v_from_left, v_from_right;
    bool visited;
    cin >> N >> M;
    vector<vint> value(N, vint(M));
    vector<vint> dp_left(N, vint(M));
    vector<vint> dp_right(N, vint(M));
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> value[i][j];
        }
    }
    
    v_from_left = 0;
    for(int j = 0; j < M; j++) {
        v_from_left += value[0][j];
        dp_left[0][j] = v_from_left;
        dp_right[0][j] = -100 * (j+1);
    }
    
    for (int i = 1; i < N; i++) {        
        // update dp_left from left to right
        dp_left[i][0] = max(dp_left[i-1][0], dp_right[i-1][0]) + value[i][0];
        for (int j = 1; j < M; j++) {
            v_from_up = max(dp_left[i-1][j], dp_right[i-1][j]);
            v_from_left = dp_left[i][j-1];
            dp_left[i][j] = max(v_from_up, v_from_left) + value[i][j];
        }
        
        //update dp_right from right to left
        dp_right[i][M-1] = max(dp_left[i-1][M-1], dp_right[i-1][M-1]) + value[i][M-1];
        for (int j = M-2; j >= 0; j--) {
            v_from_up = max(dp_left[i-1][j], dp_right[i-1][j]);
            v_from_right = dp_right[i][j+1];
            dp_right[i][j] = max(v_from_up, v_from_right) + value[i][j];
        }
    }
    cout << max(dp_left[N-1][M-1], dp_right[N-1][M-1]) << endl;
    return 0;
}

