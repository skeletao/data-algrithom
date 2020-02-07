from typing import List
import random
import numpy as np
from functools import reduce

def binary_search(a: List[int], val: int):
    low = 0
    hi = len(a)-1
    while (low <= hi):
        mid = (low + hi)//2
        if (a[mid] == val):
            return mid
        elif (a[mid] < val):
            low = mid + 1
        else:
            hi = mid -1
    return -1

def test_sort():
    a = [random.randint(1, 10) for i in range(20)]
    b = 5
    print(a)
    res = binary_search(a, b)
    print('Find {0} in the list: {1}'.format(b, res))

test_sort()
