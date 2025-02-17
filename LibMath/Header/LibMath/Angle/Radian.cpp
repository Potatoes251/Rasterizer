//#define _USE_MATH_DEFINES
//#include "Radian.h"
//#include <cmath>
//
//
//
//LibMath::Radian::Radian()
//{
//	m_value = 0.0f;
//}
//
//LibMath::Radian::Radian(float _val)
//{
//	m_value = _val;
//}
//
//LibMath::Radian::Radian(Radian const& other)
//{
//	m_value = other.m_value;
//}
//
//LibMath::Radian::operator Degree() const
//{
//	return Degree((m_value * 180.0f) / M_PI);
//}
//
//LibMath::Radian& LibMath::Radian::operator+=(Radian other)
//{
//	m_value += other.m_value;
//
//	return *this;
//}
//
//LibMath::Radian& LibMath::Radian::operator-=(Radian other)
//{
//	m_value -= other.m_value;
//
//	return *this;
//}
//
//LibMath::Radian& LibMath::Radian::operator*=(float _val)
//{
//	m_value *= _val;
//
//	return *this;
//}
//
//LibMath::Radian& LibMath::Radian::operator/=(float _val)
//{
//	m_value /= _val;
//
//	return *this;
//}
//
//void LibMath::Radian::wrap(bool _wrap)
//{
//	if (_wrap)
//	{
//		m_value = range_to_wrap(m_value, -M_PI, M_PI);
//	}
//	else
//	{
//		m_value = range_to_wrap(m_value, 0.0f, 2 * M_PI);
//	}
//}
//
//float LibMath::Radian::degree(bool _deg) const
//{
//	float temp = m_value;
//
//	temp = (180.0f * temp) / M_PI;
//
//	return _deg ? range_to_wrap(temp, 180.0f, 180.0f) : range_to_wrap(temp, 0.0f, 360.0f);
//}
//
//float LibMath::Radian::radian(bool _rad) const
//{
//	return _rad ? range_to_wrap(m_value, -M_PI, M_PI) : range_to_wrap(m_value, 0.0f, 2 * M_PI);
//}
//
//float LibMath::Radian::raw() const
//{
//	return m_value;
//}
//
//float LibMath::Radian::range_to_wrap(float _value, float min, float max) const
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
//bool LibMath::operator==(Radian _rad1, Radian _rad2)
//{
//	return _rad1.m_value == _rad2.m_value;
//}
//
//bool LibMath::operator==(Radian _rad, Degree const& _deg)
//{
//	float temp_deg = (_rad.m_value * 180.0f) / M_PI;
//
//	if (std::abs(_deg.m_value - temp_deg) < 0.01)
//	{
//		return true;
//	}
//	return false;
//}
//
//LibMath::Radian LibMath::operator-(Radian _rad)
//{
//	return Radian(-_rad.m_value);
//}
//
//LibMath::Radian LibMath::operator+(Radian _rad1, Radian _rad2)
//{
//	return Radian(_rad1.m_value + _rad2.m_value);
//}
//
//LibMath::Radian LibMath::operator-(Radian _rad1, Radian _rad2)
//{
//	return Radian(_rad1.m_value - _rad2.m_value);
//}
//
//LibMath::Radian LibMath::operator*(Radian _rad1, float _val)
//{
//	return Radian(_rad1.m_value * _val);
//}
//
//LibMath::Radian LibMath::operator/(Radian _rad1, float _val)
//{
//	return Radian(_rad1.m_value/_val);
//}
//
//LibMath::Radian LibMath::Literal::operator""_rad(long double _val)
//{
//	return LibMath::Radian(_val);
//}
//
//LibMath::Radian LibMath::Literal::operator""_rad(unsigned long long int _val)
//{
//	return LibMath::Radian(_val);
//}
