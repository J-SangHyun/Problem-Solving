S = input()
characters = sorted(list(set(S)))

dp = [[-1 for _ in range(len(S))] for _ in range(len(characters))]

for i in range(len(characters)):
    min_pos, max_pos = -1, -1
    for pos in range(len(S)):
        if S[pos] == characters[i]:
            min_pos = pos if min_pos == -1 else min_pos
            max_pos = pos

    for end in range(len(S)):
        if S[end] != characters[i]:
            continue
        if i == 0:
            start = 0
            dp[i][end] = max_pos - min_pos
            dp[i][end] += min(abs(start - min_pos) + abs(end - max_pos),
                              abs(end - min_pos) + abs(start - max_pos))
        else:
            min_dist = -1
            for start in range(len(S)):
                if dp[i-1][start] != -1:
                    dist = max_pos - min_pos
                    dist += min(abs(start - min_pos) + abs(end - max_pos),
                                abs(end - min_pos) + abs(start - max_pos))
                    dist += dp[i-1][start]
                    if min_dist == -1 or min_dist > dist:
                        min_dist = dist
            dp[i][end] = min_dist

min_total_dist = -1
for i in range(len(S)):
    if dp[-1][i] == -1:
        continue
    if min_total_dist == -1 or min_total_dist > dp[-1][i]:
        min_total_dist = dp[-1][i]
print(min_total_dist + len(S))
