/** 
 * @file vertex.hpp
 * @brief This is the header file for the vertex class
*/

#ifndef VERTEX_H
#define VERTEX_H

class Vertex{
    /**
     * @class Vertex
     * @brief is the vertex class that stores the x,y coordinates and id of the vertex
     * @param double xx - a double
     * @param double yy - a double
     * @param int idd - an integer
    */

    // declaring the required attributes for the vertex class - x,y coordinates and id
    public:
    double x, y;
    int id;
    Vertex(double xx, double yy, int idd);
};

#endif /* VERTEX_H */