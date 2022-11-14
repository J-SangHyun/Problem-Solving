C, N = list(map(int, input().split()))

pairs = []
for _ in range(N):
    pairs.append(list(map(int, input().split())))

dp = [0 for _ in range(C+1)]
for i in range(1, C+1):
    min_value = -1
    for pair in pairs:
        cost, customer = pair
        total_cost = cost + (dp[i-customer] if i >= customer else 0)
        if min_value == -1 or min_value > total_cost:
            min_value = total_cost
    dp[i] = min_value

print(dp[C])
