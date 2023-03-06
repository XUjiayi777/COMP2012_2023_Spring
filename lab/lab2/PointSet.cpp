#include <iostream>
#include "PointSet.h"
using namespace std;

PointSet::PointSet(int capacity)
{
  // This cout statement is for learning purpose only, which shows when the constructor will be invoked
  cout << "Initialized by PointSet's conversion constructor" << endl;

  // TODO #1: add your code here
  this->capacity = capacity;
  numPoints = 0;
  points = new Point[capacity];
}

PointSet::PointSet(const Point points[], int numPoints)
{
  // This cout statement is for learning purpose only, which shows when the constructor will be invoked
  cout << "Initialized by PointSet's other constructor" << endl;

  // TODO #2: add your code here
  this->points = new Point[numPoints];
  for (int i = 0; i < numPoints; i++)
  {
    this->points[i] = points[i];
  }
  this->numPoints = numPoints;
  this->capacity = numPoints;
}

PointSet::PointSet(const PointSet &s)
{
  // This cout statement is for learning purpose only, which shows when the constructor will be invoked
  cout << "Initialized by PointSet's copy constructor" << endl;

  // TODO #3: add your code here
  points = new Point[s.numPoints];
  for (int i = 0; i < s.numPoints; i++)
  {
    points[i] = s.points[i];
  }
  capacity = s.capacity;
  numPoints = s.numPoints;
}

PointSet::~PointSet()
{
  // TODO #4: add your code here
  delete[] points;
  numPoints = 0;
  capacity = 0;
}

void PointSet::addPoint(const Point &p)
{
  // TODO #5: add your code here
  if (numPoints == capacity)
  {
    cout << "Insufficient array space" << endl;
    return;
  }
  points[numPoints] = p;
  numPoints++;
}

void PointSet::removeLastPoint()
{
  // TODO #6: add your code here
  if (numPoints == 0)
  {
    cout << "No points" << endl;
    return;
  }
  numPoints--;
}

// Return true if the all the points in the point set is collinear; return false otherwise
bool PointSet::isCollinear() const
{
  // TODO #7: add your code here
  if (numPoints <= 2)
  {
    return true;
  }
  int check = 0;
  for (int j = 0; j < numPoints - 2; j++)
  {
    check += isCollinear_3points(points[j], points[j + 1], points[j + 2]);
  }
  if (check == numPoints - 2)
  {
    return true;
  }
  return false;
}

// return true if 3 given points are on the same straight line
bool PointSet::isCollinear_3points(const Point p1, const Point p2, const Point p3) const
{
  // TODO #8: add your code here
  double area = 0.5 * abs(p1.getX() * (p2.getY() - p3.getY()) + p2.getX() * (p3.getY() - p1.getY()) + p3.getX() * (p1.getY() - p2.getY()));
  if (area == 0)
  {
    return true;
  }
  return false;
}

void PointSet::print() const
{
  // This function is already completed.
  if (numPoints == 0)
  {
    cout << "The PointSet is empty!" << endl;
    return;
  }
  cout << "Number of points: " << numPoints << endl;
  ;
  cout << "points: " << endl;
  for (int i = 0; i < numPoints; i++)
  {
    points[i].print();
    cout << endl;
  }
}
