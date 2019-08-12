# _*_ coding: utf-8 _*_
# Author: flyfish(飞鱼)
# Email: xiaoranone@126.com

import sys
from src.data import SortData
from src.bubblesort import bubblesort
from src.selectsort import selectsort
from src.insertsort import insertsort
from src.mergesort import mergesort

import argparse

def get_args():
    parser=argparse.ArgumentParser(description="Sort Visulization")
    parser.add_argument('-s','--size',type=int,default=32)
    parser.add_argument('-t','--sort_type',type=str,default='bubblesort', 
                                        choices=["bubblesort","selectsort","insertsort",
                                        "mergesort"])

    args = parser.parse_args()
    return args


if __name__ == "__main__":
    args = get_args()
    size = args.size
    sort_type = args.sort_type

    sd = SortData(size=size)
    sort_method = eval(sort_type)
    sort_method(sd)
