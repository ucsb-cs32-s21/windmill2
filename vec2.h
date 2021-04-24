#ifndef VEC2_H
#define VEC2_H

#include <cmath>
#include <iostream>

#include "util.h"

using std::sqrt;

class vec2 {
	public:
		vec2(double in1, double in2) : val{in1, in2} {}
		vec2() : val{0,0} {} //default constructor
		vec2(double in) : val{in,in} {} //alt constructor

		//getters
		double x() const { return val[0]; }
		double y() const { return val[1]; }
		void setX(double inX) { val[0] = inX; }
		void setY(double inY) { val[1] = inY; }

		//overload operators
		vec2& operator+=(const vec2 &v) {
			val[0] += v.val[0];
			val[1] += v.val[1];
			return *this;
		}

		//mult by scalar
		vec2& operator*=(const double Sc) {
			val[0] *=Sc; 
			val[1] *=Sc;
			return *this;
		}

		vec2& operator/=(const double Sc) {
			return *this *= 1/Sc;
		}

		// add vectors together 
		vec2 operator+(const vec2& other){
			val[0] += other.x();
			val[1] += other.y();
			return *this;
		}

		
		inline static vec2 random() {
			return vec2(niceRand(), niceRand());
		}
		
		inline static vec2 random(double min, double max) {
			return vec2(nicerRand(min, max), nicerRand(min, max));
		}

	public:
		double val[2];
};

//Type aliases for vec2
using point2D = vec2; //2D point

inline std::ostream& operator<<(std::ostream &out, const vec2 &v) {
	return out << v.val[0] << " " << v.val[1];
}


#endif
