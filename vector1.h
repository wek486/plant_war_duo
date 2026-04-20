#ifndef VECTOR1_H
#define VECTOR1_H
#include<cmath>
class vector1 {
public:
	float x = 0;
	float y = 0;
	vector1() = default;
	~vector1() = default;
	vector1(float m, float n) :x(m), y(n){}
	vector1 operator+(const vector1& vec)const {
		return vector1(x + vec.x, y + vec.y);
	}
	void operator+=(const vector1& vec) {
		x += vec.x, y += vec.y;
	}
	void operator-=(const vector1& vec) {
		x -= vec.x, y -= vec.y;
	}
	vector1 operator-(const vector1& vec)const {
		return vector1(x - vec.x, y - vec.y);
	}
	vector1 operator*(float val)const {
		return vector1(x * val, y * val);
	}
	float operator*(const vector1& vec)const {
		return x * vec.x + y * vec.y;
	}
	void operator*=(float val) {
		x *= val; y*=val;
	}
	float get_length() {
		return sqrt(x * x+y * y);
	}
	vector1 normalize() {
		float len = get_length();
		if (len == 0)return vector1(0, 0);
		return vector1(x / len, y / len);
	}
	void set_position(float new_x, float new_y) {
		x = new_x;
		y = new_y;
	}
private:



};
#endif
