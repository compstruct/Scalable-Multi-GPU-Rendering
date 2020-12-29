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
 * $RCSfile: MemorySpace.h,v $
 * $Revision: 1.2 $
 * $Author: cgonzale $
 * $Date: 2006-06-21 11:43:46 $
 *
 * Memory Space definition file.
 *
 */

/**
 *
 *  @file MemorySpace.h
 *
 *  Memory Space definition file.  Defines masks describing how memory is mapped on the
 *  GPU address space.
 *
 */

#ifndef _MEMORY_SPACE_

#define _MEMORY_SPACE_

#include "GPUTypes.h"


namespace gpu3d
{

/**
 *
 *  Address space for the GPU memory.
 *
 */
static const u64bit GPU_ADDRESS_SPACE = 0x0000000000000000ULL;

/**
 *
 *  Address space for the system memory.
 *
 */
static const u64bit SYSTEM_ADDRESS_SPACE = 0x0000000100000000ULL;

/**
 *
 *  Address space mask.
 *
 */
static const u64bit ADDRESS_SPACE_MASK = 0x0000000100000000ULL;

/**
 *
 *  Address space mask.
 *
 */
static const u64bit SPACE_ADDRESS_MASK = 0x00000000ffffffffULL;

} // namespace gpu3d

#endif
