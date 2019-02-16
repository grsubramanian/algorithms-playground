# INPUT
from sys import stdin
line = iter(stdin.readlines())
def tokens(f):
    return [f(tok) for tok in next(line).split()]
def token(f):
    return tokens(f)[0]

# BUSINESS LOGIC
n, k = tokens(int)
ans = 0
for _ in range(n):
    ti = token(int)
    if ti % k == 0:
        ans += 1

# OUTPUT
from sys import stdout
stdout.write(str(ans))

