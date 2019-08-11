# _*_ coding: utf-8 _*_
# Author: flyfish(飞鱼)
# Email: xiaoranone@126.com

import sys, time, random
import pygame

class SortData(object):
    """构造适合排序显示的数据集
    Parms:
        size: int, 排序的数据集合的大小[1,size], 
        dataset: list, 自己传入的待排序的list
        rect_width: int, 代表数字的矩形的宽度，默认是10    
    """
    def __init__(self, size=32, dataset=None, rect_width=10, 
                 rect_interval=3, rect_height=10, shuffle=True, app_size=(800, 500)):
        self.data = [x for x in range(1, size+1)]
        if dataset and isinstance(dataset, list):
            self.data = dataset
        if shuffle:
            random.shuffle(self.data)
        
        self.rect_interval = rect_interval
        self.rect_width = rect_width
        self.rect_height = rect_height
        self.app_size = app_size
        self.start_x = 50
        self.start_y = 500
        self.balck = (15,15,15)
        self.yellow = (255,255,0)
        self.red = (255,0,0)
        self.white = (255,255,255)
        self.blue = (0,0,255)
        # 初始化颜色
        self.rect_colors = [self.yellow for i in range(len(self.data))]
        
#         print(self.data)
        
        self.positions = []
        for i in range(len(self.data)):
            pos = [self.start_x+self.rect_width*i+self.rect_interval*i, self.start_y-(self.rect_height*self.data[i]), self.rect_width, self.start_y]
            self.positions.append(pos)
        
        pygame.init()
        self.screen = pygame.display.set_mode(self.app_size)
        pygame.display.set_caption("Sort Visualizer")
        self.screen.fill((self.balck))
        for i in range(len(self.positions)):
            pos = self.positions[i]
            color = self.rect_colors[i]
            pygame.draw.rect(self.screen,color, pos)
        pygame.display.update()
    
    def visualizer(self):
        pygame.init()
        self.screen = pygame.display.set_mode(self.app_size)
        pygame.display.set_caption("Sort Visualizer")
        self.screen.fill((self.balck))
        for i in range(len(self.positions)):
            pos = self.positions[i]
            color = self.rect_colors[i]
            pygame.draw.rect(self.screen,color, pos)
        pygame.display.update()
        
        
    def update_visual(self, idx):
        self.screen.fill(self.balck)
        for i in range(len(self.positions)):
            pos = self.positions[i]
            if i == idx:
                pygame.draw.rect(self.screen,self.red, pos)
            else:
                pygame.draw.rect(self.screen,self.yellow, pos)
        pygame.display.update()        
    
    def update_color(self, idx, color):
        self.rect_colors[idx] = color
    
    def swap(self, i, j):
        self.update_color(i, color=self.yellow)
        self.update_color(i, color=self.red)
        self.data[i],self.data[j] = self.data[j],self.data[i] 
#         self.rect_colors[i], self.rect_colors[j] = self.rect_colors[j], self.rect_colors[i]
        self.positions[i][1],self.positions[j][1] = self.positions[j][1],self.positions[i][1] 
    
    def set(self, i, value, pos):
        """
        set 数据是三元组， 数值--data， 位置--positions，颜色--color
        """
        if i < 0 or i >= len(self.data):
            raise("下标越界")
        self.data[i] = value
        self.positions[i][1] = pos[1]
    
    def get(self, i):
        return self.data[i], self.positions[i]

    def close(self):
        time.sleep(3)
        for event in pygame.event.get():
            if event.type == pygame.QUIT: 
                pygame.quit()
                sys.exit()

    def message(self):
        myfont=pygame.font.Font(None,24)
        textImage=myfont.render("swaping",True,self.white)
        self.screen.blit(textImage,(300, 250))
    
    def test_sort(self):
        print(self.data)
        for i in range(len(self.data)):
            # 标记当前的之
            self.update_color(i, color=self.red)
            for j in range(i+1,len(self.data)):
                time.sleep(0.1)                    
                self.update_color(j, color=self.blue)
                if self.data[i] > self.data[j]:
                    self.swap(i, j)
                self.visualizer()
                self.update_color(j, color=self.yellow)
            self.visualizer()
        print(self.data)

if __name__ == "__main__":
    sd = SortData(size=16)
    sd.test_sort()
    sd.close()