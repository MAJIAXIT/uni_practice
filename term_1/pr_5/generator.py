from random import seed
from random import randint

ROW = 7
COLUMN = 5
ARRAY_SIZE = 57

seed(1)
_set = set()
while len(_set) < ARRAY_SIZE + ROW * COLUMN:
    _set.add(randint(-999, 999))

_set = [_ for _ in _set]
arr = [_set[_] for _ in range(ARRAY_SIZE)]
matrix = [_set[_] for _ in range(ARRAY_SIZE, ARRAY_SIZE + ROW * COLUMN)]

print(f"array size {ARRAY_SIZE}:\n")
print(*arr, sep=' ')

print(f"\nmatrix {ROW}x{COLUMN}:\n")
for i in range(ROW):
    print(*matrix[COLUMN * i: COLUMN * (i + 1)])

print("\narray min: ", min(arr))
print("matrix min: ", min(matrix))
