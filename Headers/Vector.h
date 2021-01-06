#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

/*
 ? This header file defines `Vec3`. A vector with three dimensions/elements.
 ? It also defines several functions to facilitate our work with vectors.
 */

struct Vec3 {
	float x, y, z;
	
	/* 
	 * Constructor for Vec3.
	 * 
	 * No parameters.
	 * Returns an instance of `Vec3`.
	 */
	Vec3(){
        x = 0.0f; 
        y = 0.0f;
        z = 0.0f;
    }

	/* 
	 * Another constructor for Vec3.
	 * 
	 * Parameters: `x`, `y` and `z`.
	 * Returns an instance of `Vec3`.
	 */
	Vec3(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

	/* 
	 * Overloads the `+` operator.
	 * 
	 * Parameters: `v`.
	 * Returns the resultant vector as a `Vec3`.
 	 */
	Vec3 operator+(const Vec3& v) { 
		return Vec3(x + v.x, y + v.y, z + v.z); 
	}

	/* 
	 * Overloads the `-` operator.
	 * 
	 * Parameters: `v`.
	 * Returns the resultant vector as a `Vec3`.
 	 */
	Vec3 operator-(const Vec3& v) { 
		return Vec3(x - v.x, y - v.y, z - v.z); 
	}
	
	/* 
	 * Overloads the `*` operator.
	 * 
	 * Parameters: `k`.
	 * Returns the resultant vector as a `Vec3`.
 	 */
	Vec3 operator*(const float& k) { 
		return Vec3(x*k, y*k, z*k); 
	}

	/* 
	 * Overloads the `/` operator.
	 * 
	 * Parameters: `k`.
	 * Returns the resultant vector as a `Vec3`.
 	 */
	Vec3 operator/(const float& k) { 
		return Vec3(x/k, y/k, z/k); 
	}

	/* 
	 * Calculates a vector's magnitude.
	 * 
	 * No parameters.
	 * Returns the magnitude as a `float`.
 	 */
	float vectorMagnitude() { 
        return sqrtf((x * x) + (y * y) + (z * z)); 
    }

	/* 
	 * Normalizes a vector (returns a unit vector).
	 * 
	 * No parameters.
	 * No return.
 	 */
	void normalizeVector() {
		float magnitude = vectorMagnitude();
		x = x / magnitude; 
        y = y / magnitude; 
        z = z / magnitude;
	}

	/* 
	 * Calculates the cross product of two vectors.
	 * 
	 * Parameters: `vector`.
	 * Returns a resultant vector of type `Vec3`.
 	 */
	Vec3 crossProduct(Vec3 vector) {
        Vec3 resultantVector;
        resultantVector.x = (y * vector.z) - (z * vector.y);
        resultantVector.y = (z * vector.x) - (x * vector.z);
        resultantVector.z = (x * vector.y) - (y * vector.x);
		return resultantVector;
	}
};

#endif