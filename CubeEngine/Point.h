#pragma once

//!nÎ¬µã
template <class type, int n> class Point
{
private:
	type data[n];

public:
	type getX() const { return data[0]; }
	type getY() const { return data[1]; }
	type getZ() const { return data[2]; }

	type get(int i) const { return data[i]; }

	void setX(type& d) { data[0] = d; }
	void setY(type& d) { data[1] = d; }
	void setZ(type& d) { data[2] = d; }

	void set(int i, type& d) { data[i] = d; }
};

using Point3D = Point<double, 3>;