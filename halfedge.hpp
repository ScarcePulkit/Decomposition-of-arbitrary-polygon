/** 
 * @file halfEdge.hpp
 * @brief This is the header file for the half edge class
*/

#ifndef HALFEDGE_H
#define HALFEDGE_H

#include "vertex.hpp"
#include "face.hpp"

class Face;
class Vertex;

class halfEdge{
    /**
     * @class halfEdge
     * @brief This is the half edge class which stores the starting and ending vertex.
     * One can find the next half edge, previous half edge and twin half edge 
     * @param Vertex *s - starting vertex
     * @param Vertex *e - ending vertex
     * @param halfEdge *next - next half edge
     * @param halfEdge *prev - previous half edge
     * @param halfEdge *twin - twin half edge
    */

    // declaring the required attributes for the halfedge class
    public:
    Vertex *start, *end;
    halfEdge *next, *prev, *twin;
    Face *face;

    halfEdge(Vertex *s, Vertex *e);
};

#endif /* HALFEDGE_H */