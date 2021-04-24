#ifndef WINDMILL_H
#define WINDMILL_H

#include "polygon.h"
#include "rect.h"
#include "ellipse.h"
#include "color.h"
#include "vec2.h"

class Windmill{
    private:
        std::vector<shared_ptr<Polygon>> polys;
        std::vector<shared_ptr<Rect>> rects;
        std::vector<shared_ptr<ellipse>> ellipses;

        vec2 center;
        double depth;

    public:
        Windmill(vec2 c, double d);

        color eval(int x, int y, color background);

        // mutators
        void setDepth(double d) { depth = d; }
        void setCenter(vec2 c) { center = c; }

        void translate(vec2 factor);

        // accessors
        double getDepth() const { return depth; }
        vec2 getCenter() const { return center; }
        std::vector<shared_ptr<Rect>> getRects() const { return rects; }
        std::vector<shared_ptr<ellipse>> getEllipses() const { return ellipses; }
        std::vector<shared_ptr<Polygon>> getPolys() const { return polys; }
};

#endif