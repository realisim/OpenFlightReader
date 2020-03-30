
#pragma once

#include "types.h"
#include "PrimaryRecord.h"

namespace OpenFlight
{
    //-------------------------------------------------------------------------
    // 
    // Current implementation supports the following version:
    //      15.7 to 16.5
    //
    class OFR_API DegreeOfFreedomRecord : public PrimaryRecord
    {
    public:
        enum dofFlag : int
        {
            dofNoLimit = 0,
            dofXTranslationLimited = (1 << (31-0)),
            dofYTranslationLimited = (1 << (31-1)),
            dofZTranslationLimited = (1 << (31-2)),
            dofPitchLimited = (1 << (31 - 3)),
            dofRollLimited = (1 << (31 - 4)),
            dofYawLimited = (1 << (31 - 5)),
            dofXScaleLimited = (1 << (31-6)),
            dofYScaleLimited = (1 << (31-7)),
            dofZScaleLimited = (1 << (31-8)),
            dofReserved9 = (1 << (31 - 9)),
            dofReserved10 = (1 << (31 - 10))
        };

    public:
        DegreeOfFreedomRecord() = delete;
        explicit DegreeOfFreedomRecord(PrimaryRecord* ipParent);
        DegreeOfFreedomRecord(const DegreeOfFreedomRecord&) = delete;
        DegreeOfFreedomRecord& operator=(const DegreeOfFreedomRecord&) = delete;
        virtual ~DegreeOfFreedomRecord();

        DOFParameter getTranslationXParameter()const;
        DOFParameter getTranslationYParameter()const;
        DOFParameter getTranslationZParameter()const;

        DOFParameter getScaleXParameter()const;
        DOFParameter getScaleYParameter()const;
        DOFParameter getScaleZParameter()const;

        DOFParameter getPitchParameter()const;
        DOFParameter getRollParameter()const;
        DOFParameter getYawParameter()const;

        Vector3d getOrigin()const;
        Vector3d getPointOnX_axis()const;
        Vector3d getPointOnXY_plane()const;

        dofFlag getFlags() const;

        std::string getAsciiId() const;

    protected:
        virtual bool parseRecord(std::ifstream& iRawRecord, int iVersion) override;
        virtual void handleAddedAncillaryRecord(AncillaryRecord*) override;

        std::string mAsciiId;
        
        Vector3d    mOrigin;
        Vector3d    mPointOnXaxis;
        Vector3d    mPointOnXYplane;

        DOFParameter    mTranslationX;
        DOFParameter    mTranslationY;
        DOFParameter    mTranslationZ;

        DOFParameter    mPitch;// pitch = rotation on x-axis
        DOFParameter    mRoll;// roll = rotation on y-axis
        DOFParameter    mYaw;// yaw = rotation on z-axis

        DOFParameter    mScaleX;
        DOFParameter    mScaleY;
        DOFParameter    mScaleZ;

        dofFlag         mFlags;
    };

}