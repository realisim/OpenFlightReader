
#include <cassert>
#include <fstream>
#include <iostream>
#include "OpCode.h"
#include "OpenFlightReader.h"
#include <regex>
#include <sstream>
#include "StreamUtilities.h"

using namespace std;
using namespace OpenFlight;

namespace
{
    string extractFilename(const std::string& iFilenamePath)
    {
        string r;
        size_t p = iFilenamePath.find_last_of("/\\");
        r = iFilenamePath.substr(p+1, string::npos);
        return r;
    }
    
    string extractPath(const std::string& iFilenamePath)
    {
        string r;
        size_t p = iFilenamePath.find_last_of("/\\");
        r = iFilenamePath.substr(0, p+1);
        return r;
    }
    
    // returns true, if the path is absolute.
    // 1- starting with a letter followed by a colon on Windows (d:\...)
    // 2- starting with a '/' on unix
    bool isPathAbsolute( const string& iPath )
    {
        regex e("^[a-zA-z]+:|^[\\/]+");
        smatch sm;
        regex_search(iPath, sm, e);
        return sm.size() > 0;
    }
    
    string makePathRelativeTo(const string iPathToRelativize, const string iReferencePath)
    {
        string r = iPathToRelativize;
        
        if( isPathAbsolute(r) )
        {
            // not implemented yet...
        }
        
        return r;
    }
}

//-----------------------------------------------------------------------------
OpenFlightReader::OpenFlightReader() :
mErrors(),
mProgressData(),
mpProgressFunction(nullptr),
mpProgressUserData(nullptr),
mpRootNode(nullptr),
mReadState(),
mReadStateStack()
{}

//-----------------------------------------------------------------------------
OpenFlightReader::~OpenFlightReader()
{}

//-----------------------------------------------------------------------------
void OpenFlightReader::addError(const std::string& iE) const
{
    mErrors += hasErrors() ? "\n" + iE : iE;
}

//-----------------------------------------------------------------------------
void OpenFlightReader::addPrimaryRecord(PrimaryRecord* iPr)
{
    if(getCurrentParentNode() != nullptr)
    {
        getCurrentParentNode()->addChild(iPr);
    }

    setLastPrimaryNodeAdded(iPr);
}

//-----------------------------------------------------------------------------
void OpenFlightReader::addWarning(const std::string& iW) const
{
    if(!iW.empty())
    { mWarnings.insert(iW); }
}

//-----------------------------------------------------------------------------
void OpenFlightReader::clear()
{
    mErrors = string();
    mWarnings.clear();

    mProgressData = ProgressData();
    
    mpRootNode = nullptr;
    mReadState = ReadState();
    mExternalReferences.clear();
    
    //clear the stack
    while ( !mReadStateStack.empty() )
    { mReadStateStack.pop(); }
}

//-----------------------------------------------------------------------------
std::string OpenFlightReader::getAndClearLastErrors() const
{
    string r = mErrors;
    mErrors.clear();
    return r;
}

//-----------------------------------------------------------------------------
std::string OpenFlightReader::getAndClearLastWarnings() const
{
    string r;
    auto it = mWarnings.begin();
    for(; it != mWarnings.end(); ++it)
    {
        r += *it + "\n";
    }
    mWarnings.clear();
    return r;
}

//-----------------------------------------------------------------------------
HeaderRecord* OpenFlightReader::getCurrentHeaderNode()
{ return mReadState.mpCurrentHeaderNode; }

//-----------------------------------------------------------------------------
PrimaryRecord* OpenFlightReader::getCurrentParentNode()
{ return mReadState.mpCurrentParentNode; }

//-----------------------------------------------------------------------------
PrimaryRecord* OpenFlightReader::getLastPrimaryNodeAdded()
{ return mReadState.mpLastPrimaryNodeAdded; }

//-----------------------------------------------------------------------------
string OpenFlightReader::getFilePath() const
{ return mReadState.mFilePath; }

//-----------------------------------------------------------------------------
string OpenFlightReader::getFilename() const
{ return mReadState.mFilename; }

//-----------------------------------------------------------------------------
string OpenFlightReader::getFilenamePath() const
{ return mReadState.mFilenamePath; }

//-----------------------------------------------------------------------------
uint32_t OpenFlightReader::getNumberOfRecordParsed() const
{
    return mProgressData.mNumberOfRecordParsed;
}

//-----------------------------------------------------------------------------
const OpenFlightReader::Options& OpenFlightReader::getOptions() const
{ return mOptions; }

//-----------------------------------------------------------------------------
bool OpenFlightReader::hasErrors() const
{ return !mErrors.empty(); }

//-----------------------------------------------------------------------------
bool OpenFlightReader::hasWarnings() const
{ return !mWarnings.empty(); }

//-----------------------------------------------------------------------------
// This fonction will return the root node (always a HeaderRecord) of the flt
// structure defined in file iFileNamePath.
//
// The function can return a nullptr if no flt is found or if cancellation
// is requested.
//
HeaderRecord* OpenFlightReader::open(const std::string& iFileNamePath)
{
    clear();
    // prepare
    // here we open all files to count the number of record will
    // need to be parsed.
    //
    mProgressData.mActivity = ProgressData::aPreparing;
    open(iFileNamePath, false);
    
    // now that we gathered all preparation data, lets
    // clear, but save the current progress data first
    //
    ProgressData temp = mProgressData;
    clear();
    mProgressData = temp;

    // now really open the thing...
    mProgressData.mActivity = ProgressData::aParsing;
    open(iFileNamePath, false);

    mProgressData.mActivity = ProgressData::aDone;
    updateProgress();

    // if cancellation was requested, delete everything
    //
    if (mProgressData.mRequestForCancellation)
    {
        clear();
    }
    return mpRootNode;
}

//-----------------------------------------------------------------------------
void OpenFlightReader::open(const std::string& iFileNamePath,
                                    bool iIsExternalReference )
{
    
//Avant toute chose, on devrait s'assurer que le filenamepath n'a pas déja
//été ouvert (genre un extRef). Si c'est le cas, on devrait tout simplement
//retourner le noeud deja existant... Un telle pratique demandera d'ajouter
//un compte de reference (shared_ptr) au PrimaryRecord afin de gerer correctement la destruction.
//
//De plus pour comparer les filenamePath, il faudra un methode pour transformer
//un path en path canonique. (genre QFileInfo);
    mProgressData.mCurrentFileBeingProcessed = iFileNamePath;

    // first lets separate the filename from the path.
    // hum... we could keep only mFilenamePath and call
    // the methods for mFilenae and mFilepath...
    //
    mReadState.mFilenamePath = iFileNamePath;
    mReadState.mFilename = extractFilename(iFileNamePath);
    mReadState.mFilePath = extractPath(iFileNamePath);
    
    // Parse the file
    ifstream ifs;
    ifs.open(iFileNamePath, ifstream::in | ios_base::binary);

    if (!ifs.fail())
    {
        while (ifs.good() && 
               !ifs.eof() &&
               !hasErrors() &&
               !mProgressData.mRequestForCancellation)
        { 
            readRecord(ifs);
            updateProgress();
        }
    }
    else
    {
        ostringstream oss;
        oss << "OpenFlightReader::open - Could not open file " << iFileNamePath << "\n";
        
        // if not an external reference, it means it is a top level file.
        // If a top level file was not open, we flag it as an error.
        // If it is an external reference, then we simply report as a warning
        // that the file could not be open. The idea, is that we do not want
        // to cancel the opening of an flt file is an external ref is missing...
        //
        if(!iIsExternalReference)
        { addError( oss.str() ); }
        else
        { addWarning( oss.str() ); }
    }
    
    ifs.close();
    
    
//finalize!!! l'idée est de résoudre les dépendance un peu bizarre afin
//de rendre l'interface plus conviviale... Par exemple, les vertexList
//on des byteOffset dans la vertexPalette... Il devrait plutot contenir directement
//l'index dans la palette. Il doit y avoir d'autre truc du genre qui pourrait etre
//finalisé...
}

//-----------------------------------------------------------------------------
void OpenFlightReader::parseExternalReferenceRecord(std::ifstream& iRawRecord)
{
    if( getOptions().mDebugEnabled )
    {printf("--- External reference begins ---\n\n");}
    
    ExternalReferenceRecord *extRef = new ExternalReferenceRecord(getCurrentParentNode());
    ((Record*)extRef)->parseRecord(iRawRecord, getCurrentHeaderNode()->getFormatRevision());
    

    string relativeFilenamePath = extRef->getFilenamePath();
    // External reference filenamePath should always be relative.
    // In order to locate the file on disk, we prepend the relative
    // path with the current filePath (see getFilePath() and ReadState).
    //
    // Sometimes, the external ref filename path is aboslute, we will
    // try to make it relative to the current filePath...
    
    if( isPathAbsolute( relativeFilenamePath ) )
    {
        ostringstream oss;
        oss << "An absolute path was found while parsing an external reference: \n" <<
        relativeFilenamePath;
        addWarning(oss.str());
        
        relativeFilenamePath = makePathRelativeTo( relativeFilenamePath, getFilePath() );
    }
    const string filenamePath = getFilePath() + relativeFilenamePath;
    
    // try to insert the filename path into the map of already parsed
    // external refs.
    // If the external ref has already been parse, we will reuse it.
    //
    auto insertFileIt = mExternalReferences.insert( make_pair( filenamePath, extRef ) );
    const bool fileAlreadyParsed = !insertFileIt.second;
    //printf("external ref %s insert state: %d\n", filenamePath.c_str(), fileAlreadyParsed);
    
    if( !fileAlreadyParsed )
    {
        addPrimaryRecord(extRef);
        
        // Here, we push the read state because we are about
        // to call OpenFlightReader::open() again. A call to open
        // will break the internal reading state of the object. By
        // pushing right before and poping right after, we are
        // able to keep our internal reading state.
        //
        pushReadState();
        
        // We force a push level so all nodes comming from the external ref will be
        // properly parented to the external ref node.
        //
        pushLevel();
        
        // opening a specific node from an external ref is not
        // yet supported...
        //
        if( extRef->getNodeName().empty() )
        {
            //skip external reference content if so desired.
            if( getOptions().mExternalReferenceLoadingEnabled )
            { open( filenamePath, true ); }
            else if( getOptions().mDebugEnabled )
            { printf("--- External reference content skipped; hasExternalReferenceLoadingEnabled is false ---\n\n"); }
        }
        else
        {
            ostringstream oss;
            oss << "Loading a specific node from an external reference is not " <<
            "supported. This was encountered in file: \n" <<
            "\t" << getFilenamePath() << "\n With external reference: \n" <<
            "\t" << extRef->getFilenamePath() << " node: " << extRef->getNodeName() << endl;
            addError( oss.str() );
        }
        
        popReadState();
        
    }
    else
    {
        // reuse already existing ext ref
        //
        delete extRef;
        extRef = insertFileIt.first->second;
        extRef->incrementUseCount();
        addPrimaryRecord(extRef);
    }
    
    
    // Maybe we should apply the palettes, accordingly with the flags
    // from the external ref, to the HeaderRecord that was just added.
    if( getOptions().mDebugEnabled )
    {printf("--- External reference ends ---\n\n");}
}

//-----------------------------------------------------------------------------
void OpenFlightReader::parseHeaderRecord(std::ifstream& iRawRecord)
{
    HeaderRecord *r = new HeaderRecord(getCurrentParentNode());
    ((Record*)r)->parseRecord( iRawRecord, 0 );
    
    // additionnaly, we store the path to the file (filePath and filenamePath)
    // were this HeaderRecord was loaded from. This will be useful when reading
    // back information such as the textureRecord's filename.
    // This filename is relative to the db...
    r->setFileInfo( getFilenamePath(), getFilePath(), getFilename() );
    
    // If there is no root node, it means the header record
    // encountered here is the first node of all document.
    // We need to initialize the root node and the current
    // primary node.
    //
    if (mpRootNode == nullptr)
    {
        mpRootNode = r;
    }
    
    // this should be revisited... It appears it is only needed
    // to access the current format revision while parsing...
    // If it is the case, it should be replaced by the
    // format revision...
    //
    setCurrentHeaderNode(r);
    addPrimaryRecord(r);
}

//-----------------------------------------------------------------------------
void OpenFlightReader::parseUnsupportedRecord(std::ifstream& iRawRecord)
{
    UnsupportedRecord* r = new UnsupportedRecord( getCurrentParentNode() );
    ((Record*)r)->parseRecord(iRawRecord, 0);
    
    ostringstream oss;
    oss << "Record type '" << OpCodeUtils::toString(r->getOriginalOpCode()) << "' was found but is not yet supported.";

    if(OpCodeUtils::isPrimaryRecord( r->getOriginalOpCode() ) )
    { addPrimaryRecord(r); }
    else
    {
        // we do not care much about unsupported record that are not
        // a primary record since it has no child.
        // Not having them in the tree will not break
        // the structure, so we delete it.
        delete r;
    }
    
    addWarning( oss.str() );
}

//-----------------------------------------------------------------------------
void OpenFlightReader::parseRawRecord(uint16_t iOpCode, ifstream& iRawRecord)
{
    switch (iOpCode)
    {
        case ocHeader: parseHeaderRecord(iRawRecord); break;
        case ocGroup: parsePrimaryRecord<GroupRecord>(iRawRecord); break;
        case ocObject: parsePrimaryRecord<ObjectRecord>(iRawRecord); break;
        case ocFace: parsePrimaryRecord<FaceRecord>(iRawRecord); break;        
        case ocPushLevel: pushLevel(); break;
        case ocPopLevel: popLevel(); break;
        case ocDegreeofFreedom: parsePrimaryRecord<DegreeOfFreedomRecord>(iRawRecord); break;
        case ocComment: parseAncillaryRecord<CommentRecord>(iRawRecord); break;
        case ocColorPalette: parseAncillaryRecord<ColorPaletteRecord>(iRawRecord); break;
        case ocLongId: parseAncillaryRecord<LongIdRecord>(iRawRecord); break;
        case ocMatrix: parseAncillaryRecord<MatrixRecord>(iRawRecord); break;
        case ocMultitexture: parseAncillaryRecord<MultiTextureRecord>(iRawRecord); break;
        case ocUvList: parseAncillaryRecord<UvListRecord>(iRawRecord); break;
        case ocExternalReference: parseExternalReferenceRecord(iRawRecord); break;
        case ocTexturePalette: parseAncillaryRecord<TexturePaletteRecord>(iRawRecord); break;
        case ocMaterialPalette: parseAncillaryRecord<MaterialPaletteRecord>(iRawRecord); break;
        case ocVertexPalette: parseAncillaryRecord<VertexPaletteRecord>(iRawRecord); break;
        case ocVertexWithColor:
        case ocVertexWithColorAndNormal:
        case ocVertexWithColorNormalAndUv:
        case ocVertexWithColorAndUv:
            if(!getOptions().mVertexDataSkipped)
            { parseVertexPaletteEntry(iRawRecord); }
            break;
        case ocSwitch: parsePrimaryRecord<SwitchRecord>(iRawRecord); break;
        case ocVertexList: parsePrimaryRecord<VertexListRecord>(iRawRecord); break;
        case ocLevelOfDetail: parsePrimaryRecord<LevelOfDetailRecord>(iRawRecord); break;
        case ocTranslate: parseAncillaryRecord<TranslateRecord>(iRawRecord); break;
        case ocLightSourcePalette: parseAncillaryRecord<LightSourcePaletteRecord>(iRawRecord); break;
        case ocLightPointAppearancePalette: parseAncillaryRecord<LightPointAppearancePaletteRecord>(iRawRecord); break;
        case ocLightPointAnimationPalette: parseAncillaryRecord<LightPointAnimationPaletteRecord>(iRawRecord); break;
        case ocIndexedLightPoint: parsePrimaryRecord<IndexedLightPointRecord>(iRawRecord); break;
        case ocIndexedString: parseAncillaryRecord<IndexedStringRecord>(iRawRecord); break;
    default: parseUnsupportedRecord(iRawRecord); break;
    }   
}

//-----------------------------------------------------------------------------
void OpenFlightReader::parseVertexPaletteEntry(std::ifstream& iRawRecord)
{
    // these are added to the vertex palette of the current header node
    // As stated by the specification, Vertex in the Vertex palette
    // entry will be referenced by Vertex List, Morph List ...
    //
    
    VertexPaletteRecord *r = getCurrentHeaderNode()->getVertexPalette();
    if(r)
    {
        r->addVertexRawRecord(iRawRecord);
    }
    else{ addError("Vertex palette entry was found prior defining a Vertex Palette..."); }
}

//-----------------------------------------------------------------------------
void OpenFlightReader::popLevel()
{
    if( getCurrentParentNode() && getCurrentParentNode()->getParent() != nullptr )
    {
        //By construction, the parent of a primary record is a primary record.
        //see method addPrimaryRecord. Given that, we simply cast the parent
        //of the current primary record in a PrimaryRecord*.
        //
        setCurrentPrimaryNode( (PrimaryRecord*)getCurrentParentNode()->getParent() );
    }
}

//-----------------------------------------------------------------------------
void OpenFlightReader::popReadState()
{
    mReadState = mReadStateStack.top();
    mReadStateStack.pop();
}

//-----------------------------------------------------------------------------
// This method will move us down 1 level into the hierachy. Every node between
// a push/pop are sibling. Please refer to documentation
//
void OpenFlightReader::pushLevel()
{
    if(getCurrentParentNode() != nullptr)
    {
        // set last child of parent as current primary node.
        // This effectively moves us down one level.
        //
        PrimaryRecord* p = getCurrentParentNode();
        if( p->getNumberOfChilds() > 0 )
        { setCurrentPrimaryNode( p->getChild( p->getNumberOfChilds() - 1 ) ); }
    }
    else
    {
        setCurrentPrimaryNode( getCurrentHeaderNode() );
    }
}

//-----------------------------------------------------------------------------
void OpenFlightReader::pushReadState()
{ mReadStateStack.push(mReadState); }

//-----------------------------------------------------------------------------
void OpenFlightReader::readRecord(ifstream& iFileStream)
{
    // read first 4 bytes of records, this will give us the opCode
    // and the length of the record to read.

    // record format
    //
    // |  2 bytes |  2 bytes       |  lengthOfRecord - 4 |
    // |  opCode  | LengthOfRecord |  recordPayload      | 
    //

    bool ok = true;
    uint16_t opCode = 0;
    uint16_t lengthOfRecord = 0;
    std::streamoff startOfRecord = iFileStream.tellg();
    ok &= readUint16(iFileStream, opCode);
    ok &= readUint16(iFileStream, lengthOfRecord);
    
    if (ok)
    {
        // we have found a record...
        // lets move back at the beginning of the record
        // to read cleanly the whole thing
        //
        
        iFileStream.seekg( startOfRecord );
        if( iFileStream.good() )
        {
            if( getOptions().mDebugEnabled )
            {
                ostringstream oss;
                oss << OpCodeUtils::toString((OpenFlight::opCode)opCode) << endl;
                oss << rawRecordToString(iFileStream, lengthOfRecord) << endl << endl;
                cout << oss.str();
            }

            if(mProgressData.mActivity == ProgressData::aPreparing)
            {
                mProgressData.mTotalNumberOfRecordToParse++;
                
                // parse only header and ext ref record, 
                // so we dig into the hierarchy to count all required records.
                //
                if( opCode == ocHeader ||
                    opCode == ocExternalReference)
                { parseRawRecord( opCode, iFileStream ); }
            }
            else
            {
                parseRawRecord( opCode, iFileStream );

                mProgressData.mNumberOfRecordParsed++;
            }
            
            // make sure we go to next record, even if the current record parsing
            // broked the fstream.
            //
            iFileStream.seekg(startOfRecord + lengthOfRecord);
        }
        else
        {
            ostringstream oss;
            oss << "OpenFlightReader::readRecord - Could not read record with opCode " << opCode <<
                " . " << lengthOfRecord << " bytes were requested, only " << iFileStream.gcount() << " could be read." ;
            addError( oss.str() );
        }
    }
    
    // when reaching eof, ok will be false (see istream documentation about eof, mostly due because
    // eof is set when trying to read pass the end...)
    //
    if( !ok && !iFileStream.eof() )
    { 
        ostringstream oss;
        oss << "OpenFlightReader::readRecord - Could not read record header with opCode " << opCode;
        addError( oss.str() );
    }
}

//-----------------------------------------------------------------------------
// iOpCode is in decimal
// iPayload is in hexadecimal at this point and not yet parsed.
//
string OpenFlightReader::rawRecordToString(ifstream& iRawRecord, int iRecordLength) const
{
    // keep the current position
    std::streamoff currentPos = iRawRecord.tellg();
    
    // read the record
    string record;
    readBytes(iRawRecord, iRecordLength, record);
    
    string hexPayload;
    char hex[5];
    for(size_t i = 0; i < record.size(); ++i)
    { 
        sprintf(hex, "[%02X]", (unsigned char)record[i]);
        hexPayload += hex;
    }

    ostringstream oss;
    oss << "Raw Record (hex):" << hexPayload;

    // move back the stream cursor in place
    iRawRecord.seekg(currentPos);
    
    return oss.str();
}

//-----------------------------------------------------------------------------
void OpenFlightReader::setCurrentHeaderNode(HeaderRecord* ipR)
{ mReadState.mpCurrentHeaderNode = ipR; }

//-----------------------------------------------------------------------------
void OpenFlightReader::setCurrentPrimaryNode(PrimaryRecord* ipR)
{ mReadState.mpCurrentParentNode = ipR; }

//-----------------------------------------------------------------------------
void OpenFlightReader::setLastPrimaryNodeAdded(PrimaryRecord* ipR)
{ mReadState.mpLastPrimaryNodeAdded = ipR; }

//-----------------------------------------------------------------------------
void OpenFlightReader::setOptions(Options iO)
{ mOptions = iO; }

//-----------------------------------------------------------------------------
void OpenFlightReader::setProgressCallback(ProgressFunction iPf, void *ipUserData)
{
    mpProgressFunction = iPf;
    mpProgressUserData = ipUserData;
}

//-----------------------------------------------------------------------------
void OpenFlightReader::updateProgress()
{
    if (mpProgressFunction)
    {
        bool callUpdate = true;

        switch (mProgressData.mActivity)
        {
            case ProgressData::aPreparing: 
                callUpdate = mProgressData.mTotalNumberOfRecordToParse % 1000 == 0;
                break;

            case ProgressData::aParsing: 
                callUpdate = mProgressData.mNumberOfRecordParsed % 1000 == 0;
                break;

            default: break;
        }

        if (callUpdate)
        {
            // set the request cancellation in function of the return value
            //
            mProgressData.mRequestForCancellation = !(*mpProgressFunction)(mProgressData, mpProgressUserData);
        }
    }
}

//-----------------------------------------------------------------------------
//--- OpenFlightReader::Options
//-----------------------------------------------------------------------------
OpenFlightReader::OpenFlightReader::Options::Options() :
mDebugEnabled(false),
mExternalReferenceLoadingEnabled(true),
mVertexDataSkipped(false)
{}


