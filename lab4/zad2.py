import matplotlib.pyplot as plt
from simanneal import Annealer
import math
import random
import numpy as np
import sys
import os

if len(sys.argv) != 8:
    print('usage: python3 zad2.py n d energy_strategy move_strategy tsp_steps fill_box? output_folder')
    exit(1)

n = int(sys.argv[1])
d = float(sys.argv[2])
energy_strat = sys.argv[3]
move_strat = sys.argv[4]
tsp_steps = int(sys.argv[5])
fill_box = bool(sys.argv[6])
output_folder = sys.argv[7]

if not os.path.exists(output_folder):
    os.makedirs(output_folder)

text_file = open(output_folder + "/run_arguments.txt", "w")
text_file.write("n = " + str(n) + " d = " + str(d) + "energy_strategy = " + energy_strat + " move_strategy = " + move_strat + " tsp_steps = " + str(tsp_steps) + " fill_box? = " + str(fill_box))
text_file.close()

def populate(array, density, do_fill_box=False):
    for i in range(array.shape[0]):
        for j in range(array.shape[1]):
            if i < 10 and j < 10 and do_fill_box:
                array[i][j] = True
            if random.uniform(0.0, 1.0) < density:
                array[i][j] = True

def plot(image, name, title='starting image'):
    plt.imshow(img, cmap='Greys')
    plt.savefig(output_folder + name, bbox_inches='tight')

img = np.zeros((n, n), dtype=bool)
populate(img, d, fill_box)
plot(img, '/start.png')



class BinaryImg(Annealer):
    
    def __init__(self, init_bitmap, energy_strategy='4neigh', move_strategy='slow'):
        self.x_last = init_bitmap.shape[0] - 1
        self.y_last = init_bitmap.shape[1] - 1
        self.bitmap = init_bitmap
        self.energy_strategy = energy_strategy
        self.move_strategy = move_strategy
        self.energy_stats = list()
        super(BinaryImg, self).__init__(init_bitmap)
        
    def plot_energy_stats(self, save=True):
        plt.plot(*zip(*self.energy_stats), 'ro')
        if save:
            plt.savefig(output_folder + '/energy_stats.png')
        else:
            plt.show()
    
    ## Move stuff here
    
    def move(self):
        if self.move_strategy == 'rows':
            self._move_rows()
        else:
            self._move_all()

    
    def _move_all(self):
        for i in range(self.bitmap.shape[0]):
            for j in range(self.bitmap.shape[1]):
                if self.bitmap[i][j]:
                    x_dir = random.choice([-1, 0, 1])
                    y_dir = random.choice([-1, 0, 1])
                    self._try_move(i, j, x_dir, y_dir)
    
    def _move_rows(self):
        if random.uniform(0.0, 1.0) < 0.5:
            a = random.randint(0, self.x_last)
            b = random.randint(0, self.x_last)
            self.bitmap[:,[a, b]] = self.bitmap[:,[b, a]]
        else:
            a = random.randint(0, self.y_last)
            b = random.randint(0, self.y_last)
            self.bitmap[[a, b]] = self.bitmap[[b, a]]
    
    # x, y make direction vector
    def _try_move(self, i, j, x, y):
        if i + x >= 0 and i + x <= self.x_last and j + y >= 0 and j + y <= self.y_last and not self.bitmap[i + x][j + y]:
            self.bitmap[i][j] = False
            self.bitmap[i + x][j + y] = True
            return True
        return False
    
    ## Energy stuff here
    
    def energy(self):
        res = 0
        for i in range(self.bitmap.shape[0]):
            for j in range(self.bitmap.shape[1]):
                res += self._neighbourhood_energy(i, j)
        return res
    
    
    def _neighbourhood_energy(self, i, j):
        if self.energy_strategy == '4neigh':
            return self._4neigh_energy(i, j)
        if self.energy_strategy == '8neigh':
            return self._8neigh_energy(i, j)
        if self.energy_strategy == 'pull_push':
            return _pull_push_energy(i, j)
        return res
    
    def _4neigh_energy(self, i, j):
        res = 0
        if i != 0:
            res += self.bitmap[i-1][j]
        if i != self.x_last:
            res += self.bitmap[i+1][j]
        if j != 0:
            res += self.bitmap[i][j-1]
        if j != self.y_last:
            res += self.bitmap[i][j+1]
        return res
    
    def _8neigh_energy(self, i, j):
        res = self._4neigh_energy(i, j)
        if i != 0:
            if j != 0:
                res += self.bitmap[i-1][j-1]
            if j != self.y_last:
                res += self.bitmap[i-1][j+1]
        if i != self.x_last:
            if j != 0:
                res += self.bitmap[i-1][j-1]
            if j != self.y_last:
                res += self.bitmap[i-1][j+1]
        return res

    
    def update(self, step, T, E, acceptance, improvement):
        if step % int(self.steps * 0.1) == 0:
            self.energy_stats.append([step, E])
        self.default_update(step, T, E, acceptance, improvement)
            


tsp = BinaryImg(img, energy_strat, move_strat)
tsp.steps = tsp_steps 
tsp.copy_strategy = "slice"

res_img, e = tsp.anneal()


plot(img, '/result.png')
tsp.plot_energy_stats()
