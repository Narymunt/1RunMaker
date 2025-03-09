#pragma once

/// Minimal 3-dimensional vector abstraction
class Vec3
{
public:

    // Constructors
    Vec3() : x(0), y(0), z(0)
	{}
	
	Vec3(float vx, float vy, float vz)
	{
		x = vx;
		y = vy;
		z = vz;
	}

	Vec3(const Vec3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}

	// Destructor
	~Vec3() {}

	// A minimal set of vector operations
	Vec3 operator * (float mult) const // result = this * arg
	{
		return Vec3(x * mult, y * mult, z * mult);
	}

	Vec3 operator + (const Vec3& v) const // result = this + arg
	{
		return Vec3(x + v.x, y + v.y, z + v.z);
	}

	Vec3 operator - (const Vec3& v) const // result = this - arg
	{
		return Vec3(x - v.x, y - v.y, z - v.z);
	}

	float x, y, z;
};


