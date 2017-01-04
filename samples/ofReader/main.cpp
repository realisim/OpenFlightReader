
#include "OpenFlight/DotExporter.h"
#include "OpenFlight/OpenFlightReader.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Options
{
    Options() : mDebug(false), mExportToDot(false), mDotExclusions(),
    mFilenamePath(){}
    
    bool mDebug;
    bool mExportToDot;
    vector<OpenFlight::opCode> mDotExclusions;
    string mFilenamePath;
};

vector<OpenFlight::opCode> makeAncillaryExlusions()
{
    using namespace OpenFlight;
    
    vector<OpenFlight::opCode> r;
    
    r.push_back(ocContinuation);
    r.push_back(ocComment);
    r.push_back(ocColorPalette);
    r.push_back(ocLongId);
    r.push_back(ocMatrix);
    r.push_back(ocVector);
    r.push_back(ocMultitexture);
    r.push_back(ocUvList);
    r.push_back(ocReplicate);
    r.push_back(ocTexturePalette);
    r.push_back(ocVertexPalette);
    r.push_back(ocVertexWithColor);
    r.push_back(ocVertexWithColorAndNormal);
    r.push_back(ocVertexWithColorNormalAndUv);
    r.push_back(ocVertexWithColorAndUv);
    r.push_back(ocBoundingBox);
    r.push_back(ocRotateAboutEdge);
    r.push_back(ocTranslate);
    r.push_back(ocScale);
    r.push_back(ocRotateAboutPoint);
    r.push_back(ocRotateScaleToPoint);
    r.push_back(ocPut);
    r.push_back(ocEyepointAndTrackplanePalette);
    r.push_back(ocLinkagePalette);
    r.push_back(ocSoundPalette);
    r.push_back(ocGeneralMatrix);
    r.push_back(ocLineStylePalette);
    r.push_back(ocLightSourcePalette);
    r.push_back(ocBoundingSphere);
    r.push_back(ocBoundingCylinder);
    r.push_back(ocBoundingConvexHull);
    r.push_back(ocBoundingVolumeCenter);
    r.push_back(ocBoundingVolumeOrientation);
    r.push_back(ocTextureMappingPalette);
    r.push_back(ocMaterialPalette);
    r.push_back(ocNameTable);
    r.push_back(ocBoundingHistogram);
    r.push_back(ocLightPointAppearancePalette);
    r.push_back(ocLightPointAnimationPalette);
    r.push_back(ocShaderPalette);
    r.push_back(ocExtendedMaterialHeader);
    r.push_back(ocExtendedMaterialAmbient);
    r.push_back(ocExtendedMaterialDiffuse);
    r.push_back(ocExtendedMaterialSpecular);
    r.push_back(ocExtendedMaterialEmissive);
    r.push_back(ocExtendedMaterialAlpha);
    r.push_back(ocExtendedMaterialLightMap);
    r.push_back(ocExtendedMaterialNormalMap);
    r.push_back(ocExtendedMaterialBumpMap);
    r.push_back(ocExtendedMaterialShadowMap);
    r.push_back(ocExtendedMaterialReflectionMap);
    r.push_back(ocExtensionGuidPalette);
    r.push_back(ocExtensionFieldBoolean);
    r.push_back(ocExtensionFieldInteger);
    r.push_back(ocExtensionFieldFloat);
    r.push_back(ocExtensionFieldDouble);
    r.push_back(ocExtensionFieldString);
    r.push_back(ocExtensionFieldXmlString);
    
    return r;
}

vector<OpenFlight::opCode> makePaletteExlusions()
{
    using namespace OpenFlight;
    
    vector<OpenFlight::opCode> r;
    
    r.push_back(ocColorPalette);
    r.push_back(ocTexturePalette);
    r.push_back(ocVertexPalette);
    r.push_back(ocEyepointAndTrackplanePalette);
    r.push_back(ocLinkagePalette);
    r.push_back(ocSoundPalette);
    r.push_back(ocLineStylePalette);
    r.push_back(ocLightSourcePalette);
    r.push_back(ocTextureMappingPalette);
    r.push_back(ocMaterialPalette);
    r.push_back(ocNameTable);
    r.push_back(ocLightPointAppearancePalette);
    r.push_back(ocLightPointAnimationPalette);
    r.push_back(ocShaderPalette);
    r.push_back(ocExtendedMaterialHeader);
    r.push_back(ocExtendedMaterialAmbient);
    r.push_back(ocExtendedMaterialDiffuse);
    r.push_back(ocExtendedMaterialSpecular);
    r.push_back(ocExtendedMaterialEmissive);
    r.push_back(ocExtendedMaterialAlpha);
    r.push_back(ocExtendedMaterialLightMap);
    r.push_back(ocExtendedMaterialNormalMap);
    r.push_back(ocExtendedMaterialBumpMap);
    r.push_back(ocExtendedMaterialShadowMap);
    r.push_back(ocExtendedMaterialReflectionMap);
    r.push_back(ocExtensionGuidPalette);

    
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
                    string exclusion(argv[++i]);
                    if(exclusion == "ancillaries")
                    {
                        vector<OpenFlight::opCode> e = makeAncillaryExlusions();
                        opt.mDotExclusions.insert(opt.mDotExclusions.end(), e.begin(), e.end()) ;
                    }
                    if(exclusion == "face"){ opt.mDotExclusions.push_back(OpenFlight::ocFace); }
                    if(exclusion == "longId"){ opt.mDotExclusions.push_back(OpenFlight::ocLongId); }
                    if(exclusion == "mesh"){ opt.mDotExclusions.push_back(OpenFlight::ocMesh); }
                    if(exclusion == "palettes")
                    {
                        vector<OpenFlight::opCode> e = makePaletteExlusions();
                        opt.mDotExclusions.insert(opt.mDotExclusions.end(), e.begin(), e.end()) ;
                    }
                }
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
        ofr.enableDebug(opt.mDebug);
        
        OpenFlight::HeaderRecord *pRoot = ofr.open( opt.mFilenamePath );
        if ( !ofr.hasErrors() )
        {
            if(ofr.hasWarnings())
            { cout << "Warnings: " << ofr.getAndClearLastWarnings() << endl; }
            
            if( opt.mExportToDot )
            {
                cout << OpenFlight::toDotFormat( pRoot, opt.mDotExclusions );
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
        "\t\t exlusionList: Exclusion list of the dotExport. The record excluded will not appear in the dot export.\n"<<
        "\t\t Currently supported exclusion:\n"<<
        "\t\t\t ancillaries: all ancillary records\n"<<
        "\t\t\t face: Face Record\n"<<
        "\t\t\t longId: long id records\n"<<
        "\t\t\t mesh: Mesh Record\n"<<
        "\t\t\t palettes: all palettes records\n\n"<<
        
        "\t -f: The filename path to be read.\n\n"<<
        
        "Examples: \n"<<
        "\t ofReader -debug -f /Users/Documents/flt/test.flt\n"<<
        "\t ofReader -dotExport -f /Users/Documents/flt/test.flt\n"<<
        "\t ofReader -dotExport palettes face mesh -f /Users/Documents/flt/test.flt\n\n";
        
        cout << oss.str();
    }


    return 0;
}