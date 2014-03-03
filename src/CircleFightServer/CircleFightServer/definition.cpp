#include "definition.h"

Degree Radian::toDegree()
{
		return Degree( value_ / 3.14f * 180.f );
}
Radian Degree::toRadian()
{
		return Radian(value_ * 3.14f / 180.f);
}