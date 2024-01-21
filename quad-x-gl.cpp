#include "quadtree.h"
#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>

const int WIDTH = 1024;
const int HEIGHT = 1024;
const int BOX_SIZE = 3;
const int HALF_BOX_SIZE = BOX_SIZE / 2;
bool displayQuadtreeFlag = false;
Quad quadtree(Point(0, 0), Point(WIDTH, HEIGHT));

void display()
{
    glFlush();
}

// Draws a box of 9*9 around point p
void drawBox(Point p, Color c = Color(0.0f, 0.f, 0.0f))
{
    std::cout << "Drawing box over " << p.x << " " << p.y << std::endl;
    glColor3f(c.r, c.g, c.b);
    glRecti(p.x - HALF_BOX_SIZE, p.y - HALF_BOX_SIZE, p.x + HALF_BOX_SIZE, p.y + HALF_BOX_SIZE);
    glFlush();
}

void insert2qt(Point p)
{
    // std::cout << "insertqt" << p.x << p.y << std::endl;
    auto node = std::make_shared<Node>(p, 1);
    quadtree.insert(node);
}

// Random color generation for opengl
Color randomColor()
{
    Color c;
    c.r = rand() / (float)RAND_MAX;
    c.g = rand() / (float)RAND_MAX;
    c.b = rand() / (float)RAND_MAX;
    return c;
}

void displayQuadtree(const Quad& qt)
{

    if (qt.n == nullptr)
    {
        auto c = randomColor();
        glColor3f(c.r, c.g, c.b);
        glRecti(qt.topLeft.x, qt.topLeft.y, qt.botRight.x, qt.botRight.y);
    }
    else
    {
        glColor3f(0.0f, 0.0f, 0.0f);
        glRecti(qt.topLeft.x, qt.topLeft.y, qt.botRight.x, qt.botRight.y);
    }

    if (qt.botLeftTree != nullptr)
        displayQuadtree(*(qt.botLeftTree));
    if (qt.botRightTree != nullptr)
        displayQuadtree(*(qt.botRightTree));
    if (qt.topLeftTree != nullptr)
        displayQuadtree(*(qt.topLeftTree));
    if (qt.topRightTree != nullptr)
        displayQuadtree(*(qt.topRightTree));
}

void print(std::string msg)
{
    std::cout << msg << std::endl;
}

void click_handler(int x, int y)
{
    drawBox(Point(x, y));
}

Point display2glPoint(int x, int y)
{
    return Point(x, HEIGHT - y);
}

void draw_and_update(int x, int y)
{
    Point p = display2glPoint(x, y);
    drawBox(p);

    for (int i = -HALF_BOX_SIZE; i <= HALF_BOX_SIZE; i++)
        for (int j = -HALF_BOX_SIZE; j <= HALF_BOX_SIZE; j++)
            insert2qt(p + Point(i, j));
}

void mouse_callback(int button, int state, int x, int y)
{

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (displayQuadtreeFlag == true)
        {
            print("Displaying the quadtree");
            displayQuadtree(quadtree);
        }
        else
        {
            draw_and_update(x, y);
        }
    }
    glFlush();
}

void mouse_drag_callback(int x, int y)
{
    if (displayQuadtreeFlag == true)
        return;

    draw_and_update(x, y);
}

void keyboard_callback(unsigned char key, int x, int y)
{
    if (key == 'q')
        exit(0);

    // if key is tab then
    if (key == '\t')
    {
        displayQuadtreeFlag = !displayQuadtreeFlag;
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
        glFlush();
        std::cout << "Display Quadtree: " << displayQuadtreeFlag << std::endl;
    }
}

int main(int argc, char** argv)
{
    srand(static_cast<unsigned>(time(0)));
    int window_id;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(50, 50);
    window_id = glutCreateWindow("Quadtree");
    glutDisplayFunc(display);
    glutMouseFunc(mouse_callback);
    glutKeyboardFunc(keyboard_callback);
    glutMotionFunc(mouse_drag_callback);

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glutMainLoop();

    return 0;
}
