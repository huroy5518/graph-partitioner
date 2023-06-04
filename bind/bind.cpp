#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include "AdjacentListGraph.hpp"
#include "Mesh.hpp"
#include "LDGPartitioner.hpp"
#include "KernighanLinPartitioner.hpp"
#include "KernighanLinPartitionerFast.hpp"

namespace py=pybind11;
PYBIND11_MODULE(GraphPartitioner, m) {
    py::class_<MeshElement>(m, "MeshElement")
        .def(py::init<>())
        .def(py::init<const std::vector<double> &>());
    py::class_<MeshGrid>(m, "MeshGrid")
        .def(py::init<int>());
    py::class_<AdjacentListGraph>(m, "Graph")
        .def(py::init<>())
        .def(py::init<size_t>())
        .def(py::init<const std::vector<std::vector<double>>&>())
        .def(py::init<const std::vector<std::vector<double>>&&>())
        .def(py::init<const AdjacentListGraph &>())
        .def(py::init<py::array_t<double> &, py::array_t<double>&>())
        .def(py::init<py::array_t<double> &, py::array_t<double>&, bool>(), py::arg("xv"), py::arg("yv"), py::arg("sparse") = false)
        .def("add_edge", &AdjacentListGraph::addEdge, py::arg("v1"), py::arg("v2"), py::arg("weight") = double(1.0))
        .def_property_readonly("nvert", &AdjacentListGraph::nvert)
        .def_property_readonly("neighbor", &AdjacentListGraph::neighbor)
        // .def("add_edge_list", static_cast<void (AdjacentListGraph::*)(const ))
        .def("add_edge_list", py::overload_cast<const std::vector<std::pair<size_t, size_t>>&>(&AdjacentListGraph::addEdgeList))
        .def("add_edge_list", py::overload_cast<const std::vector<std::tuple<const size_t, const size_t, double>>&>(&AdjacentListGraph::addEdgeList));
    py::class_<LDGPartitioner>(m, "LDGPartitioner")
        // .def(py::init<>())
        .def(py::init<const AdjacentListGraph&>())
        .def("part", &LDGPartitioner::Part, py::arg("target_k") = 1)
        .def("part_numpy_mesh", &LDGPartitioner::PartNumpyMesh, py::arg("target_k") = 1);
    py::class_<KernighanLinPartitioner>(m, "KernighanLinPartitioner")
        .def(py::init<const AdjacentListGraph&>())
        .def("part", &KernighanLinPartitioner::Part, py::arg("target_k") = 1, py::arg("max_iter") = 1)
        .def("part_numpy_mesh", &KernighanLinPartitioner::PartNumpyMesh, py::arg("target_k") = 1, py::arg("max_iter") = 1);
    py::class_<KernighanLinPartitionerFast>(m, "KernighanLinPartitionerFast")
        .def(py::init<const AdjacentListGraph&>())
        .def("part", &KernighanLinPartitionerFast::Part, py::arg("target_k") = 1, py::arg("max_iter") = 1)
        .def("part_numpy_mesh", &KernighanLinPartitionerFast::PartNumpyMesh, py::arg("target_k") = 1, py::arg("max_iter") = 1);
}