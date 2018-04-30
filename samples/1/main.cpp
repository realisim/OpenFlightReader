
#include "OpenFlight/DotExporter.h"
#include "OpenFlight/OpenFlightReader.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
    OpenFlight::OpenFlightReader ofr;
    OpenFlight::OpenFlightReader::Options ofrOptions;
    ofrOptions.mDebugEnabled = true;
    ofr.setOptions(ofrOptions);
    
    std::string filenamePath = "../../assets/sample/nested_references/master/master.flt";
    //    std::string filenamePath = "../assets/sample/nested_references2/db/1/1.flt"
    //    std::string filenamePath = "../assets/sample/nested_references2/db/1/12/123/1234/1234.flt";
    
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