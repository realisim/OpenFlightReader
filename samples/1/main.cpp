
#include "OpenFlight/DotExporter.h"
#include "OpenFlight/OpenFlightReader.h"
#include <iostream>
#include <string>

using namespace std;

string filenamePathFromArgs(int argc, char** argv)
{
    // Default value if no args
    //string filenamePath = "../assets/sample/nested_references/master/master.flt";
    //string filenamePath = "../assets/sample/nested_references2/db/1/1.flt";
    string r = "../assets/sample/nested_references2/db/1/12/123/1234/1234.flt";
    if(argc == 2)
    {
        r = argv[1];
    }
    return r;
}

int main(int argc, char** argv)
{
    OpenFlight::OpenFlightReader ofr;
    ofr.enableDebug(true);

    std::string filenamePath = filenamePathFromArgs(argc, argv);

    OpenFlight::HeaderRecord *pRoot = ofr.open( filenamePath );
    if ( !ofr.hasErrors() )
    {
        if(ofr.hasWarnings())
        { cout << "Warnings: " << ofr.getAndClearLastWarnings() << endl; }
        
        cout << OpenFlight::toDotFormat( pRoot );
    }
    else
    { cout << "Errors while reading flt file: " << filenamePath << "\n" <<  ofr.getAndClearLastErrors(); }
    
    delete pRoot;

    return 0;
}