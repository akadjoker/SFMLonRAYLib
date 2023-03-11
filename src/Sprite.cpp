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

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <raylib.h>
#include <rlgl.h>
#include "Sprite.hpp"
#include <cstdlib>
#include <cstdio>


namespace sf
{
////////////////////////////////////////////////////////////
Sprite::Sprite() :
m_textureRect()
{
    m_texture = {0};
    m_texture.id=-1;

}


////////////////////////////////////////////////////////////
Sprite::Sprite( Texture2D& texture) :
m_textureRect()
{
    setTexture(texture);
}


////////////////////////////////////////////////////////////
Sprite::Sprite( Texture2D& texture, const IntRect& rectangle) :
m_textureRect()
{
    setTexture(texture);
    setTextureRect(rectangle);
}


////////////////////////////////////////////////////////////
void Sprite::setTexture( Texture2D& texture, bool resetRect)
{
    // Recompute the texture area if requested, or if there was no valid texture & rect before
    if (resetRect)// || (m_textureRect == sf::IntRect()))
        setTextureRect(IntRect(0, 0, texture.width, texture.height));

    // Assign the new texture
    m_texture = texture;
}


////////////////////////////////////////////////////////////
void Sprite::setTextureRect(const IntRect& rectangle)
{
    if (rectangle != m_textureRect)
    {
        m_textureRect = rectangle;
        updatePositions();
        updateTexCoords();
    }
}


////////////////////////////////////////////////////////////
void Sprite::setColor(const iColor& color)
{
    // Update the vertices' color
    m_vertices[0].color = color;
    m_vertices[1].color = color;
    m_vertices[2].color = color;
    m_vertices[3].color = color;
}


////////////////////////////////////////////////////////////
 Texture2D Sprite::getTexture()
{
    return m_texture;
}


////////////////////////////////////////////////////////////
const IntRect& Sprite::getTextureRect() const
{
    return m_textureRect;
}


////////////////////////////////////////////////////////////
const iColor& Sprite::getColor() const
{
    return m_vertices[0].color;
}


////////////////////////////////////////////////////////////
FloatRect Sprite::getLocalBounds() const
{
    float width = static_cast<float>(std::abs(m_textureRect.width));
    float height = static_cast<float>(std::abs(m_textureRect.height));

    return FloatRect(0.f, 0.f, width, height);
}


////////////////////////////////////////////////////////////
FloatRect Sprite::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}


////////////////////////////////////////////////////////////
void Sprite::draw() const
{


        rlPushMatrix();
        rlMultMatrixf((float*)getTransform().getMatrix());






       rlCheckRenderBatchLimit(4);


            if (m_texture.id>0)
               rlSetTexture(m_texture.id);
            else
                rlSetTexture(0);


            rlBegin(RL_QUADS);








                Vector2 v0=(Vector2){m_vertices[0].position.x,m_vertices[0].position.y};
                Vector2 v1=(Vector2){m_vertices[1].position.x,m_vertices[1].position.y};
                Vector2 v2=(Vector2){m_vertices[3].position.x,m_vertices[3].position.y};
                Vector2 v3=(Vector2){m_vertices[2].position.x,m_vertices[2].position.y};

                Vector2 t0=(Vector2){m_vertices[0].texCoords.x,m_vertices[0].texCoords.y};
                Vector2 t1=(Vector2){m_vertices[1].texCoords.x,m_vertices[1].texCoords.y};
                Vector2 t2=(Vector2){m_vertices[3].texCoords.x,m_vertices[3].texCoords.y};
                Vector2 t3=(Vector2){m_vertices[2].texCoords.x,m_vertices[2].texCoords.y};

                 iColor c0 =m_vertices[0].color;
                 iColor c1 =m_vertices[1].color;
                 iColor c2 =m_vertices[3].color;
                 iColor c3 =m_vertices[2].color;


                rlColor4ub(c0.r,c0.g,c0.b,c0.a);
                rlColor4ub(c1.r,c1.g,c1.b,c1.a);
                rlColor4ub(c2.r,c2.g,c2.b,c2.a);
                rlColor4ub(c3.r,c3.g,c3.b,c3.a);


                rlTexCoord2f(t0.x,t0.y);
                rlVertex2f(v0.x, v0.y);


                rlTexCoord2f(t1.x,t1.y);
                rlVertex2f(v1.x, v1.y);


                rlTexCoord2f(t2.x,t2.y);
                rlVertex2f(v2.x, v2.y);

                rlTexCoord2f(t3.x,t3.y);
                rlVertex2f(v3.x, v3.y);

        rlEnd();


   rlPopMatrix();

}


////////////////////////////////////////////////////////////
void Sprite::updatePositions()
{
    FloatRect bounds = getLocalBounds();

    m_vertices[0].position = iVector2f(0, 0);
    m_vertices[1].position = iVector2f(0, bounds.height);
    m_vertices[2].position = iVector2f(bounds.width, 0);
    m_vertices[3].position = iVector2f(bounds.width, bounds.height);
}


////////////////////////////////////////////////////////////
void Sprite::updateTexCoords()
{
    float width  = (float)m_textureRect.width;
    float height = (float)m_textureRect.height;

    float left   = static_cast<float>(m_textureRect.left);
    float right  = m_textureRect.width;
    float top    = static_cast<float>(m_textureRect.top);
    float bottom = m_textureRect.height;


     Rectangle source=(Rectangle){left,top,width,height};

    m_vertices[0].texCoords = iVector2f(source.x/width, source.y/height);

    m_vertices[1].texCoords = iVector2f(source.x/width, (source.y + source.height)/height);

    m_vertices[3].texCoords = iVector2f((source.x + source.width)/width, (source.y + source.height)/height);

    m_vertices[2].texCoords =  iVector2f((source.x + source.width)/width, source.y/height);



/*


    float left   = static_cast<float>(m_textureRect.left);
    float right  = left + m_textureRect.width;
    float top    = static_cast<float>(m_textureRect.top);
    float bottom = top + m_textureRect.height;

    m_vertices[0].texCoords = iVector2f(left, top);
    m_vertices[1].texCoords = iVector2f(left, bottom);
    m_vertices[2].texCoords = iVector2f(right, top);
    m_vertices[3].texCoords = iVector2f(right, bottom);



                Vector2 t0=(Vector2){m_vertices[0].texCoords.x,m_vertices[0].texCoords.y};
                Vector2 t1=(Vector2){m_vertices[1].texCoords.x,m_vertices[1].texCoords.y};
                Vector2 t2=(Vector2){m_vertices[2].texCoords.x,m_vertices[2].texCoords.y};
                Vector2 t3=(Vector2){m_vertices[3].texCoords.x,m_vertices[3].texCoords.y};


                 printf("1 %f %f \n",t0.x,t0.y);
                 printf("2 %f %f \n",t1.x,t1.y);
                 printf("3 %f %f \n",t2.x,t2.y);
                 printf("4 %f %f \n",t3.x,t3.y);
*/
}

} // namespace sf
