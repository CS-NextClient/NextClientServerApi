/*
 *  Half Life 1 SDK Copyright(c) Valve Corp.
 *
 *  THIS DOCUMENT DESCRIBES A CONTRACT BETWEEN YOU AND VALVE CORPORATION ("Valve").
 *  PLEASE READ IT BEFORE DOWNLOADING OR USING THE HALF LIFE 1 SDK ("SDK"). BY
 *  DOWNLOADING AND/OR USING THE HALF LIFE 1 SDK YOU ACCEPT THIS LICENSE. IF YOU DO
 *  NOT AGREE TO THE TERMS OF THIS LICENSE PLEASE DON'T DOWNLOAD OR USE THE SDK.
 *
 *  You may, free of charge, download and use the SDK to develop a modified Valve
 *  game running on the Half-Life 1 engine. You may distribute your modified Valve
 *  game in source and object code form, but only for free. Terms of use for Valve
 *  games are found in the Steam Subscriber Agreement located here:
 *  http://store.steampowered.com/subscriber_agreement/
 *
 *  You may copy, modify, and distribute the SDK and any modifications you make to
 *  the SDK in source and object code form, but only for free. Any distribution of
 *  this SDK must include this LICENSE file.
 *
 *  Any distribution of the SDK or a substantial portion of the SDK must include
 *  the above copyright notice and the following:
 *
 *    DISCLAIMER OF WARRANTIES. THE HALF LIFE 1 SDK AND ANY OTHER MATERIAL
 *    DOWNLOADED BY LICENSEE IS PROVIDED "AS IS". VALVE AND ITS SUPPLIERS
 *    DISCLAIM ALL WARRANTIES WITH RESPECT TO THE SDK, EITHER EXPRESS OR IMPLIED,
 *    INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY,
 *    NON-INFRINGEMENT, TITLE AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *    LIMITATION OF LIABILITY. IN NO EVENT SHALL VALVE OR ITS SUPPLIERS BE LIABLE
 *    FOR ANY SPECIAL, INCIDENTAL, INDIRECT, OR CONSEQUENTIAL DAMAGES WHATSOEVER
 *    (INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS,
 *    BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR ANY OTHER PECUNIARY
 *    LOSS) ARISING OUT OF THE USE OF OR INABILITY TO USE THE ENGINE AND/OR THE
 *    SDK, EVEN IF VALVE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 *
 *  If you would like to use the SDK for a commercial purpose, please contact Valve
 *  at sourceengine@valvesoftware.com.
 */

#pragma once

#include <cssdk/common/const.h>
#include <cassert>
#include <cmath>

// ReSharper disable CppNonExplicitConvertingConstructor
// ReSharper disable CppNonExplicitConversionOperator

namespace cssdk
{
    struct Vector2D;

    inline Vector2D operator+(const Vector2D& rhs, const Vector2D& lhs) noexcept;
    inline Vector2D operator-(const Vector2D& rhs, const Vector2D& lhs) noexcept;
    inline Vector2D operator/(const Vector2D& rhs, const Vector2D& lhs) noexcept;
    inline Vector2D operator*(const Vector2D& rhs, const Vector2D& lhs) noexcept;

    inline Vector2D& operator+=(Vector2D& rhs, const Vector2D& lhs) noexcept;
    inline Vector2D& operator-=(Vector2D& rhs, const Vector2D& lhs) noexcept;
    inline Vector2D& operator/=(Vector2D& rhs, const Vector2D& lhs) noexcept;
    inline Vector2D& operator*=(Vector2D& rhs, const Vector2D& lhs) noexcept;

    inline Vector2D operator+(const Vector2D& rhs, float lhs) noexcept;
    inline Vector2D operator-(const Vector2D& rhs, float lhs) noexcept;
    inline Vector2D operator/(const Vector2D& rhs, float lhs) noexcept;
    inline Vector2D operator*(const Vector2D& rhs, float lhs) noexcept;

    inline Vector2D operator+(float rhs, const Vector2D& lhs) noexcept;
    inline Vector2D operator-(float rhs, const Vector2D& lhs) noexcept;
    inline Vector2D operator/(float rhs, const Vector2D& lhs) noexcept;
    inline Vector2D operator*(float rhs, const Vector2D& lhs) noexcept;

    inline Vector2D& operator+=(Vector2D& rhs, float lhs) noexcept;
    inline Vector2D& operator-=(Vector2D& rhs, float lhs) noexcept;
    inline Vector2D& operator/=(Vector2D& rhs, float lhs) noexcept;
    inline Vector2D& operator*=(Vector2D& rhs, float lhs) noexcept;

    struct Vector2D
    {
        Vector2D()
            : x(0.F), y(0.F)
        {
        }

        Vector2D(const float x_axis, const float y_axis) noexcept
            : x(x_axis), y(y_axis)
        {
        }

        ~Vector2D() = default;
        Vector2D(Vector2D&&) = default;
        Vector2D(const Vector2D&) = default;
        Vector2D& operator=(Vector2D&&) = default;
        Vector2D& operator=(const Vector2D&) = default;

        [[nodiscard]] float* Ptr()
        {
            return &x;
        }

        [[nodiscard]] const float* Ptr() const
        {
            return &x;
        }

        operator float*()
        {
            return Ptr();
        }

        operator const float*() const
        {
            return Ptr();
        }

        template <typename Index>
        [[nodiscard]] float& operator[](const Index index)
        {
            assert(index >= 0 && index < 2);
            return *Ptr()[index];
        }

        template <typename Index>
        [[nodiscard]] float operator[](const Index index) const
        {
            assert(index >= 0 && index < 2);
            return *Ptr()[index];
        }

        Vector2D& operator=(const float value)
        {
            x = y = value;
            return *this;
        }

        [[nodiscard]] Vector2D operator-() const noexcept
        {
            return Vector2D{-x, -y};
        }

        [[nodiscard]] Vector2D operator+() const noexcept
        {
            return Vector2D{+x, +y};
        }

        /**
         * @brief Tests if this vector contains valid finite elements.
        */
        [[nodiscard]] bool IsFinite() const noexcept
        {
            return std::isfinite(x) && std::isfinite(y);
        }

        /**
         * @brief Return \c true if this vector is (0,0) within the tolerance, \c false otherwise.
        */
        [[nodiscard]] bool IsZero(const float tolerance = 0.01F) const noexcept
        {
            return LengthSquared() <= tolerance;
        }

        /**
         * @brief Checks if the length of this vector is equal to one within the given tolerance.
        */
        [[nodiscard]] bool IsNormalized(const float tolerance = 1E-5F) const noexcept
        {
            return std::abs(LengthSquared() - 1.F) <= tolerance;
        }

        /**
         * @brief Returns \c true if the two vectors are equal within the tolerance, \c false otherwise.
        */
        [[nodiscard]] bool Equals(const Vector2D& other, const float tolerance = 0.001F) const noexcept
        {
            return std::abs(x - other.x) < tolerance && std::abs(y - other.y) < tolerance;
        }

        /**
         * @brief Returns \c true if the unary predicate returns true for all vector elements, \c false otherwise.
         *
         * @param predicate Unary predicate.
        */
        template <typename Func>
        [[nodiscard]] bool All(const Func& predicate) const
        {
            return predicate(x) && predicate(y);
        }

        /**
         * @brief Returns \c true if the unary predicate returns true for at least one of the vector elements,
         * \c false otherwise.
         *
         * @param predicate Unary predicate.
        */
        template <typename Func>
        [[nodiscard]] bool Any(const Func& predicate) const
        {
            return predicate(x) || predicate(y);
        }

        /**
         * @brief Computes the squared length of this vector.
         *
         * @note Calling this function is faster than calling \c Length,
         * since this function avoids computing a square root.
         *
         * @note If you only need to compare lengths to each other, but are not interested in the actual length values,
         * you can compare by using \c LengthSquared, instead of \c Length, since \c sqrt
         * is an order-preserving (monotonous and non-decreasing) function.
        */
        [[nodiscard]] float LengthSquared() const noexcept
        {
            return x * x + y * y;
        }

        /**
         * @brief Computes the squared length of this vector (same as Magnitude).
        */
        [[nodiscard]] float Length() const noexcept
        {
            return std::sqrt(LengthSquared());
        }

        /**
         * @brief Computes the squared distance between this and the given vector.
         *
         * @note Calling this function is faster than calling \c Distance,
         * since this function avoids computing a square root.
         *
         * @note If you only need to compare distances to each other, but are not interested in the actual distance
         * values, you can compare by using \c DistanceSquared, instead of \c Distance, since \c sqrt is an
         * order-preserving (monotonous and non-decreasing) function.
        */
        [[nodiscard]] float DistanceSquared(const Vector2D& other) const noexcept
        {
            const auto dx = x - other.x;
            const auto dy = y - other.y;

            return dx * dx + dy * dy;
        }

        /**
         * @brief Computes the distance between this and the given vector.
        */
        [[nodiscard]] float Distance(const Vector2D& other) const noexcept
        {
            return std::sqrt(DistanceSquared(other));
        }

        /**
         * @brief Computes the dot product of this and the given vector.
         *
         * @note The dot product has a geometric interpretation of measuring how close two direction vectors
         * are to pointing in the same direction, computing angles between vectors,
         * or the length of a projection of one vector to another.
        */
        [[nodiscard]] float DotProduct(const Vector2D& other) const noexcept
        {
            return x * other.x + y * other.y;
        }

        /**
         * @brief Returns the aimed angle direction of this vector, in radians.
         *
         * @note The aimed angle of a 2D vector corresponds to the theta part (or azimuth) of the polar coordinate
         * representation of this vector. Essentially, describes the direction this vector is pointing at.
         * A vector pointing towards +X returns 0, vector pointing towards +Y returns pi / 2,
         * vector pointing towards -X returns pi, and a vector pointing towards -Y returns -pi / 2 (equal to 3pi / 2).
        */
        [[nodiscard]] float AimedAngle() const noexcept
        {
            assert(!IsZero());
            return std::atan2(y, x);
        }

        /**
         * @brief Returns the angle between this vector and the specified vector, in radians.
         *
         * @note This function takes into account that this vector or the other vector can be unnormalized,
         * and normalizes the computations. If you are computing the angle between two normalized vectors,
         * it is better to use \c AngleBetweenNorm.
        */
        [[nodiscard]] float AngleBetween(const Vector2D& other) const noexcept
        {
            return std::acos(DotProduct(other)) / std::sqrt(LengthSquared() * other.LengthSquared());
        }

        /**
         * @brief Returns the angle between this vector and the specified normalized vector, in radians.
         *
         * @note This vector must be normalized to call this function.
        */
        [[nodiscard]] float AngleBetweenNorm(const Vector2D& other) const noexcept
        {
            assert(IsNormalized());
            assert(other.IsNormalized());

            return std::acos(DotProduct(other));
        }

        /**
         * @brief Negate this vector.
         *
         * @return \c *this
        */
        Vector2D& Negate() noexcept
        {
            x = -x;
            y = -y;

            return *this;
        }

        /**
         * @brief Normalizes this vector.
         * In the case of failure, this vector is set to (0, 1), so calling this function
         * will never result in an unnormalized vector.
         *
         * @return \c *this
        */
        Vector2D& Normalize() noexcept
        {
            assert(IsFinite());

            if (const auto length_squared = LengthSquared(); length_squared > 1E-6F) {
                *this *= 1.F / std::sqrt(length_squared);
            }
            else {
                x = 0.F;
                y = 1.F; // We will always produce a normalized vector.
            }

            return *this;
        }

        /**
         * @brief Returns a normalized copy of this vector.
         * In the case of failure, this vector is set to (0, 1), so calling this function
         * will never result in an unnormalized vector.
        */
        [[nodiscard]] Vector2D Normalized() const noexcept
        {
            Vector2D vector_copy{x, y};
            vector_copy.Normalize();

            return vector_copy;
        }

        /**
         * @brief Projects this vector onto the given unnormalized direction vector.
         * In the case of failure, this vector is set to (0, 1), so calling this function
         * will never result in an unnormalized vector.
         *
         * @param direction The direction vector to project this vector onto.
         * This function will normalize this vector, so you can pass in an unnormalized vector.
        */
        [[nodiscard]] Vector2D ProjectTo(const Vector2D& direction) const noexcept
        {
            assert(!direction.IsZero());
            return direction * DotProduct(direction) / direction.LengthSquared();
        }

        /**
         * @brief Projects this vector onto the given normalized direction vector.
         *
         * @param direction The vector to project onto. This vector must be normalized.
        */
        [[nodiscard]] Vector2D ProjectToNorm(const Vector2D& direction) const noexcept
        {
            assert(!direction.IsZero());
            assert(direction.IsNormalized());

            return direction * DotProduct(direction);
        }

        /**
         * @brief Returns this vector reflected about a plane with the given normal.
         * By convention, both this and the reflected vector point away from the plane with the given normal.
        */
        [[nodiscard]] Vector2D Reflect(const Vector2D& normal) const noexcept
        {
            assert(normal.IsNormalized());
            return 2.F * ProjectToNorm(normal) - *this;
        }

        /**
         * @brief Converts this euclidean (x, y) \c Vector2D to polar coordinates
         * representation in the form (theta, length).
         *
         * @note A \c Vector2D that has the first component (x) representing the aimed angle (azimuth) of
         * this direction vector, in radians, and is equal to atan2(this.y, this.x).
         * The x component has a range of [-pi / 2, pi / 2].
         * The second component (y) of the returned vector stores the length (radius) of this vector.
        */
        [[nodiscard]] Vector2D ToPolarCoordinates() const noexcept
        {
            const float radius = Length();
            return radius > 1E-4F ? Vector2D{std::atan2(y, x), radius} : Vector2D{0.F, 0.F};
        }

        /**
         * @brief Returns a vector that is perpendicular to this vector (rotated 90 degrees clock-wise).
        */
        [[nodiscard]] Vector2D Rotated90CW() const noexcept
        {
            return Vector2D{y, -x};
        }

        /**
         * @brief Returns a vector that is perpendicular to this vector (rotated 90 degrees counter-clock-wise).
        */
        [[nodiscard]] Vector2D Rotated90CCW() const noexcept
        {
            return Vector2D{-y, x};
        }

        /**
         * @brief Linearly interpolates between this and the other vector.
         *
         * @param b The target endpoint to lerp towards to.
         * @param t The interpolation weight, in the range [0, 1].
         *
         * @return \c Lerp(b, 0) returns this vector, \c Lerp(b, 1) returns the vector b.
         * \c Lerp(b, 0.5) returns the vector half-way in between the two vectors, and so on.
         * \c Lerp(b, t) returns \c (1 - t) *this + t * b.
        */
        [[nodiscard]] Vector2D Lerp(const Vector2D& b, const float t) const noexcept
        {
            return (1.F - t) * *this + t * b;
        }

        /**
         * @brief X-axis.
        */
        float x;

        /**
         * @brief Y-axis.
        */
        float y;
    };

    [[nodiscard]] inline Vector2D operator+(const Vector2D& rhs, const Vector2D& lhs) noexcept
    {
        assert(rhs.IsFinite());
        assert(lhs.IsFinite());

        return Vector2D{rhs.x + lhs.x, rhs.y + lhs.y};
    }

    [[nodiscard]] inline Vector2D operator-(const Vector2D& rhs, const Vector2D& lhs) noexcept
    {
        assert(rhs.IsFinite());
        assert(lhs.IsFinite());

        return Vector2D{rhs.x - lhs.x, rhs.y - lhs.y};
    }

    [[nodiscard]] inline Vector2D operator*(const Vector2D& rhs, const Vector2D& lhs) noexcept
    {
        assert(rhs.IsFinite());
        assert(lhs.IsFinite());

        return Vector2D{rhs.x * lhs.x, rhs.y * lhs.y};
    }

    [[nodiscard]] inline Vector2D operator/(const Vector2D& rhs, const Vector2D& lhs) noexcept
    {
        assert(rhs.IsFinite());
        assert(lhs.IsFinite());
        assert(lhs.x > FLOAT_EPSILON);
        assert(lhs.y > FLOAT_EPSILON);

        return Vector2D{rhs.x / lhs.x, rhs.y / lhs.y};
    }

    inline Vector2D& operator+=(Vector2D& rhs, const Vector2D& lhs) noexcept
    {
        assert(rhs.IsFinite());
        assert(lhs.IsFinite());

        rhs.x += lhs.x;
        rhs.y += lhs.y;

        return rhs;
    }

    inline Vector2D& operator-=(Vector2D& rhs, const Vector2D& lhs) noexcept
    {
        assert(rhs.IsFinite());
        assert(lhs.IsFinite());

        rhs.x -= lhs.x;
        rhs.y -= lhs.y;

        return rhs;
    }

    inline Vector2D& operator*=(Vector2D& rhs, const Vector2D& lhs) noexcept
    {
        assert(rhs.IsFinite());
        assert(lhs.IsFinite());

        rhs.x *= lhs.x;
        rhs.y *= lhs.y;

        return rhs;
    }

    inline Vector2D& operator/=(Vector2D& rhs, const Vector2D& lhs) noexcept
    {
        assert(rhs.IsFinite());
        assert(lhs.IsFinite());
        assert(lhs.x > FLOAT_EPSILON);
        assert(lhs.y > FLOAT_EPSILON);

        rhs.x /= lhs.x;
        rhs.y /= lhs.y;

        return rhs;
    }

    [[nodiscard]] inline Vector2D operator+(const Vector2D& rhs, const float lhs) noexcept
    {
        assert(std::isfinite(lhs));
        return Vector2D{rhs.x + lhs, rhs.y + lhs};
    }

    [[nodiscard]] inline Vector2D operator-(const Vector2D& rhs, const float lhs) noexcept
    {
        assert(std::isfinite(lhs));
        return Vector2D{rhs.x - lhs, rhs.y - lhs};
    }

    [[nodiscard]] inline Vector2D operator*(const Vector2D& rhs, const float lhs) noexcept
    {
        assert(std::isfinite(lhs));
        return Vector2D{rhs.x * lhs, rhs.y * lhs};
    }

    [[nodiscard]] inline Vector2D operator/(const Vector2D& rhs, const float lhs) noexcept
    {
        assert(std::isfinite(lhs));
        assert(lhs > FLOAT_EPSILON);

        return Vector2D{rhs.x / lhs, rhs.y / lhs};
    }

    [[nodiscard]] inline Vector2D operator+(const float rhs, const Vector2D& lhs) noexcept
    {
        return operator+(lhs, rhs);
    }

    [[nodiscard]] inline Vector2D operator-(const float rhs, const Vector2D& lhs) noexcept
    {
        return operator-(lhs, rhs);
    }

    [[nodiscard]] inline Vector2D operator*(const float rhs, const Vector2D& lhs) noexcept
    {
        return operator*(lhs, rhs);
    }

    [[nodiscard]] inline Vector2D operator/(const float rhs, const Vector2D& lhs) noexcept
    {
        return operator/(lhs, rhs);
    }

    inline Vector2D& operator+=(Vector2D& rhs, const float lhs) noexcept
    {
        assert(rhs.IsFinite());
        assert(std::isfinite(lhs));

        rhs.x += lhs;
        rhs.y += lhs;

        return rhs;
    }

    inline Vector2D& operator-=(Vector2D& rhs, const float lhs) noexcept
    {
        assert(rhs.IsFinite());
        assert(std::isfinite(lhs));

        rhs.x -= lhs;
        rhs.y -= lhs;

        return rhs;
    }

    inline Vector2D& operator*=(Vector2D& rhs, const float lhs) noexcept
    {
        assert(rhs.IsFinite());
        assert(std::isfinite(lhs));

        rhs.x *= lhs;
        rhs.y *= lhs;

        return rhs;
    }

    inline Vector2D& operator/=(Vector2D& rhs, const float lhs) noexcept
    {
        assert(rhs.IsFinite());
        assert(std::isfinite(lhs));
        assert(lhs > FLOAT_EPSILON);

        rhs.x /= lhs;
        rhs.y /= lhs;

        return rhs;
    }
}
