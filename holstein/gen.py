#!/usr/bin/python
import random

def gen_data():
    with open("t15",'w') as f:
        V = 25
        f.writelines([str(V), '\n'])
        for i in range(0,V):
            f.write("1000 ")
        f.write('\n')

        G = 15
        f.writelines([str(G), '\n'])
        for i in range(0,G):
            for j in range(0,V):
                f.write(str(random.randint(0,1000)))
                f.write(' ')
            f.write('\n')

if __name__ == "__main__":
    gen_data()
