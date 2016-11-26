#include "Document.h"
#include "PrimaryRecords/HeaderRecord.h"
#include <sstream>

using namespace std;
using namespace OpenFlight;

//-----------------------------------------------------------------------------
Document::Document() :
mpRootNode(nullptr)
{}

//-----------------------------------------------------------------------------
Document::~Document()
{
    if(mpRootNode != nullptr)
    { delete mpRootNode; }
}

//-----------------------------------------------------------------------------
void Document::clear()
{
    if(mpRootNode != nullptr)
    { delete mpRootNode; }
}

//-----------------------------------------------------------------------------
const HeaderRecord* Document::getRoot() const
{
    return mpRootNode;
}

//-----------------------------------------------------------------------------
bool Document::isValid() const
{
    return mpRootNode != nullptr;
}

//-----------------------------------------------------------------------------
void Document::setRootNode(OpenFlight::HeaderRecord *ipRoot)
{
    clear();
    mpRootNode = ipRoot;
}