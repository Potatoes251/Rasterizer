#define _USE_MATH_DEFINES
#include <cmath>
#include "LibMath/GeometricObject2.h"

#define COLLISION_ACCURACY	0.000001f

#pragma region Point
LibMath::Point2::Point2(float x, float y)
{
	m_x = x;
	m_y = y;
}

LibMath::Point2::Point2(Point2 const& other)
{
	m_x = other.m_x;
	m_y = other.m_y;
}

LibMath::Point2& LibMath::Point2::operator=(const Point2& other)
{
	m_x = other.m_x;
	m_y = other.m_y;

	return *this;
}

bool LibMath::operator==(Point2 point1, Point2 point2)
{
	return (std::abs(point1.getX() - point2.getX()) <= 1e-6f && std::abs(point1.getY() - point2.getY()) <=1e-6f);
}
#pragma endregion All functions for Point


#pragma region Line

LibMath::Line2::Line2(Point2 const& p1, Point2 const& p2)
{
	m_p1 = p1;
	m_p2 = p2;
}
LibMath::Line2::Line2(const Line2& other)
{
	m_p1 = other.m_p1;
	m_p2 = other.m_p2;
}
LibMath::Line2& LibMath::Line2::operator=(const Line2& other)
{
	m_p1 = other.m_p1;
	m_p2 = other.m_p2;

	return *this;
}
LibMath::Point2& LibMath::Line2::get_p1(void)
{
	return m_p1;
}
LibMath::Point2& LibMath::Line2::get_p2(void)
{
	return m_p2;
}
float LibMath::Line2::lenght(void)
{

	return sqrtf(powf(m_p1.getX() - m_p2.getX(), 2.0f) + powf(m_p1.getY() - m_p2.getY(), 2.0f));
}
float LibMath::Line2::lenghtSquare(void)
{
	return powf(m_p1.getX() - m_p2.getX(), 2.0f) + powf(m_p1.getY() - m_p2.getY(), 2.0f);
}

bool LibMath::Line2::checkCollision(Point2& point)
{
	// Distance between the point and the 1st edge of the line
	float distance1 = sqrtf(powf(point.getX() - m_p1.getX(), 2) + powf(point.getY() - m_p1.getY(), 2));

	// Distance between the point and the 2nd edge of the line
	float distance2 = sqrtf(powf(point.getX() - m_p2.getX(), 2) + powf(point.getY() - m_p2.getY(), 2));

	float distSum = distance1 + distance2;



	if (abs(distSum - lenght()) <= COLLISION_ACCURACY) //
	{
		return true;
	}

	return false;
}

bool LibMath::Line2::checkCollision(Line2& line)
{
	/*
		Parametric equation of a segment AB: AM = tAB, t [0, 1]

		Let two segment AB and CD:
			- AM = t AB
			- CM' = u CD
		If AB and CD collides, that means M = M'
	*/
	const float EPSILON = 1e-6f;

	//float denominator = ((m_p2.getX() - m_p1.getX()) * (line.m_p1.getY() - line.m_p2.getY())) -((m_p2.getY() - m_p1.getY()) * (line.m_p1.getX() - line.m_p2.getX()));
	float temp2 =       ((m_p2.getY() - m_p1.getY()) * (line.m_p1.getX() - line.m_p2.getX())) - ((m_p2.getX() - m_p1.getX()) * (line.m_p1.getY() - line.m_p2.getY()));

	// Check if lines are parallel or colinear
	if (fabs(temp2) < EPSILON) {
		// Check if the lines are colinear and overlap
		if (isPointOnSegment(m_p1, line.m_p1, line.m_p2) ||
			isPointOnSegment(m_p2, line.m_p1, line.m_p2) ||
			isPointOnSegment(line.m_p1, m_p1, m_p2) ||
			isPointOnSegment(line.m_p2, m_p1, m_p2)) {
			return true;
		}
		return false;
	}


	float temp1 = ( (m_p2.getX() - m_p1.getX()) * (line.m_p2.getY() - m_p1.getY())) - ((m_p2.getY() - m_p1.getY()) * (line.m_p2.getX() - m_p1.getX()));
	
	float temp3 = ((line.m_p1.getX() - line.m_p2.getX()) * (line.m_p2.getY() - m_p1.getY())) - ((line.m_p1.getY() - line.m_p2.getY()) * (line.m_p2.getX() - m_p1.getX()));

	float uA = temp1 / temp2;

	float uB = temp3 / temp2;

	// uA [0, 1] and uB [0, 1]
	if ((uA >= 0 && uA <= 1) && (uB >= 0 && uB <= 1))
	{
		return true;
	}

	return false;
}

bool LibMath::operator==(Line2 line1, Line2 line2)
{
	return (line1.get_p1() == line2.get_p1() && line2.get_p2() == line2.get_p2());
}
bool LibMath::isPointOnSegment(Point2& point, Point2& segStart, Point2& segEnd)
{
	const float EPSILON =  1e-6f;
	float crossProduct = (point.getY() - segStart.getY()) * (segEnd.getX() - segStart.getX()) -
		(point.getX() - segStart.getX()) * (segEnd.getY() - segStart.getY());

	if (std::abs(crossProduct) > EPSILON)
	{
		return false; // Not colinear
	}

	float dotProduct = (point.getX() - segStart.getX()) * (segEnd.getX() - segStart.getX()) +
		(point.getY() - segStart.getY()) * (segEnd.getY() - segStart.getY());
	if (dotProduct < 0) {
		return false; // Outside segment
	}

	float squaredLength = (segEnd.getX() - segStart.getX()) * (segEnd.getX() - segStart.getX()) +
		(segEnd.getY() - segStart.getY()) * (segEnd.getY() - segStart.getY());
	if (dotProduct > squaredLength) {
		return false; // Outside segment
	}

	return true; // Colinear and within bounds
}
#pragma endregion All functions for Line


#pragma region RectangleAABB

LibMath::RectangleAABB::RectangleAABB(Point2 const center, float const height, float const width)
{
	m_center = center;
	m_height = height;
	m_width = width;
}

LibMath::RectangleAABB::RectangleAABB(RectangleAABB const& other)
{
	m_center = other.m_center;
	m_height = other.m_height;
	m_width = other.m_width;
}

LibMath::RectangleAABB& LibMath::RectangleAABB::operator=(const RectangleAABB& other)
{
	m_center = other.m_center;
	m_height = other.m_height;
	m_width = other.m_width;

	return *this;
}

LibMath::Point2 LibMath::RectangleAABB::center(void)
{
	return m_center;
}

float LibMath::RectangleAABB::extentX(void) const
{
	return m_width / 2;
}

float LibMath::RectangleAABB::extentY(void) const
{
	return m_height / 2;
}

bool LibMath::RectangleAABB::checkCollision(RectangleAABB& rectanlge)
{
	if (abs(m_center.getX() - rectanlge.m_center.getX()) > (extentX() + rectanlge.extentX()))
	{
		return false;
	}

	if (abs(m_center.getY() - rectanlge.m_center.getY()) > (extentY() + rectanlge.extentY()))
	{
		return false;
	}

	return true;
}

bool LibMath::RectangleAABB::checkCollision(Line2& line)
{	
	// create the lines of the rectangle
	Line2 leftLine(getTopLeftCorner(), getBottomLeftCorner());
	Line2 topLine(getTopRightCorner(), getTopLeftCorner());
	Line2 botLine(getBottomRightCorner(), getBottomLeftCorner());
	Line2 rightLine(getTopRightCorner(), getBottomRightCorner());

	// check colllision with each line 
	bool top = line.checkCollision(topLine);
	bool bot = line.checkCollision(botLine);
	bool left = line.checkCollision(leftLine);
	bool right = line.checkCollision(rightLine);

	if (top || bot || left || right)
	{
		return true;
	}

	// Check if the entire line is inside the rectangle
	Point2 p1 = line.get_p1();
	Point2 p2 = line.get_p2();

	bool p1Inside = checkCollision(p1);

	bool p2Inside = checkCollision(p2);

	if (p1Inside && p2Inside)
	{
		return true; // The line is entirely inside the rectangle
	}

	return false; // No collision detected
}

bool LibMath::RectangleAABB::checkCollision(Point2& point)
{
	if (point.getX() >= getBottomLeftCorner().getX() &&
		point.getX() <= getBottomRightCorner().getX() &&
		point.getY() >= getBottomLeftCorner().getY() &&
		point.getY() <= getTopLeftCorner().getY())
	{
		return true;
	}
	return false;
}

LibMath::Point2 LibMath::RectangleAABB::getTopRightCorner(void) 
{
	Point2 point(m_center.getX() + extentX(), m_center.getY() + extentY());

	return point;
}

LibMath::Point2 LibMath::RectangleAABB::getTopLeftCorner(void)
{
	Point2 point(m_center.getX() - extentX(), m_center.getY() + extentY());

	return point;
}

LibMath::Point2 LibMath::RectangleAABB::getBottomRightCorner(void)
{
	Point2 point(m_center.getX() + extentX(), m_center.getY() - extentY());

	return point;
}

LibMath::Point2 LibMath::RectangleAABB::getBottomLeftCorner(void)
{
	Point2 point(m_center.getX() - extentX(), m_center.getY() - extentY());

	return point;
}
#pragma endregion All functions for RectangleAABB

#pragma region RectangleOBB

LibMath::RectangleOBB::RectangleOBB(Point2 center, float height, float width)
{
	m_center = center;
	m_height = height;
	m_width = width;
	m_rotation = LibMath::Radian();
}

LibMath::RectangleOBB::RectangleOBB(RectangleOBB const& other)
{
	m_center = other.m_center;
	m_height = other.m_height;
	m_width = other.m_width;
	m_rotation = other.m_rotation;
}

LibMath::RectangleOBB& LibMath::RectangleOBB::operator=(const RectangleOBB& other)
{
	m_center = other.m_center;
	m_height = other.m_height;
	m_width = other.m_width;

	return *this;
}

LibMath::Point2 LibMath::RectangleOBB::getCenter(void)
{
	return m_center;
}

float LibMath::RectangleOBB::getHeight(void) const
{
	return m_height;
}

float LibMath::RectangleOBB::getWidth(void) const
{
	return m_width;
}

LibMath::Radian LibMath::RectangleOBB::getRotation(void) const
{
	return m_rotation;
}

void LibMath::RectangleOBB::rotate(LibMath::Radian rad)
{
	m_rotation = rad;
}

LibMath::Point2 LibMath::RectangleOBB::getTopRightCorner(void)
{

	float halfHeight = m_height / 2;
	float halfWidth = m_width / 2;

	float cosR = LibMath::cos(m_rotation);
	float sinR = LibMath::sin(m_rotation);

	float x = m_center.getX() + (halfWidth * cosR - halfHeight * sinR);
	float y = m_center.getY() + (halfWidth * sinR + halfHeight * cosR);

	Point2 point(x, y);

	return point;
}

LibMath::Point2 LibMath::RectangleOBB::getTopLeftCorner(void)
{
	float halfHeight = m_height / 2;
	float halfWidth = m_width / 2;

	float cosR = LibMath::cos(m_rotation);
	float sinR = LibMath::sin(m_rotation);

	float x = m_center.getX() + (-halfWidth * cosR - halfHeight * sinR);
	float y = m_center.getY() + (-halfWidth * sinR + halfHeight * cosR);

	Point2 point(x, y);

	return point;
}

LibMath::Point2 LibMath::RectangleOBB::getBotRightCorner(void)
{
	float halfHeight = m_height / 2;
	float halfWidth = m_width / 2;

	float cosR = LibMath::cos(m_rotation);
	float sinR = LibMath::sin(m_rotation);

	float x = m_center.getX() + (halfWidth * cosR - (-halfHeight) * sinR);
	float y = m_center.getY() + (halfWidth * sinR + (-halfHeight) * cosR);

	Point2 point(x, y);

	return point;
}

LibMath::Point2 LibMath::RectangleOBB::getBotLeftCorner(void)
{
	float halfHeight = m_height / 2;
	float halfWidth = m_width / 2;

	float cosR = LibMath::cos(m_rotation);
	float sinR = LibMath::sin(m_rotation);

	float x = m_center.getX() + (-halfWidth * cosR - (-halfHeight) * sinR);
	float y = m_center.getY() + (-halfWidth * sinR + (-halfHeight) * cosR);

	Point2 point(x, y);

	return point;
}

LibMath::Vector2 LibMath::normalVector(Point2 p1, Point2 p2)
{
	float x = p2.getX() - p1.getX();
	float y = p2.getY() - p1.getY();

	LibMath::Vector2 normal(-y, x);

	normal.normalize();

	return normal;
}

bool LibMath::overlapOnAxis(float& min1, float& max1, float& min2, float& max2)
{
	return !(max1 < min2 || max2 < min1);
}

void LibMath::projectRectangleOnAxis(RectangleOBB& rectangle, const LibMath::Vector2& axis, float& min, float& max)
{
	Point2 center = rectangle.getCenter();

	LibMath::Radian rotation = rectangle.getRotation();

	Point2 topRight = rectangle.getTopRightCorner();
	Point2 topLeft = rectangle.getTopLeftCorner();
	Point2 botRight = rectangle.getBotRightCorner();
	Point2 botLeft = rectangle.getBotLeftCorner();
	
	//Compute the corners of the rectangle
	LibMath::Vector2 corners[4] = {
		{topRight.getX(), topRight.getX()},
		{topLeft.getX(), topLeft.getY()},
		{botRight.getX(), botRight.getY()},
		{botLeft.getX(), botLeft.getX()}
	};



	// Project the corners onto the axis and find the min and max projections
	min = max = axis.dotProduct(corners[0]);

	for (int i = 1; i < 4; ++i)
	{
		float projection = axis.dotProduct(corners[i]);
		if (projection < min)
		{
			min = projection;
		}
		if (projection > max)
		{
			max = projection;
		}
	}

}

bool LibMath::isCollision(RectangleOBB& rect1, RectangleOBB& rect2)
{
	Point2 center1 = rect1.getCenter();
	Point2 center2 = rect2.getCenter();

	// Define the axes to test (normals to the edges of the rectangles)
	LibMath::Vector2 axes[4] =
	{
		{normalVector(rect1.getTopRightCorner(), rect1.getTopLeftCorner())},
		{normalVector(rect1.getTopLeftCorner(), rect1.getBotLeftCorner())},
		{normalVector(rect2.getTopRightCorner(), rect2.getTopLeftCorner())},
		{normalVector(rect2.getTopLeftCorner(), rect2.getBotLeftCorner())}
	};

	float min1, max1, min2, max2;

	for (LibMath::Vector2& axis : axes)
	{
		axis.normalize();
		projectRectangleOnAxis(rect1, axis, min1, max1);
		projectRectangleOnAxis(rect2, axis, min2, max2);
		if (!overlapOnAxis(min1, max1, min2, max2))
		{
			return false; // Separation axis found, no collision
		}
	}
	return true; // No separating axis found, collision occurs
}




#pragma endregion All functions for RectangleOBB

#pragma region Circle

LibMath::Circle2::Circle2(Point2 const center, float const radius)
{
	m_center = center;
	m_radius = radius;
}
LibMath::Circle2::Circle2(Circle2 const& other)
{
	m_center = other.m_center;
	m_radius = other.m_radius;

}
LibMath::Circle2& LibMath::Circle2::operator=(const Circle2& other)
{
	m_center = other.m_center;
	m_radius = other.m_radius;

	return *this;
}
float LibMath::Circle2::perimeter(void) const
{
	return static_cast<float>(M_PI) * 2 * m_radius;
}
float LibMath::Circle2::area(void) const
{
	return static_cast<float>(M_PI) * powf(m_radius, 2);
}
bool LibMath::Circle2::checkCollision(Circle2& circle)
{
	// Distance between the center of the two circle
	float distance = sqrtf(powf(m_center.getX() - circle.m_center.getX(), 2) + powf(m_center.getY() - circle.m_center.getY(), 2));

	if (distance <= m_radius + circle.m_radius)
	{
		return true;
	}
	return false;
}

bool LibMath::Circle2::checkCollision(Line2& line)
{
	// Check if one of the edges of the line is in the circle
	bool inside1 = checlCollision(line.get_p1());
	bool inside2 = checlCollision(line.get_p2());

	if (inside1 || inside2)
	{
		return true;
	}

	// compute the distance between the circle and it's closest point to the line
	// dot product of the vectors v1(circle - edge1)
	float dot = ((m_center.getX() - line.get_p1().getX()) * (line.get_p2().getX() - line.get_p1().getX())) +
				((m_center.getY() - line.get_p1().getY())) * (line.get_p2().getY() - line.get_p1().getY());

	dot = (dot / line.lenghtSquare());
	
	//Clamp the dot product to the range[0, 1] to keep the closest point on the segment
	dot = std::max(0.0f, std::min(1.0f, dot));

	float closestX = line.get_p1().getX() + (dot * (line.get_p2().getX() - line.get_p1().getX()));
	float closestY = line.get_p1().getY() + (dot * (line.get_p2().getY() - line.get_p1().getY()));

	//distance between the closest point and the circle
	float distX = closestX - m_center.getX();
	float distY = closestY - m_center.getY();

	float distance = sqrtf(powf(distX, 2) + powf(distY, 2));

	// check if the distance is smaller the circle's radius
	if (distance <= m_radius )
	{
		return true;
	}

	return false;

}

bool LibMath::Circle2::checlCollision(Point2& point)
{
	// distance between circle radius and the point
	float distance  = sqrtf(powf(m_center.getX() - point.getX(), 2) + powf(m_center.getY() - point.getY(), 2));

	if (distance <= m_radius)
	{
		return true;
	}

	return false;
}
#pragma endregion 
