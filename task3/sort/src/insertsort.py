# _*_ coding: utf-8 _*_
# Author: flyfish(飞鱼)
# Email: xiaoranone@126.com

from .data import SortData
import time
import copy

def insertsort(sd):
    """插入排序
    Param:
        sd: SortData
    return: 
        sorted SortData
    """
    size = len(sd.data)
    for i in range(1, size):
        key, pos = copy.deepcopy(sd.get(i))
        sd.update_color(i, color=sd.red)
        j = i - 1
        while j >= 0 and sd.data[j] > key:
            time.sleep(0.1)
            sd.update_color(j, color=sd.blue)
            t_key, t_pos = sd.get(j)
            sd.set(j+1, t_key, t_pos)
            sd.visualizer()
            sd.update_color(j, color=sd.red)
            j = j - 1
        sd.set(j+1, key, pos)
        # sd.update_color(i, color=sd.red)        
    sd.visualizer()
    sd.close()
    return sd

if __name__ == "__main__":
    sd = SortData(size=16)
    insertsort(sd)