
#pragma once
#include <string>
#include <list>
#include <pybind11/pybind11.h>
#include <nlohmann/json.hpp>
#include <pybind11_json/pybind11_json.hpp>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

namespace py = pybind11;


class Hasheur {
public:
	Hasheur();
	std::string sha256(std::string data) {return "A8C8E2042F702DCA60AC688EDCDFC72F6EA535745B2A0FD01EF9506E4839C134";};
};
