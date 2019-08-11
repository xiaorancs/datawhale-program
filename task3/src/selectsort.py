# _*_ coding: utf-8 _*_
# Author: flyfish(飞鱼)
# Email: xiaoranone@126.com

from .data import SortData
import time

def selectsort(sd):
    """选择排序
    Param:
        sd: SortData
    return: 
        sorted SortData
    """
    size = len(sd.data)
    for i in range(size):
        sd.update_color(i, color=sd.red)
        for j in range(i+1, size):
            time.sleep(0.1)
            sd.update_color(j, color=sd.blue)
            if sd.data[j] < sd.data[i]:
                sd.swap(j, i)
            sd.visualizer()
            sd.update_color(j, color=sd.yellow)
    sd.visualizer()
    sd.close()
    return sd

if __name__ == "__main__":
    sd = SortData(size=16)
    selectsort(sd)