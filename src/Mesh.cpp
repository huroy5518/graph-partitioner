#include "Mesh.hpp"


MeshGrid::MeshGrid(int _dim) {
    this->dim = _dim;
}

MeshGrid::MeshGrid(std::vector<MeshElement> &_elements, int _dim) {
    this->dim = _dim;
    this->elements = elements;
}

MeshGrid::MeshGrid(std::vector<MeshElement> &&_elements, int _dim) {
    this->dim = _dim;
    this->elements = _elements;
}

MeshGrid::MeshGrid(MeshGrid &ano) {
    this->dim = ano.dim;
    this->elements = ano.elements;
}

MeshGrid::MeshGrid(MeshGrid &&ano) {
    this->dim = ano.dim;
    this->elements = ano.elements;
}

