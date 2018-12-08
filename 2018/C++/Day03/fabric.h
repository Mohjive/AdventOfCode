#include <iostream>
#include <unordered_map>

using namespace std;

namespace fabric {

    struct Coordinate {
        Coordinate() {}
        Coordinate(int _x, int _y) {
            x = _x;
            y = _y;
        }
        int x;
        int y;
    };

    struct Area {
        int width;
        int height;
    };

    struct Claim {
        int id;
        Coordinate coord;
        Area size;
    };

    struct Data {
        Data(int _id, int _count) {
            id = _id;
            count = _count;
        }
        int id;
        int count;
    };

    typedef unordered_map<fabric::Coordinate, fabric::Data> Fabric;
    typedef vector<fabric::Claim> Claims;
    
    std::ostream& operator << (ostream& os, const Coordinate& c) {
        return os << "x: " << c.x << " y: " << c.y;
    }

    std::ostream& operator << (ostream& os, const Area& a) {
        return os << "height: " << a.height << " width: " << a.width;
    }

    std::ostream& operator << (ostream& os, const Claim& c) {
        return os << "id: " << c.id << " coord: { " << c.coord << " } size: { " << c.size << " }";
    }

    bool operator == (const Coordinate& c1, const Coordinate& c2) {
        return (c1.x == c2.x && c1.y == c2.y);
    }
}

namespace std {
        template<> struct hash<fabric::Coordinate>
    {
        typedef fabric::Coordinate argument_type;
        typedef std::size_t result_type;
        result_type operator()(argument_type const& c) const noexcept
        {
            result_type const h1 ( std::hash<int>{}(c.x) );
            result_type const h2 ( std::hash<int>{}(c.y) );
            return h1 ^ (h2 << 1);
        }
    };
}