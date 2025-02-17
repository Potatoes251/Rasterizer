#ifndef GEOMERTIC_OBJECT2_H_
#define GEOMERTIC_OBJECT2_H_
#include <iostream>
#include "LibMath/Vector/Vector2.h"
#include "LibMath/Angle/Radian.h"
#include "LibMath/Trigonometry.h"


namespace LibMath
{
	class Point2
	{
	public:
						Point2() = default;
						Point2(float x, float y);
						Point2(Point2 const& other);
						~Point2() = default;

		Point2&			operator=(const Point2& other);

		float			getX(void) { return m_x; }
		float			getY(void) { return m_y; }


	private:
		float m_x = 0.f;
		float m_y = 0.f;

	};

	bool operator==(Point2 point1, Point2 point2);


	class Line2
	{
	public:
						Line2() = default;
						Line2(Point2 const& p1, Point2 const& p2);
						Line2(const Line2& other);
						~Line2() = default;

		Line2&			operator=(const Line2& other);

		Point2&			get_p1(void);
		Point2&			get_p2(void);
		float			lenght(void);
		float			lenghtSquare(void);

		bool			checkCollision(Point2& point);
		bool			checkCollision(Line2& line);

	private:
		Point2 m_p1;
		Point2 m_p2;

	};
	bool operator==(Line2 line1, Line2 line2);
	bool isPointOnSegment(Point2& point, Point2& segStart, Point2& segEnd);

	class RectangleAABB
	{
	public:
						RectangleAABB() = default;
		explicit		RectangleAABB(Point2 const center, float const height, float const width); 
						RectangleAABB(RectangleAABB const& other);
						~RectangleAABB() = default;

		RectangleAABB&	operator=(const RectangleAABB& other);

		Point2			center(void);
		float			extentX(void) const;
		float			extentY(void) const;

		bool			checkCollision(RectangleAABB& rectanlge);
		bool			checkCollision(Line2& line);
		bool			checkCollision(Point2& point);

		Point2			getTopRightCorner(void);
		Point2			getTopLeftCorner(void);
		Point2			getBottomRightCorner(void);
		Point2			getBottomLeftCorner(void);

	private:
		Point2	m_center;
		float	m_height = 0.f;
		float	m_width = 0.f;

		
	};

	class RectangleOBB
	{
	public:
						RectangleOBB() = default;
		explicit		RectangleOBB(Point2 center, float height, float width);
						RectangleOBB(RectangleOBB const& other);
						~RectangleOBB() = default;

		RectangleOBB&	operator=(const RectangleOBB& other);
	
		Point2			getCenter(void);
		float			getHeight(void) const;
		float			getWidth(void) const;
		LibMath::Radian			getRotation(void) const;

		void			rotate(LibMath::Radian rad);

		Point2			getTopRightCorner(void);
		Point2			getTopLeftCorner(void);
		Point2			getBotRightCorner(void);
		Point2			getBotLeftCorner(void);

	private:
		Point2 m_center;
		float  m_height = 0.f;
		float  m_width = 0.f;
		LibMath::Radian m_rotation;

	};

	LibMath::Vector2			normalVector(Point2 p1, Point2 p2);
	bool						overlapOnAxis(float& min1, float& max1, float& min2, float& max2);
	void						projectRectangleOnAxis(RectangleOBB& rectangle, const LibMath::Vector2& axis, float& min, float& max);
	bool						isCollision(RectangleOBB& rect1, RectangleOBB& rect2);

	class Circle2
	{
	public:
		friend			class Point2;
						Circle2() = default;
		explicit		Circle2(Point2 const center, float const radius);
						Circle2(Circle2 const& other);
						~Circle2() = default;

		Circle2&		operator=(const Circle2& other);

		Point2			getCenter(void) { return m_center; };
		float			getRadius(void) { return m_radius; };

		float			perimeter(void) const;
		float			area(void) const;

		bool			checkCollision(Circle2& circle);
		bool			checkCollision(Line2& line);
		bool			checlCollision(Point2& point);

	private:
		Point2 m_center;
		float  m_radius = 0.f;

	};
}

#endif // !GEOMERTIC_OBJECT2_H_
