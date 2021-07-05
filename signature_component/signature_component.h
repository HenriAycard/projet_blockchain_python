//
//  Signature.h
//  Composant-Signature
#pragma once
#ifndef _BLOC_H

#include <stdio.h>
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <pybind11/pybind11.h>
#include <nlohmann/json.hpp>
#include <pybind11_json/pybind11_json.hpp>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

namespace py = pybind11;

using namespace std;

class Signature {
public:
    string signMessage(string data, string private_key);
    bool validateSignature(string data, string public_key, string signature);
private:
    uint8_t* hex_str_to_uint8(const char* string);
};


#endif
