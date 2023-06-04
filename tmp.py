import numpy as np
from GraphPartitioner import Graph, LDGPartitioner, KernighanLinPartitioner, KernighanLinPartitionerFast

nx, ny = (25, 25)
x = np.linspace(0, 1, nx)
y = np.linspace(0, 1, ny)

xv, yv = np.meshgrid(x, y)
X = Graph(xv, yv)
# part = LDGPartitioner(X)
# l = part.Part(3)
part = KernighanLinPartitionerFast(X)
# X.addEdge(1, 2)
l = part.part_numpy_mesh(3)
print(l)
k = 25
for i in range(k):
    for j in range(k):
        print(l[i][j], end=' ')
    print()

# G = Graph(8)
# G.addEdge(1, 2)
# G.addEdge(1, 5)
# G.addEdge(1, 6)
# G.addEdge(2, 5)
# G.addEdge(2, 6)
# G.addEdge(3, 4)
# G.addEdge(3, 6)
# G.addEdge(3, 7)
# G.addEdge(3, 8)
# G.addEdge(4, 7)
# G.addEdge(4, 8)
# G.addEdge(5, 6)
# G.addEdge(7, 8)
# part = KernighanLinPartitioner(G)
# # part = LDGPartitioner(G)
# # X.addEdge(1, 2)
# l = part.Part(3)
# print(l)