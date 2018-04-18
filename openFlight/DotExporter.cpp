
#include <queue>
#include "Records.h"
#include <sstream>
#include "DotExporter.h"

using namespace OpenFlight;
using namespace std;


std::string bakeName(const Record* ipNode)
{
    char m[200];
    
    sprintf(m, "\"%s 0x%08llx\"",
		OpCodeUtils::toString(ipNode->getOpCode()).c_str(), (uint64_t)ipNode);
    
    return m;
}

std::string bakeName(const PrimaryRecord* ipNode)
{
    char m[400];
    
    if(ipNode->hasLongIdRecord())
    {
        sprintf(m, "\"%s\"",
                ipNode->getLongIdRecord()->getAsciiId().c_str() );
//        sprintf(m, "\"%s (%s)\"",
//                ipNode->getLongIdRecord()->getAsciiId().c_str(),
//                toString(ipNode->getOpCode()).c_str() );
    }
    else
    {
        sprintf(m, "\"%s 0x%08llx\"",
			OpCodeUtils::toString(ipNode->getOpCode()).c_str(), (uint64_t)ipNode);
    }
    
    return m;
}

bool isIncluded(opCode code, const set<opCode> iInclusion)
{
    return iInclusion.find(code) != iInclusion.end();
}

//-----------------------------------------------------------------------------
// see method toDotFormat(const HeaderRecord* ipRoot, const std::vector<opCode>& iExclusions)
std::string OpenFlight::toDotFormat(const HeaderRecord* ipRoot)
{ return toDotFormat(ipRoot, set<opCode>()); }
                                    
//-----------------------------------------------------------------------------
// This method will return DOT representation of the current document.
//
// Refer to https://fr.wikipedia.org/wiki/DOT_(langage) for explanation
// on DOT language.
//
// Use graphviz or online tool to visualize the graph.
//      http://dreampuf.github.io/GraphvizOnline/
//      http://www.webgraphviz.com/
//
std::string OpenFlight::toDotFormat(const HeaderRecord* ipRoot, const std::set<opCode>& iInclusions)
{
    ostringstream oss;
    
    oss << "graph OpenFlighReader {\n" <<
        "node [ fillcolor=white, style=filled ];\n";
    
    const PrimaryRecord* n = nullptr;
    std::deque<const PrimaryRecord*> q;
    q.push_back(ipRoot);
    while (!q.empty())
    {
        n = q.front();
        q.pop_front();
        
        for(int i = 0; i < n->getNumberOfChilds(); ++i)
        {
            PrimaryRecord* c = n->getChild(i);
            q.push_back(c);
        }
        
        if(n->getParent() && isIncluded(n->getParent()->getOpCode(), iInclusions) &&
           isIncluded(n->getOpCode(), iInclusions))
        {
            oss << bakeName(n->getParent()) << "--" <<
                bakeName(n) << ";\n";
        }
        

        //first define the node with color
        for(int i = 0; i < n->getNumberOfAncillaryRecords(); ++i )
        {
            AncillaryRecord* a = n->getAncillaryRecord(i);
            
            if( isIncluded(a->getOpCode(), iInclusions) )
            { oss << bakeName(a) << " [fillcolor=grey];\n"; }
        }

        
        //define node relation
        for(int i = 0; i < n->getNumberOfAncillaryRecords(); ++i )
        {
            Record* a = n->getAncillaryRecord(i);

            if( isIncluded(n->getOpCode(), iInclusions) &&
               isIncluded(a->getOpCode(), iInclusions))
            {
                oss << bakeName(n) << "--" << bakeName(a) << ";\n";
            }
        }
        
    }
    
    oss << "}\n";
    
    return oss.str();
}