

#ifndef SFML_CONFIG_HPP
#define SFML_CONFIG_HPP
#include  <raylib.h>


    // Static build doesn't need import/export macros
    #define SFML_API_EXPORT
    #define SFML_API_IMPORT

////////////////////////////////////////////////////////////
// Define portable fixed-size types
////////////////////////////////////////////////////////////
namespace sf
{
    // All "common" platforms use the same size for char, short and int
    // (basically there are 3 types for 3 sizes, so no other match is possible),
    // we can use them without doing any kind of check

    // 8 bits integer types
    typedef signed   char Int8;
    typedef unsigned char Uint8;

    // 16 bits integer types
    typedef signed   short Int16;
    typedef unsigned short Uint16;

    // 32 bits integer types
    typedef signed   int Int32;
    typedef unsigned int Uint32;

    // 64 bits integer types

        typedef signed   long long Int64;
        typedef unsigned long long Uint64;


} // namespace sf


#endif // SFML_CONFIG_HPP
