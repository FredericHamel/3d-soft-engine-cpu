#define __VECTF4_INLINE
# include "./VectF4.h"
#undef __VECTF4_INLINE

#include <iosfwd>

// -----------------------------------------------------------------------------
// VectF4 Constructors
// -----------------------------------------------------------------------------
VectF4::VectF4() {
#ifdef __SSE4_1__
  this->v = _mm_setzero_ps();
#else
  this->x = 0.0f;
  this->y = 0.0f;
  this->z = 0.0f;
  this->w = 0.0f;
#endif
}

VectF4::VectF4(float x, float y, float z, float w) {
#ifdef __SSE4_1__
  this->v = _mm_setr_ps(x, y, z, w);
#else
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
#endif
}

VectF4::VectF4(VectF4 const& v) {
#ifdef __SSE4_1__
  this->v = v.v;
#else
  this->x = v.x;
  this->y = v.y;
  this->z = v.z;
  this->w = v.w;
#endif
}

#ifdef __SSE4_1__
VectF4::VectF4(const __m128 &v) {
  this->v = v;
}
#endif

// -----------------------------------------------------------------------------
// VectF4 Operators overload
// -----------------------------------------------------------------------------
inline bool VectF4::operator==(VectF4 const& v) const {
#ifdef __SSE4_1__
    __m128 compare = _mm_cmpeq_ps(this->v, v.v);
    return _mm_movemask_ps(compare);
#else
    return this->x == v.x
      && this->y == v.y
      && this->z == v.z
      && this->w == v.w;
#endif
}

inline bool VectF4::operator!=(VectF4 const& v) const{
#ifdef __SSE4_1__
  __m128 compare = _mm_cmpneq_ps(this->v, v.v);
  return _mm_movemask_ps(compare);
#else
    return this->x != v.x
      || this->y != v.y
      || this->z != v.z
      || this->w != v.w;
#endif
}

inline VectF4 VectF4::operator*(float const s) const{
#ifdef __SSE4_1__
    return VectF4(this->v*s);
#else
    return VectF4(this->x*s, this->y*s, this->z*s, this->w*s);
#endif
}
inline VectF4 VectF4::operator/(float const s) const{
#ifdef __SSE4_1__
    return VectF4(this->v/s);
#else
    return VectF4(this->x/s, this->y/s, this->z/s, this->w/s);
#endif
}
inline VectF4 VectF4::operator+(VectF4 const& v) const{
#ifdef __SSE4_1__
    return VectF4(this->v + v.v);
#else
    return VectF4(this->x+v.x, this->y+v.y, this->z+v.z, this->w+v.w);
#endif
}
inline VectF4 VectF4::operator-(VectF4 const& v) const{
#ifdef __SSE4_1__
    return VectF4(this->v - v.v);
#else
    return VectF4(this->x-v.x, this->y-v.y, this->z-v.z, this->w-v.w);
#endif
}

inline VectF4& VectF4::operator*=(float const s){
#ifdef __SSE4_1__
    this->v *= s;
#else
    this->x *= s;
    this->y *= s;
    this->z *= s;
    this->w *= s;
#endif
    return *this;
}
inline VectF4& VectF4::operator/=(float const s){
#ifdef __SSE4_1__
    this->v /= s;
#else
    this->x /= s;
    this->y /= s;
    this->z /= s;
    this->w /= s;
#endif
    return *this;
}
inline VectF4& VectF4::operator+=(VectF4 const& v){
#ifdef __SSE4_1__
    this->v += v.v;
#else
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
    this->w += v.w;
#endif
    return *this;
}
inline VectF4& VectF4::operator-=(VectF4 const& v){
#ifdef __SSE4_1__
    this->v -= v.v;
#else
    this->x -= v.x;
    this->y -= v.y;
    this->z -= v.z;
    this->w -= v.w;
#endif
    return *this;
}

// -----------------------------------------------------------------------------
// VectF4 functions
// -----------------------------------------------------------------------------
inline float VectF4::length() const {
#ifdef __SSE4_1__
  return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(this->v, this->v, 0xF1)));
#else
  return sqrt(VectF4::dotProduct(*this, *this));
#endif
}

inline float VectF4::length3() const {
#ifdef __SSE4_1__
  return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(this->v, this->v, 0x71)));
#else
  return sqrt(VectF4::dotProduct3(*this, *this));
#endif
}

inline float VectF4::squareLength() const {
#ifdef __SSE4_1__
    return _mm_cvtss_f32(_mm_dp_ps(v, v, 0xF1));
#else
    return VectF4::dotProduct(*this, *this);
#endif
}

inline float VectF4::squareLength3() const {
#ifdef __SSE4_1__
    return _mm_cvtss_f32(_mm_dp_ps(v, v, 0x71));
#else
    return VectF4::dotProduct3(*this, *this);
#endif
}

inline VectF4 VectF4::normalize() const {
#ifdef __SSE4_1__
    __m128 vn = _mm_div_ps(v, _mm_sqrt_ps(_mm_dp_ps(v,v, 0xFF)));
    return VectF4(vn);
#else
    float len = this->length();
    return VectF4(x/len, y/len, z/len, w/len);
#endif
}

inline VectF4 VectF4::normalize3() const {
#ifdef __SSE4_1__
    __m128 vn = _mm_div_ps(v, _mm_sqrt_ps(_mm_dp_ps(v, v, 0x7F)));
    vn[3] = 0.0f;
    return VectF4(vn);
#else
    float len = this->length3();
    return VectF4(x/len, y/len, z/len, 0.0f);
#endif
}

inline void VectF4::set(float x, float y, float z, float w) {
#ifdef __SSE4_1__
  this->v = _mm_setr_ps(x, y, z, w);
#else
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
#endif
}

inline void VectF4::set(VectF4 const& v) {
#ifdef __SSE4_1__
  this->v = v.v;
#else
  this->x = v.x;
  this->y = v.y;
  this->z = v.z;
  this->w = v.w;
#endif
}

inline float VectF4::dotProduct(VectF4 const& v1, VectF4 const& v2) {
#ifdef __SSE4_1__
  return _mm_cvtss_f32(_mm_dp_ps(v1.v, v2.v, 0xF1));
#else
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
#endif
}

inline float VectF4::dotProduct3(VectF4 const& v1, VectF4 const& v2) {
#ifdef __SSE4_1__
  return _mm_cvtss_f32(_mm_dp_ps(v1.v, v2.v, 0x71));
#else
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
#endif
}

inline VectF4 VectF4::crossProduct3(const VectF4& b) const {
#ifdef __SSE4_1__
  return VectF4(
      _mm_sub_ps(
        _mm_mul_ps(
          _mm_shuffle_ps(this->v, this->v, _MM_SHUFFLE(1, 2, 0, 3)),
          _mm_shuffle_ps(b.v, b.v, _MM_SHUFFLE(2,0,1,3))),
        _mm_mul_ps(
          _mm_shuffle_ps(this->v, this->v, _MM_SHUFFLE(2, 0, 1, 3)),
          _mm_shuffle_ps(b.v, b.v, _MM_SHUFFLE(1, 2, 0, 3)))));
#else
  return VectF4(
      this->y * b.z - this->z * b.y,
      this->z * b.x - this->x * b.z,
      this->x * b.y - this->y * b.x, 0.0f);
#endif
}

std::ostream& operator<<(std::ostream &os, VectF4 const& v){
    os << "<" << v.x
      << ", " << v.y
      << ", " << v.z
      << ", " << v.w
      << ">";
    return os;
}
