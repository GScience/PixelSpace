#pragma once

//!nÎ¬µã
template <class type, int n> class Point
{
private:
	type mData[n];

public:
	type getX() const { return mData[0]; }
	type getY() const { return mData[1]; }
	type getZ() const { return mData[2]; }

	type get(const int i) const { return mData[i]; }

	void setX(type& d) { mData[0] = d; }
	void setY(type& d) { mData[1] = d; }
	void setZ(type& d) { mData[2] = d; }

	void set(const int i, type& d) { mData[i] = d; }
};

using Point3D = Point<double, 3>;