/**
 * @file face.hpp
 * @brief This is the header file for the face class
*/

#ifndef FACE_H
#define FACE_H

#include "halfedge.hpp"

class halfEdge;

class Face {
public:
    /**
     * @class Face
     * @brief This is the face class which stores the half edge, boolean and integer.
     * Given an edge of the face, one can traverse the face.
     * Boolean is used to check if the face is valid or not.
     * Integer is used to assign a unique id to each face.
     * @param halfEdge *e - half edge
     * @param bool valid - boolean
     * @param int idd - integer
    */

    halfEdge *edge;
    bool valid;
    int idd;

    Face(halfEdge *e);
};

#endif /* FACE_H */
