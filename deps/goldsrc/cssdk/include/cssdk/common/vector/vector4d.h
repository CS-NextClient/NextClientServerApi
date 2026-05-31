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
#include <cssdk/common/vector/vector2d.h>
#include <cssdk/common/vector/vector3d.h>
#include <cassert>
#include <cmath>

// ReSharper disable CppNonExplicitConvertingConstructor
// ReSharper disable CppNonExplicitConversionOperator

namespace cssdk
{
    struct Vector4D;

    inline Vector4D operator+(const Vector4D& rhs, const Vector4D& lhs) noexcept;
    inline Vector4D operator-(const Vector4D& rhs, const Vector4D& lhs) noexcept;
    inline Vector4D operator/(const Vector4D& rhs, const Vector4D& lhs) noexcept;
    inline Vector4D operator*(const Vector4D& rhs, const Vector4D& lhs) noexcept;

    inline Vector4D& operator+=(Vector4D& rhs, const Vector4D& lhs) noexcept;
    inline Vector4D& operator-=(Vector4D& rhs, const Vector4D& lhs) noexcept;
    inline Vector4D& operator/=(Vector4D& rhs, const Vector4D& lhs) noexcept;
    inline Vector4D& operator*=(Vector4D& rhs, const Vector4D& lhs) noexcept;

    inline Vector4D operator+(const Vector4D& rhs, float lhs) noexcept;
    inline Vector4D operator-(const Vector4D& rhs, float lhs) noexcept;
    inline Vector4D operator/(const Vector4D& rhs, float lhs) noexcept;
    inline Vector4D operator*(const Vector4D& rhs, float lhs) noexcept;

    inline Vector4D operator+(float rhs, const Vector4D& lhs) noexcept;
    inline Vector4D operator-(float rhs, const Vector4D& lhs) noexcept;
    inline Vector4D operator/(float rhs, const Vector4D& lhs) noexcept;
    inline Vector4D operator*(float rhs, const Vector4D& lhs) noexcept;

    inline Vector4D& operator+=(Vector4D& rhs, float lhs) noexcept;
    inline Vector4D& operator-=(Vector4D& rhs, float lhs) noexcept;
    inline Vector4D& operator/=(Vector4D& rhs, float lhs) noexcept;
    inline Vector4D& operator*=(Vector4D& rhs, float lhs) noexcept;

    struct Vector4D
    {
        Vector4D()
            : x(0.F), y(0.F), z(0.F), w(0.F)
        {
        }

        Vector4D(const float x_axis, const float y_axis, const float z_axis, const float w_axis = 0.F) noexcept
            : x(x_axis), y(y_axis), z(z_axis), w(w_axis)
        {
        }

        explicit Vector4D(const Vector2D& vector_2d, const float z_axis = 0.F, const float w_axis = 0.F) noexcept
            : x(vector_2d.x), y(vector_2d.y), z(z_axis), w(w_axis)
        {
        }

        explicit Vector4D(const Vector3D& vector_3d, const float w_axis = 0.F) noexcept
            : x(vector_3d.x), y(vector_3d.y), z(vector_3d.z), w(w_axis)
        {
        }

        ~Vector4D() = default;
        Vector4D(Vector4D&&) = default;
        Vector4D(const Vector4D&) = default;
        Vector4D& operator=(Vector4D&&) = default;
        Vector4D& operator=(const Vector4D&) = default;

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
            assert(index >= 0 && index < 4);
            return *Ptr()[index];
        }

        template <typename Index>
        [[nodiscard]] float operator[](const Index index) const
        {
            assert(index >= 0 && index < 4);
            return *Ptr()[index];
        }

        Vector4D& operator=(const float value)
        {
            x = y = z = w = value;
            return *this;
        }

        [[nodiscard]] Vector4D operator-() const noexcept
        {
            return Vector4D{-x, -y, -z, -w};
        }

        [[nodiscard]] Vector4D operator+() const noexcept
        {
            return Vector4D{+x, +y, +z, +w};
        }

        /**
         * @brief Tests if this vector contains valid finite elements.
        */
        [[nodiscard]] bool IsFinite() const noexcept
        {
            return std::isfinite(x) && std::isfinite(y) && std::isfinite(z) && std::isfinite(w);
        }

        /**
         * @brief Return \c true if this vector is (0,0,0,0) within the tolerance, \c false otherwise.
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
        [[nodiscard]] bool Equals(const Vector4D& other, const float tolerance = 0.001F) const noexcept
        {
            return std::abs(x - other.x) < tolerance && std::abs(y - other.y) < tolerance &&
                std::abs(z - other.z) < tolerance && std::abs(w - other.w) < tolerance;
        }

        /**
         * @brief Returns \c true if the unary predicate returns true for all vector elements, \c false otherwise.
         *
         * @param predicate Unary predicate.
        */
        template <typename Func>
        [[nodiscard]] bool All(const Func& predicate) const
        {
            return predicate(x) && predicate(y) && predicate(z) && predicate(w);
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
            return predicate(x) || predicate(y) || predicate(z) || predicate(w);
        }

        /**
         * @brief Computes the squared length of this vector.
         *
         * @note Calling this function is faster than calling \c Length,
         * since this function avoids computing a square root.
         * If you only need to compare lengths to each other, but are not interested in the actual length values,
         * you can compare by using \c LengthSquared, instead of \c Length,
         * since \c sqrt is an order-preserving (monotonous and non-decreasing) function.
        */
        [[nodiscard]] float LengthSquared() const noexcept
        {
            return x * x + y * y + z * z + w * w;
        }

        /**
         * @brief Computes the squared length of this vector (same as Magnitude).
        */
        [[nodiscard]] float Length() const noexcept
        {
            return std::sqrt(LengthSquared());
        }

        /**
         * @brief Computes the distance between a plane and a point.
        */
        [[nodiscard]] float PlaneDistance(const Vector3D& point) const noexcept
        {
            return Vector3D{x, y, z}.DotProduct(point) + w;
        }

        /**
         * @brief Returns the intersection point.
        */
        bool PlaneRayIntersect(const Vector3D& ray_origin, const Vector3D& ray_dir, Vector3D& intersection) const noexcept
        {
            if (const auto dp = Vector3D{x, y, z}.DotProduct(ray_dir); std::abs(dp) > 0.01F) {
                const auto distance1 = PlaneDistance(ray_origin + ray_dir);
                const auto distance2 = PlaneDistance(ray_origin);

                if (std::abs(distance1) <= std::abs(distance2) || std::signbit(distance1) != std::signbit(distance2)) {
                    intersection = ray_origin - ray_dir * (distance2 / dp);
                    return true;
                }
            }

            return false;
        }

        /**
         * @brief Negate this vector.
        */
        Vector4D& Negate() noexcept
        {
            x = -x;
            y = -y;
            z = -z;
            w = -w;

            return *this;
        }

        /**
         * @brief Constructs a plane out of 4 points in space.
        */
        static Vector4D Plane3Points(const Vector3D& point1, const Vector3D& point2, const Vector3D& point3) noexcept
        {
            const auto normal_a = (point3 - point1).Normalize();
            const auto normal_b = (point3 - point2).Normalize();
            const auto normal_c = normal_a.CrossProduct(normal_b).Normalize();

            Vector4D plane{normal_c.x, normal_c.y, normal_c.z};
            plane.w = normal_c.Negated().DotProduct(point1);

            return plane;
        }

        /**
         * @brief X-axis.
        */
        float x;

        /**
         * @brief Y-axis.
        */
        float y;

        /**
         * @brief Z-axis.
        */
        float z;

        /**
         * @brief W-axis.
        */
        float w;
    };

    [[nodiscard]] inline Vector4D operator+(const Vector4D& rhs, const Vector4D& lhs) noexcept
    {
        assert(rhs.IsFinite());
        assert(lhs.IsFinite());

        return Vector4D{rhs.x + lhs.x, rhs.y + lhs.y, rhs.z + lhs.z, rhs.w + lhs.w};
    }

    [[nodiscard]] inline Vector4D operator-(const Vector4D& rhs, const Vector4D& lhs) noexcept
    {
        assert(rhs.IsFinite());
        assert(lhs.IsFinite());

        return Vector4D{rhs.x - lhs.x, rhs.y - lhs.y, rhs.z - lhs.z, rhs.w - lhs.w};
    }

    [[nodiscard]] inline Vector4D operator*(const Vector4D& rhs, const Vector4D& lhs) noexcept
    {
        assert(rhs.IsFinite());
        assert(lhs.IsFinite());

        return Vector4D{rhs.x * lhs.x, rhs.y * lhs.y, rhs.z * lhs.z, rhs.w * lhs.w};
    }

    [[nodiscard]] inline Vector4D operator/(const Vector4D& rhs, const Vector4D& lhs) noexcept
    {
        assert(rhs.IsFinite());
        assert(lhs.IsFinite());
        assert(lhs.x > FLOAT_EPSILON);
        assert(lhs.y > FLOAT_EPSILON);
        assert(lhs.z > FLOAT_EPSILON);
        assert(lhs.w > FLOAT_EPSILON);

        return Vector4D{rhs.x / lhs.x, rhs.y / lhs.y, rhs.z / lhs.z, rhs.w / lhs.w};
    }

    inline Vector4D& operator+=(Vector4D& rhs, const Vector4D& lhs) noexcept
    {
        assert(rhs.IsFinite());
        assert(lhs.IsFinite());

        rhs.x += lhs.x;
        rhs.y += lhs.y;
        rhs.z += lhs.z;
        rhs.w += lhs.w;

        return rhs;
    }

    inline Vector4D& operator-=(Vector4D& rhs, const Vector4D& lhs) noexcept
    {
        assert(rhs.IsFinite());
        assert(lhs.IsFinite());

        rhs.x -= lhs.x;
        rhs.y -= lhs.y;
        rhs.z -= lhs.z;
        rhs.w -= lhs.w;

        return rhs;
    }

    inline Vector4D& operator*=(Vector4D& rhs, const Vector4D& lhs) noexcept
    {
        assert(rhs.IsFinite());
        assert(lhs.IsFinite());

        rhs.x *= lhs.x;
        rhs.y *= lhs.y;
        rhs.z *= lhs.z;
        rhs.w *= lhs.w;

        return rhs;
    }

    inline Vector4D& operator/=(Vector4D& rhs, const Vector4D& lhs) noexcept
    {
        assert(rhs.IsFinite());
        assert(lhs.IsFinite());
        assert(lhs.x > FLOAT_EPSILON);
        assert(lhs.y > FLOAT_EPSILON);
        assert(lhs.z > FLOAT_EPSILON);
        assert(lhs.w > FLOAT_EPSILON);

        rhs.x /= lhs.x;
        rhs.y /= lhs.y;
        rhs.z /= lhs.z;
        rhs.w /= lhs.w;

        return rhs;
    }

    [[nodiscard]] inline Vector4D operator+(const Vector4D& rhs, const float lhs) noexcept
    {
        assert(std::isfinite(lhs));
        return Vector4D{rhs.x + lhs, rhs.y + lhs, rhs.z + lhs, rhs.w + lhs};
    }

    [[nodiscard]] inline Vector4D operator-(const Vector4D& rhs, const float lhs) noexcept
    {
        assert(std::isfinite(lhs));
        return Vector4D{rhs.x - lhs, rhs.y - lhs, rhs.z - lhs, rhs.w - lhs};
    }

    [[nodiscard]] inline Vector4D operator*(const Vector4D& rhs, const float lhs) noexcept
    {
        assert(std::isfinite(lhs));
        return Vector4D{rhs.x * lhs, rhs.y * lhs, rhs.z * lhs, rhs.w * lhs};
    }

    [[nodiscard]] inline Vector4D operator/(const Vector4D& rhs, const float lhs) noexcept
    {
        assert(std::isfinite(lhs));
        assert(lhs > FLOAT_EPSILON);

        return Vector4D{rhs.x / lhs, rhs.y / lhs, rhs.z / lhs, rhs.w / lhs};
    }

    [[nodiscard]] inline Vector4D operator+(const float rhs, const Vector4D& lhs) noexcept
    {
        return operator+(lhs, rhs);
    }

    [[nodiscard]] inline Vector4D operator-(const float rhs, const Vector4D& lhs) noexcept
    {
        return operator-(lhs, rhs);
    }

    [[nodiscard]] inline Vector4D operator*(const float rhs, const Vector4D& lhs) noexcept
    {
        return operator*(lhs, rhs);
    }

    [[nodiscard]] inline Vector4D operator/(const float rhs, const Vector4D& lhs) noexcept
    {
        return operator/(lhs, rhs);
    }

    inline Vector4D& operator+=(Vector4D& rhs, const float lhs) noexcept
    {
        assert(rhs.IsFinite());
        assert(std::isfinite(lhs));

        rhs.x += lhs;
        rhs.y += lhs;
        rhs.z += lhs;
        rhs.w += lhs;

        return rhs;
    }

    inline Vector4D& operator-=(Vector4D& rhs, const float lhs) noexcept
    {
        assert(rhs.IsFinite());
        assert(std::isfinite(lhs));

        rhs.x -= lhs;
        rhs.y -= lhs;
        rhs.z -= lhs;
        rhs.w -= lhs;

        return rhs;
    }

    inline Vector4D& operator*=(Vector4D& rhs, const float lhs) noexcept
    {
        assert(rhs.IsFinite());
        assert(std::isfinite(lhs));

        rhs.x *= lhs;
        rhs.y *= lhs;
        rhs.z *= lhs;
        rhs.w *= lhs;

        return rhs;
    }

    inline Vector4D& operator/=(Vector4D& rhs, const float lhs) noexcept
    {
        assert(rhs.IsFinite());
        assert(std::isfinite(lhs));
        assert(lhs > FLOAT_EPSILON);

        rhs.x /= lhs;
        rhs.y /= lhs;
        rhs.z /= lhs;
        rhs.w /= lhs;

        return rhs;
    }
}
