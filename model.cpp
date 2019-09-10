#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "model.h"

Model::Model(const char *filename) : verts_(), faces_() {                       // Q: Where verts_() and faces_() came from? (model.h - line 9, 10 mean variables, not functions). Maybe, they are constructors of vector and the class inherits them, but why?
    std::ifstream in;                                                           // make a new filestream
    in.open (filename, std::ifstream::in);                                      // open the object file
    if (in.fail()) return;
    std::string line;                                                           // a new string for get lines from the object file
    while (!in.eof()) {                                                         // before meet end of file
        std::getline(in, line);                                                 // get a line and put in the string
        std::istringstream iss(line.c_str());                                   // make a sequence of characters be access directly as a string object using member str
                                                                                // c_str() returns a pointer to an array that contains a null-terminated sequence of characters representing the current value of the string object.
        
        char trash;                                                             // Q: line 18~34
        if (!line.compare(0, 2, "v ")) {                                        // my guess: if 'v' push to verts
            iss >> trash;
            Vec3f v;
            for (int i=0;i<3;i++) iss >> v.raw[i];
            verts_.push_back(v);
        } else if (!line.compare(0, 2, "f ")) {                                 // else if 'f' push to f
            std::vector<int> f;
            int itrash, idx;
            iss >> trash;
            while (iss >> idx >> trash >> itrash >> trash >> itrash) {
                idx--; // in wavefront obj all indices start at 1, not zero
                f.push_back(idx);
            }
            faces_.push_back(f);
        }
    }                                                                           // but I still don't know what the face and the verts mean
    
    std::cerr << "# v# " << verts_.size() << " f# "  << faces_.size() << std::endl;  // error
}

Model::~Model() {                                                               // destructor
}

int Model::nverts() {                                                           // size of the private member verts_
    return (int)verts_.size();
}

int Model::nfaces() {                                                           // size of the private member faces_
    return (int)faces_.size();
}

std::vector<int> Model::face(int idx) {                                         // face(idx) = faces_[idx]
    return faces_[idx];
}

Vec3f Model::vert(int i) {                                                      // vert(idx) = verts_[i]
    return verts_[i];
}

