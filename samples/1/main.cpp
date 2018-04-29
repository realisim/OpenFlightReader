
#include "OpenFlight/DotExporter.h"
#include "OpenFlight/OpenFlightReader.h"
#include <iostream>
#include <fstream>
#include <string>


#include "OpenFlight/StreamUtilities.h"
using namespace std;

int main(int argc, char** argv)
{
    OpenFlight::OpenFlightReader ofr;
    OpenFlight::OpenFlightReader::Options ofrOptions;
    //ofrOptions.mDebugEnabled = true;
    ofrOptions.mDebugEnabled = false;
    ofr.setOptions(ofrOptions);
    
    std::string filenamePath = "../../assets/sample/nested_references/master/master.flt";
    //    std::string filenamePath = "../assets/sample/nested_references2/db/1/1.flt"
    //    std::string filenamePath = "../assets/sample/nested_references2/db/1/12/123/1234/1234.flt";
    
    //--------
    //IIIIII CONTENU BIDON DANS ifs
    filenamePath = "/Users/po/MultiTextureRecord.flt";
    ofstream ofs;
    ofs.open(filenamePath);
    
    //make header record
    uint16_t opCode = OpenFlight::ocHeader;
    OpenFlight::swapBytes2(&opCode);
    ofs.write( (char*)&opCode, sizeof(uint16_t) );

    uint16_t sizeOfRecord = 600;
    OpenFlight::swapBytes2(&sizeOfRecord);
    ofs.write( (char*)&sizeOfRecord, sizeof(uint16_t) );
    
    string data(600-4, 1);
    ofs.write( data.c_str(), data.size() );
    
    // push
    opCode = OpenFlight::ocPushLevel;
    OpenFlight::swapBytes2(&opCode);
    ofs.write( (char*)&opCode, sizeof(uint16_t) );

    sizeOfRecord = 4;
    OpenFlight::swapBytes2(&sizeOfRecord);
    ofs.write( (char*)&sizeOfRecord, sizeof(uint16_t) );
    
    // make multitexture node.
    opCode = OpenFlight::ocMultitexture;
    OpenFlight::swapBytes2(&opCode);
    ofs.write( (char*)&opCode, sizeof(uint16_t) );
    
    sizeOfRecord = 200;
    OpenFlight::swapBytes2(&sizeOfRecord);
    ofs.write( (char*)&sizeOfRecord, sizeof(uint16_t) );
    
    int32_t attribMask = 1<<9;
    OpenFlight::swapBytes4(&attribMask);
    ofs.write( (char*)&attribMask, sizeof(int32_t) );
    
    uint32_t a = 1, b = 2, c = 3, d = 4;
    OpenFlight::swapBytes4(&a);
    ofs.write( (char*)&a, sizeof(uint32_t) );
    OpenFlight::swapBytes4(&b);
    ofs.write( (char*)&b, sizeof(uint32_t) );
    OpenFlight::swapBytes4(&c);
    ofs.write( (char*)&c, sizeof(uint32_t) );
    OpenFlight::swapBytes4(&d);
    ofs.write( (char*)&d, sizeof(uint32_t) );
    
    a = 5, b = 6, c = 7, d = 8;
    OpenFlight::swapBytes4(&a);
    ofs.write( (char*)&a, sizeof(uint32_t) );
    OpenFlight::swapBytes4(&b);
    ofs.write( (char*)&b, sizeof(uint32_t) );
    OpenFlight::swapBytes4(&c);
    ofs.write( (char*)&c, sizeof(uint32_t) );
    OpenFlight::swapBytes4(&d);
    ofs.write( (char*)&d, sizeof(uint32_t) );
    ofs.close();
    //!!!!!!!!! FIN DU CONTENU BIDON
    
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