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

def insert_sort(a: List[int]):
    n = len(a)
    if (n < 2):
        return
    for i in range(1,n):
        tmp = a[i]

        j = i -1 
        while j >= 0 and tmp < a[j]:
            a[j+1] = a[j]
            j -= 1
        a[j+1] = tmp

        # this can not work, because in case j = 0 and tmp < a[0], a[0] will not be updated as tmp
        # for j in range(i-1, -1, -1):
        #     if tmp < a[j]:
        #         a[j+1] = a[j]
        #     else:
        #         break
        # a[j+1] = tmp
    

def select_sort(a: List[int]):
    n = len(a)
    if (n < 2):
        return
    for i in range(n):
        index = i
        for j in range(i+1, n):
            if (a[j] < a[index]):
                index = j
            
        if index != i:
            a[i], a[index] = a[index], a[i]
            

def test_sort():
    a = [random.randint(1, 10) for i in range(10)]
    print(a)
    select_sort(a)
    print(a)


test_sort()
