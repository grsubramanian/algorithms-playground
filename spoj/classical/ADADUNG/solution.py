
def mod(x):
    return x % 1000000007

cache = [-1] * 10000001
cache[1] = 0
cache[2] = 1

def prepare_cache():
    global cache
    for i in range(3, 10000001):
        cache[i] = mod((i - 1) * (cache[i - 1] + cache[i - 2]))

if __name__ == '__main__':

    prepare_cache()

    import sys

    first = True
    for line in sys.stdin:
        if first:
            first = False
            continue
        N = int(line)
        sys.stdout.write(str(cache[N]) + '\n')

