#include "windmill.h"

// Initializes windmill with specified center at the center of the sails
Windmill::Windmill(vec2 c, double d)
{
    // sails and cap
    ellipses.push_back(make_shared<ellipse>(c, vec2(20,20), 2.0, color(120,80,20)));
    rects.push_back(make_shared<Rect>(vec2(c.x()-5,c.y()-75), vec2(c.x()+5,c.y()), color(150,130,105), 1.5));
    rects.push_back(make_shared<Rect>(vec2(c.x()-5,c.y()), vec2(c.x()+5,c.y()+75), color(150,130,105), 1.5));
    rects.push_back(make_shared<Rect>(vec2(c.x()-75,c.y()-5), vec2(c.x(),c.y()+5), color(150,130,105), 1.5));
    rects.push_back(make_shared<Rect>(vec2(c.x(),c.y()-5), vec2(c.x()+75,c.y()+5), color(150,130,105), 1.5));

    std::vector<vec2> roofVerts;
    // top
    roofVerts.push_back(vec2(c.x(), c.y()));
    // bottom left
    roofVerts.push_back(vec2(c.x()-40, c.y()+40));
    // bottom right
    roofVerts.push_back(vec2(c.x()+40, c.y()+40));
    polys.push_back(make_shared<Polygon>(roofVerts, 1.0, color(150,200,90)));

    // body
    rects.push_back(make_shared<Rect>(vec2(c.x()-40,c.y()+40), vec2(c.x()+40,c.y()+140), color(150,200,90), 1.0));
}

color Windmill::eval(int x, int y, color background) 
{
    float res;
    color inC1, inC2, inC3;
    bool result, inTrue1(false), inTrue2(false), inTrue3(false);
    double curDepth = -1.0;

    for (auto obj : ellipses) 
    {
        // evaluate the center circle
        res = obj->eval(x, y);
        if (res < 0 && obj->getDepth() > curDepth) 
        {
        inC3 = obj->getInC();
        inTrue3 = true;
        curDepth = obj->getDepth();
        }
    }

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

    for (auto obj : polys) 
    {
        // evaluate the roof
        result = obj->eval(x, y);
        if (result && obj->getDepth() > curDepth) 
        {
        inC1 = obj->getInC();
        inTrue1 = true;
        curDepth = obj->getDepth();
        }
    }
    
    if (inTrue3) 
    {			
        return inC3;
    }
    else if (inTrue2) 
    {			
        return inC2;
    }
    else if (inTrue1) 
    {			
        return inC1;
    }
    else
    {
        return background;
    }
}