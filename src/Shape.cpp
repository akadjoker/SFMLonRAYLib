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
#include "Shape.hpp"
#include <raylib.h>
#include <rlgl.h>
#include <stdlib.h>
#include <cstdio>
#include <cmath>


namespace
{
    // Compute the normal of a segment
    sf::iVector2f computeNormal(const sf::iVector2f& p1, const sf::iVector2f& p2)
    {
        sf::iVector2f normal(p1.y - p2.y, p2.x - p1.x);
        float length = std::sqrt(normal.x * normal.x + normal.y * normal.y);
        if (length != 0.f)
            normal /= length;
        return normal;
    }

    // Compute the dot product of two vectors
    float dotProduct(const sf::iVector2f& p1, const sf::iVector2f& p2)
    {
        return p1.x * p2.x + p1.y * p2.y;
    }
}


namespace sf
{
////////////////////////////////////////////////////////////
Shape::~Shape()
{
}


////////////////////////////////////////////////////////////
void Shape::setTexture( Texture2D texture, bool resetRect)
{
    if (texture.id>0)
    {
        // Recompute the texture area if requested, or if there was no texture & rect before
         if (resetRect) //||  (m_textureRect == IntRect()))
            setTextureRect(IntRect(0, 0, texture.width, texture.height));
    }

    // Assign the new texture
   m_texture = texture;
   m_useTexture=true;
}


////////////////////////////////////////////////////////////
 Texture2D Shape::getTexture()
{
    return m_texture;
}


////////////////////////////////////////////////////////////
void Shape::setTextureRect(const IntRect& rect)
{
    m_textureRect = rect;
    updateTexCoords();
    m_useTexture=true;
}


////////////////////////////////////////////////////////////
const IntRect& Shape::getTextureRect() const
{
    return m_textureRect;
}


////////////////////////////////////////////////////////////
void Shape::setFillColor(const iColor& color)
{
    m_fillColor = color;
    updateFillColors();
}


////////////////////////////////////////////////////////////
const iColor& Shape::getFillColor() const
{
    return m_fillColor;
}


////////////////////////////////////////////////////////////
void Shape::setOutlineColor(const iColor& color)
{
    m_outlineColor = color;
    updateOutlineColors();
}


////////////////////////////////////////////////////////////
const iColor& Shape::getOutlineColor() const
{
    return m_outlineColor;
}


////////////////////////////////////////////////////////////
void Shape::setOutlineThickness(float thickness)
{
    m_outlineThickness = thickness;
    update(); // recompute everything because the whole shape must be offset
}


////////////////////////////////////////////////////////////
float Shape::getOutlineThickness() const
{
    return m_outlineThickness;
}


////////////////////////////////////////////////////////////
FloatRect Shape::getLocalBounds() const
{
    return m_bounds;
}


////////////////////////////////////////////////////////////
FloatRect Shape::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}


////////////////////////////////////////////////////////////
Shape::Shape() :
m_textureRect     (),
m_fillColor       (255, 255, 255),
m_outlineColor    (255, 255, 255),
m_outlineThickness(0),
m_vertices        (TriangleFan),
m_outlineVertices (TriangleStrip),
m_insideBounds    (),
m_bounds          ()
{
m_texture = {0};
m_texture.id=-1;
m_useTexture=false;
}


////////////////////////////////////////////////////////////
void Shape::update()
{
    // Get the total number of points of the shape
    std::size_t count = getPointCount();
    if (count < 3)
    {
        m_vertices.resize(0);
        m_outlineVertices.resize(0);
        return;
    }

    m_vertices.resize(count + 2); // + 2 for center and repeated first point

    // Position
    for (std::size_t i = 0; i < count; ++i)
        m_vertices[i + 1].position = getPoint(i);
    m_vertices[count + 1].position = m_vertices[1].position;

    // Update the bounding rectangle
    m_vertices[0] = m_vertices[1]; // so that the result of getBounds() is correct
    m_insideBounds = m_vertices.getBounds();

    // Compute the center and make it the first vertex
    m_vertices[0].position.x = m_insideBounds.left + m_insideBounds.width / 2;
    m_vertices[0].position.y = m_insideBounds.top + m_insideBounds.height / 2;

    // Color
    updateFillColors();

    // Texture coordinates
    updateTexCoords();

    // Outline
    updateOutline();
}


////////////////////////////////////////////////////////////


void Shape::draw() const
{

      static const char* modes[] = {"POINTS", "LINES", "LINE_STRIP", "TRIANGLES",
                                   "TRIANGLE_STRIP", "TRIANGLE_FAN", "QUADS"};

        rlPushMatrix();
        rlMultMatrixf((float*)getTransform().getMatrix());


    if (m_vertices.getVertexCount() >= 1)
    {
     int pointCount = (int) m_vertices.getVertexCount();

        rlCheckRenderBatchLimit((pointCount - 2)*4);

       if (m_useTexture)
            rlSetTexture(m_texture.id);

            rlBegin(RL_QUADS);




            for (int i = 1; i < pointCount - 1; i++)
            {


                 iColor c2 =m_vertices[0].color;
                 iColor c1 =m_vertices[i].color;
                 iColor c0 =m_vertices[i+1].color;



                Vector2 v2=(Vector2){m_vertices[0].position.x,m_vertices[0].position.y};
                Vector2 v1=(Vector2){m_vertices[i].position.x,m_vertices[i].position.y};
                Vector2 v0=(Vector2){m_vertices[i+1].position.x,m_vertices[i+1].position.y};

                Vector2 vt2=(Vector2){m_vertices[0].texCoords.x,m_vertices[0].texCoords.y};
                Vector2 vt1=(Vector2){m_vertices[i].texCoords.x,m_vertices[i].texCoords.y};
                Vector2 vt0=(Vector2){m_vertices[i+1].texCoords.x,m_vertices[i+1].texCoords.y};

                rlColor4ub(c0.r,c0.g,c0.b,c0.a);
                rlTexCoord2f(vt0.x,vt0.y);
                rlVertex2f(v0.x, v0.y);

                rlColor4ub(c1.r,c1.g,c1.b,c1.a);
                rlTexCoord2f(vt1.x,vt1.y);
                rlVertex2f(v1.x, v1.y);

                rlColor4ub(c2.r,c2.g,c2.b,c2.a);
                rlTexCoord2f(vt2.x,vt2.y);
                rlVertex2f(v2.x, v2.y);

                rlColor4ub(c2.r,c2.g,c2.b,c2.a);
                rlTexCoord2f(vt2.x,vt2.y);
                rlVertex2f(v2.x, v2.y);
            }
        rlEnd();

    }




  if (m_outlineThickness != 0)
    {


    rlSetTexture(0);

    if (m_outlineVertices.getVertexCount() >= 1)
    {
          int pointCount = (int) m_outlineVertices.getVertexCount();
         rlCheckRenderBatchLimit(3*(pointCount - 2));



          rlBegin(RL_TRIANGLES);
            for (int i = 2; i < pointCount; i++)
            {
                if ((i%2) == 0)
                {
                    iColor c2 =m_outlineVertices[i-1].color;
                    iColor c1 =m_outlineVertices[i-2].color;
                    iColor c0 =m_outlineVertices[i].color;

                    rlColor4ub(c0.r,c0.g,c0.b,c0.a);
                    rlColor4ub(c1.r,c1.g,c1.b,c1.a);
                    rlColor4ub(c2.r,c2.g,c2.b,c2.a);

                    rlVertex2f(m_outlineVertices[i - 1].position.x, m_outlineVertices[i - 1].position.y);
                    rlVertex2f(m_outlineVertices[i - 2].position.x, m_outlineVertices[i - 2].position.y);
                    rlVertex2f(m_outlineVertices[i].position.x, m_outlineVertices[i].position.y);
                }
                else
                {

                    iColor c2 =m_outlineVertices[i-2].color;
                    iColor c1 =m_outlineVertices[i-1].color;
                    iColor c0 =m_outlineVertices[i].color;

                    rlColor4ub(c0.r,c0.g,c0.b,c0.a);
                    rlColor4ub(c1.r,c1.g,c1.b,c1.a);
                    rlColor4ub(c2.r,c2.g,c2.b,c2.a);

                    rlVertex2f(m_outlineVertices[i - 2].position.x, m_outlineVertices[i - 2].position.y);
                    rlVertex2f(m_outlineVertices[i - 1].position.x, m_outlineVertices[i - 1].position.y);
                    rlVertex2f(m_outlineVertices[i].position.x, m_outlineVertices[i].position.y);
                }
            }

         rlEnd();

     }
    }

   rlPopMatrix();
}


////////////////////////////////////////////////////////////
void Shape::updateFillColors()
{
    for (std::size_t i = 0; i < m_vertices.getVertexCount(); ++i)
        m_vertices[i].color = m_fillColor;
}


////////////////////////////////////////////////////////////
void Shape::updateTexCoords()
{
     float width  = (float)m_textureRect.width;
     float height = (float)m_textureRect.height;


    for (std::size_t i = 0; i < m_vertices.getVertexCount(); ++i)
    {
        float xratio = m_insideBounds.width  > 0 ? (m_vertices[i].position.x - m_insideBounds.left) / m_insideBounds.width : 0;
        float yratio = m_insideBounds.height > 0 ? (m_vertices[i].position.y - m_insideBounds.top) / m_insideBounds.height : 0;
        m_vertices[i].texCoords.x = (m_textureRect.left + m_textureRect.width) * xratio;
        m_vertices[i].texCoords.y = (m_textureRect.top + m_textureRect.height) * yratio;
    }
}


////////////////////////////////////////////////////////////
void Shape::updateOutline()
{
     // Return if there is no outline
    if (m_outlineThickness == 0.f)
    {
        m_outlineVertices.clear();
        m_bounds = m_insideBounds;
        return;
    }

    std::size_t count = m_vertices.getVertexCount() - 2;
    m_outlineVertices.resize((count + 1) * 2);

    for (std::size_t i = 0; i < count; ++i)
    {
        std::size_t index = i + 1;

        // Get the two segments shared by the current point
        iVector2f p0 = (i == 0) ? m_vertices[count].position : m_vertices[index - 1].position;
        iVector2f p1 = m_vertices[index].position;
        iVector2f p2 = m_vertices[index + 1].position;

        // Compute their normal
        iVector2f n1 = computeNormal(p0, p1);
        iVector2f n2 = computeNormal(p1, p2);

        // Make sure that the normals point towards the outside of the shape
        // (this depends on the order in which the points were defined)
        if (dotProduct(n1, m_vertices[0].position - p1) > 0)
            n1 = -n1;
        if (dotProduct(n2, m_vertices[0].position - p1) > 0)
            n2 = -n2;

        // Combine them to get the extrusion direction
        float factor = 1.f + (n1.x * n2.x + n1.y * n2.y);
        iVector2f normal = (n1 + n2) / factor;

        // Update the outline points
        m_outlineVertices[i * 2 + 0].position = p1;
        m_outlineVertices[i * 2 + 1].position = p1 + normal * m_outlineThickness;
    }

    // Duplicate the first point at the end, to close the outline
    m_outlineVertices[count * 2 + 0].position = m_outlineVertices[0].position;
    m_outlineVertices[count * 2 + 1].position = m_outlineVertices[1].position;

    // Update outline colors
    updateOutlineColors();

    // Update the shape's bounds
    m_bounds = m_outlineVertices.getBounds();
}


////////////////////////////////////////////////////////////
void Shape::updateOutlineColors()
{
    for (std::size_t i = 0; i < m_outlineVertices.getVertexCount(); ++i)
        m_outlineVertices[i].color = m_outlineColor;
}

} // namespace sf
