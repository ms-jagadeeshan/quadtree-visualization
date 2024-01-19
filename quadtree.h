#include <memory>

struct Color
{
    float r;
    float g;
    float b;

    Color(float _r, float _g, float _b)
        : r(_r), g(_g), b(_b)
    {
    }

    Color()
        : r(0), g(0), b(0)
    {
    }
};

struct Point
{
    int x;
    int y;

    Point(int _x, int _y)
        : x(_x), y(_y)
    {
    }
    Point()
        : x(0), y(0)
    {
    }

    Point& operator=(const Point& a)
    {
        x = a.x;
        y = a.y;
        return *this;
    }

    Point operator+(const Point& a) const
    {
        return Point(a.x + x, a.y + y);
    }

    Point operator-(const Point& a) const
    {
        return Point(x - a.x, y - a.y);
    }

    bool operator==(const Point& a) const
    {
        return (x == a.x && y == a.y);
    }
};

struct Node
{
    Point pos;
    int data;
    Node(Point _pos, int _data)
        : pos(_pos), data(_data)
    {
    }
    Node()
        : data(0)
    {
    }
};

// The main quadtree class
class Quad
{
public:
    Quad()
    {
        topLeft = Point(0, 0);
        botRight = Point(0, 0);
        n = nullptr;
        topLeftTree = nullptr;
        topRightTree = nullptr;
        botLeftTree = nullptr;
        botRightTree = nullptr;
    }
    Quad(Point topL, Point botR)
    {
        n = nullptr;
        topLeftTree = nullptr;
        topRightTree = nullptr;
        botLeftTree = nullptr;
        botRightTree = nullptr;
        topLeft = topL;
        botRight = botR;
    }
    void insert(std::shared_ptr<Node>);
    std::shared_ptr<Node> search(Point);
    friend void displayQuadtree(const Quad& qt);

private:
    bool inBoundary(Point);
    // Hold details of the boundary of this node
    Point topLeft;
    Point botRight;

    // Contains details of node
    std::shared_ptr<Node> n;

    // Children of this tree
    std::shared_ptr<Quad> topLeftTree, topRightTree, botLeftTree, botRightTree;
};
