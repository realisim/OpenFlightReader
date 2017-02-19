
#include "OpenFlight/DotExporter.h"
#include "OpenFlight/OpenFlightReader.h"
#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <vector>

using namespace std;

struct Options
{
    Options() :
        mDebug(false),
        mExportToDot(false),
        mVertexDataSkipped(false),
        mDotInclusions(),
        mFilenamePath(){}
    
    bool mDebug;
    bool mExportToDot;
    bool mVertexDataSkipped;
    set<OpenFlight::opCode> mDotInclusions;
    string mFilenamePath;
};

set<OpenFlight::opCode> makePrimaryInclusions()
{
    using namespace OpenFlight;
    set<OpenFlight::opCode> r;
    
    r.insert( ocUnsupported);
    r.insert( ocHeader );
    r.insert( ocGroup );
    r.insert( ocObject );
    r.insert( ocFace );
    r.insert( ocDegreeofFreedom );
    r.insert( ocBinarySeparatingPlane );
    r.insert( ocInstanceReference );
    r.insert( ocInstanceDefinition );
    r.insert( ocExternalReference );
    r.insert( ocVertexList );
    r.insert( ocLevelofDetail );
    r.insert( ocMesh );
    r.insert( ocLocalVertexPool );
    r.insert( ocMeshPrimitive );
    r.insert( ocRoadSegment );
    r.insert( ocRoadZone );
    r.insert( ocMorphVertexList );
    r.insert( ocSound );
    r.insert( ocRoadPath );
    r.insert( ocText );
    r.insert( ocSwitch );
    r.insert( ocClipRegion );
    r.insert( ocExtension );
    r.insert( ocLightSource );
    r.insert( ocReserved103 );
    r.insert( ocReserved104 );
    r.insert( ocReserved110 );
    r.insert( ocLightPoint );
    r.insert( ocContinuouslyAdaptiveTerrain );
    r.insert( ocCatData );
    r.insert( ocReserved117 );
    r.insert( ocReserved118 );
    r.insert( ocReserved120 );
    r.insert( ocReserved121 );
    r.insert( ocReserved124 );
    r.insert( ocReserved125 );
    r.insert( ocCurve );
    r.insert( ocRoadConstruction );
    r.insert( ocIndexedLightPoint );
    r.insert( ocLightPointSystem );
    r.insert( ocIndexedString );
    r.insert( ocReserved134 );
    r.insert( ocReserved144 );
    r.insert( ocReserved146 );
    
    return r;
}

set<OpenFlight::opCode> makeAncillaryInclusions()
{
    using namespace OpenFlight;
    
    set<OpenFlight::opCode> r;
    
    r.insert(ocContinuation);
    r.insert(ocComment);
    r.insert(ocColorPalette);
    r.insert(ocLongId);
    r.insert(ocMatrix);
    r.insert(ocVector);
    r.insert(ocMultitexture);
    r.insert(ocUvList);
    r.insert(ocReplicate);
    r.insert(ocTexturePalette);
    r.insert(ocVertexPalette);
    r.insert(ocVertexWithColor);
    r.insert(ocVertexWithColorAndNormal);
    r.insert(ocVertexWithColorNormalAndUv);
    r.insert(ocVertexWithColorAndUv);
    r.insert(ocBoundingBox);
    r.insert(ocRotateAboutEdge);
    r.insert(ocTranslate);
    r.insert(ocScale);
    r.insert(ocRotateAboutPoint);
    r.insert(ocRotateScaleToPoint);
    r.insert(ocPut);
    r.insert(ocEyepointAndTrackplanePalette);
    r.insert(ocLinkagePalette);
    r.insert(ocSoundPalette);
    r.insert(ocGeneralMatrix);
    r.insert(ocLineStylePalette);
    r.insert(ocLightSourcePalette);
    r.insert(ocBoundingSphere);
    r.insert(ocBoundingCylinder);
    r.insert(ocBoundingConvexHull);
    r.insert(ocBoundingVolumeCenter);
    r.insert(ocBoundingVolumeOrientation);
    r.insert(ocTextureMappingPalette);
    r.insert(ocMaterialPalette);
    r.insert(ocNameTable);
    r.insert(ocBoundingHistogram);
    r.insert(ocLightPointAppearancePalette);
    r.insert(ocLightPointAnimationPalette);
    r.insert(ocShaderPalette);
    r.insert(ocExtendedMaterialHeader);
    r.insert(ocExtendedMaterialAmbient);
    r.insert(ocExtendedMaterialDiffuse);
    r.insert(ocExtendedMaterialSpecular);
    r.insert(ocExtendedMaterialEmissive);
    r.insert(ocExtendedMaterialAlpha);
    r.insert(ocExtendedMaterialLightMap);
    r.insert(ocExtendedMaterialNormalMap);
    r.insert(ocExtendedMaterialBumpMap);
    r.insert(ocExtendedMaterialShadowMap);
    r.insert(ocExtendedMaterialReflectionMap);
    r.insert(ocExtensionGuidPalette);
    r.insert(ocExtensionFieldBoolean);
    r.insert(ocExtensionFieldInteger);
    r.insert(ocExtensionFieldFloat);
    r.insert(ocExtensionFieldDouble);
    r.insert(ocExtensionFieldString);
    r.insert(ocExtensionFieldXmlString);
    
    return r;
}

set<OpenFlight::opCode> makePaletteInclusions()
{
    using namespace OpenFlight;
    
    set<OpenFlight::opCode> r;
    
    r.insert(ocColorPalette);
    r.insert(ocTexturePalette);
    r.insert(ocVertexPalette);
    r.insert(ocEyepointAndTrackplanePalette);
    r.insert(ocLinkagePalette);
    r.insert(ocSoundPalette);
    r.insert(ocLineStylePalette);
    r.insert(ocLightSourcePalette);
    r.insert(ocTextureMappingPalette);
    r.insert(ocMaterialPalette);
    r.insert(ocNameTable);
    r.insert(ocLightPointAppearancePalette);
    r.insert(ocLightPointAnimationPalette);
    r.insert(ocShaderPalette);
    r.insert(ocExtendedMaterialHeader);
    r.insert(ocExtendedMaterialAmbient);
    r.insert(ocExtendedMaterialDiffuse);
    r.insert(ocExtendedMaterialSpecular);
    r.insert(ocExtendedMaterialEmissive);
    r.insert(ocExtendedMaterialAlpha);
    r.insert(ocExtendedMaterialLightMap);
    r.insert(ocExtendedMaterialNormalMap);
    r.insert(ocExtendedMaterialBumpMap);
    r.insert(ocExtendedMaterialShadowMap);
    r.insert(ocExtendedMaterialReflectionMap);
    r.insert(ocExtensionGuidPalette);

    return r;
}

Options parseArgs(int argc, char** argv)
{
    // Default value if no args
    Options opt;
    
    if(argc > 1)
    {
        for(int i = 1; i < argc; ++i)
        {
            if( string(argv[i]) == "-debug" )
                opt.mDebug = true;
            if( string(argv[i]) == "-dotExport" )
            {
                opt.mExportToDot = true;
                while( argc > (i+1) && string(argv[i+1]).find("-") == string::npos )
                {
                    string inclusion(argv[++i]);
                    if(inclusion == "primaryRecords")
                    {
                        set<OpenFlight::opCode> e = makePrimaryInclusions();
                        opt.mDotInclusions.insert(e.begin(), e.end()) ;
                    }
                    if(inclusion == "ancillaryRecords")
                    {
                        set<OpenFlight::opCode> e = makeAncillaryInclusions();
                        opt.mDotInclusions.insert(e.begin(), e.end()) ;
                    }
                    if(inclusion == "paletteRecords")
                    {
                        set<OpenFlight::opCode> e = makePaletteInclusions();
                        opt.mDotInclusions.insert(e.begin(), e.end()) ;
                    }
                    
                    if(inclusion == "headerRecord")
                    { opt.mDotInclusions.insert( OpenFlight::ocHeader ); }
                    if(inclusion == "externalReference")
                    { opt.mDotInclusions.insert( OpenFlight::ocExternalReference ); }
                    if(inclusion == "groupRecord")
                    { opt.mDotInclusions.insert( OpenFlight::ocGroup ); }
                    if(inclusion == "objectRecord")
                    { opt.mDotInclusions.insert( OpenFlight::ocObject ); }
                    if(inclusion == "matrixRecord")
                    { opt.mDotInclusions.insert( OpenFlight::ocMatrix ); }
                }
            }
            
            if(string(argv[i]) == "-skipVertexData" )
            {
                opt.mVertexDataSkipped = true;
            }
            
            if( string(argv[i]) == "-f" && argc > i+1)
            {
                opt.mFilenamePath = argv[++i];
            }
        }
    }
    
    return opt;
}

int main(int argc, char** argv)
{
    OpenFlight::OpenFlightReader ofr;

    Options opt = parseArgs(argc, argv);
    
    if(!opt.mFilenamePath.empty())
    {
        OpenFlight::OpenFlightReader::Options ofrOptions;
        ofrOptions.mDebugEnabled = opt.mDebug;
        ofrOptions.mVertexDataSkipped = opt.mVertexDataSkipped;
        ofr.setOptions(ofrOptions);
        
        OpenFlight::HeaderRecord *pRoot = ofr.open( opt.mFilenamePath );
        if ( !ofr.hasErrors() )
        {
            if(ofr.hasWarnings())
            { cout << "Warnings: " << ofr.getAndClearLastWarnings() << endl; }
            
            if( opt.mExportToDot )
            {
                cout << OpenFlight::toDotFormat( pRoot, opt.mDotInclusions );
            }
        }
        else
        { cout << "Errors while reading flt file: " << opt.mFilenamePath << "\n" <<  ofr.getAndClearLastErrors(); }
        
        delete pRoot;
    }
    else
    {
        ostringstream oss;
        oss<< "Usage: ofReader [-debug] [-dotExport [exlusionList]] -f filenamePath\n\n"<<
        "\t -debug: will print, for each record found, the record type and the binary payload.\n\n"<<
        
        "\t -dotExport: will print the graph in dot format to be visualize with graphViz for example.\n"<<
        "\t\t Inclusion list must follow the -dotExport options. Every record type listed will appear in the dot export.\n"<<
        "\t\t Currently supported inclusion:\n"<<
        "\t\t\t all: all records\n"<<
        "\t\t\t primaryRecords: all primary records\n"<<
        "\t\t\t ancillaryRecords: all ancillary records\n"<<
        "\t\t\t paletteRecords: all palette records\n"<<
        
        "\t\t\t headerRecord: header record\n"<<
        "\t\t\t externalReference: group record\n"<<
        "\t\t\t groupRecord: group record\n"<<
        "\t\t\t objectRecord: object record\n"<<
        
        "\t\t\t matrixRecord: matrix record\n"<<
        
        
        "\t -skipVertexData: All vertex data (vertex palette content and vertex pool content records) will be skipped.\n\n"<<
        "\t -f: The filename path to be read.\n\n"<<
        
        "Examples: \n"<<
        "\t ofReader -debug -f /Users/Documents/flt/test.flt\n"<<
        "\t ofReader -dotExport -f /Users/Documents/flt/test.flt\n"<<
        "\t ofReader -dotExport headerRecords groupRecords objectRecords -f /Users/Documents/flt/test.flt\n\n";
        
        cout << oss.str();
    }


    return 0;
}