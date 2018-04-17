
#include <OpCode.h>
#include <string>
#include <set>


namespace OpenFlight
{
    class HeaderRecord;
    
    std::string toDotFormat(const HeaderRecord*);
    std::string toDotFormat(const HeaderRecord*, const std::set<opCode>& iInclusions);
}