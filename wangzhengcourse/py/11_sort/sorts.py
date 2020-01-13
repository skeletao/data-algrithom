from typing import List
import random


def bubble_sort(a: List[int]):
    n = len(a)
    if (n < 2):
        return
    for i in range(n):
        swap_flag = False
        for j in range(n-i-1):
            if a[j] > a [j+1]:
                a[j], a[j+1] = a[j+1], a[j]
                swap_flag = True
        if not swap_flag:
            break



def test_sort():
    a = [random.randint(1, 10) for i in range(10)]
    bubble_sort(a)
    print(a)


test_sort()
