#pragma once

#include <cmath>

#define PI atan(1.0f) * 4.0f

static int range(const int& i, const int& upper, const int& lower = 0){
	int h = i % (upper - lower);
	return lower + (h < 0 ? (h + (upper - lower)) : h);
}

static float interv(const float& f0, const float& f1){
	return f0 > f1 ? f0 - f1 : f1 - f0;
}

static float distance2D(const float& x0, const float& y0, const float& x1, const float& y1){
	return sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2));
}

static float distance3D(const float& x0, const float& y0, const float& z0, const float& x1, const float& y1, const float& z1){
	return sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2) + pow(z1 - z0, 2));
}

static float angleTo(const float& x0, const float& y0, const float& x1, const float& y1){
	return atan2(y1 - y0, x1 - x0) + (y1 - y0 < 0 ? 2.0f * PI : 0);
}

static float toDegrees(const float& rad){
	return rad / PI * 180.0f;
}

static float toRadians(const float& degrees){
	return degrees / 180.0f * PI;
}
