#include "Mipe3DLog.h"
#include <iomanip>

std::ostream& operator << (std::ostream& out, const glm::ivec2& ivec2)
{
    out << "(" << ivec2.x << ", " << ivec2.y << ")";
    return out;
}

std::ostream& operator << (std::ostream& out, const glm::vec3& vec)
{
    out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return out;
}

std::ostream& operator << (std::ostream& out, const glm::mat4x4& mat4x4)
{
    using namespace std;

    // store current format
    ios state(nullptr);
    state.copyfmt(out);
    
    const glm::mat4x4& m = mat4x4;

    // set new format
    out << scientific;

    // print the matrix into the stream
    out << " ["  << m[0][0]
        << " "  << m[1][0]
        << " "  << m[2][0]
        << " "  << m[3][0]
        << "\n"
        << "  "  << m[0][1]
        << " "  << m[1][1]
        << " "  << m[2][1]
        << " "  << m[3][1]
        << "\n"
        << "  "  << m[0][2]
        << " "  << m[1][2]
        << " "  << m[2][2]
        << " "  << m[3][2]
        << "\n"
        << "  "  << m[0][3]
        << " "  << m[1][3]
        << " "  << m[2][3]
        << " "  << m[3][3] 
        << "]";
    
    // restore the original format
    out.copyfmt(state);

    return out;
}