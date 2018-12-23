
#include "OpCode.h"

using namespace std;
using namespace OpenFlight;

std::string OpCodeUtils::toString(opCode iOpcode)
{
    std::string r;
    switch (iOpcode)
    {
        case ocUnsupported: r = "Unsupported record"; break;
        case ocHeader: r = "Header Record"; break;
        case ocGroup: r = "Group Record"; break;
        case ocObject: r = "Object Record"; break;
        case ocFace: r = "Face Record"; break;
        case ocPushLevel: r = "Push Level Record"; break;
        case ocPopLevel: r = "Pop Level Record"; break;
        case ocDegreeofFreedom: r = "Degree of Freedom Record"; break;
        case ocPushSubface: r = "Push Subface Record"; break;
        case ocPopSubface: r = "Pop Subface Record"; break;
        case ocPushExtension: r = "Push Extension Record"; break;
        case ocPopExtension: r = "Pop Extension Record"; break;
        case ocContinuation: r = "Continuation Record"; break;
        case ocComment: r = "Comment Record"; break;
        case ocColorPalette: r = "Color Palette Record"; break;
        case ocLongId: r = "Long ID Record"; break;
        case ocMatrix: r = "Matrix Record"; break;
        case ocVector: r = "Vector Record"; break;
        case ocMultitexture: r = "Multitexture Record"; break;
        case ocUvList: r = "UV List Record"; break;
        case ocBinarySeparatingPlane: r = "Binary Separating Plane Record"; break;
        case ocReplicate: r = "Replicate Record"; break;
        case ocInstanceReference: r = "Instance Reference Record"; break;
        case ocInstanceDefinition: r = "Instance Definition Record"; break;
        case ocExternalReference: r = "External Reference Record"; break;
        case ocTexturePalette: r = "Texture Palette Record"; break;
        case ocVertexPalette: r = "Vertex Palette Record"; break;
        case ocVertexWithColor: r = "Vertex with Color Record"; break;
        case ocVertexWithColorAndNormal: r = "Vertex with Color and Normal Record"; break;
        case ocVertexWithColorNormalAndUv: r = "Vertex with Color, Normal and UV Record"; break;
        case ocVertexWithColorAndUv: r = "Vertex with Color and UV Record"; break;
        case ocVertexList: r = "Vertex List Record"; break;
        case ocLevelOfDetail: r = "Level of Detail Record"; break;
        case ocBoundingBox: r = "Bounding Box Record"; break;
        case ocRotateAboutEdge: r = "Rotate About Edge Record"; break;
        case ocTranslate: r = "Translate Record"; break;
        case ocScale: r = "Scale Record"; break;
        case ocRotateAboutPoint: r = "Rotate About Point Record"; break;
        case ocRotateScaleToPoint: r = "Rotate and/or Scale to Point Record"; break;
        case ocPut: r = "Put Record"; break;
        case ocEyepointAndTrackplanePalette: r = "Eyepoint and Trackplane Palette Record"; break;
        case ocMesh: r = "Mesh Record"; break;
        case ocLocalVertexPool: r = "Local Vertex Pool Record"; break;
        case ocMeshPrimitive: r = "Mesh Primitive Record"; break;
        case ocRoadSegment: r = "Road Segment Record"; break;
        case ocRoadZone: r = "Road Zone Record"; break;
        case ocMorphVertexList: r = "Morph Vertex List Record"; break;
        case ocLinkagePalette: r = "Linkage Palette Record"; break;
        case ocSound: r = "Sound Record"; break;
        case ocRoadPath: r = "Road Path Record"; break;
        case ocSoundPalette: r = "Sound Palette Record"; break;
        case ocGeneralMatrix: r = "General Matrix Record"; break;
        case ocText: r = "Text Record"; break;
        case ocSwitch: r = "Switch Record"; break;
        case ocLineStylePalette: r = "Line Style Palette Record"; break;
        case ocClipRegion: r = "Clip Region Record"; break;
        case ocExtension: r = "Extension Record"; break;
        case ocLightSource: r = "Light Source Record"; break;
        case ocLightSourcePalette: r = "Light Source Palette Record"; break;
        case ocReserved103: r = "reserved"; break;
        case ocReserved104: r = "reserved"; break;
        case ocBoundingSphere: r = "Bounding Sphere Record"; break;
        case ocBoundingCylinder: r = "Bounding Cylinder Record"; break;
        case ocBoundingConvexHull: r = "Bounding Convex Hull Record"; break;
        case ocBoundingVolumeCenter: r = "Bounding Volume Center Record"; break;
        case ocBoundingVolumeOrientation: r = "Bounding Volume Orientation Record"; break;
        case ocReserved110: r = "reserved"; break;
        case ocLightPoint: r = "Light Point Record"; break;
        case ocTextureMappingPalette: r = "Texture Mapping Palette Record"; break;
        case ocMaterialPalette: r = "Material Palette Record"; break;
        case ocNameTable: r = "Name Table Record"; break;
        case ocContinuouslyAdaptiveTerrain: r = "CAT Record"; break;
        case ocCatData: r = "CAT Data Record"; break;
        case ocReserved117: r = "reserved"; break;
        case ocReserved118: r = "reserved"; break;
        case ocBoundingHistogram: r = "Bounding Histogram Record"; break;
        case ocReserved120: r = "reserved"; break;
        case ocReserved121: r = "reserved"; break;
        case ocPushAttribute: r = "Push Attribute Record"; break;
        case ocPopAttribute: r = "Pop Attribute Record"; break;
        case ocReserved124: r = "reserved"; break;
        case ocReserved125: r = "reserved"; break;
        case ocCurve: r = "Curve Record"; break;
        case ocRoadConstruction: r = "Road Construction Record"; break;
        case ocLightPointAppearancePalette: r = "Light Point Appearance Palette Record"; break;
        case ocLightPointAnimationPalette: r = "Light Point Animation Palette Record"; break;
        case ocIndexedLightPoint: r = "Indexed Light Point Record"; break;
        case ocLightPointSystem: r = "Light Point System Record"; break;
        case ocIndexedString: r = "Indexed String Record"; break;
        case ocShaderPalette: r = "Shader Palette Record"; break;
        case ocReserved134: r = "reserved"; break;
        case ocExtendedMaterialHeader: r = "Extended Material Header Record"; break;
        case ocExtendedMaterialAmbient: r = "Extended Material Ambient Record"; break;
        case ocExtendedMaterialDiffuse: r = "Extended Material Diffuse Record"; break;
        case ocExtendedMaterialSpecular: r = "Extended Material Specular Record"; break;
        case ocExtendedMaterialEmissive: r = "Extended Material Emissive Record"; break;
        case ocExtendedMaterialAlpha: r = "Extended Material Alpha Record"; break;
        case ocExtendedMaterialLightMap: r = "Extended Material Light Map Record"; break;
        case ocExtendedMaterialNormalMap: r = "Extended Material Normal Map Record"; break;
        case ocExtendedMaterialBumpMap: r = "Extended Material Bump Map Record"; break;
        case ocReserved144: r = "reserved"; break;
        case ocExtendedMaterialShadowMap: r = "Extended Material Shadow Map Record"; break;
        case ocReserved146: r = "reserved"; break;
        case ocExtendedMaterialReflectionMap: r = "Extended Material Reflection Map Record"; break;
        case ocExtensionGuidPalette: r = "Extension GUID Palette Record"; break;
        case ocExtensionFieldBoolean: r = "Extension Field Boolean Record"; break;
        case ocExtensionFieldInteger: r = "Extension Field Integer Record"; break;
        case ocExtensionFieldFloat: r = "Extension Field Float Record"; break;
        case ocExtensionFieldDouble: r = "Extension Field Double Record"; break;
        case ocExtensionFieldString: r = "Extension Field String Record"; break;
        case ocExtensionFieldXmlString: r = "Extension Field XML String Record"; break;
        default: r = "unknown opCode"; break;
    }
    return r;
}

//------------------------------------------------------------------------------
bool OpCodeUtils::isAncillaryRecord(opCode iOpcode)
{
    bool r = false;
    switch (iOpcode)
    {
        case ocContinuation:
        case ocComment:
        case ocColorPalette:
        case ocLongId:
        case ocMatrix:
        case ocVector:
        case ocMultitexture:
        case ocUvList:
        case ocReplicate:
        case ocTexturePalette:
        case ocVertexPalette:
        case ocVertexWithColor:
        case ocVertexWithColorAndNormal:
        case ocVertexWithColorNormalAndUv:
        case ocVertexWithColorAndUv:
        case ocBoundingBox:
        case ocRotateAboutEdge:
        case ocTranslate:
        case ocScale:
        case ocRotateAboutPoint:
        case ocRotateScaleToPoint:
        case ocPut:
        case ocEyepointAndTrackplanePalette:
        case ocLinkagePalette:
        case ocSoundPalette:
        case ocGeneralMatrix:
        case ocLineStylePalette:
        case ocLightSourcePalette:
        case ocBoundingSphere:
        case ocBoundingCylinder:
        case ocBoundingConvexHull:
        case ocBoundingVolumeCenter:
        case ocBoundingVolumeOrientation:
        case ocTextureMappingPalette:
        case ocMaterialPalette:
        case ocNameTable:
        case ocBoundingHistogram:
        case ocLightPointAppearancePalette:
        case ocLightPointAnimationPalette:
        case ocIndexedString :
        case ocShaderPalette:
        case ocExtendedMaterialHeader:
        case ocExtendedMaterialAmbient:
        case ocExtendedMaterialDiffuse:
        case ocExtendedMaterialSpecular:
        case ocExtendedMaterialEmissive:
        case ocExtendedMaterialAlpha:
        case ocExtendedMaterialLightMap:
        case ocExtendedMaterialNormalMap:
        case ocExtendedMaterialBumpMap:
        case ocExtendedMaterialShadowMap:
        case ocExtendedMaterialReflectionMap:
        case ocExtensionGuidPalette:
        case ocExtensionFieldBoolean:
        case ocExtensionFieldInteger:
        case ocExtensionFieldFloat:
        case ocExtensionFieldDouble:
        case ocExtensionFieldString:
        case ocExtensionFieldXmlString:
            r = true;
            break;
        default: r = false; break;
    }
    return r;
}

//------------------------------------------------------------------------------
bool OpCodeUtils::isExtendedMaterialPaletteRecord(opCode iOpcode)
{
    bool r = false;
    switch(iOpcode)
    {
        case ocExtendedMaterialHeader:
        case ocExtendedMaterialAmbient:
        case ocExtendedMaterialDiffuse:
        case ocExtendedMaterialSpecular:
        case ocExtendedMaterialEmissive:
        case ocExtendedMaterialAlpha:
        case ocExtendedMaterialLightMap:
        case ocExtendedMaterialNormalMap:
        case ocExtendedMaterialBumpMap:
        case ocExtendedMaterialShadowMap:
        case ocExtendedMaterialReflectionMap:
            r = true;
            break;
        default: r = false; break;
    }
    return r;
}

//------------------------------------------------------------------------------
bool OpCodeUtils::isContinuationRecord(opCode iOpcode)
{
    bool r = false;
    switch(iOpcode)
    {
        case ocContinuation:
        case ocExtensionFieldBoolean:
        case ocExtensionFieldInteger:
        case ocExtensionFieldFloat:
        case ocExtensionFieldDouble:
        case ocExtensionFieldString:
        case ocExtensionFieldXmlString:
            r = true;
            break;
        default: r = false; break;
    }
    return r;
}

//------------------------------------------------------------------------------
bool OpCodeUtils::isControlRecord(opCode iOpcode)
{
    bool r = false;
    switch(iOpcode)
    {
        case ocPushLevel:
        case ocPopLevel:
        case ocPushSubface:
        case ocPopSubface:
        case ocPushExtension:
        case ocPopExtension:
        case ocPushAttribute:
        case ocPopAttribute:
            r = true;
            break;
        default: r = false; break;
    }
    return r;
}

//------------------------------------------------------------------------------
bool OpCodeUtils::isPaletteRecord(opCode iOpcode)
{
    bool r = false;
    switch (iOpcode)
    {
        case ocColorPalette:
        case ocTexturePalette:
        case ocVertexPalette:
        case ocEyepointAndTrackplanePalette:
        case ocLinkagePalette:
        case ocSoundPalette:
        case ocLineStylePalette:
        case ocLightSourcePalette:
        case ocTextureMappingPalette:
        case ocMaterialPalette:
        case ocNameTable:
        case ocLightPointAppearancePalette:
        case ocLightPointAnimationPalette:
        case ocShaderPalette:
        case ocExtendedMaterialHeader:
        case ocExtendedMaterialAmbient:
        case ocExtendedMaterialDiffuse:
        case ocExtendedMaterialSpecular:
        case ocExtendedMaterialEmissive:
        case ocExtendedMaterialAlpha:
        case ocExtendedMaterialLightMap:
        case ocExtendedMaterialNormalMap:
        case ocExtendedMaterialBumpMap:
        case ocExtendedMaterialShadowMap:
        case ocExtendedMaterialReflectionMap:
        case ocExtensionGuidPalette:
            r = true;
            break;
        default: r = false; break;
    }
    return r;
}

//------------------------------------------------------------------------------
bool OpCodeUtils::isPrimaryRecord(opCode iOpcode)
{
    bool r = false;
    switch (iOpcode)
    {
        case ocUnsupported:
        case ocHeader :
        case ocGroup :
        case ocObject :
        case ocFace :
        case ocDegreeofFreedom :
        case ocBinarySeparatingPlane :
        case ocInstanceReference :
        case ocInstanceDefinition :
        case ocExternalReference :
        case ocVertexList :
        case ocLevelOfDetail :
        case ocMesh :
        case ocLocalVertexPool :
        case ocMeshPrimitive :
        case ocRoadSegment :
        case ocRoadZone :
        case ocMorphVertexList :
        case ocSound :
        case ocRoadPath :
        case ocText :
        case ocSwitch :
        case ocClipRegion :
        case ocExtension :
        case ocLightSource :
        //case ocReserved103 :
        //case ocReserved104 :
        //case ocReserved110 :
        case ocLightPoint :
        case ocContinuouslyAdaptiveTerrain :
        case ocCatData :
        //case ocReserved117 :
        //case ocReserved118 :
        //case ocReserved120 :
        //case ocReserved121 :
        //case ocReserved124 :
        //case ocReserved125 :
        case ocCurve :
        case ocRoadConstruction :
        case ocIndexedLightPoint :
        case ocLightPointSystem :
        //case ocReserved134 :
        //case ocReserved144 :
        //case ocReserved146 :
            r = true;
            break;
        default: r = false; break;
    }
    return r;
}

//------------------------------------------------------------------------------
bool OpCodeUtils::isTransformationRecord(opCode iOpcode)
{
    bool r = false;
    switch(iOpcode)
    {
        case ocMatrix:
        case ocRotateAboutEdge:
        case ocTranslate:
        case ocScale:
        case ocRotateAboutPoint:
        case ocRotateScaleToPoint:
        case ocPut:
        case ocGeneralMatrix:
            r = true;
            break;
        default: r = false; break;
    }
    return r;
}