#pragma once

#include <string>

namespace OpenFlight
{
    enum opCode
    {
        ocUnknown = 0,
        ocHeader                                 =   1  ,  //“Header Record”
        ocGroup                                  =   2  ,  //“Group Record”
        ocObject                                 =   4  ,  //“Object Record”
        ocFace                                   =   5  ,  //“Face Record”
        ocPushLevel                              =   10 ,  //“Push Level Record”
        ocPopLevel                               =   11 ,  //“Pop Level Record”
        ocDegreeofFreedom                        =   14 ,  //“Degree of Freedom Record”
        ocPushSubface                            =   19 ,  //“Push Subface Record”
        ocPopSubface                             =   20 ,  //“Pop Subface Record”
        ocPushExtension                          =   21 ,  //“Push Extension Record”
        ocPopExtension                           =   22 ,  //“Pop Extension Record”
        ocContinuation                           =   23 ,  //“Continuation Record”
        ocComment                                =   31 ,  //“Comment Record”
        ocColorPalette                           =   32 ,  //“Color Palette Record”
        ocLongId                                 =   33 ,  //“Long ID Record”
        ocMatrix                                 =   49 ,  //“Matrix Record”
        ocVector                                 =   50 ,  //“Vector Record”
        ocMultitexture                           =   52 ,  //“Multitexture Record”
        ocUvList                                 =   53 ,  //“UV List Record”
        ocBinarySeparatingPlane                  =   55 ,  //“Binary Separating Plane Record”
        ocReplicate                              =   60 ,  //“Replicate Record”
        ocInstanceReference                      =   61 ,  //“Instance Reference Record”
        ocInstanceDefinition                     =   62 ,  //“Instance Definition Record”
        ocExternalReference                      =   63 ,  //“External Reference Record”
        ocTexturePalette                         =   64 ,  //“Texture Palette Record”
        ocVertexPalette                          =   67 ,  //“Vertex Palette Record”
        ocVertexWithColor                        =   68 ,  //“Vertex with Color Record”
        ocVertexWithColorAndNormal               =   69 ,  //“Vertex with Color and Normal Record”
        ocVertexWithColorNormalAndUv             =   70 ,  //“Vertex with Color, Normal and UV Record”
        ocVertexWithColorAndUv                   =   71 ,  //“Vertex with Color and UV Record”
        ocVertexList                             =   72 ,  //“Vertex List Record”
        ocLevelofDetail                          =   73 ,  //“Level of Detail Record”
        ocBoundingBox                            =   74 ,  //“Bounding Box Record”
        ocRotateAboutEdge                        =   76 ,  //“Rotate About Edge Record”
        ocTranslate                              =   78 ,  //“Translate Record”
        ocScale                                  =   79 ,  //“Scale Record”
        ocRotateAboutPoint                       =   80 ,  //“Rotate About Point Record”
        ocRotateScaleToPoint                     =   81 ,  //“Rotate and/or Scale to Point Record”
        ocPut                                    =   82 ,  //“Put Record”
        ocEyepointAndTrackplanePalette           =   83 ,  //“Eyepoint and Trackplane Palette Record”
        ocMesh                                   =   84 ,  //“Mesh Record”
        ocLocalVertexPool                        =   85 ,  //“Local Vertex Pool Record”
        ocMeshPrimitive                          =   86 ,  //“Mesh Primitive Record”
        ocRoadSegment                            =   87 ,  //“Road Segment Record”
        ocRoadZone                               =   88 ,  //“Road Zone Record”
        ocMorphVertexList                        =   89 ,  //“Morph Vertex List Record”
        ocLinkagePalette                         =   90 ,  //“Linkage Palette Record”
        ocSound                                  =   91 ,  //“Sound Record”
        ocRoadPath                               =   92 ,  //“Road Path Record”
        ocSoundPalette                           =   93 ,  //“Sound Palette Record”
        ocGeneralMatrix                          =   94 ,  //“General Matrix Record”
        ocText                                   =   95 ,  //“Text Record”
        ocSwitch                                 =   96 ,  //“Switch Record”
        ocLineStylePalette                       =   97 ,  //“Line Style Palette Record”
        ocClipRegion                             =   98 ,  //“Clip Region Record”
        ocExtension                              =   100,  //“Extension Record”
        ocLightSource                            =   101,  //“Light Source Record”
        ocLightSourcePalette                     =   102,  //“Light Source Palette Record”
        ocReserved103                            =   103,  //“reserved"
        ocReserved104                            =   104,  //“reserved"
        ocBoundingSphere                         =   105,  //“Bounding Sphere Record”
        ocBoundingCylinder                       =   106,  //“Bounding Cylinder Record”
        ocBoundingConvexHull                     =   107,  //“Bounding Convex Hull Record”
        ocBoundingVolumeCenter                   =   108,  //“Bounding Volume Center Record”
        ocBoundingVolumeOrientation              =   109,  //“Bounding Volume Orientation Record”
        ocReserved110                            =   110,  //“reserved"
        ocLightPoint                             =   111,  //“Light Point Record”
        ocTextureMappingPalette                  =   112,  //“Texture Mapping Palette Record”
        ocMaterialPalette                        =   113,  //“Material Palette Record”
        ocNameTable                              =   114,  //“Name Table Record”
        ocContinuouslyAdaptiveTerrain            =   115,  //“CAT Record”
        ocCatData                                =   116,  //“CAT Data Record”
        ocReserved117                            =   117,  //“reserved"
        ocReserved118                            =   118,  //“reserved"
        ocBoundingHistogram                      =   119,  //“Bounding Histogram Record”
        ocReserved120                            =   120,  //“reserved"
        ocReserved121                            =   121,  //“reserved"
        ocPushAttribute                          =   122,  //“Push Attribute Record”
        ocPopAttribute                           =   123,  //“Pop Attribute Record”
        ocReserved124                            =   124,  //“reserved"
        ocReserved125                            =   125,  //“reserved"
        ocCurve                                  =   126,  //“Curve Record”
        ocRoadConstruction                       =   127,  //“Road Construction Record”
        ocLightPointAppearancePalette            =   128,  //“Light Point Appearance Palette Record”
        ocLightPointAnimationPalette             =   129,  //“Light Point Animation Palette Record”
        ocIndexedLightPoint                      =   130,  //“Indexed Light Point Record”
        ocLightPointSystem                       =   131,  //“Light Point System Record”
        ocIndexedString                          =   132,  //“Indexed String Record”
        ocShaderPalette                          =   133,  //“Shader Palette Record”
        ocReserved134                            =   134,  //“reserved"
        ocExtendedMaterialHeader                 =   135,  //“Extended Material Header Record”
        ocExtendedMaterialAmbient                =   136,  //“Extended Material Ambient Record”
        ocExtendedMaterialDiffuse                =   137,  //“Extended Material Diffuse Record”
        ocExtendedMaterialSpecular               =   138,  //“Extended Material Specular Record”
        ocExtendedMaterialEmissive               =   139,  //“Extended Material Emissive Record”
        ocExtendedMaterialAlpha                  =   140,  //“Extended Material Alpha Record”
        ocExtendedMaterialLightMap               =   141,  //“Extended Material Light Map Record”
        ocExtendedMaterialNormalMap              =   142,  //“Extended Material Normal Map Record”
        ocExtendedMaterialBumpMap                =   143,  //“Extended Material Bump Map Record”
        ocReserved144                            =   144,  //“reserved"
        ocExtendedMaterialShadowMap              =   145,  //“Extended Material Shadow Map Record”
        ocReserved146                            =   146,  //“reserved"
        ocExtendedMaterialReflectionMap          =   147,  //“Extended Material Reflection Map Record”
        ocExtensionGuidPalette                   =   148,  //“Extension GUID Palette Record”
        ocExtensionFieldBoolean                  =   149,  //“Extension Field Boolean Record”
        ocExtensionFieldInteger                  =   150,  //“Extension Field Integer Record”
        ocExtensionFieldFloat                    =   151,  //“Extension Field Float Record”
        ocExtensionFieldDouble                   =   152,  //“Extension Field Double Record”
        ocExtensionFieldString                   =   153,  //“Extension Field String Record”
        ocExtensionFieldXmlString                =   154   //“Extension Field XML String Record”
    };


    enum obSoleteOpCode
    {
        oocLevelofDetail                   = 3 ,     //(single precision floating point, replaced by Opcode 73)
        oocVertexWithId                    = 6 ,     //(scaled integer coordinates, replaced by Opcodes 68-71)
        oocShortVertexWhitoutId            = 7 ,     //(scaled integer coordinates, replaced by Opcodes 68-71)
        oocVertexWithColor                 = 8 ,     //(scaled integer coordinates, replaced by Opcodes 68-71)
        oocVertexWithColorAndNormal        = 9 ,     //(scaled integer coordinates, replaced by Opcodes 68-71)
        oocTranslate12                     = 12,     //(replaced by Opcode 78)
        oocDegreeofFreedom                 = 13,     //(scaled integer coordinates, replaced by Opcode 14)
        oocInstanceReference               = 16,     //(replaced by Opcode 61)
        oocInstanceDefinition              = 17,     //(replaced by Opcode 62)
        oocTranslate40                     = 40,     //(replaced by Opcode 78)
        oocRotateAboutPoint41              = 41,     //(replaced by Opcode 80)
        oocRotateAboutEdge                 = 42,     //(replaced by Opcode 76)
        oocScale43                         = 43,     //(replaced by Opcode 79)
        oocTranslate44                     = 44,     //(replaced by Opcode 78)
        oocScaleNonuniform                 = 45,     //(replaced by Opcode 79)
        oocRotateAboutPoint46              = 46,     //(replaced by Opcode 80)
        oocRotateAndScaleToPoint           = 47,     //(replaced by Opcode 81)
        oocPut                             = 48,     //(replaced by Opcode 82)
        oocBoundingBox                     = 51,     //(replaced by Opcode 74)
        oocEyepointPalette                 = 65,     //(only eyepoints, replaced by Opcode 83)
        oocMaterialPalette                 = 66,     //(fixed size 64 entries, replaced by Opcode 80)
        oocScale77                         = 77      //(replaced by Opcode 79)
    };

    bool isAncillaryRecord(opCode iOpcode);
    bool isContinuationRecord(opCode iOpcode);
    bool isControlRecord(opCode iOpcode);
    bool isExtendedMaterialPaletteRecord(opCode iOpcode);
    bool isPaletteRecord(opCode iOpcode);
    bool isPrimaryRecord(opCode iOpcode);
    bool isTransformationRecord(opCode iOpcode);
    std::string toString(opCode iOpcode);
    
}






