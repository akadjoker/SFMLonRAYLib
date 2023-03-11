////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2018 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef SFML_VECTOR2_HPP
#define SFML_VECTOR2_HPP


namespace sf
{
////////////////////////////////////////////////////////////
/// \brief Utility template class for manipulating
///        2-dimensional vectors
///
////////////////////////////////////////////////////////////
template <typename T>
class iVector2
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Creates a iVector2(0, 0).
    ///
    ////////////////////////////////////////////////////////////
    iVector2();

    ////////////////////////////////////////////////////////////
    /// \brief Construct the vector from its coordinates
    ///
    /// \param X X coordinate
    /// \param Y Y coordinate
    ///
    ////////////////////////////////////////////////////////////
    iVector2(T X, T Y);

    ////////////////////////////////////////////////////////////
    /// \brief Construct the vector from another type of vector
    ///
    /// This constructor doesn't replace the copy constructor,
    /// it's called only when U != T.
    /// A call to this constructor will fail to compile if U
    /// is not convertible to T.
    ///
    /// \param vector Vector to convert
    ///
    ////////////////////////////////////////////////////////////
    template <typename U>
    explicit iVector2(const iVector2<U>& vector);

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    T x; ///< X coordinate of the vector
    T y; ///< Y coordinate of the vector
};

////////////////////////////////////////////////////////////
/// \relates iVector2
/// \brief Overload of unary operator -
///
/// \param right Vector to negate
///
/// \return Memberwise opposite of the vector
///
////////////////////////////////////////////////////////////
template <typename T>
iVector2<T> operator -(const iVector2<T>& right);

////////////////////////////////////////////////////////////
/// \relates iVector2
/// \brief Overload of binary operator +=
///
/// This operator performs a memberwise addition of both vectors,
/// and assigns the result to \a left.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Reference to \a left
///
////////////////////////////////////////////////////////////
template <typename T>
iVector2<T>& operator +=(iVector2<T>& left, const iVector2<T>& right);

////////////////////////////////////////////////////////////
/// \relates iVector2
/// \brief Overload of binary operator -=
///
/// This operator performs a memberwise subtraction of both vectors,
/// and assigns the result to \a left.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Reference to \a left
///
////////////////////////////////////////////////////////////
template <typename T>
iVector2<T>& operator -=(iVector2<T>& left, const iVector2<T>& right);

////////////////////////////////////////////////////////////
/// \relates iVector2
/// \brief Overload of binary operator +
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Memberwise addition of both vectors
///
////////////////////////////////////////////////////////////
template <typename T>
iVector2<T> operator +(const iVector2<T>& left, const iVector2<T>& right);

////////////////////////////////////////////////////////////
/// \relates iVector2
/// \brief Overload of binary operator -
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Memberwise subtraction of both vectors
///
////////////////////////////////////////////////////////////
template <typename T>
iVector2<T> operator -(const iVector2<T>& left, const iVector2<T>& right);

////////////////////////////////////////////////////////////
/// \relates iVector2
/// \brief Overload of binary operator *
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a scalar value)
///
/// \return Memberwise multiplication by \a right
///
////////////////////////////////////////////////////////////
template <typename T>
iVector2<T> operator *(const iVector2<T>& left, T right);

////////////////////////////////////////////////////////////
/// \relates iVector2
/// \brief Overload of binary operator *
///
/// \param left  Left operand (a scalar value)
/// \param right Right operand (a vector)
///
/// \return Memberwise multiplication by \a left
///
////////////////////////////////////////////////////////////
template <typename T>
iVector2<T> operator *(T left, const iVector2<T>& right);

////////////////////////////////////////////////////////////
/// \relates iVector2
/// \brief Overload of binary operator *=
///
/// This operator performs a memberwise multiplication by \a right,
/// and assigns the result to \a left.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a scalar value)
///
/// \return Reference to \a left
///
////////////////////////////////////////////////////////////
template <typename T>
iVector2<T>& operator *=(iVector2<T>& left, T right);

////////////////////////////////////////////////////////////
/// \relates iVector2
/// \brief Overload of binary operator /
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a scalar value)
///
/// \return Memberwise division by \a right
///
////////////////////////////////////////////////////////////
template <typename T>
iVector2<T> operator /(const iVector2<T>& left, T right);

////////////////////////////////////////////////////////////
/// \relates iVector2
/// \brief Overload of binary operator /=
///
/// This operator performs a memberwise division by \a right,
/// and assigns the result to \a left.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a scalar value)
///
/// \return Reference to \a left
///
////////////////////////////////////////////////////////////
template <typename T>
iVector2<T>& operator /=(iVector2<T>& left, T right);

////////////////////////////////////////////////////////////
/// \relates iVector2
/// \brief Overload of binary operator ==
///
/// This operator compares strict equality between two vectors.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return True if \a left is equal to \a right
///
////////////////////////////////////////////////////////////
template <typename T>
bool operator ==(const iVector2<T>& left, const iVector2<T>& right);

////////////////////////////////////////////////////////////
/// \relates iVector2
/// \brief Overload of binary operator !=
///
/// This operator compares strict difference between two vectors.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return True if \a left is not equal to \a right
///
////////////////////////////////////////////////////////////
template <typename T>
bool operator !=(const iVector2<T>& left, const iVector2<T>& right);

#include "Vector2.inl"

// Define the most common types
typedef iVector2<int>          iVector2i;
typedef iVector2<unsigned int> iVector2u;
typedef iVector2<float>        iVector2f;

} // namespace sf


#endif // SFML_VECTOR2_HPP


////////////////////////////////////////////////////////////
/// \class sf::iVector2
/// \ingroup system
///
/// sf::iVector2 is a simple class that defines a mathematical
/// vector with two coordinates (x and y). It can be used to
/// represent anything that has two dimensions: a size, a point,
/// a velocity, etc.
///
/// The template parameter T is the type of the coordinates. It
/// can be any type that supports arithmetic operations (+, -, /, *)
/// and comparisons (==, !=), for example int or float.
///
/// You generally don't have to care about the templated form (sf::iVector2<T>),
/// the most common specializations have special typedefs:
/// \li sf::iVector2<float> is sf::iVector2f
/// \li sf::iVector2<int> is sf::iVector2i
/// \li sf::iVector2<unsigned int> is sf::iVector2u
///
/// The sf::iVector2 class has a small and simple interface, its x and y members
/// can be accessed directly (there are no accessors like setX(), getX()) and it
/// contains no mathematical function like dot product, cross product, length, etc.
///
/// Usage example:
/// \code
/// sf::iVector2f v1(16.5f, 24.f);
/// v1.x = 18.2f;
/// float y = v1.y;
///
/// sf::iVector2f v2 = v1 * 5.f;
/// sf::iVector2f v3;
/// v3 = v1 + v2;
///
/// bool different = (v2 != v3);
/// \endcode
///
/// Note: for 3-dimensional vectors, see sf::Vector3.
///
////////////////////////////////////////////////////////////
