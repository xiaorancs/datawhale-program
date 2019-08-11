# _*_ coding: utf-8 _*_
# Author: flyfish(飞鱼)
# Email: xiaoranone@126.com

from data import SortData
import time
import copy

def shellsort(sd):
    """希尔排序
    Param:
        sd: SortData
    return: 
        sorted SortData
    """
    size = len(sd.data)
    h = 1
    start = 0
    while h < size - 1:
        h = 3 * h + 1
    while h >= 1:
        for i in range(h, size):
            t_key, t_pos = copy.deepcopy(sd.get(i))
            j = i - h
            sd.update_color(i, sd.red)
            sd.visualizer()
            time.sleep(0.5)
            while j >= start and sd.data[j] > t_key:
                sd.update_color(j, sd.blue)
                sd.visualizer()
                time.sleep(0.5)
                sd.update_color(j, sd.red)
                sd.set(j+h, *sd.get(j))
                j -= h
            sd.set(j+h, t_key, t_pos) 
        h //= 3
    sd.visualizer()
    sd.close()
    return sd

if __name__ == "__main__":
    sd = SortData(size=16)
    print(sd.data)
    shellsort(sd)
    print(sd.data)