# 魔方阵
n = int(input())
magic_square = [
    [0 for x in range(n)] for y in range(n)
]
x = n // 2
y = n - 1
magic_square[x][y] = 1
for i in range(2, n * n + 1):
    tx = x
    ty = y
    x -= 1
    y += 1
    if x == -1:
        x = n-1
    if y == n:
        y = 0
    if magic_square[x][y] != 0:
        x = tx
        y = ty # 恢复影响
        y -= 1
    magic_square[x][y]=i

for i in range(0, n):
    for j in range(0, n):
        print('%2d ' % (magic_square[i][j]),end='')
        if j == n - 1:
            print()