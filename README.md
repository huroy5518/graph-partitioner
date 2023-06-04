# graph-partitioner
A library that can perform graph partitioning.

## Basic Information
Graph partition can be used in many area. Especially in computing area. For some computing problems, like solving PDEs, we can try to distributely computing numerical result by partition graph partitioning.
For this project, we aim to provide one or more graph partition library that is easy to use.

## Problem to Solve
The definition of graph partition is the reduction of a graph to smaller graph by partitioning its set of nodes into mutally exclusive groups. With edges accros between the groups.

The problem has been known to be NP-complete, however, there still be some heuristic algorithms for finding good solutions for graph partition, include spectral partitioning, recursive partitioning, multi-level partitioning, and evolutionary algorithms.

This project will try to implement one or more algorithm for graph partitioning.

## System Architecture
- Implement the library in C++.
- An interface for C++.
- An interface for python by using pybind11.

## API Description
- Please see the demo.ipynb

## Engineering Infrastructure
- Use ``Make`` to build the code
- Use ``pytest`` for testing and evulation
- Use ``git`` for version control

## Reference
- [Graph Partition Wiki](https://en.wikipedia.org/wiki/Graph_partition)
- [Kernighan-Lin, Graph Distance Metrics](https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/kernlin.pdf)
- [An Efficient Heuristic Procedure for Partitioning Graphs](https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=6771089)
- [Linear Determinist Greedy Partition](https://blog.csdn.net/qq_39731130/article/details/118080392)