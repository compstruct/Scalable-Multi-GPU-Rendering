/**************************************************************************
 *
 * Copyright (c) 2002 - 2011 by Computer Architecture Department,
 * Universitat Politecnica de Catalunya.
 * All rights reserved.
 *
 * The contents of this file may not be disclosed to third parties,
 * copied or duplicated in any form, in whole or in part, without the
 * prior permission of the authors, Computer Architecture Department
 * and Universitat Politecnica de Catalunya.
 *
 */

#ifndef ACD_DEVICE_IMP
    #define ACD_DEVICE_IMP

#include "ACDDevice.h"
#include "StateItem.h"
#include "MemoryObjectAllocator.h"
#include "StateItemUtils.h"
#include "GPUDriver.h"
#include "ShaderOptimizer.h"
#include "ACDStoredStateImp.h"
#include "ACDStoredState.h"
#include "StoredStateItem.h"
#include "ACDStoredItemID.h"
#include "ACDTextureCubeMap.h"
#include "ACDTexture2DImp.h"
#include "ACDSampler.h"


#include <vector>
#include <set>
#include <string>


//#define ACD_DUMP_STREAMS
//#define ACD_DUMP_SAMPLERS

class GPUDriver;

namespace acdlib
{

class ACDBlendingStageImp;
class ACDRasterizationStageImp;
class ACDZStencilStageImp;
class ACDStreamImp;
class ACDSamplerImp;
class ACDShaderProgramImp;
class ACDRenderTargetImp;

class ACDDeviceImp : public ACDDevice
{
public:

    ACDDeviceImp(GPUDriver* driver);

    ~ACDDeviceImp();

    virtual acd_uint getNumGPUs() const { return numGPUs; }
    virtual acd_uint getMultiGPUExecMode() const { return multiGPUExecMode; }
    virtual acd_uint getExecRound() const { return execRound; }

    virtual void setOptions(const ACD_CONFIG_OPTIONS& configOptions);

    virtual void setPrimitive(ACD_PRIMITIVE primitive);

    virtual ACDBlendingStage& blending();

    virtual ACDRasterizationStage& rast();

    virtual ACDZStencilStage& zStencil();

    virtual ACDTexture2D* createTexture2D();

    virtual ACDTexture3D* createTexture3D();

    virtual ACDTextureCubeMap* createTextureCubeMap();

    virtual ACDBuffer* createBuffer(acd_uint size, const acd_ubyte* data);

    virtual acd_bool destroy(ACDResource* resourcePtr);

    virtual acd_bool destroy(ACDShaderProgram* shProgram);

    virtual void setResolution(acd_uint width, acd_uint height);

    virtual acd_bool getResolution(acd_uint& width, acd_uint& height);

    virtual ACDStream& stream(acd_uint streamID);

    virtual void enableVertexAttribute(acd_uint vaIndex, acd_uint streamID);
        
    virtual void disableVertexAttribute(acd_uint vaIndex);

    virtual void disableVertexAttributes();

    virtual acd_uint availableStreams() const;

    virtual acd_uint availableVertexAttributes() const;

    virtual void setIndexBuffer( ACDBuffer* ib,
                                 acd_uint offset,
                                 ACD_STREAM_DATA indicesType);

    virtual ACDSampler& sampler(acd_uint samplerID);

    virtual void draw(acd_uint start, acd_uint count, acd_uint instances = 1);
    
    //virtual void draw(acd_uint start, acd_uint count, std::vector<acd_uint> starts, std::vector<acd_uint> counts, acd_uint instances = 1);

    virtual void drawIndexed(acd_uint startIndex, 
                             acd_uint indexCount,
                             acd_uint minIndex,
                             acd_uint maxIndex, 
                             acd_int baseVertexIndex = 0,
                             acd_uint instances = 1);

    //virtual void drawIndexed(acd_uint startIndex, 
    //                         acd_uint indexCount,
    //    		     std::vector<acd_uint> startIndexes, 
    //                         std::vector<acd_uint> indexCounts,
    //                         acd_uint minIndex,
    //                         acd_uint maxIndex, 
    //                         acd_int baseVertexIndex = 0,
    //                         acd_uint instances = 1);

    virtual ACDRenderTarget* createRenderTarget( ACDTexture* resource, const ACD_RT_DIMENSION rtdimension, ACD_CUBEMAP_FACE face, acd_uint mipmap );

    virtual acd_bool setRenderTargets( acd_uint numRenderTargets,
                                   const ACDRenderTarget* const * renderTargets,
                                   const ACDZStencilTarget* zStencilTarget );
                                   
    virtual acd_bool setRenderTarget(acd_uint indexRenderTarget, ACDRenderTarget *renderTarget);
    
    virtual acd_bool setZStencilBuffer(ACDRenderTarget *renderTarget);
    
    virtual ACDRenderTarget *getRenderTarget(acd_uint indexRenderTarget);
    
    virtual ACDRenderTarget *getZStencilBuffer();

    virtual void updateResource( const ACDResource* destResource,
                                 acd_uint destSubResource, 
                                 const ACD_BOX* destRegion,
                                 const acd_ubyte* srcData,
                                 acd_uint srcRowPitch,
                                 acd_uint srcDepthPitch );

    virtual acd_bool swapBuffers();

    virtual void clearColorBuffer(acd_ubyte red, acd_ubyte green, acd_ubyte blue, acd_ubyte alpha);

    virtual void clearZStencilBuffer( acd_bool clearZ,
                                      acd_bool clearStencil,
                                      acd_float zValue,
                                      acd_int stencilValue );

    virtual void clearRenderTarget(ACDRenderTarget* rTarget, 
                                   acd_ubyte red, acd_ubyte green, acd_ubyte blue, acd_ubyte alpha);

    virtual void clearZStencilTarget(ACDZStencilTarget* zsTarget,
                                     acd_bool clearZ,
                                     acd_bool clearStencil,
                                     acd_float zValue,
                                     acd_ubyte stencilValue );

    virtual void copySurfaceDataToRenderBuffer(ACDTexture2D *sourceTexture, acd_uint mipLevel, ACDRenderTarget *destRenderTarget, bool preload);

    virtual void setColorSRGBWrite(acd_bool enable);

    virtual void getShaderLimits(ACD_SHADER_TYPE type, ACD_SHADER_LIMITS* limits);

    virtual ACDShaderProgram* createShaderProgram() const;

    virtual void setGeometryShader(ACDShaderProgram* program);

    virtual void setVertexShader(ACDShaderProgram* program);

    virtual void setFragmentShader(ACDShaderProgram* program);

    virtual void setVertexDefaultValue(acd_float currentColor[4]);

    virtual ACDStoredState* saveState(ACDStoredItemIDList siIds) const;

    virtual ACDStoredState* saveState(ACD_STORED_ITEM_ID stateId) const;

    virtual ACDStoredState* saveAllState() const;

    virtual void destroyState(ACDStoredState* state);

    virtual void restoreState(const ACDStoredState* state);

    virtual void setStartFrame(acd_uint startFrame);

    virtual void DBG_dump(const acd_char* file, acd_enum flags);

    virtual void DBG_deferred_dump(const acd_char* file, acd_enum flags, acd_uint frame, acd_uint batch);

    virtual acd_bool DBG_save(const acd_char* file);

    virtual acd_bool DBG_load(const acd_char* file);

    virtual acd_bool DBG_printMemoryUsage();

    virtual void alphaTestEnabled(acd_bool enabled);

    virtual ACDRenderTarget* getFrontBufferRT();

    virtual ACDRenderTarget* getBackBufferRT();

    virtual void copyMipmap (   ACDTexture* inTexture, 
                                acdlib::ACD_CUBEMAP_FACE inFace, 
                                acd_uint inMipmap, 
                                acd_uint inX, 
                                acd_uint inY, 
                                acd_uint inWidth, 
                                acd_uint inHeight, 
                                ACDTexture* outTexture, 
                                acdlib::ACD_CUBEMAP_FACE outFace, 
                                acd_uint outMipmap, 
                                acd_uint outX, 
                                acd_uint outY,
                                acd_uint outWidth,
                                acd_uint outHeight,
                                acdlib::ACD_TEXTURE_FILTER minFilter,
								acdlib::ACD_TEXTURE_FILTER magFilter);

    virtual void performBlitOperation2D(acd_uint sampler, acd_uint xoffset, acd_uint yoffset,
                                        acd_uint x, acd_uint y, acd_uint width, acd_uint height,
                                        acd_uint textureWidth, ACD_FORMAT internalFormat,
                                        ACDTexture2D* texture, acd_uint level);

    virtual acd_ubyte* compressTexture(ACD_FORMAT originalFormat, ACD_FORMAT compressFormat, acd_uint width, acd_uint height, acd_ubyte* originalData, acd_uint selectionMode);

    // Only available with ACDDeviceImp
    virtual void HACK_setPreloadMemory(acd_bool enablePreload);

    // gpu3d::AGPTransaction* nextAGPTransaction();

    MemoryObjectAllocator& allocator() const;
    GPUDriver& driver() const;

    const StoredStateItem* createStoredStateItem(ACD_STORED_ITEM_ID stateId, acd_uint gpuId = 0) const;

    void restoreStoredStateItem(const StoredStateItem* ssi, acd_uint gpuId = 0);

    ACDStoredState* saveAllDeviceState() const;

    void restoreAllDeviceState(const ACDStoredState* ssi);

    void copyTexture2RenderTarget(ACDTexture2DImp* texture, ACDRenderTargetImp* renderTarget);

    virtual acd_uint getCurrentFrame();

    virtual acd_uint getCurrentBatch();

    void clearROPBufferForComp(acd_bool anyRtBlend, acd_bool anyZTest);

private:

    acd_uint numGPUs;
    acd_uint multiGPUExecMode;
    acd_uint cpdDrawCommBatchSize;
    bool runaheadInGPUpd;
    u32bit execRound;
    gpu3d::exchangedIndexesInGPUpd_t *exchangedIndexesInGPUpd;
    gpu3d::kdTreeIndexesInSortLast_t *kdTreeIndexesInSortLast;
    u32bit minKDTreeInSortLast;
    StateItem<acd_bool> _frameDupInSortLast;
    u32bit lastScheduledGPUId;
    u32bit lastKDTreeId;
    u32bit processedDrawsInCurrentKDTree;
    bool compEnabled;
    
    bool gpupdBatchEnabled;
    u32bit gpupdBatchThreshold;
    u32bit numTrisInCurrentGPUpdBatch;
    u32bit currentGPUpdBatch;
    u32bit firstDrawCommPerGPUpdBatch[2];
    u32bit numDrawsPerGPUpdBatch[2];

    static acd_uint _packRGBA8888(acd_ubyte red, acd_ubyte green, acd_uint blue, acd_uint alpha);
    
    static acd_ubyte defaultVSh[];
    static acd_ubyte defaultFSh[];

    static acd_uint compressionDifference(acd_uint texel, acd_uint compare, acd_uint rowSize, acd_ubyte* data, ACD_FORMAT originalFormat);
    
    ACDShaderProgramImp* _defaultVshProgram;
    ACDShaderProgramImp* _defaultFshProgram;

    void _syncRegisters();

    const acd_uint _MAX_STREAMS;

    const acd_uint _MAX_SAMPLES;

    GPUDriver* _driver;
    MemoryObjectAllocator* _moa;

    StateItem<acd_float> zValuePartialClear;
    ACDBuffer* vertexBufferPartialClear;

    StateItem<ACD_PRIMITIVE> _primitive;

    ACDBlendingStageImp* _blending;
    ACDRasterizationStageImp* _rast;
    ACDZStencilStageImp* _zStencil;

    std::vector<ACDStreamImp*> _stream;
    ACDStreamImp*  _indexStream;
    StateItem<acd_bool> _indexedMode;
    
    /** Vertex indexes in different GPUs. */
    ACDStreamImp**  _indexStreams;
    /** Vertex indexes of each draw commands after cooperative projection and distribution. Runahead execution doubes the memory cost. */
    ACDStreamImp*** _redistributedIndexStreams[2]; 
    /** Memory used to store the GPU IDs that each primitive should be sent to in GPUpd. Runahead execution doubes the memory cost. */
    ACDStreamImp*** _p2gMappings[2]; 

    StateItem<acd_uint> _clearColorBuffer;
    StateItem<acd_float> _zClearValue;
    StateItem<acd_int> _stencilClearValue;

    StateItem<acd_bool> _hzActivated; // HZ enabled (true) or disabled (false)
    acd_bool _hzBufferValid; // Tracks if the current HZ buffer contents are valid or invalid

    std::vector<StateItem<acd_uint> > _streamStart;
    std::vector<StateItem<acd_uint> > _streamCount;
    // Assume _indexMode is false in single-GPU system, and the primitive type is TRIANGLE_FAN
    // The the vertex index order will be like 0, 1, 2, 3, ... 0 is the root vertex of the FAN, other indexes are the vertexes of the fan edge
    // However, in multi-GPUs, the prmitive of FAN will be split into multiple pieces and distributed to different GPUs
    // After split, each piece of the fan will share the same root vertex, but the start vertex of fan edge will be different
    // So we define the _streamStartOfFan to tell Streamer what's the index of the start vertex of fan edge in each GPU
    // If _indexMode is true, _addBaseVertexIndex() copies the root index of fan primitive into _indexStream of each GPU before other vertex indexes
    std::vector<StateItem<acd_uint> > _streamStartOfFan;
    StateItem<acd_uint> _streamInstances;

    // Enables or disables Hierarchical Z test depending on current ACDDevice state
    void _syncHZRegister();

    StateItem<ACDRenderTargetImp *> _defaultBackBuffer;
    StateItem<ACDRenderTargetImp *> _defaultFrontBuffer;
    StateItem<ACDRenderTargetImp *> _defaultZStencilBuffer;
    
    StateItem<ACDRenderTargetImp *> _currentRenderTarget[ACD_MAX_RENDER_TARGETS];
    StateItem<ACDRenderTargetImp *> _currentZStencilBuffer;
    
    StateItem<ACDRenderTargetImp *> _currentRenderTargetForComp[ACD_MAX_RENDER_TARGETS];
    StateItem<ACDRenderTargetImp *> _currentZStencilBufferForComp;
    
    acd_bool _defaultRenderBuffers;
    acd_bool _defaultZStencilBufferInUse;
    acd_uint _mdColorBufferSavedState;
    acd_uint _mdZStencilBufferSavedState;

    StateItem<acd_bool> _colorSRGBWrite;
    
    ACDSamplerImp** _sampler;

    // vertex attribute -> stream
    std::vector<StateItem<acd_uint> > _vaMap;
    std::set<acd_uint> _usedStreams;

    std::vector<StateItem<acd_bool> > _vshOutputs;
    std::vector<StateItem<acd_bool> > _fshInputs;

    StateItem<acd_uint> _vshResources;
    StateItem<acd_uint> _fshResources;

    StateItem<ACDShaderProgramImp*> _gsh;
    acd_uint _gpuMemGshTrack;
    
    StateItem<ACDShaderProgramImp*> _vsh;
    acd_uint _gpuMemVshTrack;

    StateItem<ACDShaderProgramImp*> _fsh;
    acd_uint _gpuMemFshTrack;

    // The shader optimizer module
    acdlib_opt::ShaderOptimizer _shOptimizer;

    // Frame and batch tracking.
    acd_uint _startFrame;
    acd_uint _currentFrame;
    acd_uint _currentBatch;
    StateItem<ACDFloatVector4> _currentColor;

    StateItem<acd_bool> _alphaTest;
    StateItem<acd_bool> _earlyZ;

    // Deferred dump structures
    struct DumpEventInfo
    {
        std::string fileName;
        acd_enum flags;
        acd_uint frame;
        acd_uint batch;
        acd_bool valid;
        
        DumpEventInfo()
            : fileName(""), flags(0), frame(0), batch(0), valid(false) {;}

        DumpEventInfo(const acd_char* file, acd_enum flags, acd_uint frame, acd_uint batch)
            : fileName(file), flags(flags), frame(frame), batch(batch), valid(true) {;}

        bool operator ==(const DumpEventInfo& val)    {    return ((frame == val.frame) && (batch == val.batch));    }
    };

    std::list<DumpEventInfo> _dumpEventList;
    
    DumpEventInfo _nextDumpEvent;

    const char* primitiveString(ACD_PRIMITIVE primitive);

    // called just before issue a draw command
    void _syncStreamerState(bool frameDup, std::vector<acd_uint> copyCounts);

    acd_uint _requiredSync;

    void _syncVertexShader();
    void _syncFragmentShader();

    void _optimizeShader(ACDShaderProgramImp* shProgramImp, ACD_SHADER_TYPE shType);

    void _syncStreamingMode(std::vector<acd_uint> start, std::vector<acd_uint> count, std::vector<acd_uint> startOfFan,
		            acd_uint instances, acd_uint min, acd_uint max,
			    std::vector<acd_uint> copyPrimitives, acd_uint totalPrimitives);

    void _partialClear(acd_bool clearColor, acd_bool clearZ, acd_bool clearStencil, 
                       acd_ubyte red, acd_ubyte green, acd_ubyte blue, acd_ubyte alpha,
                       acd_float zValue, acd_int stencilValue);
    
    // Generic draw command
    void _draw(acd_uint start, acd_uint count,
	       acd_uint min, acd_uint max,
               acd_uint baseVertexIndex = 0,
               acd_uint instances = 1);
	       //std::vector<acd_uint> starts, std::vector<acd_uint> counts,

    acd_uint _getPrimitiveCount(ACD_PRIMITIVE primitive, acd_uint vertexCount);
    acd_uint _getVertexCount(ACD_PRIMITIVE primitive, acd_uint primitiveCount);
    acd_uint _getTriangleCount(ACD_PRIMITIVE primitive, acd_uint primitiveCount);
    acd_uint _getStartVertex(ACD_PRIMITIVE primitive, acd_uint indexStreamStart, acd_uint primitiveIndex);

    void _addBaseVertexIndex(acd_uint gpuId, acd_uint baseVertexIndex, acd_uint indexStreamStart,
		             acd_uint copyStart, acd_uint copyCount, acd_bool compMode, acd_bool anyRtBlend);

    void _syncSamplerState(bool frameDup, std::vector<acd_uint> copyCounts);

    void _translatePrimitive(ACD_PRIMITIVE primitive, gpu3d::GPURegData* data);

    void _syncRenderBuffers();

    bool _multipleRenderTargetsSet();

    acd_uint _numActiveRenderTargets();

    // Dump state
    void _dump(const acd_char* file, acd_enum flags);

    void _check_deferred_dump();

    // Printer help classes

    class PrimitivePrint : public PrintFunc<ACD_PRIMITIVE>
    {
    public:

        virtual const char* print(const ACD_PRIMITIVE& var) const;
    }
    primitivePrint;


}; // class ACDDeviceImp

} // namespace acdlib


#endif // ACD_DEVICE_IMP
