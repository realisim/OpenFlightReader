
#include "OpenFlight/OpenFlightReader.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
    OpenFlight::OpenFlightReader ofr;
    ofr.enableDebug(true);

    //string filenamePath = "F:\\code\\OpenFlightReader\\assets\\sample\\nested_references\\master\\master.flt";
    //string filenamePath = "G:\CYYZ-Toronto\\main_CYYZ.flt";

    ofr.open( filenamePath );
    if ( ofr.hasErrors() )
    {
        cout << "Error while reading flt file: " << filenamePath << "\n" <<  ofr.getAndClearLastErrors();
    }

    return 0;
}