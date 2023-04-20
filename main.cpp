/**
 * @file main.cpp
*/

/*
Pulkit Agrawal - 2020A7PS2072H
Ishan Chhangani - 2020A7PS0230H
Abhirath NB - 2020A7PS0260H
Samandeep Singh - 2020A7PS0065H
*/

#include <bits/stdc++.h>
using namespace std::chrono;
#include "dcel.hpp"
#include "vertex.hpp"
#include "face.hpp"
#include "halfedge.hpp"
using namespace std;
#define in(n) \
    double n; \
    cin >> n;
#define sz(x) static_cast<int>(x.size())
#define dbg(x) cerr << #x << "->" << x << "\n"
#define prnt(x)           \
    cerr << #x << '{';    \
    for (auto T : x)      \
        cerr << T << ' '; \
    cerr << "}\n";
#define prntp(x)                                   \
    cerr << #x << '{';                             \
    for (auto T : x)                               \
        cerr << T.first << '-' << T.second << ' '; \
    cerr << "}\n";
#define FAST cin.tie(0)->sync_with_stdio(0);

class Dcel;
class Vertex;
class Face;
class halfEdge;

Vertex::Vertex(double xx, double yy, int idd) {
    x = xx;
    y = yy;
    id = idd;
}

halfEdge::halfEdge(Vertex *s, Vertex *e) {
    start = s;
    end = e;
    next = NULL;
    prev = NULL;
    twin = NULL;
    face = NULL;
}

int g = 1;

Face::Face(halfEdge *e) {
    edge = e;
    valid = true;
    idd = g++;
}

class Point
{
    /**
     * @class Point
     * @brief This is the point class which stores the x,y coordinates and id of the point.
     * @param double xx - a double
     * @param double yy - a double
     * @param int idd - an integer
    */

    // declaring the required attributes for the point class - x,y coordinates and id
public:
    double x, y;
    int id;
    Point(double xx, double yy, int idd)
    {
        x = xx;
        y = yy;
        id = idd;
    }
};

// adds a half edge to the dcel
void Dcel::addhalfEdge(Vertex *s, Vertex *t) {
    /**
     * @brief This function adds a half edge to the Dcel
     * @param Vertex *s - starting vertex
     * @param Vertex *t - ending vertex
     * @return NULL
    */
    halfEdge *h = new halfEdge(s, t);
    edges.push_back(h);
}

// adds a face to the dcel
void Dcel::addFace(halfEdge *he) {
    /**
     * @brief This function adds a face to the Dcel
     * @param halfEdge *he - half edge
     * @return NULL
    */
    Face *f = new Face(he);
    faces.push_back(f);
}

// traverses a specific face(component of a polygon)
void Dcel::traverseFace(Face *f) {
    /**
     * @brief This function traverses a specific face of the polygon with given face.
     * @param Face *f - a face
     * @return NULL
    */
    if (f->valid == false)
        return;

    halfEdge *h = f->edge;
    halfEdge *temp = h;
    do {
        Vertex *s = temp->start;
        Vertex *e = temp->end;
        cout << s->id << " " << e->id << endl;
        temp = temp->next;
    } while (temp != h);
}

// traverses the face with the edge
void Dcel::traverseFace2(halfEdge *h) {
    /**
     * @brief This function traverses a specific face on a given half edge.
     * @param halfEdge *h - a half edge
     * @return NULL
    */

    halfEdge *temp = h;
    do {
        Vertex *s = temp->start;
        Vertex *e = temp->end;
        cout << s->id << " " << e->id << endl;
        temp = temp->next;
    } while (temp != h);
}

void Dcel::traversePoly()
{
    /**
     * @brief This function traverses all the faces of the polygon.
     * @param NULL
     * @return NULL
    */
    freopen("outputAfterMerge.txt", "w+", stdout);
    int cnt = 0;
    for (int i = 0; i < faces.size(); i++)
    {
        if (faces[i]->valid)
            cnt++;
    }
    cout << cnt << endl;
    vector<pair<double, double>> coor;
    for (int i = 0; i < faces.size(); i++)
    {
        if (faces[i]->valid == false)
            continue;

        halfEdge *h = faces[i]->edge;
        halfEdge *temp = h;
        do
        {
            Vertex *s = temp->start;
            Vertex *e = temp->end;
            //cout<<s->id<<" "<<e->id<<endl;
            coor.push_back({s->x, s->y});
            temp = temp->next;
        } while (temp != h);

        cout << coor.size();
        cout << endl;

        for (int i = 0; i < coor.size(); i++)
        {
            cout << coor[i].first << " " << coor[i].second << endl;
        }
        coor.clear();
    }
}

// adds a vertex to the dcel
void Dcel::addVertex(double xx, double yy, int id) {
    /**
     * @brief This function adds a vertex to the Dcel
     * @param double xx - a double
     * @param double yy - a double
     * @param int id - an integer
     * @return NULL
    */
    Vertex *v = new Vertex(xx, yy, id);
    vertices.push_back(v);
}

class Rect
{
    /**
     * @class Rect
     * @brief This is the rectangle class, and it creates a rectangle.
     * @param double minxx - a double
     * @param double minyy - a double
     * @param double maxxx - a double
     * @param double maxyy - a double
    */

    // creating a rectangle with the leftmost, rightmost, topmost and bottommost points
public:
    double minx, miny, maxx, maxy;
    Rect(double minxx, double minyy, double maxxx, double maxyy)
    {
        maxx = maxxx;
        maxy = maxyy;
        minx = minxx;
        miny = minyy;
    }

    // whether a point is in the rectangle or not
    bool isInRect(Point *p)
    {
        /**
         * @brief This function checks whether a point is in a rectangle or not.
         * @param Point *p - a point
         * @return bool
        */
        if (p->x > minx && p->x < maxx)
        {
            if (p->y > miny && p->y < maxy)
                return true;
        }
        return false;
    }
};

double CrossProduct(vector<Point *> &A)
{
    /**
     * @brief This function calculates the cross product of two vectors.
     * @param vector<Point *> &A - a vector of points
     * @return double
    */

    // checks whether angle is greater than 180 or not
    double X1 = (A[1]->x - A[0]->x);
    double Y1 = (A[1]->y - A[0]->y);
    double X2 = (A[1]->x - A[2]->x);
    double Y2 = (A[1]->y - A[2]->y);
    // if (X1 * Y2 - Y1 * X2 == 0)
    //     cout << "Linear";
    return (X1 * Y2 - Y1 * X2);
}

// function to find the leftmost, rightmost, topmost and bottommost points
Rect *genRect(vector<Point *> L)
{
    /**
     * @brief This function generates a rectangle with the leftmost, rightmost, topmost and bottommost points.
     * @param vector<Point *> L - a vector of points
     * @return Rect *
    */

    // took the smallest and largest coordinates
    double minix = L[0]->x, miniy = L[0]->y;
    double maxix = L[0]->x, maxiy = L[0]->y;

    for (int i = 1; i < sz(L); i++)
    {
        if (L[i]->x < minix)
        {
            minix = L[i]->x;
        }
        if (L[i]->x > maxix)
        {
            maxix = L[i]->x;
        }
        if (L[i]->y < miniy)
        {
            miniy = L[i]->y;
        }
        if (L[i]->y > maxiy)
        {
            maxiy = L[i]->y;
        }
    }

    // took the farthest coordinates and constructed the rectangle
    Rect *rect = new Rect(minix, miniy, maxix, maxiy);
    return rect;
}

double CrossProductV(vector<Vertex *> &A)
{
    /**
     * @brief This function calculates the cross product of two vectors.
     * @param vector<Vertex *> &A - a vector of vertices
     * @return double
    */

    // checks whether angle is greater than 180 or not
    double X1 = (A[1]->x - A[0]->x);
    double Y1 = (A[1]->y - A[0]->y);
    double X2 = (A[1]->x - A[2]->x);
    double Y2 = (A[1]->y - A[2]->y);
    // if (X1 * Y2 - Y1 * X2 == 0)
    //     cout << "Linear";
    return (X1 * Y2 - Y1 * X2);
}

vector<Point *> isNotch(vector<Point *> points)
{
    /**
     * @brief This function return the notches in the vector of points.
     * @param vector<Point *> points - a vector of points
     * @return vector<Point *>
    */

    vector<Point *> notches;
    int N = points.size();
    double curr = 0;

    // finding the notches
    for (int i = 0; i < N; i++)
    {
        vector<Point *> temp = {points[i], points[(i + 1) % N], points[(i + 2) % N]};
        curr = CrossProduct(temp);

        if (curr == 0)
            cout << "3 points are collinear" << endl;
        if (curr < 0)
            notches.push_back(points[(i + 1) % N]);
    }

    return notches;
}

Point *nextPoint(std::vector<Point *> points, Point *P)
{
    /**
     * @brief This function finds the next point of the point P in the vector points.
     * @param vector<Point *> points - a vector of points
     * @param Point *P - a point
     * @return Point *
    */

    // finds the next point of the point P in the vector points
    int i = 0;
    for (i; i < sz(points); i++)
    {
        if (points[i] == P)
            break;
    }
    return points[(i + 1) % sz(points)];
}
vector<vector<Point *>> poly;

vector<Point*> reduceL(vector<Point*>L, Point* v) {
    /**
     * @brief This function reduces the vector L points to make it a valid convex polygon.
     * @param vector<Point*>L - a vector of points
     * @param Point* v - a point
     * @return vector<Point*>
    */

    // reducing the polygon to make it a valid convex polygon
    vector<Point*>finalL;
    finalL.push_back(L[0]);
    // reference point
    Point* ref = L[0];
    vector<Point*> templ = {L[1], ref, v};
    int sign;
    if (CrossProduct(templ) > 0)
        sign = 1;
    else
        sign = 0;

    for (int i = 1; i < L.size(); i++) {
        vector<Point*> temp = {L[i], ref, v};
        int tempsign;
        if (CrossProduct(temp) > 0) {
            tempsign = 1;
        }
        else {
            tempsign = 0;
        }

        if (sign == tempsign) {
            finalL.push_back(L[i]);
        }
        else
        {
            break;
        }
    }
    return finalL;
}

vector<Point *> findLPVS(vector<Point *> points, vector<Point *> L)
{
    /**
     * @brief This function finds the points that are notches and are not in L.
     * Thus finding the LPVS.
     * @param vector<Point *> points - a vector of points
     * @param vector<Point *> L - a vector of points
     * @return vector<Point *>
    */

    // finding the lpvs of the polygon
    vector<Point *> lpvs;
    int n = sz(points);
    for (int i = 0; i < sz(points); i++)
    {
        vector<Point *> temp = {points[(i - 1 + n) % n], points[i], points[(i + 1) % n]};
        double curr = CrossProduct(temp);
        if (curr < 0)
        {
            if (find(L.begin(), L.end(), points[i]) == L.end())
            {
                lpvs.push_back(points[i]);
            }
        }
    }
    return lpvs;
}

void solve(vector<Point *> points)
{
    /**
     * @brief This function solves the problem.
     * It converts the polygon into a different convex polygons.
     * It also finds the bounding box of each polygon.
     * Then return the final set of faces after decomposition.
     * @param vector<Point *> points - a vector of points
     * @return void
    */

    int m = 1;
    vector<Point *> L;
    L.push_back(points[0]);
    int n = sz(points);

    while (n > 3)
    {
        // v1 is the starting point, v2 is the next point of v1
        auto v1 = L[sz(L) - 1];
        auto v2 = nextPoint(points, v1);

        L.clear();
        L.push_back(v1);
        L.push_back(v2);

        int i = 2;
        auto vi = nextPoint(points, L[i - 1]);

        // pushing points to L until a notch is found
        while (sz(L) < sz(points))
        {
            int size = sz(L);
            vector<Point *> temp1 = {L[size - 2], L[size - 1], vi};
            vector<Point *> temp2 = {L[size - 1], vi, v1};
            vector<Point *> temp3 = {vi, v1, v2};
            double curr = CrossProduct(temp1), curr2 = CrossProduct(temp2), curr3 = CrossProduct(temp3);
            if (curr >= 0 && curr2 >= 0 && curr3 >= 0)
            {
                L.push_back(vi);
                vi = nextPoint(points, vi);
            }
            else
            {
                break;
            }
        }

        // 3.4
        if (sz(L) != sz(points))
        {
            vector<Point *> lpvs = findLPVS(points, L);
            while (sz(lpvs))
            {
                // creating a rectangle to check if the notch
                // points are in the rectangle
                Rect *rect = genRect(L);
                bool backward = false;
                while (!backward and sz(lpvs))
                {
                    while (sz(lpvs))
                    {
                        auto v = lpvs[0];
                        if (rect->isInRect(v))
                        {
                            break;
                        }
                        else
                        {
                            lpvs.erase(lpvs.begin());
                        }
                    }
                    if (sz(lpvs))
                    {
                        L = reduceL(L, lpvs[0]);
                        backward = 1;
                        lpvs.erase(lpvs.begin());
                    }
                }
            }
        }
        if (L.size() == 1)
        {
            continue;
        }
        // 3.5
        if (L[sz(L) - 1] != v2)
        {
            //pushing the final L to the vector of polygons
            poly.push_back(L);

            //removing the points L from the points vector
            set<Point *> l;
            for (auto I : L)
            {
                l.insert(I);
            }
            bool flag = true;
            vector<Point *> newPoints;
            vector<Point *> newPoints2;

            int i = 0;
            for (i; i < points.size(); i++)
            {
                if (l.find(points[i]) == l.end() && flag)
                {
                    newPoints2.push_back(points[i]);
                }
                else
                {
                    flag = false;
                    break;
                }
            }

            while (i--)
            {
                points.erase(points.begin());
            }

            for (auto p : newPoints2)
            {
                points.push_back(p);
            }

            for (auto p : points)
            {
                if (!l.count(p))
                {
                    newPoints.push_back(p);
                }
            }
            points = newPoints;

            //Pushing back the starting and ending points of L to the points vector
            Point *Ls = L[0];
            Point *Le = L[L.size() - 1];
            points.push_back(Ls);
            points.insert(points.begin(), Le);
            n = n - sz(L) + 2;
        }
    }

    // if remaining points are 3, then push them to the poly vector
    if (n == 3)
    {
        poly.push_back(points);
    }
}

void assignface(halfEdge *h, Face *f) {
    /**
     * @brief This function assigns a face to all the half edges of the face.
     * @param halfEdge *h - a half edge
     * @param Face *f - a face
     * @return void
    */

    // assigning the face to all the half edges of the face
    halfEdge *temp = h;
    do {
        Vertex *s = temp->start;
        Vertex *e = temp->end;
        temp->face = f;
        temp = temp->next;
    } while (temp != h);
}

int main()
{
    /**
     * @brief This is the main function.
     * First it takes the input from the input.txt file in clockwise order.
     * Then it calls the solve function to solve the problem.
     * Then it prints the output to the output.txt file of the decomposition.
     * Now it performs merging of the faces if possible.
     * Then it prints the output to the output.txt file of the decomposition and
     * returns the result of the final polygon decomposition.
     * @param void
    */

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    //taking n as the no. of points
    int n;
    cin >> n;
    int noEdges = n;

    // points vector stores the points
    std::vector<Point *> points;
    for (int i = 0; i < n; i++)
    {
        in(x);
        in(y);
        Point *a = new Point(x, y, i + 1);
        points.push_back(a);
    }

    // reverse used to make the points in clockwise order
    // if given in anticlockwise order
    //reverse(points.begin(), points.end());

    auto nott = isNotch(points);
    // calling the mp1 algorithm
    clock_t beginclock = clock();
    auto start = high_resolution_clock::now();
    solve(points);

    cout << poly.size() << endl;
    for (int i = 0; i < poly.size(); i++)
    {
        cout << poly[i].size() << endl;
        for (int j = 0; j < poly[i].size(); j++)
        {
            cout << poly[i][j]->x << " " << poly[i][j]->y << endl;
        }
    }

    // creating an object for DCEL
    Dcel *d = new Dcel();

    vector<Face*> fac;
    vector<Vertex*> vert;
    vector<halfEdge*> ed;

    // map to store the half edges corresponding to the pair of vertices
    map<pair<int, int>, halfEdge *> mp;
    for (int i = 0; i < poly.size(); i++) {

        // create a vertex for each point in the polygon
        for (int j = 0; j < poly[i].size(); j++) {
            Vertex* v = new Vertex(poly[i][j]->x, poly[i][j]->y, poly[i][j]->id);
            vert.push_back(v);
            d->addVertex(poly[i][j]->x, poly[i][j]->y, poly[i][j]->id);
        }

        // create a half edge for each edge in the polygon
        int ss = vert.size();
        for (int j = 0; j < vert.size(); j++) {
            halfEdge *h = new halfEdge(vert[j], vert[(j + 1) % ss]);
            ed.push_back(h);
            if (mp.find({vert[(j + 1) % ss]->id, vert[j]->id}) == mp.end()) {
                mp[ {vert[j]->id, vert[(j + 1) % ss]->id}] = h;
            }
            else {
                h->twin = mp[ {vert[(j + 1) % ss]->id, vert[j]->id}];
                mp[ {vert[(j + 1) % ss]->id, vert[j]->id}]->twin = h;
            }
            d->addhalfEdge(vert[j], vert[(j + 1) % ss]);
        }

        // assign the next and prev pointers to the half edges
        int es = ed.size();
        for (int j = 0; j < ed.size(); j++) {
            ed[j]->next = ed[(j + 1) % es];
            ed[j]->prev = ed[(j - 1 + es) % es];
        }

        halfEdge *h = ed[es - 1];
        Face* f = new Face(h);
        // assign the face to the half edges
        assignface(h, f);
        fac.push_back(f);
        ed.clear();
        vert.clear();
    }

    d->faces = fac;

    //for finding the common sides of the faces
    vector<halfEdge*> diag;
    for (int i = 0; i < d->faces.size(); i++) {
        halfEdge *h = d->faces[i]->edge;
        diag.push_back(h);
    }

    //merging process
    for (int i = 0; i < diag.size(); i++) {
        // curr, next and prev halfedge of the f1 face
        halfEdge *h = diag[i];
        halfEdge *hn = h->next;
        halfEdge *hp = h->prev;

        // curr, next and prev halfedge of the f1-adjoining face
        halfEdge *t = h->twin;
        halfEdge *tn = t->next;
        halfEdge *tp = t->prev;

        // vertices to check the angle i1,i2,i3 and j1,j2,j3
        Vertex *i1 = hp->start;
        Vertex *i2 = hp->end;
        Vertex *i3 = tn->end;

        Vertex *j1 = tp->start;
        Vertex *j2 = hn->start;
        Vertex *j3 = hn->end;

        vector<Vertex *> temp1 = {i1, i2, i3};
        vector<Vertex *> temp2 = {j1, j2, j3};

        // checking the cross product of the points
        double angle1 = CrossProductV(temp1);
        double angle2 = CrossProductV(temp2);

        // cout<<i1->id<<" "<<i2->id<<" "<<i3->id<<" "<<angle1<<endl;
        // cout<<j1->id<<" "<<j2->id<<" "<<j3->id<<" "<<angle2<<endl;

        // if angle1 and angle2 are positive then merge the faces
        if (angle1 >= 0 && angle2 >= 0) {
            Face *f1 = h->face;
            Face *f2 = h->twin->face;

            // doing the merging
            hp->next = tn;
            tn->prev = hp;
            tp->next = hn;
            hn->prev = tp;

            // making the face invalid
            f1->valid = false;
            f2->valid = false;

            // adding the new added face
            Face *f = new Face(hp);
            // assigning the new face to all the half edges of existing two faces
            assignface(hp, f);
            d->faces.push_back(f);
        }
    }

    // for traversing the final polygon
    d->traversePoly();


    clock_t endclock = clock() - beginclock;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    freopen("time.txt", "a", stdout);
    cout << noEdges << " " << duration.count() * 0.000001 << endl;
    return 0;
}