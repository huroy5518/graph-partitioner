#ifndef __MESH_H
#define __MESH_H


#include <vector>

class MeshElement {
public:
    std::vector<double> coord;
    MeshElement() = default;
    MeshElement(const std::vector<double> &elem) {
        coord = elem;
    }
};

class MeshGrid {
private:
    std::vector<MeshElement> elements;
    int dim;
public:
    MeshGrid() = default;
    MeshGrid(int _dim = 2);
    MeshGrid(std::vector<MeshElement> &element, int _dim = 2);
    MeshGrid(std::vector<MeshElement> &&element, int _dim = 2);
    MeshGrid(MeshGrid &ano);
    MeshGrid(MeshGrid &&ano);
};

#endif