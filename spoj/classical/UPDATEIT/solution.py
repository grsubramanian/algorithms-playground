# INPUT
from sys import stdin
line = iter(stdin.readlines())
def tokens(f):
    return [f(tok) for tok in next(line).split()]
def token(f):
    return tokens(f)[0]

# BUSINESS LOGIC
t = token(int)
ans = []
for _ in range(t):
    n, u = tokens(int)

    arr = [0] * n
    for _ in range(u):
        l, r, val = tokens(int)
        arr[l] += val
        if (r + 1) < n:
            arr[r + 1] -= val

    cum = 0
    for i in range(n):
        cum += arr[i]
        arr[i] = cum

    q = token(int)
    for _ in range(q):
        index = token(int)
        ans.append(str(arr[index]))

# OUTPUT
from sys import stdout
stdout.write('\n'.join(ans))

