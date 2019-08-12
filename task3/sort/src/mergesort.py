# _*_ coding: utf-8 _*_
# Author: flyfish(飞鱼)
# Email: xiaoranone@126.com

from .data import SortData
import time
import copy

def merge(sd, l, m, r):
    """
    合并数据集sd(SortData)
    merge sd[l, m] and sd[m+1, r]
    """
    sd.visualizer()
    sd_copy_data = copy.deepcopy(sd.data)
    sd_copy_positions = copy.deepcopy(sd.positions)

    i = l
    j = m+1
    k = l
    while i<=m and j<=r:
        sd.update_color(i, sd.blue)
        sd.update_color(j, sd.blue)
        sd.visualizer()
        time.sleep(0.4)
        if sd_copy_data[i] < sd_copy_data[j]:
            # sd.update_color(i, sd.blue)
            sd.set(k, sd_copy_data[i], sd_copy_positions[i])
            sd.update_color(k, sd.red)
            sd.update_color(i, sd.red)
            i += 1
            k += 1
        else:
            sd.set(k, sd_copy_data[j], sd_copy_positions[j])
            sd.update_color(k, sd.red)
            sd.update_color(j, sd.red)
            j += 1
            k += 1
        
        sd.visualizer()
        time.sleep(0.2)
    
    while i<=m:
        sd.set(k, sd_copy_data[i], sd_copy_positions[i])
        sd.update_color(k, sd.red)
        i += 1
        k += 1

    while j<=r:
        sd.set(k, sd_copy_data[j], sd_copy_positions[j])
        sd.update_color(k, sd.red)
        j += 1
        k += 1

    # del sd_copy_data, sd_copy_positions
    sd.visualizer()


def mergesort_util(sd, l, r):
    """[0, n-1]"""
    if l < r:
        m = (l+r) // 2
        mergesort_util(sd, l, m)
        mergesort_util(sd, m+1, r)
        merge(sd, l, m, r)

def mergesort(sd):
    # print(sd.data)
    size = len(sd.data)
    mergesort_util(sd, 0, size-1)
    sd.visualizer()
    time.sleep(2)
    # print(sd.data)

if __name__ == "__main__":
    sd = SortData(size=16)
    mergesort(sd)