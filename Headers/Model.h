#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cfloat>

#include "Vector.h"

/* 
 ? This header file defines a Model. A Model is a 3D object read from a .obj file.
 ? A Model is a struct that is later used by a GameObject. It is also defined two
 ? more structs: Face and VertexNormal which are characteristic from .obj files.
 */

struct VertexNormal {
    float x;
    float y;
    float z;
};

struct Face {
    int v1; // Vertex
    int v2;
    int v3;
    int vn1; // Vertex normal
    int vn2;
    int vn3;
};

struct Model {
    std::vector<Vec3> vertices;
    std::vector<VertexNormal> verticesNormals;
    std::vector<Face> faces;
    Vec3 minVertex;
    Vec3 maxVertex;

    /* 
     * Obtain the min and max vertices of the model and set them to the model that called the function.
     * 
     * No parameters.
     * No return.
     */ 
    void getMinMaxVertices() {
        std::vector<Vec3> v = vertices;
        Vec3 minV = v.at(0);
        Vec3 maxV = v.at(0);

        for (int i = 1; i < v.size(); i++) {
            if (v.at(i).x < minV.x) 
                minV.x = v.at(i).x;
            if (v.at(i).y < minV.y) 
                minV.y = v.at(i).y;
            if (v.at(i).z < minV.z) 
                minV.z = v.at(i).z;

            if (v.at(i).x > maxV.x) 
                maxV.x = v.at(i).x;
            if (v.at(i).y > maxV.y) 
                maxV.y = v.at(i).y;
            if (v.at(i).z > maxV.z) 
                maxV.z = v.at(i).z;
        }
        minVertex = minV;
        maxVertex = maxV;
    }

    /* 
     * Print the model's vertices, normals and faces.
     * 
     * No parameters.
     * No return.
     */ 
    void printModel() {
        std::cout << "-- Vertices --" << "\n";
        std::cout << "=> Total vertices: " << vertices.size() << "\n";
        for (Vec3 vertex : vertices)
            std::cout << "v " << vertex.x << " " << vertex.y << " " << vertex.z << "\n";

        std::cout << "-- Vertices Normals -- " << "\n";
        std::cout << "=> Total vertices normals: " << verticesNormals.size() << "\n";
        for (VertexNormal vertexNormal : verticesNormals)
            std::cout << "vn " << vertexNormal.x << " " << vertexNormal.y << " " << vertexNormal.z << "\n";
        
        std::cout << "\n";
        std::cout << "-- Faces --" << "\n";
        std::cout << "=> Total faces: " << faces.size() << "\n";
        for (Face face : faces)
            std::cout << "f " << face.v1 << "//" << face.vn1 << " " << face.v2 << "//" << face.vn2 << " " << face.v3 << "//" << face.vn3 << "\n";
    }
};

/* 
 * Loads a 3D model from a .obj file. The file indicating how the faces are constructed
 * must have the following format: "1//1" (Vertex/ /Normal). Texture coordinates are not allowed.
 * There are two examples of valid .obj files in the folder "3DObjects".
 * Another characteristic of this functon is that it only reads triangles, which means that any
 * other .obj that has "squares" must be transformed into only triangles.
 * 
 * Parameters: `textureID` and `size`.
 * No return.
 */ 
inline void loadModel(std::string filePath, std::vector<Model>& models) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "ERROR! Could not find: " << filePath << "\n";
        exit(EXIT_FAILURE);
    }

    std::string symbol = "";
    char skipChar = '0';
    Model model;
    std::string line = "";

    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        lineStream >> symbol;

        if (symbol == "v") {
            Vec3 vertex;
            lineStream >> vertex.x >> vertex.y >> vertex.z;
            model.vertices.push_back(vertex);
        }
        else if (symbol == "vn") {
            VertexNormal vertexNormal;
            lineStream >> vertexNormal.x >> vertexNormal.y >> vertexNormal.z;
            model.verticesNormals.push_back(vertexNormal);
        }
        else if (symbol == "f") {
            Face face;
            lineStream >> face.v1 >> skipChar >> skipChar >> face.vn1 >> face.v2 >> skipChar >> skipChar >> face.vn2 >> face.v3 >> skipChar >> skipChar >> face.vn3;
            model.faces.push_back(face);
        }
        else {
            continue;
        }
    }
    model.getMinMaxVertices();
    models.push_back(model);

    file.close();
}

#endif // MODEL_H