import networkx as nx
from networkx.algorithms.community import kernighan_lin_bisection
import timeit
from GraphPartitioner import *
import numpy as np


def test_networx_kernighan_lin_bisection_metric_large():
    graph = nx.Graph()

    n = 25

    edges = []
    for i in range(n):
        for j in range(n):
            if i > 0:
                edges.append(((i - 1) * n + j, ((i) * n + j)))
            if j > 0:
                edges.append(((i) * n + j - 1, (i) * n + j))


    graph.add_edges_from(edges)
    l = list(kernighan_lin_bisection(graph))
    cut_num = 0
    node_num = {0: len(l[0]), 1: len(l[1])}
    for i in range(n):
        for j in range(n):
            if i:
                if (i * n + j) in l[0]:
                    c1 = 0
                else:
                    c1 = 1
                if ((i - 1) * n + j) in l[0]:
                    c2 = 0
                else:
                    c2 = 1
                if c1 != c2:
                    cut_num += 1
            if j:
                if (i * n + j) in l[0]:
                    c1 = 0
                else:
                    c1 = 1
                if ((i) * n + j - 1) in l[0]:
                    c2 = 0
                else:
                    c2 = 1
                if c1 != c2:
                    cut_num += 1

    with open('test/performance/networkx_kernighan_lin_bisection_metric.txt', 'w') as f:
        f.write(f'''for large graph and k = 2\ncut_num = {cut_num}\nnode_num={node_num}\n''')

def test_ldg_part_metric_large():
    graph = Graph()
    nx, ny = (25, 25)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)

    xv, yv = np.meshgrid(x, y)
    X = Graph(xv, yv)
    part = LDGPartitioner(X)

    p = part.part_numpy_mesh(2)
    cut_num = 0
    node_num = {0: 0, 1: 0}

    for i in range(len(p)):
        for j in range(len(p[i])):
            node_num[p[i][j]] += 1
            if i:
                if p[i - 1][j] != p[i][j]:
                    cut_num += 1
            if j:
                if p[i][j] != p[i][j - 1]:
                    cut_num += 1
    with open('test/performance/ldg_metric.txt', 'w') as f:
        f.write(f'''for large graph and k = 2\ncut_num = {cut_num}\nnode_num={node_num}\n''')

def test_kernighan_lin_fast_metric_large():
    graph = Graph()
    nx, ny = (25, 25)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)

    xv, yv = np.meshgrid(x, y)
    X = Graph(xv, yv)
    part = KernighanLinPartitionerFast(X)
    
    p = part.part_numpy_mesh(2)
    cut_num = 0
    node_num = {0: 0, 1: 0}

    for i in range(len(p)):
        for j in range(len(p[i])):
            node_num[p[i][j]] += 1
            if i:
                if p[i - 1][j] != p[i][j]:
                    cut_num += 1
            if j:
                if p[i][j] != p[i][j - 1]:
                    cut_num += 1
    with open('test/performance/kernighan_lin_fast_metric.txt', 'w') as f:
        f.write(f'''for large graph and k = 2\ncut_num = {cut_num}\nnode_num={node_num}\n''')

def test_kernighan_lin_metric_large():
    graph = Graph()
    nx, ny = (25, 25)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)

    xv, yv = np.meshgrid(x, y)
    X = Graph(xv, yv)
    part = KernighanLinPartitioner(X)

    p = part.part_numpy_mesh(2)
    cut_num = 0
    node_num = {0: 0, 1: 0}

    for i in range(len(p)):
        for j in range(len(p[i])):
            node_num[p[i][j]] += 1
            if i:
                if p[i - 1][j] != p[i][j]:
                    cut_num += 1
            if j:
                if p[i][j] != p[i][j - 1]:
                    cut_num += 1
    with open('test/performance/kernighan_lin_metric.txt', 'w') as f:
        f.write(f'''for large graph and k = 2\ncut_num = {cut_num}\nnode_num={node_num}\n''')

def test_ldg_part_metric_large_3():
    graph = Graph()
    nx, ny = (25, 25)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)

    xv, yv = np.meshgrid(x, y)
    X = Graph(xv, yv)
    part = LDGPartitioner(X)

    p = part.part_numpy_mesh(3)
    cut_num = 0
    node_num = {0: 0, 1: 0, 2:0}

    for i in range(len(p)):
        for j in range(len(p[i])):
            node_num[p[i][j]] += 1
            if i:
                if p[i - 1][j] != p[i][j]:
                    cut_num += 1
            if j:
                if p[i][j] != p[i][j - 1]:
                    cut_num += 1
    with open('test/performance/ldg_metric.txt', 'a') as f:
        f.write(f'''for large graph and k = 3\ncut_num = {cut_num}\nnode_num={node_num}\n''')

def test_kernighan_lin_fast_metric_large_3():
    graph = Graph()
    nx, ny = (25, 25)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)

    xv, yv = np.meshgrid(x, y)
    X = Graph(xv, yv)
    part = KernighanLinPartitionerFast(X)
    
    p = part.part_numpy_mesh(3)
    cut_num = 0
    node_num = {0: 0, 1: 0, 2:0}

    for i in range(len(p)):
        for j in range(len(p[i])):
            node_num[p[i][j]] += 1
            if i:
                if p[i - 1][j] != p[i][j]:
                    cut_num += 1
            if j:
                if p[i][j] != p[i][j - 1]:
                    cut_num += 1
    with open('test/performance/kernighan_lin_fast_metric.txt', 'a') as f:
        f.write(f'''for large graph and k = 3\ncut_num = {cut_num}\nnode_num={node_num}\n''')

def test_kernighan_lin_metric_large_3():
    graph = Graph()
    nx, ny = (25, 25)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)

    xv, yv = np.meshgrid(x, y)
    X = Graph(xv, yv)
    part = KernighanLinPartitioner(X)

    p = part.part_numpy_mesh(3)
    cut_num = 0
    node_num = {0: 0, 1: 0, 2:0}

    for i in range(len(p)):
        for j in range(len(p[i])):
            node_num[p[i][j]] += 1
            if i:
                if p[i - 1][j] != p[i][j]:
                    cut_num += 1
            if j:
                if p[i][j] != p[i][j - 1]:
                    cut_num += 1
    with open('test/performance/kernighan_lin_metric.txt', 'a') as f:
        f.write(f'''for large graph and k = 3\ncut_num = {cut_num}\nnode_num={node_num}\n''')