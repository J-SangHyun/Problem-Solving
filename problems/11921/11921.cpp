#include <stdio.h>
#define BUFFER_SIZE 1 << 20

using namespace std;
char read_buffer[BUFFER_SIZE];

int main(void) {
    bool is_N = true, in_num = false, stdin_end = false;
    char c;
    int read_idx = 0, next_idx = 0, N, n = 0, cnt = 0;
    long long sum = 0;
    
    while(true) {
        if(read_idx == next_idx) {
            next_idx = fread(read_buffer, sizeof(char), BUFFER_SIZE, stdin);
            if(next_idx == 0) {
                stdin_end = true;
            }
            read_idx = 0;
        }
        c = read_buffer[read_idx++];
        
        if(c == ' ' || c == '\n' || c == '\0' || stdin_end) {
            if(in_num && is_N) {
                N = n;
                is_N = false;
            }
            else if(in_num) {
                cnt++;
                sum += n;
            }
            in_num = false;
            n = 0;
            
            if(c == '\0' || stdin_end) {
                break;
            }
        }
        else if('0' <= c && c <= '9') {
            in_num = true;
            n = 10 * n + (c - '0');
        }
    }
    printf("%d\n%lld\n", cnt, sum);
    return 0;
}

