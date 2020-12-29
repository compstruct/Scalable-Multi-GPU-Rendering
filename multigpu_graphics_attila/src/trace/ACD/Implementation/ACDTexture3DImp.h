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

#ifndef ACD_TEXTURE3D_IMP
    #define ACD_TEXTURE3D_IMP

#include "ACDTexture3D.h"
#include "TextureMipmapChain.h"
#include "TextureMipmap.h"
#include "MemoryObject.h"
#include <set>

namespace acdlib
{

class ACDTexture3DImp : public ACDTexture3D, public MemoryObject
{
public:

    ACDTexture3DImp();

    /// Methods inherited from ACDResource interface

    virtual void setUsage(ACD_USAGE usage);

    virtual ACD_USAGE getUsage() const;

    virtual void setMemoryLayout(ACD_MEMORY_LAYOUT layout);
    
    virtual ACD_MEMORY_LAYOUT getMemoryLayout() const;
    
    virtual ACD_RESOURCE_TYPE getType() const;

    virtual void setPriority(acd_uint prio);

    virtual acd_uint getPriority() const;

    virtual acd_uint getSubresources() const;

    virtual acd_bool wellDefined() const;

    /// Methods inherited form ACDTexture interface

    virtual acd_uint getBaseLevel() const;

    virtual acd_uint getMaxLevel() const;

    virtual void setBaseLevel(acd_uint minMipLevel);

    virtual void setMaxLevel(acd_uint maxMipLevel);

	virtual acd_uint getSettedMipmaps();

    /// Methods inherited from ACDTexture2D interface

    virtual acd_uint getWidth(acd_uint mipmap) const;

    virtual acd_uint getHeight(acd_uint mipmap) const;
    
    virtual acd_uint getDepth(acd_uint mipLevel) const;

    virtual ACD_FORMAT getFormat(acd_uint mipmap) const;

    virtual acd_bool isMultisampled(acd_uint mipmap) const;
    
    virtual acd_uint getSamples(acd_uint mipmap) const;
    
    virtual acd_uint getTexelSize(acd_uint mipmap) const;

    virtual void setData( acd_uint mipLevel,
                          acd_uint width,
                          acd_uint height,
                          acd_uint depth,
                          ACD_FORMAT format,
                          acd_uint rowPitch,
                          const acd_ubyte* srcTexelData,
                          acd_uint texSize,
                          acd_bool preloadData = false);

    virtual void setData(acd_uint mipLevel,
                         acd_uint width,
                         acd_uint height,
                         acd_uint depth,
                         acd_bool multisampling,
                         acd_uint samples,
                         ACD_FORMAT format);

    virtual void updateData( acd_uint mipLevel,
                             acd_uint x,
                             acd_uint y,
                             acd_uint z,
                             acd_uint width,
                             acd_uint height,
                             acd_uint depth,
                             ACD_FORMAT format,
                             acd_uint rowPitch,
                             const acd_ubyte* srcTexelData,
                             acd_bool preloadData = false);

    virtual acd_bool map( acd_uint mipLevel,
                      ACD_MAP mapType,
                      acd_ubyte*& pData,
                      acd_uint& dataRowPitch,
                      acd_uint& dataPlanePitch);

    virtual acd_bool unmap(acd_uint mipLevel, acd_bool preloadData = false);

    /// Method required by MemoryObject derived classes
    virtual const acd_ubyte* memoryData(acd_uint region, acd_uint& memorySizeInBytes) const;

    virtual const acd_char* stringType() const;

    void dumpMipmap(acd_uint region, acd_ubyte* mipName);

    const acd_ubyte* getData(acd_uint mipLevel, acd_uint& memorySizeInBytes, acd_uint& rowPitch, acd_uint& planePitch) const;

    virtual void setSamplerID(acd_int id) { samplerID = id; }
    virtual acd_int getSamplerID() const { return samplerID; }


private:

    const TextureMipmap* _getMipmap(acd_uint mipLevel, const acd_char* methodStr) const;

    acd_uint _baseLevel;
    acd_uint _maxLevel;
    TextureMipmapChain _mips;
    std::set<acd_uint> _mappedMips;
    
    ACD_MEMORY_LAYOUT layout;
    
    acd_int samplerID;
}; // class ACDTexture3DImp


}

#endif // ACD_TEXTURE3D_IMP
