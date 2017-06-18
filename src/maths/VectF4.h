#ifndef ENGINE_MATHS_VECTF4_H_
#define ENGINE_MATHS_VECTF4_H_

#include <iostream>
#include <cmath>
#include <xmmintrin.h>

/**
 * 4 Dimensions vector with float precision.
 *
 * \since   Jun 4, 2017
 * \author  Constantin MASSON
 */
class VectF4 {
    // -------------------------------------------------------------------------
    // Attributes
    // -------------------------------------------------------------------------
    public:
      __m128 v;

    // -------------------------------------------------------------------------
    // Constructors
    // -------------------------------------------------------------------------
    public:
        VectF4(void);
        VectF4(float x, float y, float z, float w);
        VectF4(VectF4 const& v);
        VectF4(const __m128 &v);

    // -------------------------------------------------------------------------
    // Functions (Object range)
    // -------------------------------------------------------------------------
    public:
        /**
         * Get the length of this vector.
         *
         * \return The length (Magnitude) of this vector.
         */
        float length() const;

        /**
         * Get the length of this vector without W axis.
         *
         * \return The length (Magnitude) of this vector.
         */
        float length3() const;

        /**
         * Get the square length of this vector.
         *
         *\return The square length (Magnitude) of this vector.
         */
        float squareLength() const;

        /**
         * Get the square length of this vector without W axis.
         *
         *\return The square length (Magnitude) of this vector.
         */
        float squareLength3() const;

        /**
         * Returns a normalized copy of this vector
         * Vector shouldn't be null (No check done here).
         *
         * \return The normalized vector.
         */
        VectF4 normalize() const;

        /**
         * Returns a normalized copy of this vector without taking W axis into account.
         * Vector shouldn't be null (No check done here).
         * W axis is set to 0.
         *
         * \return The normalized vector.
         */
        VectF4 normalize3() const;

        /**
         * Reset all axis value of this vector.
         *
         * \param x New x coordinate.
         * \param y New y coordinate.
         * \param z New z coordinate.
         * \param w New w coordinate.
         */
        void set(float x, float y, float z, float w);

        /**
         * Change axis values by the given vector values
         *
         * \param v Vector to use as copy
         */
        void set(VectF4 const& v);


    // -------------------------------------------------------------------------
    // Static Functions
    // -------------------------------------------------------------------------
    public:
        /**
         * Get Dot Product of 2 vectors.
         *
         * \param v1 Vector 1
         * \param v2 Vector 2
         * \return The dot product v1.v2
         */
        static float dotProduct3(VectF4 const& v1, VectF4 const& v2);

        /**
         * Get Dot Product of 2 vectors using only axis X,Y,and Z (No W)
         *
         * \param v1 Vector 1
         * \param v2 Vector 2
         * \return The dot product v1.v2
         */
        static float dotProduct(VectF4 const& v1, VectF4 const& v2);


    // -------------------------------------------------------------------------
    // Operators overload
    // -------------------------------------------------------------------------
    public:
        // Comparison operators
        bool operator==(VectF4 const& v) const;
        bool operator!=(VectF4 const& v) const;

    public:
        // Arithmetic operators
        VectF4 operator*(float const s) const;
        VectF4 operator/(float const s) const;
        VectF4 operator+(VectF4 const& v) const;
        VectF4 operator-(VectF4 const& v) const;

        VectF4& operator*=(float const s);
        VectF4& operator/=(float const s);
        VectF4& operator+=(VectF4 const& v);
        VectF4& operator-=(VectF4 const& v);

        // Flux operators
        friend std::ostream& operator<<(std::ostream& os, VectF4 const& v);
};

#define VECTF4_X(obj) (obj.v)[0]
#define VECTF4_Y(obj) (obj.v)[1]
#define VECTF4_Z(obj) (obj.v)[2]
#define VECTF4_W(obj) (obj.v)[3]

#ifndef __VECTF4_INLINE
#  include "./VectF4.inl"
#endif

#endif



