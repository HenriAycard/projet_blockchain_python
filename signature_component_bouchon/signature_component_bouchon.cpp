//
//  Signature.cpp
//  Composant-Signature
//
//  Created by Henri Aycard on 26/06/2021.
//  Copyright © 2021 Aycard. All rights reserved.
//

#include "signature_component_bouchon.h"
#include "../Bloc.h"
#include "../Hasheur.h"
#include "micro-ecc/uECC.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>


namespace py = pybind11;
using namespace std;


__attribute__ ((visibility ("default"))) string Signature::signMessage(string data, string private_key) {
    uECC_Curve curve = uECC_secp256k1();
    string dataHashed = SHA256(data);
    uint8_t* hash = hex_str_to_uint8(dataHashed.c_str());
    uint8_t* _private = hex_str_to_uint8(private_key.c_str());
    uint8_t sig[128] = { 0 };

    if (!uECC_sign(_private, hash, sizeof(hash), sig, curve)) {
        cout << "uECC_sign() failed" << endl;
    }
    vector<uint8_t> sigVector = fill_vector(sig, 64); 
    return uint8_to_hex_str(sigVector);
}

__attribute__ ((visibility ("default"))) bool Signature::validateSignature(string data, string public_key, string _signature) {
    uECC_Curve curve = uECC_secp256k1();
    string dataHashed = SHA256(data);
    uint8_t* hash = hex_str_to_uint8(dataHashed.c_str());
    uint8_t* _public = hex_str_to_uint8(public_key.c_str());
    uint8_t* _sig = hex_str_to_uint8(_signature.c_str());

    if (!uECC_verify(_public, hash, sizeof(hash), _sig, curve)) {
        return false;
    }
    return true;
}

uint8_t* Signature::hex_str_to_uint8(const char* string) {

    if (string == NULL)
        return NULL;

    size_t slength = strlen(string);
    if ((slength % 2) != 0) // must be even
        return NULL;

    size_t dlength = slength / 2;

    uint8_t* data = (uint8_t*)malloc(dlength);

    memset(data, 0, dlength);

    size_t index = 0;
    while (index < slength) {
        char c = string[index];
        int value = 0;
        if (c >= '0' && c <= '9')
            value = (c - '0');
        else if (c >= 'A' && c <= 'F')
            value = (10 + (c - 'A'));
        else if (c >= 'a' && c <= 'f')
            value = (10 + (c - 'a'));
        else
            return NULL;

        data[(index / 2)] += value << (((index + 1) % 2) * 4);

        index++;
    }

    return data;
}

string Signature::uint8_to_hex_str(vector<uint8_t>& v) {
	stringstream ss;
	ss << std::hex << setfill('0');
	vector<uint8_t>::const_iterator it;

	for (it = v.begin(); it != v.end(); it++) {
		ss << setw(2) << static_cast<unsigned>(*it);
	}
	return ss.str();
}

vector<uint8_t> Signature::fill_vector(uint8_t* data, int size) {
	std::vector<uint8_t> out;
	for (int x = 0; x < size; x++){
		out.push_back(data[x]);
	}
	return out;
}

string Signature::SHA256(string data) {
    Hasheur hasheur = Hasheur();
    string result = hasheur.SHA256(data);
    return result;
}


PYBIND11_MODULE(signature_component_bouchon, m) {
    py::class_<Signature>(m, "Signature")
        .def(py::init())
        .def("signMessage", &Signature::signMessage)
        .def("validateSignature", &Signature::validateSignature);
}
