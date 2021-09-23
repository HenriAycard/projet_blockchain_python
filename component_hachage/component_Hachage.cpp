//
// Created by ahmed on 30/05/2021.
//
#include "sha256/sha256/sha256.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cstring>



using std::cout; using std::endl;

class component_Hachage {
    public:
        component_Hachage() {}
        ~component_Hachage() {}

        std::string SHA256 (std::string input){
            std::string result;
            if(input.empty()) {
                cout << "ERROR input is empty !!" <<endl;
            }else {
                result = sha256(input);

            }
            return result;
        }

        bool checkValidity(std::string str, std::string strSHA){

            std ::string result=sha256(str);
            if(result.compare(strSHA)==0)
                return true;
            else
                return false;

        }




};

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(component_Hachage, m) {
    py::class_<component_Hachage>(m, "component_Hachage")
        .def(py::init())
        .def("SHA256", &component_Hachage::SHA256)
        .def("checkValidity", &component_Hachage::checkValidity);

}
