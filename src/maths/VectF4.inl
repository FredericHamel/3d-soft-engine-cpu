#define __VECTF4_INLINE
# include "./VectF4.h"
#undef __VECTF4_INLINE


// -----------------------------------------------------------------------------
// VectF4 Operators overload
// -----------------------------------------------------------------------------
inline bool VectF4::operator==(VectF4 const& v) const {
    __m128 compare = _mm_cmpeq_ps(this->v, v.v);
    return _mm_movemask_ps(compare);
}
inline bool VectF4::operator!=(VectF4 const& v) const{
  __m128 compare = _mm_cmpneq_ps(this->v, v.v);
  return _mm_movemask_ps(compare);
}
inline VectF4 VectF4::operator*(float const s) const{
    return VectF4(this->v*s);
}
inline VectF4 VectF4::operator/(float const s) const{
    return VectF4(this->v/s);
}
inline VectF4 VectF4::operator+(VectF4 const& v) const{
    return VectF4(this->v + v.v);
}
inline VectF4 VectF4::operator-(VectF4 const& v) const{
    return VectF4(this->v - v.v);
}

inline VectF4& VectF4::operator*=(float const s){
    this->v *= s;
    return *this;
}
inline VectF4& VectF4::operator/=(float const s){
    this->v /= s;
    return *this;
}
inline VectF4& VectF4::operator+=(VectF4 const& v){
    this->v += v.v;
    return *this;
}
inline VectF4& VectF4::operator-=(VectF4 const& v){
    this->v -= v.v;
    return *this;
}

