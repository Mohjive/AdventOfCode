#include <iostream>
#include <unordered_map>

using namespace std;

namespace fabric
{

    struct Coordinate
    {
        Coordinate() {}
        Coordinate(int _x, int _y): x(_x), y(_y) {};
        int x;
        int y;
    };

    struct Area
    {
        int width;
        int height;
    };

    struct Claim
    {
        int id;
        Coordinate coord;
        Area size;
    };

    struct Data
    {
        Data(int _id, int _count): id(_id), count(_count){};
        int id;
        int count;
    };

    typedef unordered_map<fabric::Coordinate, fabric::Data> Fabric;
    typedef vector<fabric::Claim> Claims;

    std::ostream& operator << (ostream& os, Coordinate const &c)
    {
        return os << "x: " << c.x << " y: " << c.y;
    }

    std::ostream& operator << (ostream& os, Area const &a)
    {
        return os << "height: " << a.height << " width: " << a.width;
    }

    std::ostream& operator << (ostream &os, Claim const &c)
    {
        return os << "id: " << c.id << " coord: { " << c.coord << " } size: { " << c.size << " }";
    }

    bool operator == ( Coordinate const &c1, Coordinate const &c2)
    {
        return (c1.x == c2.x && c1.y == c2.y);
    }
}

namespace std
{
    template<> struct hash<fabric::Coordinate>
    {
        std::size_t operator()(fabric::Coordinate const &c) const noexcept
        {
            std::size_t const h1 ( std::hash<int>{}(c.x) );
            std::size_t const h2 ( std::hash<int>{}(c.y) );
            return h1 ^ (h2 << 1);
        }
    };
}