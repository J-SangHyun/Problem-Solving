#include <iostream>
#include <string>
#include <vector>

using namespace std;
vector<int> kmp_search(string &S, string &W);
vector<int> kmp_table(string &W);

int main(void) {
    string T, P;
    getline(cin, T);
    getline(cin, P);
    
    vector<int> searched = kmp_search(T, P);
    int n_searched = searched.size();
    cout << n_searched << endl;
    for(int i = 0; i < n_searched; i++) {
        cout << searched[i] + 1 << "\n";
    }
    return 0;
}

vector<int> kmp_search(string &S, string &W) {
    int j = 0, k = 0, nP = 0, n = S.size(), m = W.size();
    vector<int> T = kmp_table(W), P;
    
    while(j < n) {
        if(W[k] == S[j]) {
            j++;
            k++;
            if(k == m) {
                P.push_back(j - k);
                k = T[k];
            }
        }
        else {
            k = T[k];
            if(k < 0) {
                j++;
                k++;
            }
        }
    }
    return P;
}

vector<int> kmp_table(string &W) {
    int m = W.size(), pos = 1, cnd = 0;
    vector<int> T(m+1);
    T[0] = -1;
    while(pos < m) {
        if(W[pos] == W[cnd]) {
            T[pos] = T[cnd];
        }
        else {
            T[pos] = cnd;
            while(cnd >= 0 && W[pos] != W[cnd]) {
                cnd = T[cnd];
            }
        }
        pos++;
        cnd++;
    }
    T[pos] = cnd;
    return T;
}

