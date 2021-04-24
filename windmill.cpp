#include "windmill.h"

// Initializes windmill with specified center at the center of the sails
Windmill::Windmill(vec2 c, double d)
{
    depth = d;

    // roof
    ellipses.push_back(make_shared<ellipse>(vec2(c.x(),c.y()+40), vec2(40,40), depth+0.1, color(150,150,150)));
    // center circle
    ellipses.push_back(make_shared<ellipse>(c, vec2(12,12), depth+0.3, color(150,130,105)));
    // top sail
    rects.push_back(make_shared<Rect>(vec2(c.x()-2,c.y()-75), vec2(c.x()+2,c.y()), color(150,130,105), depth+0.2));
    rects.push_back(make_shared<Rect>(vec2(c.x()-15,c.y()-75), vec2(c.x(),c.y()-30), color(120,80,20), depth+0.1));
    // bottom sail
    rects.push_back(make_shared<Rect>(vec2(c.x()-2,c.y()), vec2(c.x()+2,c.y()+75), color(150,130,105), depth+0.2));
    rects.push_back(make_shared<Rect>(vec2(c.x(),c.y()+30), vec2(c.x()+15,c.y()+75), color(120,80,20), depth+0.1));
    // left sail
    rects.push_back(make_shared<Rect>(vec2(c.x()-75,c.y()-2), vec2(c.x(),c.y()+2), color(150,130,105), depth+0.2));
    rects.push_back(make_shared<Rect>(vec2(c.x()-75,c.y()), vec2(c.x()-30,c.y()+15), color(120,80,20), depth+0.1));
    // right sail
    rects.push_back(make_shared<Rect>(vec2(c.x(),c.y()-2), vec2(c.x()+75,c.y()+2), color(150,130,105), depth+0.2));
    rects.push_back(make_shared<Rect>(vec2(c.x()+30,c.y()), vec2(c.x()+75,c.y()+15), color(120,80,20), depth+0.1));
    // body
    rects.push_back(make_shared<Rect>(vec2(c.x()-40,c.y()+40), vec2(c.x()+40,c.y()+140), color(128,0,0), depth+0.1));
    // door
    rects.push_back(make_shared<Rect>(vec2(c.x()-12,c.y()+100), vec2(c.x()+12,c.y()+140), color(0,0,0), depth+0.2));
    ellipses.push_back(make_shared<ellipse>(vec2(c.x()+6,c.y()+115), vec2(2,2), depth+0.3, color(150,130,105)));
    // foundation
    rects.push_back(make_shared<Rect>(vec2(c.x()-60,c.y()+140), vec2(c.x()+60,c.y()+160), color(256,256,256), depth+0.3));

    /*
    std::vector<vec2> roofVerts;
    // top
    roofVerts.push_back(vec2(c.x(), c.y()));
    // bottom left
    roofVerts.push_back(vec2(c.x()-40, c.y()+40));
    // bottom right
    roofVerts.push_back(vec2(c.x()+40, c.y()+40));
    polys.push_back(make_shared<Polygon>(roofVerts, 1.0, color(150,200,90)));
    */

}

color Windmill::eval(int x, int y, color background) 
{
    float res;
    color inC1, inC2;
    bool result, inTrue1(false), inTrue2(false);
    double curDepth = -1.0;

    for (auto obj : rects) 
    {
        // evaluate the body and blades
        result = obj->evalIn(x, y);
        if (result && obj->getDepth() > curDepth) 
        {
        inC2 = obj->getInC();
        inTrue2 = true;
        curDepth = obj->getDepth();
        }
    }

    for (auto obj : ellipses) 
    {
        // evaluate the center circle and roof
        res = obj->eval(x, y);
        if (res < 0 && obj->getDepth() > curDepth) 
        {
        inC1 = obj->getInC();
        inTrue1 = true;
        curDepth = obj->getDepth();
        }
    }

    /*
    for (auto obj : polys) 
    {
        // evaluate the roof
        result = obj->eval(x, y);
        if (result && obj->getDepth() > curDepth) 
        {
        inC3 = obj->getInC();
        inTrue3 = true;
        curDepth = obj->getDepth();
        }
    }
    */
    
    if (inTrue1) 
    {			
        return inC1;
    }
    else if (inTrue2) 
    {			
        return inC2;
    }
    else
    {
        return background;
    }
}

void Windmill::translate(vec2 factor)
{
    for (auto obj : rects)
    {
        obj->translate(factor);
    }
    for (auto obj : ellipses)
    {
        obj->translate(factor);
    }

}