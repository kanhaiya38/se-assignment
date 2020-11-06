import sys


def find_primes(n: int) -> None:
    prime = [True] * (n + 1)
    p = 2
    for i in range(2, n + 1, 1):
        if prime[i] == True:
            for j in range(i * i, n + 1, i):
                prime[j] = False

    for i in range(2, n + 1, 1):
        if prime[i] == True:
            print(i, end=' ')
    print()


if __name__ == "__main__":
    n = int(sys.argv[1])
    find_primes(n)
