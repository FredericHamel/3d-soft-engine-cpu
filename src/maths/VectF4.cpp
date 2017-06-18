#include "VectF4.h"

// -----------------------------------------------------------------------------
// VectF4 Constructors
// -----------------------------------------------------------------------------
VectF4::VectF4(void) {
  this->v = _mm_setzero_ps();
}

VectF4::VectF4(float x, float y, float z, float w) {
  this->v = _mm_set_ps(z, y, x, w);
}

VectF4::VectF4(VectF4 const& v) {
  this->v = v.v;
}

VectF4::VectF4(const __m128 &v) {
  this->v = v;
}

// -----------------------------------------------------------------------------
// VectF4 functions
// -----------------------------------------------------------------------------
float VectF4::length() const {
    return sqrt(this->squareLength());
}

float VectF4::length3() const {
    return sqrt(this->squareLength3());
}

float VectF4::squareLength() const {
    __m128 v = this->v * this->v;
    return v[0] + v[1] + v[2] + v[3];
}

float VectF4::squareLength3() const {
    __m128 v = _mm_mul_ps(this->v, this->v);
    return v[0] + v[1] + v[2];
}

VectF4 VectF4::normalize() const {
    float l = this->length();
    VectF4 v(this->v / l);
    return v;
}

VectF4 VectF4::normalize3() const {
    float l = this->length3();
    __m128 r = this->v / l;
    r[3] = 0.0f;
    VectF4 v(r);
    return v;
}

void VectF4::set(float x, float y, float z, float w) {
  this->v = _mm_set_ps(z, y, x, w);
}

void VectF4::set(VectF4 const& v) {
  this->v = v.v;
}

float VectF4::dotProduct(VectF4 const& v1, VectF4 const& v2) {
  __m128 prod = v1.v * v2.v; 
  return prod[0] + prod[1] + prod[2] + prod[3];
}

float VectF4::dotProduct3(VectF4 const& v1, VectF4 const& v2) {
    __m128 prod = v1.v * v2.v;
    return prod[0] + prod[1] + prod[2] + prod[3];
}

std::ostream& operator<<(std::ostream &os, VectF4 const& v){
    os << "(" << VECTF4_X(v)
      << ", " << VECTF4_Y(v)
      << ", " << VECTF4_Z(v)
      << ", " << VECTF4_W(v)
      << ")";
    return os;
}
