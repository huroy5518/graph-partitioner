import pytest
from GraphPartitioner import *
import numpy as np

def test_ldg_partitioner_small():
    nx, ny = (3, 2)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)

    xv, yv = np.meshgrid(x, y)
    X = Graph(xv, yv)
    part = LDGPartitioner(X)
    part.part(3)

def test_ldg_partitioner_large():
    nx, ny = (25, 25)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)

    xv, yv = np.meshgrid(x, y)
    X = Graph(xv, yv)
    part = LDGPartitioner(X)
    part.part(3)

def test_kernighan_partitioner_small():
    nx, ny = (3, 2)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)

    xv, yv = np.meshgrid(x, y)
    X = Graph(xv, yv)
    part = KernighanLinPartitioner(X)
    l = part.part(3)

def test_kernighan_partitioner_large():
    nx, ny = (25, 25)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)

    xv, yv = np.meshgrid(x, y)
    X = Graph(xv, yv)
    part = KernighanLinPartitioner(X)
    l = part.part(3)

def test_kernighanfast_partitioner_small():
    nx, ny = (3, 2)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)

    xv, yv = np.meshgrid(x, y)
    X = Graph(xv, yv)
    part = KernighanLinPartitionerFast(X)
    l = part.part(3)

def test_kernighanfast_partitioner_large():
    nx, ny = (25, 25)
    x = np.linspace(0, 1, nx)
    y = np.linspace(0, 1, ny)

    xv, yv = np.meshgrid(x, y)
    X = Graph(xv, yv)
    part = KernighanLinPartitionerFast(X)
    l = part.part(3)