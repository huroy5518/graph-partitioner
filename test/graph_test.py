import pytest
import random
from GraphPartitioner import Graph, MeshGrid, LDGPartitioner
import numpy as np


def test_add_non_exist_vertex():
    x = Graph(10)
    try:
        x.addEdge(11, 12)
        assert False
    except:
        assert True

    return

def test_from_numpy_meshgrid_sparse():
    nx, ny = (3, 2)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)

    xv, yv = np.meshgrid(x, y, sparse=True)
    A = Graph(xv, yv, sparse=True)

    nx, ny, nz = (3, 2, 1)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)
    z = np.linspace(0, 1, nz)

    xv, yv, zv = np.meshgrid(x, y, z, sparse=True)
    try:
        A = Graph(xv, yv, True)
        assert False
    except:
        assert True

def test_from_numpy_meshgrid_non_sparse():
    nx, ny = (3, 2)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)

    xv, yv = np.meshgrid(x, y)
    A = Graph(xv, yv)

    nx, ny, nz = (3, 2, 1)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)
    z = np.linspace(0, 1, nz)

    xv, yv, zv = np.meshgrid(x, y, z)
    try:
        A = Graph(xv, yv)
        assert False
    except:
        assert True

def test_generate_graph():
    for _ in range(100):
        n = random.randint(10, 100)
        g = Graph(n)
        enum = random.randint(n, n * n)
        edges = dict()
        for k in range(enum):
            u = random.randint(1, n)
            v = random.randint(1, n)
            if edges.get((u, v), False):
                continue
            g.add_edge(u, v)
            edges[(u, v)] = True
            edges[(v, u)] = True



