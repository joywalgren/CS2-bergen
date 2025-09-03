#include "point.h"

using namespace std;

//Constructor
points::Point::Point(int X, int Y, points::Point* closestPoint)
{
    x = X;
    y = Y;
    nearestPoint = closestPoint;

}
//Destructor
points::Point::~Point()
{

}

//Getters
int points::Point::getX()
{
    return x;
}

int points::Point::getY()
{
    return y;
}

points::Point* points::Point::getNearestPoint()
{
    return nearestPoint;
}

points::Point* points::Point::calcNearestPoint(Point* pointList[], unsigned long arrSize)
{
    if (arrSize == 0) return nullptr;
    
    Point* best = nullptr;
    double bestDist = 0.0;

    for (unsigned long i = 0; i < arrSize; i++)
    {
        if (pointList[i] == nullptr) continue;


        double d = distPoints(*pointList[i]);
        if (best == nullptr || d < bestDist)
        {
            best = pointList[i];
            bestDist = d;
        }
    }
    return best;

}

//Setters
void points::Point::setX(int newVal)
{
    x = newVal;
}

void points::Point::setY(int newVal)
{
    y = newVal;
}

void points::Point::setNearestPoint(Point* newNearestPoint)
{
    nearestPoint = newNearestPoint;
}

double points::Point::distPoints(Point& point)
{
    double distanceX = x-point.getX();
    double distanceY = y-point.getY();
    return sqrt(distanceX*distanceX+distanceY*distanceY);
}