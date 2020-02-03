from typing import List
import random

def merge_sentry(a: List[int], left: int, right: int, middle: int):
    ltmp = a[left: middle+1]
    rtmp = a[middle+1: right+1]
    ltmp.append(2^32)
    rtmp.append(2^32)

    i, j, k = 0, 0, left

    while k <= right:
        if ltmp[i] <= rtmp[j]:
            a[k] = ltmp[i]
            i, k = i+1, k+1
        else:
            a[k] = rtmp[j]
            j, k = j+1, k+1



def merge(a: List[int], left: int, right: int, middle: int):
    tmp = []
    i, j = left, middle+1
    while i <= middle and j <= right:
        if a[i] <= a[j]:
            tmp.append(a[i])
            i += 1
        else:
            tmp.append(a[j])
            j += 1
    start = i if j > right else j
    end = middle if j > right else right
    tmp.extend(a[start: end+1])
    a[left:right+1] = tmp
        


def merge_sort_btw(a: List[int], left: int, right: int):
    if left < right:
        m = (left + right)//2
        merge_sort_btw(a, left, m)
        merge_sort_btw(a, m+1, right)
        merge(a, left, right, m)
        #merge_sentry(a, left, right, m)        


def merge_sort(a: List[int]):
    merge_sort_btw(a, 0, len(a)-1)


def partition(a: List[int], left: int, right: int):
    k = random.randint(left, right)
    a[k], a[right] = a[right], a[k]
    j = left
    for i in range(left, right):
        if a[i] < a[right]:
            if i != j:
                a[i], a[j] = a[j], a[i]
            j += 1
    a[j], a[right] = a[right], a[j]
    return j 


def quick_sort_btw(a: List[int], left: int, right: int):
    if (left < right):
        m = partition(a, left, right)
        quick_sort_btw(a, left, m-1)
        quick_sort_btw(a, m+1, right)


def quick_sort(a: List[int]):
    quick_sort_btw(a, 0, len(a)-1)
            

def test_sort():
    a = [random.randint(1, 10) for i in range(10)]
    print(a)
    quick_sort(a)
    print(a)


test_sort()
