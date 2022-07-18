#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stdio.h>

using namespace std;
vector<double> p(4, 0);
int match[6][2];
double probs[6][3];
void dfs(vector<int> &pts, double prob, int idx);

int main(void) {
    string country1, country2;
    int idx1, idx2;
    double W, D, L;
    map<string, int> country2idx;
    
    for(int i = 0; i < 4; i++) {
        cin >> country1;
        country2idx[country1] = i;
    }
    
    for(int i = 0; i < 6; i++) {
        cin >> country1 >> country2 >> W >> D >> L;
        idx1 = country2idx[country1];
        idx2 = country2idx[country2];
        match[i][0] = idx1;
        match[i][1] = idx2;
        probs[i][0] = W;
        probs[i][1] = D;
        probs[i][2] = L;
    }
    vector<int> pts(4, 0);
    dfs(pts, 1.0, 0);
    
    for(int i = 0; i < 4; i++) {
        printf("%.10lf\n", p[i]);
    }
    return 0;
}

void dfs(vector<int> &pts, double prob, int idx) {
    if(idx == 6) {
        int first_max = 0, second_max = 0;
        vector<int> first_cnt, second_cnt;
        for(int i = 0; i < 4; i++) {
            if(first_max < pts[i]) {
                first_max = pts[i];
            }
        }
        for(int i = 0; i < 4; i++) {
            if(first_max == pts[i]) {
                first_cnt.push_back(i);
            }
        }
        for(int i = 0; i < 4; i++) {
            if(first_max != pts[i] && second_max < pts[i]) {
                second_max = pts[i];
            }
        }
        for(int i = 0; i < 4; i++) {
            if(second_max == pts[i]) {
                second_cnt.push_back(i);
            }
        }
        
        int n_first = first_cnt.size();
        int n_second = second_cnt.size();
        if(n_first == 1) {
            p[first_cnt[0]] += prob;
            for(int i = 0; i < n_second; i++) {
                p[second_cnt[i]] += prob / n_second;
            }
        }
        else {
            for(int i = 0; i < n_first; i++) {
                p[first_cnt[i]] += prob * 2 / n_first;
            }
        }
        return;
    }
    
    vector<int> new_pts;
    // case 1 : A > B
    new_pts = pts;
    new_pts[match[idx][0]] += 3;
    dfs(new_pts, prob * probs[idx][0], idx+1);
    
    // case 2 : A == B
    new_pts = pts;
    new_pts[match[idx][0]] += 1;
    new_pts[match[idx][1]] += 1;
    dfs(new_pts, prob * probs[idx][1], idx+1);
    
    // case 3 : A < B
    new_pts = pts;
    new_pts[match[idx][1]] += 3;
    dfs(new_pts, prob * probs[idx][2], idx+1);
}

