def digit(x):
    d = 0
    while x > 0:
        d += 1
        x //= 10
    return d

def main():
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    ans = 1
    for i in range(n):
        ans *= a[i]
        if digit(ans) > k:
            ans = 1
    print(ans)

if __name__ == "__main__":
    main()
