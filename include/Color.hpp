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

#ifndef SFML_COLOR_HPP
#define SFML_COLOR_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Export.hpp"


namespace sf
{
////////////////////////////////////////////////////////////
/// \brief Utility class for manipulating RGBA colors
///
////////////////////////////////////////////////////////////
class  iColor
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Constructs an opaque black color. It is equivalent to
    /// sf::iColor(0, 0, 0, 255).
    ///
    ////////////////////////////////////////////////////////////
    iColor();

    ////////////////////////////////////////////////////////////
    /// \brief Construct the color from its 4 RGBA components
    ///
    /// \param red   Red component (in the range [0, 255])
    /// \param green Green component (in the range [0, 255])
    /// \param blue  Blue component (in the range [0, 255])
    /// \param alpha Alpha (opacity) component (in the range [0, 255])
    ///
    ////////////////////////////////////////////////////////////
    iColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255);

    ////////////////////////////////////////////////////////////
    /// \brief Construct the color from 32-bit unsigned integer
    ///
    /// \param color Number containing the RGBA components (in that order)
    ///
    ////////////////////////////////////////////////////////////
    explicit iColor(Uint32 color);

    ////////////////////////////////////////////////////////////
    /// \brief Retrieve the color as a 32-bit unsigned integer
    ///
    /// \return iColor represented as a 32-bit unsigned integer
    ///
    ////////////////////////////////////////////////////////////
    Uint32 toInteger() const;

    ////////////////////////////////////////////////////////////
    // Static member data
    ////////////////////////////////////////////////////////////
    static const iColor Black;       ///< Black predefined color
    static const iColor White;       ///< White predefined color
    static const iColor Red;         ///< Red predefined color
    static const iColor Green;       ///< Green predefined color
    static const iColor Blue;        ///< Blue predefined color
    static const iColor Yellow;      ///< Yellow predefined color
    static const iColor Magenta;     ///< Magenta predefined color
    static const iColor Cyan;        ///< Cyan predefined color
    static const iColor Transparent; ///< Transparent (black) predefined color

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    Uint8 r; ///< Red component
    Uint8 g; ///< Green component
    Uint8 b; ///< Blue component
    Uint8 a; ///< Alpha (opacity) component
};

////////////////////////////////////////////////////////////
/// \relates iColor
/// \brief Overload of the == operator
///
/// This operator compares two colors and check if they are equal.
///
/// \param left  Left operand
/// \param right Right operand
///
/// \return True if colors are equal, false if they are different
///
////////////////////////////////////////////////////////////
 bool operator ==(const iColor& left, const iColor& right);

////////////////////////////////////////////////////////////
/// \relates iColor
/// \brief Overload of the != operator
///
/// This operator compares two colors and check if they are different.
///
/// \param left  Left operand
/// \param right Right operand
///
/// \return True if colors are different, false if they are equal
///
////////////////////////////////////////////////////////////
 bool operator !=(const iColor& left, const iColor& right);

////////////////////////////////////////////////////////////
/// \relates iColor
/// \brief Overload of the binary + operator
///
/// This operator returns the component-wise sum of two colors.
/// Components that exceed 255 are clamped to 255.
///
/// \param left  Left operand
/// \param right Right operand
///
/// \return Result of \a left + \a right
///
////////////////////////////////////////////////////////////
 iColor operator +(const iColor& left, const iColor& right);

////////////////////////////////////////////////////////////
/// \relates iColor
/// \brief Overload of the binary - operator
///
/// This operator returns the component-wise subtraction of two colors.
/// Components below 0 are clamped to 0.
///
/// \param left  Left operand
/// \param right Right operand
///
/// \return Result of \a left - \a right
///
////////////////////////////////////////////////////////////
 iColor operator -(const iColor& left, const iColor& right);

////////////////////////////////////////////////////////////
/// \relates iColor
/// \brief Overload of the binary * operator
///
/// This operator returns the component-wise multiplication
/// (also called "modulation") of two colors.
/// Components are then divided by 255 so that the result is
/// still in the range [0, 255].
///
/// \param left  Left operand
/// \param right Right operand
///
/// \return Result of \a left * \a right
///
////////////////////////////////////////////////////////////
 iColor operator *(const iColor& left, const iColor& right);

////////////////////////////////////////////////////////////
/// \relates iColor
/// \brief Overload of the binary += operator
///
/// This operator computes the component-wise sum of two colors,
/// and assigns the result to the left operand.
/// Components that exceed 255 are clamped to 255.
///
/// \param left  Left operand
/// \param right Right operand
///
/// \return Reference to \a left
///
////////////////////////////////////////////////////////////
 iColor& operator +=(iColor& left, const iColor& right);

////////////////////////////////////////////////////////////
/// \relates iColor
/// \brief Overload of the binary -= operator
///
/// This operator computes the component-wise subtraction of two colors,
/// and assigns the result to the left operand.
/// Components below 0 are clamped to 0.
///
/// \param left  Left operand
/// \param right Right operand
///
/// \return Reference to \a left
///
////////////////////////////////////////////////////////////
 iColor& operator -=(iColor& left, const iColor& right);

////////////////////////////////////////////////////////////
/// \relates iColor
/// \brief Overload of the binary *= operator
///
/// This operator returns the component-wise multiplication
/// (also called "modulation") of two colors, and assigns
/// the result to the left operand.
/// Components are then divided by 255 so that the result is
/// still in the range [0, 255].
///
/// \param left  Left operand
/// \param right Right operand
///
/// \return Reference to \a left
///
////////////////////////////////////////////////////////////
 iColor& operator *=(iColor& left, const iColor& right);

} // namespace sf


#endif // SFML_COLOR_HPP


////////////////////////////////////////////////////////////
/// \class sf::iColor
/// \ingroup graphics
///
/// sf::iColor is a simple color class composed of 4 components:
/// \li Red
/// \li Green
/// \li Blue
/// \li Alpha (opacity)
///
/// Each component is a public member, an unsigned integer in
/// the range [0, 255]. Thus, colors can be constructed and
/// manipulated very easily:
///
/// \code
/// sf::iColor color(255, 0, 0); // red
/// color.r = 0;                // make it black
/// color.b = 128;              // make it dark blue
/// \endcode
///
/// The fourth component of colors, named "alpha", represents
/// the opacity of the color. A color with an alpha value of
/// 255 will be fully opaque, while an alpha value of 0 will
/// make a color fully transparent, whatever the value of the
/// other components is.
///
/// The most common colors are already defined as static variables:
/// \code
/// sf::iColor black       = sf::iColor::Black;
/// sf::iColor white       = sf::iColor::White;
/// sf::iColor red         = sf::iColor::Red;
/// sf::iColor green       = sf::iColor::Green;
/// sf::iColor blue        = sf::iColor::Blue;
/// sf::iColor yellow      = sf::iColor::Yellow;
/// sf::iColor magenta     = sf::iColor::Magenta;
/// sf::iColor cyan        = sf::iColor::Cyan;
/// sf::iColor transparent = sf::iColor::Transparent;
/// \endcode
///
/// iColors can also be added and modulated (multiplied) using the
/// overloaded operators + and *.
///
////////////////////////////////////////////////////////////
