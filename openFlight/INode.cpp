
#include "INode.h"
#include <sstream>
#include "StreamUtilities.h"

using namespace OpenFlight;
using namespace std;

//-------------------------------------------------------------------------
//--- INode
//-------------------------------------------------------------------------
INode::INode()
{}

//-------------------------------------------------------------------------
INode::~INode()
{
    // delete all childs
    for(size_t i = 0; i < mChilds.size(); ++i)
    { delete mChilds[i]; }

    mChilds.clear();
}

//-------------------------------------------------------------------------
void INode::addChild(INode* iChild)
{ 
    if (iChild != nullptr)
    { mChilds.push_back(iChild); }
}

//-------------------------------------------------------------------------
int INode::getNumberOfChilds() const
{ return (int)mChilds.size(); }
