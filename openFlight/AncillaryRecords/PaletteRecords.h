#pragma once

#include <map>
#include "AncillaryRecord.h"
#include "Types.h"
#include <vector>

namespace OpenFlight
{
    //-------------------------------------------------------------------------
    class ColorPaletteRecord : public AncillaryRecord
    {
    public:
        ColorPaletteRecord() = delete;
        explicit ColorPaletteRecord(PrimaryRecord* ipParent);
        ColorPaletteRecord(const ColorPaletteRecord&) = delete;
        ColorPaletteRecord& operator=(const ColorPaletteRecord&) = delete;
        virtual ~ColorPaletteRecord() {}

    protected:
        virtual bool parseRecord(std::ifstream& iRawRecord, int iVersion) override;

        std::vector< Color4ub > mColors;
        std::map<std::string, int> mColorNameToIndex;
    };
    
    //-------------------------------------------------------------------------
    class LightSourcePaletteRecord : public AncillaryRecord
    {
    public:
        LightSourcePaletteRecord() = delete;
        explicit LightSourcePaletteRecord(PrimaryRecord* ipParent);
        LightSourcePaletteRecord(const LightSourcePaletteRecord&) = delete;
        LightSourcePaletteRecord& operator=(const LightSourcePaletteRecord&) = delete;
        virtual ~LightSourcePaletteRecord() {}
        
        enum lightType{ltInfinite = 0, ltLocal, ltSpot, ltUndefined};
        
        const Color4f& getAmbient() const;
        float getConstantAttenuationCoefficient() const;
        const Color4f& getDiffuse() const;
        int getIndex() const;
        lightType getLightType() const;
        float getLinearAttenuationCoefficient() const;
        std::string getName() const;
        float getPitch() const;
        float getQuadraticAttenuationCoefficient() const;
        const Color4f& getSpecular() const;
        float getSpotCutoffAngle() const;
        float getSpotExponentialDropoff() const;
        float getYaw() const;
        bool isModelingLight() const;
        
        /*Setters
        void setAmbient(Color3f);
        void setConstantAttenuationCoefficient(float);
        void setDiffuse(Color3f);
        void setIndex(int32_t);
        void setAsModelingLight(bool);
        void setLightType(lightType);
        void setLinearAttenuationCoefficient(float);
        void setName(std::string);
        void setPitch(float);
        void setQuadraticAttenuationCoefficient(float);
        void setSpecular(Color3f);
        void setSpotCutoffAngle(float);
        void setSpotExponentialDropoff(float);
        void setYaw(float);*/
        
    protected:
        virtual bool parseRecord(std::ifstream& iRawRecord, int iVersion) override;
        
        int32_t mIndex;
        std::string mName;
        Color4f mAmbient;
        Color4f mDiffuse;
        Color4f mSpecular;
        lightType mLightType;
        float mSpotExponentialDropoff;
        float mSpotCutoffAngle; //in degree
        float mYaw;
        float mPitch;
        float mConstantAttenuationCoefficient;
        float mLinearAttenuationCoefficient;
        float mQuadraticAttenuationCoefficient;
        bool mIsModelingLight;
    };
    
    //-------------------------------------------------------------------------
    class MaterialPaletteRecord : public AncillaryRecord
    {
    public:
        MaterialPaletteRecord() = delete;
        explicit MaterialPaletteRecord(PrimaryRecord* ipParent);
        MaterialPaletteRecord(const MaterialPaletteRecord&) = delete;
        MaterialPaletteRecord& operator=(const MaterialPaletteRecord&) = delete;
        virtual ~MaterialPaletteRecord() {}
        
        float getAlpha() const;
        const Color3f& getAmbient() const;
        const Color3f& getDiffuse() const;
        const Color3f& getEmissive() const;
        int getFlags() const;
        int getIndex() const;
        std::string getName() const;
        float getShininess() const;
        const Color3f& getSpecular() const;
        
        /*void setAlpha(float);
        void setAmbient(Color3f);
        void setDiffuse(Color3f);
        void setEmissive(Color3f);
        void setFlags(int);
        void setIndex(int);
        void setName(std::string);
        void setShininess(float);
        void setSpecular(Color3f);*/
        
    protected:
        virtual bool parseRecord(std::ifstream& iRawRecord, int iVersion) override;
        
        int32_t mIndex;
        std::string mName;
        int32_t mFlags;
        Color3f mAmbient;
        Color3f mDiffuse;
        Color3f mSpecular;
        Color3f mEmissive;
        float mShininess;
        float mAlpha;
    };
    
    //-------------------------------------------------------------------------
    class VertexPaletteRecord : public AncillaryRecord
    {
    public:
        VertexPaletteRecord() = delete;
        explicit VertexPaletteRecord(PrimaryRecord* ipParent);
        VertexPaletteRecord(const VertexPaletteRecord&) = delete;
        VertexPaletteRecord& operator=(const VertexPaletteRecord&) = delete;
        virtual ~VertexPaletteRecord() {}
        
        bool addVertexRawRecord(std::ifstream& iRawRecord); //protected...
        int getIndexFromByteOffset(int iOffset) const;
        int getNumberOfVertices() const;
        const Vertex& getVertex(int iIndex) const;
        const std::vector<Vertex>& getVertices() const;
        
    protected:
        virtual bool parseRecord(std::ifstream& iRawRecord, int iVersion) override;
        
        int mOffset;
        std::map<int, int> mOffsetToVertexIndex;
        std::vector<Vertex> mVertices;
    };
}