# _*_ coding: utf-8 _*_
# Author: flyfish(飞鱼)
# Email: xiaoranone@126.com

from data import SortData
import time
import copy

def partition(sd, l, r):
    p = l
    i = l + 1
    j = r
    while True:
        while i < r and sd.data[i] <= sd.data[p]: 
            sd.update_color(i, sd.blue)
            sd.visualizer()
            time.sleep(0.2)
            sd.update_color(i, sd.red)
            i += 1
        while j > l and sd.data[j] > sd.data[p]: 
            sd.update_color(j, sd.blue)
            sd.visualizer()
            time.sleep(0.2)
            sd.update_color(j, sd.red)
            j -= 1
        if i >= j:
            break
        else:
            sd.update_color(i, sd.red)
            sd.update_color(j, sd.red)
            sd.visualizer()
            time.sleep(0.2)
            sd.swap(i, j)
            i += 1
            j -= 1
    sd.swap(p, j)
    sd.update_color(p, sd.red)
    sd.update_color(j, sd.red)
    sd.visualizer()
    return j

def quick_sort_util(sd, l, r):
    if l >= r: 
        return
    p = partition(sd, l, r)
    quick_sort_util(sd, l, p-1)
    quick_sort_util(sd, p+1, r)

def quicksort(sd):
    size = len(sd.data)
    quick_sort_util(sd, 0, size-1)
    time.sleep(3)

if __name__ == "__main__":
    sd = SortData(size=16)
    quicksort(sd)