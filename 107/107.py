from math import log

def summation(a, r, n):
    if r != 1.0:
        return a * (r ** n - 1) / (r - 1)
    else:
        return a * n

while True:
    line = input().split()

    a = int(line[0])
    b = int(line[1])

    if a == 0 and b == 0:
        print('0 0')
        break

    stop = False

    if b == 1:
        if a == 1:
            print('0 1')
            continue
        else:
            N = 1
    else:
        for N in range(2, a):
            if abs(log(a, b) - log(N + 1, N)) < 0.000001:
                break

    n = int(round(log(a, N + 1)))

    r_a = summation(1, N, n)
    r_b = summation(a, float(N) / float(N + 1), n + 1)

    s = '{} {}'.format(int(r_a), int(round(r_b)))

    print(s)
