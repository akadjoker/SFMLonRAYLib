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
#include "VertexArray.hpp"
#include <raylib.h>
#include <rlgl.h>

namespace sf
{
////////////////////////////////////////////////////////////
VertexArray::VertexArray() :
m_vertices     (),
m_primitiveType(Points)
{
}


////////////////////////////////////////////////////////////
VertexArray::VertexArray(PrimitiveType type, std::size_t vertexCount) :
m_vertices     (vertexCount),
m_primitiveType(type)
{
}


////////////////////////////////////////////////////////////
std::size_t VertexArray::getVertexCount() const
{
    return m_vertices.size();
}


////////////////////////////////////////////////////////////
Vertex& VertexArray::operator [](std::size_t index)
{
    return m_vertices[index];
}


////////////////////////////////////////////////////////////
const Vertex& VertexArray::operator [](std::size_t index) const
{
    return m_vertices[index];
}


////////////////////////////////////////////////////////////
void VertexArray::clear()
{
    m_vertices.clear();
}


////////////////////////////////////////////////////////////
void VertexArray::resize(std::size_t vertexCount)
{
    m_vertices.resize(vertexCount);
}


////////////////////////////////////////////////////////////
void VertexArray::append(const Vertex& vertex)
{
    m_vertices.push_back(vertex);
}


////////////////////////////////////////////////////////////
void VertexArray::setPrimitiveType(PrimitiveType type)
{
    m_primitiveType = type;
}


////////////////////////////////////////////////////////////
PrimitiveType VertexArray::getPrimitiveType() const
{
    return m_primitiveType;
}


////////////////////////////////////////////////////////////
FloatRect VertexArray::getBounds() const
{
    if (!m_vertices.empty())
    {
        float left   = m_vertices[0].position.x;
        float top    = m_vertices[0].position.y;
        float right  = m_vertices[0].position.x;
        float bottom = m_vertices[0].position.y;

        for (std::size_t i = 1; i < m_vertices.size(); ++i)
        {
            iVector2f position = m_vertices[i].position;

            // Update left and right
            if (position.x < left)
                left = position.x;
            else if (position.x > right)
                right = position.x;

            // Update top and bottom
            if (position.y < top)
                top = position.y;
            else if (position.y > bottom)
                bottom = position.y;
        }

        return FloatRect(left, top, right - left, bottom - top);
    }
    else
    {
        // Array is empty
        return FloatRect();
    }
}


////////////////////////////////////////////////////////////
void VertexArray::draw() const
{
    if (m_vertices.empty())
        return;

     int pointCount = (int) m_vertices.size();


    rlPushMatrix();
           if (getPrimitiveType()== PrimitiveType::Points)
            {
                rlBegin(RL_LINES);
                for (int i = 0; i < pointCount ; i++)
                {



                     iColor c =m_vertices[i ].color;
                     Vector2 v0=(Vector2){m_vertices[i].position.x,m_vertices[i].position.y};
                     Vector2 vt0=(Vector2){m_vertices[i].texCoords.x,m_vertices[i].texCoords.y};

                    rlColor4ub(c.r,c.g,c.b,c.a);
                    rlTexCoord2f(vt0.x,vt0.y);
                    rlVertex2f(v0.x, v0.y);
                    rlColor4ub(c.r,c.g,c.b,c.a);
                    rlTexCoord2f(vt0.x,vt0.y);
                    rlVertex2f(v0.x+1, v0.y+1);


                //    DrawPixel(m_vertices[i].position.x,m_vertices[i].position.y,(Color){c.r,c.g,c.b,c.a});

                }
            rlEnd();

            } else
            if (getPrimitiveType()== PrimitiveType::Quads)
            {



              int pointCount = (int) m_vertices.size();

        rlCheckRenderBatchLimit((pointCount - 2)*4);



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

    /*

    if (getVertexCount() >= 1)
    {
     int pointCount = (int) m_vertices.size();

        rlCheckRenderBatchLimit (pointCount*3);


            rlBegin(RL_TRIANGLES);




            for (int i = 0; i < pointCount/3 ; i++)
            {


                 iColor c2 =m_vertices[i * 3 + 0].color;
                 iColor c1 =m_vertices[i * 3 + 1].color;
                 iColor c0 =m_vertices[i * 3 + 2].color;



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

            }
        rlEnd();

    }

*/




   rlPopMatrix();

    //    target.draw(&m_vertices[0], m_vertices.size(), m_primitiveType, states);
}

} // namespace sf
