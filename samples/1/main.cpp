
#include "OpenFlight/DotExporter.h"
#include "OpenFlight/OpenFlightReader.h"
#include <iostream>
#include <string>

using namespace std;

void parseArgs(int argc, char** argv, string *oFilenamePath, bool *oEnableDebug)
{
    // Default value if no args
    //*oFilenamePath = "../assets/sample/nested_references/master/master.flt";
    //*oFilenamePath = "../assets/sample/nested_references2/db/1/1.flt";
    *oFilenamePath = "../assets/sample/nested_references2/db/1/12/123/1234/1234.flt";
    *oEnableDebug = false;
    
    if(argc > 1)
    {
        for(int i = 1; i < argc; ++i)
        {
            if( string(argv[i]) == "-d" )
                *oEnableDebug = true;
            else
                *oFilenamePath = argv[i];
        }
    }
}

int main(int argc, char** argv)
{
    OpenFlight::OpenFlightReader ofr;

    bool enableDebug = false;
    std::string filenamePath;
    parseArgs(argc, argv, &filenamePath, &enableDebug);

    ofr.enableDebug(enableDebug);
    
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