/**
 * @file dcel.hpp
 * @brief This is the header file for the dcel class
*/

#ifndef DCEL_H
#define DCEL_H

#include <vector>
#include "vertex.hpp"
#include "face.hpp"
#include "halfedge.hpp"
using namespace std;
class Vertex;
class Face;
class halfEdge;

class Dcel {
public:
    /**
     * @class Dcel
     * @brief This is the Dcel class which `stores the vertices, faces and half edges.
     * It has functions to add a vertex, half edge and face.
     * It has functions to traverse the face and polygon
     * @param vector<Vertex *> vertices - a vector of vertices
     * @param vector<Face *> faces - a vector of faces
     * @param vector<halfEdge *> edges - a vector of half edges
    */

    void addVertex(double xx, double yy, int id);
    void addhalfEdge(Vertex *s, Vertex *t);
    void addFace(halfEdge *he);
    void traverseFace(Face *f);
    void traverseFace2(halfEdge *h);
    void traversePoly();
    vector<Vertex *> vertices;
    vector<Face *> faces;
    vector<halfEdge *> edges;
};

#endif /* DCEL_H */
