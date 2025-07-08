for x in range(100, 1000):
    if (x // 100) ** 3 + (x // 10 % 10) ** 3 + (x % 10) ** 3 == x:
        print(x)
