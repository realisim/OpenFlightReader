
#include <deque>
#include "OpenFlightReader.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

//------------------------------------------------------------------------------
//--- FltDocument
//------------------------------------------------------------------------------
class FltDocument
{
public:
    FltDocument() = delete;
    FltDocument(const string& iFileNamePath, OpenFlight::HeaderRecord*);
    FltDocument(const FltDocument&) = delete;
    FltDocument& operator=(const FltDocument&) = delete;
    ~FltDocument();
    
    struct Statistics
    {
        Statistics() : mNumberOfGroups(0), mNumberOfObjects(0),
            mNumberOfPolygons(0), mNumberOfVertices(0) {;}
        int mNumberOfGroups;
        int mNumberOfObjects;
        int mNumberOfPolygons;
        int mNumberOfVertices;
        
        string toString() const;
    };
    
    const string& getFilenamePath() const {return mFilenamePath; }
    const Statistics& getStatistics() const {return mStatistics;}
    
protected:
    void collectStatistics();
    
    Statistics mStatistics;
    
    string mFilenamePath;
    OpenFlight::HeaderRecord* mpRoot; //owned
};

//------------------------------------------------------------------------------
FltDocument::FltDocument(const string& iFileNamePath,
                         OpenFlight::HeaderRecord* ipRoot):
mFilenamePath(iFileNamePath),
mpRoot(ipRoot)
{ collectStatistics(); }

//------------------------------------------------------------------------------
FltDocument::~FltDocument()
{ if(mpRoot != nullptr){ delete mpRoot; } }

//------------------------------------------------------------------------------
void FltDocument::collectStatistics()
{
    using namespace OpenFlight;
    
    //early out
    if(mpRoot == nullptr){ return; }
    
    //breadth first visit

    deque<PrimaryRecord*> q;
    q.push_back( (PrimaryRecord*)mpRoot );
    PrimaryRecord* n;
    while (!q.empty())
    {
        //--- grab first element and pop from queu
        n = q.front();
        q.pop_front();
        
        //--- add childs of n to queue
        for(int i = 0; i < n->getNumberOfChilds(); ++i)
        {
            q.push_back(n->getChild(i));
        }
        
        //--- visit n;
        switch (n->getOpCode())
        {
            case ocGroup: mStatistics.mNumberOfGroups++; break;
            case ocObject: 
                mStatistics.mNumberOfObjects++;
                printf("\t object name: %s\n", ((ObjectRecord*)n)->getAsciiId().c_str() );
                break;
            case ocFace: mStatistics.mNumberOfPolygons++; break;
            case ocMesh: break;
            default: break;
        }
        
        //visit Ancillary records of n, Ancillary can't have
        //childs.
        for(int i = 0; i < n->getNumberOfAncillaryRecords(); ++i)
        {
            AncillaryRecord* a = n->getAncillaryRecord(i);
            
            switch (a->getOpCode())
            {
                case ocVertexPalette:
                {
                    VertexPaletteRecord* vpr = (VertexPaletteRecord*)a;
                    mStatistics.mNumberOfVertices += vpr->getNumberOfVertices();
                }break;
                
                default: break;
            }
        }
    }
}

//------------------------------------------------------------------------------
string FltDocument::Statistics::toString() const
{
    ostringstream oss;
    oss <<
    "number of Groups: " << mNumberOfGroups << endl <<
    "number of Objects: " << mNumberOfObjects << endl <<
    "number of Polygons: " << mNumberOfPolygons << endl <<
    "number of Vertices: " << mNumberOfVertices << endl;
    
    return oss.str();
}


//------------------------------------------------------------------------------
//--- MAIN
//------------------------------------------------------------------------------
int main(int argc, char** argv)
{
    OpenFlight::OpenFlightReader ofr;

    //string filenamePath = "../assets/sample/nested_references/master/master.flt";
    //string filenamePath = "../assets/sample/nested_references2/db/1/1.flt";
    string filenamePath = "../../../assets/sample/nested_references2/db/1/12/123/1234/1234.flt";

    OpenFlight::HeaderRecord *pRoot = ofr.open( filenamePath );
    FltDocument doc(filenamePath, pRoot);
    if ( !ofr.hasErrors() )
    {
        if(ofr.hasWarnings())
        { cout << "Warnings: " << ofr.getAndClearLastWarnings() << endl; }
        
        
        cout << "Stats for file: " << doc.getFilenamePath() << endl <<
            doc.getStatistics().toString();
    }
    else
    { cout << "Errors while reading flt file: " << filenamePath << "\n" <<  ofr.getAndClearLastErrors(); }

    return 0;
}