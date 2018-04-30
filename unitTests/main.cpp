
#include <cassert>
#include "OpenFlight/DotExporter.h"
#include "OpenFlight/OpenFlightReader.h"
#include <iostream>
#include <fstream>
#include <string>

#include "OpenFlight/StreamUtilities.h"
using namespace std;

namespace
{

    //---------------------------------------------------------------------
    #define CHECK( iCondition ) \
    do{ \
    if (iCondition) printf("%s: %s\n", #iCondition, "passes"); \
    string f = string("fails at ") + __FILE__;\
    if (!iCondition) { printf("%s: %s (%d)\n", #iCondition, f.c_str(), __LINE__); } \
    } while(0);

    //---------------------------------------------------------------------
    #define CHECK_TRUE( iCondition ) \
        CHECK( (iCondition) );

    //---------------------------------------------------------------------
    #define CHECK_FALSE( iCondition ) \
        CHECK( !(iCondition) );
}

//--------------------------------------------------------------------------
void testMultiTextureRecord()
{
    printf("\n\n --- testMultiTextureRecord --- \n");

    OpenFlight::OpenFlightReader ofr;
    OpenFlight::OpenFlightReader::Options ofrOptions;
    ofrOptions.mDebugEnabled = false;
    ofr.setOptions(ofrOptions);

    //--------
    string filenamePath = "./MultiTextureRecord.flt";
    ofstream ofs;
    ofs.open(filenamePath, ifstream::out | ios_base::binary);

    //make header record
    OpenFlight::writeUint16(ofs, OpenFlight::ocHeader);    
    OpenFlight::writeUint16(ofs, 600);

    string data(600-4, 0);
    OpenFlight::writeBytes(ofs, data);

    // push
    OpenFlight::writeUint16(ofs, OpenFlight::ocPushLevel);    
    OpenFlight::writeUint16(ofs, 4);

    // make multitexture node.
    OpenFlight::writeUint16(ofs, OpenFlight::ocMultitexture);    
    OpenFlight::writeUint16(ofs, 4 + 9*4);

    int32_t attribMask = 5;
    OpenFlight::writeInt32(ofs, attribMask);

    OpenFlight::writeUint32(ofs, 1);
    OpenFlight::writeUint32(ofs, OpenFlight::MultiTextureRecord::etTextureEnvironment);
    OpenFlight::writeUint32(ofs, 3);
    OpenFlight::writeUint32(ofs, 4);
    
    OpenFlight::writeUint32(ofs, 5);
    OpenFlight::writeUint32(ofs, OpenFlight::MultiTextureRecord::etBump);
    OpenFlight::writeUint32(ofs, 7);
    OpenFlight::writeUint32(ofs, 8);

    // make UV LIST RECORD.
    OpenFlight::writeUint16(ofs, OpenFlight::ocUvList);    
    OpenFlight::writeUint16(ofs, 4 + 4 + 8*4);

    OpenFlight::writeInt32(ofs, attribMask);
    
    // only two vertice define for layer 1 and 3.
    //Vertex 0
    //u layer 1
    OpenFlight::writeFloat32(ofs, 1.5);
    //v layer 1
    OpenFlight::writeFloat32(ofs, 2.5);

    //u layer 3
    OpenFlight::writeFloat32(ofs, 3.5);
    //v layer 3
    OpenFlight::writeFloat32(ofs, 4.5);

    //Vertex 1
    //u layer 1
    OpenFlight::writeFloat32(ofs, 5.5);
    //v layer 1
    OpenFlight::writeFloat32(ofs, 6.5);

    //u layer 3
    OpenFlight::writeFloat32(ofs, 7.5);
    //v layer 3
    OpenFlight::writeFloat32(ofs, 8.5);

    //!!!!!!!!! FIN DU CONTENU BIDON
    ofs.close();

    OpenFlight::HeaderRecord *pRoot = ofr.open( filenamePath );

    {
        // fetch MultiTexture record and validate.
        OpenFlight::MultiTextureRecord *pMulti = (OpenFlight::MultiTextureRecord*)pRoot->getAncillaryRecord(0);
        CHECK_TRUE(pMulti);
        CHECK_TRUE(pMulti->hasLayer(0));
        CHECK_FALSE(pMulti->hasLayer(1));
        CHECK_TRUE(pMulti->hasLayer(2));
        CHECK_FALSE(pMulti->hasLayer(3));
        CHECK_FALSE(pMulti->hasLayer(4));
        CHECK_FALSE(pMulti->hasLayer(5));
        CHECK_FALSE(pMulti->hasLayer(6));

        CHECK_TRUE(pMulti->hasLayers());

        CHECK_TRUE( pMulti->getTexturePatternIndex(0) == 1 );
        CHECK_TRUE( pMulti->getEffect(0) == OpenFlight::MultiTextureRecord::etTextureEnvironment);
        CHECK_TRUE( pMulti->getMappingIndex(0) == 3);
        CHECK_TRUE( pMulti->getData(0) == 4);

        CHECK_TRUE( pMulti->getTexturePatternIndex(1) == 0);
        CHECK_TRUE( pMulti->getEffect(1) == 0);
        CHECK_TRUE( pMulti->getMappingIndex(1) == 0);
        CHECK_TRUE( pMulti->getData(1) == 0);

        CHECK_TRUE( pMulti->getTexturePatternIndex(2) == 5);
        CHECK_TRUE( pMulti->getEffect(2) == OpenFlight::MultiTextureRecord::etBump);
        CHECK_TRUE( pMulti->getMappingIndex(2) == 7);
        CHECK_TRUE( pMulti->getData(2) == 8);

        CHECK_TRUE( pMulti->getTexturePatternIndex(11) == -1);
        CHECK_TRUE( pMulti->getMappingIndex(11) == -1);
        CHECK_TRUE( pMulti->getEffect(11) == OpenFlight::MultiTextureRecord::etUserDefined);
        CHECK_TRUE( pMulti->getData(11) == -1);


        // fetch Uv list record and validate.
        OpenFlight::UvListRecord *pUv = (OpenFlight::UvListRecord*)pRoot->getAncillaryRecord(1);
        CHECK_TRUE(pUv);
        CHECK_TRUE(pUv->hasLayer(0));
        CHECK_FALSE(pUv->hasLayer(1));
        CHECK_TRUE(pUv->hasLayer(2));
        CHECK_FALSE(pUv->hasLayer(3));
        CHECK_FALSE(pUv->hasLayer(4));
        CHECK_FALSE(pUv->hasLayer(5));
        CHECK_FALSE(pUv->hasLayer(6));

        OpenFlight::Vector2f l0v0 = pUv->getUv(0, 0);
        OpenFlight::Vector2f l1v0 = pUv->getUv(1, 0);
        OpenFlight::Vector2f l2v0 = pUv->getUv(2, 0);
        OpenFlight::Vector2f l3v0 = pUv->getUv(3, 0);
        OpenFlight::Vector2f l22v0 = pUv->getUv(22, 0);

        OpenFlight::Vector2f l0v1 = pUv->getUv(0, 1);
        OpenFlight::Vector2f l2v1 = pUv->getUv(2, 1);
        
        CHECK_TRUE(l0v0.mX == 1.5);
        CHECK_TRUE(l0v0.mY == 2.5);

        CHECK_TRUE(l1v0.mX == 0.0);
        CHECK_TRUE(l1v0.mY == 0.0);

        CHECK_TRUE(l2v0.mX == 3.5);
        CHECK_TRUE(l2v0.mY == 4.5);

        CHECK_TRUE(l0v1.mX == 5.5);
        CHECK_TRUE(l0v1.mY == 6.5);

        CHECK_TRUE(l2v1.mX == 7.5);
        CHECK_TRUE(l2v1.mY == 8.5);
    }

    delete pRoot;
}

int main(int argc, char** argv)
{
    testMultiTextureRecord();

    return 0;
}