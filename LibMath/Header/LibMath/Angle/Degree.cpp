//#define _USE_MATH_DEFINES
//#include "LibMath/Angle/Degree.h"
//#include "cmath"
//
//LibMath::Degree::Degree()
//{
//	m_value = 0.0f;
//}
//
//LibMath::Degree::Degree(float value)
//{
//	m_value = value;
//}
//
//LibMath::Degree::Degree(Degree const& other)
//{
//	m_value = other.m_value;
//}
//
//LibMath::Degree::operator Radian() const
//{
//	return Radian((m_value * M_PI) / 180.0f);
//}
//
//LibMath::Degree& LibMath::Degree::operator+=(Degree other)
//{
//	m_value += other.m_value;
//
//	return *this;
//}
//
//LibMath::Degree& LibMath::Degree::operator-=(Degree other)
//{
//	m_value -= other.m_value;
//
//	return *this;
//}
//
//LibMath::Degree& LibMath::Degree::operator*=(float value)
//{
//	m_value *= value;
//
//	return *this;
//}
//
//LibMath::Degree& LibMath::Degree::operator/=(float value)
//{
//	m_value /= value;
//
//	return *this;
//}
//
//void LibMath::Degree::wrap(bool _wrap)
//{
//	if (_wrap)
//	{
//		m_value = range_to_wrap(m_value, -180.0f, 180.0f);
//	}
//	else
//	{
//		m_value = range_to_wrap(m_value, 0.0f, 360.0f);
//	}
//}
//
//float LibMath::Degree::degree(bool _deg) const
//{
//
//	return _deg ? range_to_wrap(m_value, 180.0f, 180.0f) : range_to_wrap(m_value, 0.0f, 360.0f);
//}
//
//float LibMath::Degree::radian(bool _rad) const
//{
//	float temp = m_value;
//	temp = (M_PI * temp) / 180.0f;
//
//	return _rad ? range_to_wrap(temp, -M_PI, M_PI) : range_to_wrap(temp, 0.0f, 2 * M_PI) ;
//}
//
//float LibMath::Degree::raw() const
//{
//	return m_value;
//}
//
//float LibMath::Degree::range_to_wrap(float _value, float min, float max) const 
//{
//	float range = max - min;
//	while (_value < min)
//	{ // increase until in interval
//		_value += range;
//	}
//
//	while (_value >= max)
//	{ // decrease until in interval
//		_value -= range;
//	}
//	
//	return _value;
//}
//
//bool LibMath::operator==(Degree _deg1, Degree _deg2)
//{
//	return _deg1.m_value == _deg2.m_value;
//}
//
//bool LibMath::operator==(Degree _deg, Radian const& _rad)
//{
//	float temp_rad = (_deg.m_value * M_PI) / 180.f;
//
//	if (std::abs(_rad.m_value - temp_rad) < 0.01)
//	{
//		return true;
//	}
//	
//	return false;
//}
//
//LibMath::Degree LibMath::operator-(Degree _deg)
//{
//	return Degree(-_deg.m_value);
//}
//
//LibMath::Degree LibMath::operator+(Degree _deg1, Degree _deg2)
//{
//	return Degree(_deg1.m_value + _deg2.m_value);
//}
//
//LibMath::Degree LibMath::operator-(Degree _deg1, Degree _deg2)
//{
//	return Degree(_deg1.m_value - _deg2.m_value);
//}
//
//LibMath::Degree LibMath::operator*(Degree _deg, float _val)
//{
//	return Degree(_deg.m_value * _val);
//}
//
//LibMath::Degree LibMath::operator/(Degree _deg, float _val)
//{
//	return Degree(_deg.m_value / _val);
//}
//
//LibMath::Degree LibMath::Literal::operator""_deg(long double _val)
//{
//	return LibMath::Degree((float)_val);
//}
//
//LibMath::Degree LibMath::Literal::operator""_deg(unsigned long long int _val)
//{
//	return LibMath::Degree((float)_val);
//}
