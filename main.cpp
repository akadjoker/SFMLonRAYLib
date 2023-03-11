#include "Config.hpp"
#include "NonCopyable.hpp"
#include "String.hpp"
#include "Utf.hpp"

#include "Color.hpp"
#include "Rect.hpp"


#include "Time.hpp"
#include "Clock.hpp"

#include "Vector2.hpp"
#include "Vector3.hpp"

#include "Transform.hpp"
#include "Transformable.hpp"

#include "Drawable.hpp"
#include "Rect.hpp"
#include "CircleShape.hpp"
#include "ConvexShape.hpp"
#include "RectangleShape.hpp"
#include "Sprite.hpp"

#include "Vertex.hpp"
#include "VertexArray.hpp"


#include <raylib.h>
#include <rlgl.h>




#include <iostream>
#include <math.h>

using namespace std;

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const std::string& tileset, sf::iVector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
    {
        // load the tileset texture
        m_tileset = LoadTexture(tileset.c_str());


        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                // get the current tile number
                int tileNumber = tiles[i + j * width];

                // find its position in the tileset texture
                int tu = tileNumber % (m_tileset.width / tileSize.x);
                int tv = tileNumber / (m_tileset.height / tileSize.x);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // define its 4 corners
                quad[0].position = sf::iVector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::iVector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::iVector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::iVector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::iVector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::iVector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::iVector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::iVector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }

        return true;
    }
    virtual void draw() const
    {
    m_vertices.draw();
    }

private:



    sf::VertexArray m_vertices;
   Texture2D m_tileset;
};


class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:

    ParticleSystem(unsigned int count) :
    m_particles(count),
    m_vertices(sf::Points, count),
    m_lifetime(sf::seconds(3.f)),
    m_emitter(0.f, 0.f)
    {
    }

    void setEmitter(sf::iVector2f position)
    {
        m_emitter = position;
    }

    void update(sf::Time elapsed)
    {
        for (std::size_t i = 0; i < m_particles.size(); ++i)
        {
            // update the particle lifetime
            Particle& p = m_particles[i];
            p.lifetime -= elapsed;

            // if the particle is dead, respawn it
            if (p.lifetime <= sf::Time::Zero)
                resetParticle(i);

            // update the position of the corresponding vertex
            m_vertices[i].position += p.velocity * elapsed.asSeconds();

            // update the alpha (transparency) of the particle according to its lifetime
            float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
            m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
        }
    }

    virtual void draw() const
    {
    m_vertices.draw();
    }


private:

    struct Particle
    {
        sf::iVector2f velocity;
        sf::Time lifetime;
    };



    void resetParticle(std::size_t index)
    {
        // give a random velocity and lifetime to the particle
        float angle = (std::rand() % 360) * 3.14f / 180.f;
        float speed = (std::rand() % 50) + 50.f;
        m_particles[index].velocity = sf::iVector2f(std::cos(angle) * speed, std::sin(angle) * speed);
        m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

        // reset the position of the corresponding vertex
        m_vertices[index].position = m_emitter;
    }

    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Time m_lifetime;
    sf::iVector2f m_emitter;
};

int main()
{
 const int screenWidth = 1050;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib framework");


    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second


  // Define some constants
    const float pi = 3.14159f;
    const int gameWidth = 800;
    const int gameHeight = 600;
    sf::iVector2f paddleSize(25, 100);
    float ballRadius = 10.f;

     sf::Clock AITimer;
    const sf::Time AITime   = sf::seconds(0.1f);
    const float paddleSpeed = 400.f;
    float rightPaddleSpeed  = 0.f;
    const float ballSpeed   = 400.f;
    float ballAngle         = 0.f; // to be changed later

    sf::Clock clock;


     Texture2D tex =LoadTexture("assets/logo.png");


    sf::RectangleShape leftPaddle;
    leftPaddle.setSize(paddleSize - sf::iVector2f(3, 3));
    leftPaddle.setOutlineThickness(3);
    leftPaddle.setOutlineColor(sf::iColor::Black);
    leftPaddle.setFillColor(sf::iColor(100, 100, 200));
    leftPaddle.setOrigin(paddleSize / 2.f);
    leftPaddle.setPosition(300,200);
    leftPaddle.update();

     // Create the ball
    sf::CircleShape ball;
    ball.setRadius(ballRadius - 3);
    ball.setOutlineThickness(3);
    ball.setOutlineColor(sf::iColor::Black);
    ball.setFillColor(sf::iColor::White);
    ball.setOrigin(ballRadius / 2, ballRadius / 2);
    ball.setPosition(200,200);
    leftPaddle.update();

 sf::RectangleShape rectangle;
 rectangle.setSize(sf::iVector2f(100, 50));
 rectangle.setOutlineColor(sf::iColor::Red);
 rectangle.setOutlineThickness(5);
 rectangle.setPosition(10, 20);

  sf::CircleShape circle;
  circle.setRadius(150);
  circle.setOutlineColor(sf::iColor::Red);
  circle.setOutlineThickness(5);
  circle.setPosition(400, 20);
  circle.setTexture(tex); // texture is a sf::Texture
  circle.setTextureRect(sf::IntRect(0, 0, 1, 1));




 // resize it to 5 points
sf::ConvexShape convex;
convex.setPointCount(5);
convex.setPoint(0, sf::iVector2f(0.f, 0.f));
convex.setPoint(1, sf::iVector2f(150.f, 10.f));
convex.setPoint(2, sf::iVector2f(120.f, 90.f));
convex.setPoint(3, sf::iVector2f(30.f, 100.f));
convex.setPoint(4, sf::iVector2f(0.f, 50.f));
convex.setOutlineColor(sf::iColor::Red);
convex.setOutlineThickness(5);
convex.setPosition(200, 300);
convex.setTexture(tex); // texture is a sf::Texture
convex.setTextureRect(sf::IntRect(0, 0, 1, 1));


  sf::Sprite sprite;


  sprite.setTexture(tex);
  sprite.setTextureRect(sf::IntRect(0, 0, 150, 150));
  sprite.setColor(sf::iColor(255, 255, 255, 255));
  sprite.setPosition(400, 305);

  ParticleSystem particles(1000);

    // create a clock to track the elapsed time

 while (!WindowShouldClose())        // Detect window close button or ESC key
    {

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground((Color{100, 200, 100,255}));

             leftPaddle.draw();
              ball.draw();
              rectangle.draw();
              circle.draw();
              sprite.draw();

              convex.draw();

         particles.setEmitter(sf::iVector2f(GetMouseX(),GetMouseY()));

        // update it
        sf::Time elapsed = clock.restart();
        particles.update(elapsed);

        particles.draw();


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    UnloadTexture(tex);
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}
