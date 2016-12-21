
#include <OpCode.h>
#include <string>
#include <vector>


namespace OpenFlight
{
    class HeaderRecord;
    
    std::string toDotFormat(const HeaderRecord*);
    std::string toDotFormat(const HeaderRecord*, const std::vector<opCode>& iExclusions);
}