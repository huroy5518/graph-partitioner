import networkx as nx
from networkx.algorithms.community import kernighan_lin_bisection
import timeit
from GraphPartitioner import *
import numpy as np


def test_networx_kernighan_lin_bisection_speed_small():
    graph = nx.Graph()


    n = 5

    edges = []
    for i in range(n):
        for j in range(n):
            if i > 0:
                edges.append(((i - 1) * n + j, ((i) * n + j)))
            if j > 0:
                edges.append(((i) * n + j - 1, (i) * n + j))


    graph.add_edges_from(edges)
    with open('test/performance/networkx_kernighan_lin_bisection_time.txt', 'w') as f:
        val = timeit.timeit('kernighan_lin_bisection(graph)', number=10, globals={'kernighan_lin_bisection': kernighan_lin_bisection, 'graph': graph})
        f.write(f'''for small graph time use = {val:.20f}\n''')

def test_ldg_part_speed_small():
    graph = Graph()
    nx, ny = (5, 5)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)

    xv, yv = np.meshgrid(x, y)
    X = Graph(xv, yv)
    part = LDGPartitioner(X)
    with open('test/performance/ldg_time.txt', 'w') as f:
        val = timeit.timeit('part.part(2)', number=10, globals={'part': part})
        f.write(f'''for small graph time use = {val:.20f}\n''')

def test_kernighan_lin_fast_speed_small():
    graph = Graph()
    nx, ny = (5, 5)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)

    xv, yv = np.meshgrid(x, y)
    X = Graph(xv, yv)
    part = KernighanLinPartitionerFast(X)
    with open('test/performance/kernighan_lin_fast_time.txt', 'w') as f:
        val = timeit.timeit('part.part(2)', number=10, globals={'part': part})
        f.write(f'''for small time use = {val:.20f}\n''')

def test_kernighan_lin_speed_small():
    graph = Graph()
    nx, ny = (5, 5)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)

    xv, yv = np.meshgrid(x, y)
    X = Graph(xv, yv)
    part = KernighanLinPartitioner(X)
    with open('test/performance/kernighan_lin_time.txt', 'w') as f:
        val = timeit.timeit('part.part(2)', number=10, globals={'part': part})
        f.write(f'''for small time use = {val:.20f}\n''')

def test_networx_kernighan_lin_bisection_speed_large():
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
    with open('test/performance/networkx_kernighan_lin_bisection_time.txt', 'a') as f:
        val = timeit.timeit('kernighan_lin_bisection(graph)', number=10, globals={'kernighan_lin_bisection': kernighan_lin_bisection, 'graph': graph})
        f.write(f'''for large time use = {val:.20f}\n''')

def test_ldg_part_speed_large():
    graph = Graph()
    nx, ny = (25, 25)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)

    xv, yv = np.meshgrid(x, y)
    X = Graph(xv, yv)
    part = LDGPartitioner(X)
    with open('test/performance/ldg_time.txt', 'a') as f:
        val = timeit.timeit('part.part(2)', number=10, globals={'part': part})
        f.write(f'''for large time use = {val:.20f}\n''')

def test_kernighan_lin_fast_speed_large():
    graph = Graph()
    nx, ny = (25, 25)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)

    xv, yv = np.meshgrid(x, y)
    X = Graph(xv, yv)
    part = KernighanLinPartitionerFast(X)
    with open('test/performance/kernighan_lin_fast_time.txt', 'a') as f:
        val = timeit.timeit('part.part(2)', number=10, globals={'part': part})
        f.write(f'''for large time use = {val:.20f}\n''')

def test_kernighan_lin_speed_large():
    graph = Graph()
    nx, ny = (25, 25)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)

    xv, yv = np.meshgrid(x, y)
    X = Graph(xv, yv)
    part = KernighanLinPartitioner(X)
    with open('test/performance/kernighan_lin_time.txt', 'a') as f:
        val = timeit.timeit('part.part(2)', number=10, globals={'part': part})
        f.write(f'''for large time use = {val:.20f}\n''')

def test_ldg_part_speed_small_3():
    graph = Graph()
    nx, ny = (5, 5)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)

    xv, yv = np.meshgrid(x, y)
    X = Graph(xv, yv)
    part = LDGPartitioner(X)
    with open('test/performance/ldg_time.txt', 'a') as f:
        val = timeit.timeit('part.part(3)', number=10, globals={'part': part})
        f.write(f'''for k=3 small graph time use = {val:.20f}\n''')

def test_kernighan_lin_fast_speed_small_3():
    graph = Graph()
    nx, ny = (5, 5)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)

    xv, yv = np.meshgrid(x, y)
    X = Graph(xv, yv)
    part = KernighanLinPartitionerFast(X)
    with open('test/performance/kernighan_lin_fast_time.txt', 'a') as f:
        val = timeit.timeit('part.part(3)', number=10, globals={'part': part})
        f.write(f'''for k=3 small graph time use = {val:.20f}\n''')

def test_kernighan_lin_speed_small_3():
    graph = Graph()
    nx, ny = (5, 5)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)

    xv, yv = np.meshgrid(x, y)
    X = Graph(xv, yv)
    part = KernighanLinPartitioner(X)
    with open('test/performance/kernighan_lin_time.txt', 'a') as f:
        val = timeit.timeit('part.part(3)', number=10, globals={'part': part})
        f.write(f'''for k=3 small graph time use = {val:.20f}\n''')

def test_ldg_part_speed_large_3():
    graph = Graph()
    nx, ny = (25, 25)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)

    xv, yv = np.meshgrid(x, y)
    X = Graph(xv, yv)
    part = LDGPartitioner(X)
    with open('test/performance/ldg_time.txt', 'a') as f:
        val = timeit.timeit('part.part(3)', number=10, globals={'part': part})
        f.write(f'''for k=3 large time use = {val:.20f}\n''')

def test_kernighan_lin_fast_speed_large_3():
    graph = Graph()
    nx, ny = (25, 25)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)

    xv, yv = np.meshgrid(x, y)
    X = Graph(xv, yv)
    part = KernighanLinPartitionerFast(X)
    with open('test/performance/kernighan_lin_fast_time.txt', 'a') as f:
        val = timeit.timeit('part.part(3)', number=10, globals={'part': part})
        f.write(f'''for k=3 large time use = {val:.20f}\n''')

def test_kernighan_lin_speed_large_3():
    graph = Graph()
    nx, ny = (25, 25)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)

    xv, yv = np.meshgrid(x, y)
    X = Graph(xv, yv)
    part = KernighanLinPartitioner(X)
    with open('test/performance/kernighan_lin_time.txt', 'a') as f:
        val = timeit.timeit('part.part(3)', number=10, globals={'part': part})
        f.write(f'''for k=3 large time use = {val:.20f}\n''')