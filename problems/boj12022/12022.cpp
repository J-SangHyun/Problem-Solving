#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(void) {
    int N, input;
    cin >> N;
    
    vector<queue<int> > male(N);
    vector<vector<int> > female(N, vector<int>(N));
    
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> input;
            male[i].push(input-1);
        }
    }
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> input;
            female[i][input-1] = N - j;
        }
    }
    
    queue<int> free_male;
    vector<int> female_partner(N, -1), male_partner(N);
    for(int i = 0; i < N; i++) {
        free_male.push(i);
    }
    
    int current_male, current_female, current_partner;
    while(!free_male.empty()) {
        current_male = free_male.front();
        current_female = male[current_male].front();
        male[current_male].pop();
        current_partner = female_partner[current_female];
        if(current_partner == -1) {
            female_partner[current_female] = current_male;
            free_male.pop();
        }
        else if(female[current_female][current_male] > female[current_female][current_partner]) {
            female_partner[current_female] = current_male;
            free_male.push(current_partner);
            free_male.pop();
        }
    }
    
    for(int i = 0; i < N; i++) {
        male_partner[female_partner[i]] = i;
    }
    for(int i = 0; i < N; i++) {
        cout << male_partner[i] + 1 << "\n";
    }
    return 0;
}

