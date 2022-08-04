#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

#define MAX_GEN 12
#define N_SURV 230

using namespace std;
int N;
int gene_score(vector<vector<bool> > &board, vector<int> &gene);
bool cmp_gene(vector<int> &g1, vector<int> &g2);

int main(void) {
    cin >> N;
    
    char HT;
    vector<vector<bool> > board(N, vector<bool>(N));
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> HT;
            board[i][j] = (HT == 'H');
        }
    }
    
    int N_GENE = N_SURV * (N_SURV - 1) / 2;
    vector<vector<int> > genes(N_GENE, vector<int>(2*N + 1));
    for(int gen = 0; gen < MAX_GEN; gen++) {
        if(gen == 0) {
            for(int g = 0; g < N_GENE; g++) {
                for(int i = 0; i < 2*N; i++) {
                    genes[g][i] = rand() % 2;
                }
            }
        }
        else {
            int n_gene = 0, mix_idx;
            vector<vector<int> > new_genes(N_GENE, vector<int>(2*N + 1));
            for(int i = 0; i < N_SURV - 1; i++) {
                for(int j = i + 1; j < N_SURV; j++) {
                    for(int k = 0; k < 2*N; k++) {
                        new_genes[n_gene][k] = rand()%2 ? genes[i][k] : genes[j][k];
                    }
                    n_gene++;
                }
            }
            genes = new_genes;
        }
        
        for(int g = 0; g < N_GENE; g++) {
            genes[g][2*N] = gene_score(board, genes[g]);
        }
        sort(genes.begin(), genes.end(), cmp_gene);
    }
    cout << N*N - genes[0][2*N] << "\n";
    return 0;
}

int gene_score(vector<vector<bool> > &board, vector<int> &gene) {
    int score = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(board[i][j] != (gene[i] != gene[N+j])) {
                score++;
            }
        }
    }
    return score;
}

bool cmp_gene(vector<int> &g1, vector<int> &g2) {
    return g1[2*N] > g2[2*N];
}

