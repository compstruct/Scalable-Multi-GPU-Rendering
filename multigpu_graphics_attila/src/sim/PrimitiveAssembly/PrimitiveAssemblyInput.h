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
 * $RCSfile: PrimitiveAssemblyInput.h,v $
 * $Revision: 1.2 $
 * $Author: cgonzale $
 * $Date: 2005-04-26 17:28:51 $
 *
 * Primitive Assembly Input implementation file. 
 *
 */

#ifndef _PRIMITIVEASSEMBLYRINPUT_

#define _PRIMITIVEASSEMBLYINPUT_

#include "support.h"
#include "GPUTypes.h"
#include "DynamicObject.h"

namespace gpu3d
{

/**
 *
 *  This class defines objects that carry transformed vertex
 *  information from the Streamer Commit (output cache) to
 *  the Primitive Assembly unit.
 *
 *  This class inherits from DynamicObject class that provides
 *  basic dynamic memory support and signal tracing capabilities.
 *
 */
 
class PrimitiveAssemblyInput : public DynamicObject
{

private:

    u32bit id;                /**<  Primitive Assembly Input identifier (it uses to be its index).  */
    QuadFloat *attributes;    /**<  Primitive Assembly Input attributes.  */
    QuadFloat *attributes3D;  /**<  Primitive Assembly Input attributes in 3D space.  */

public:

    /**
     *
     *  Primitive Assembly Input constructor.
     *
     *  Creates and initializes a Primitive Assembly input.
     *
     *  @param id The Primitive Assembly input identifier (vertex index).
     *  @param attrib Primitive Assembly input attributes.
     *
     *  @return An initialized Primitive Assembly input.
     *
     */
     
    PrimitiveAssemblyInput(u32bit id, QuadFloat *attrib, QuadFloat *attrib3D);
    
    /**
     *
     *  Gets the Primitive Assembly input identifier (vertex index).
     *
     *  @return The Primitive Assembly input identifier.
     *
     */

    u32bit getID();
    
    /**
     *
     *  Gets the Primitive Assembly input attributes.
     *
     *  @return A pointer to the Primitive Assembly input attribute array.
     *
     */

    QuadFloat *getAttributes();
    
    /**
     *
     *  Gets the Primitive Assembly input attributes in 3D space.
     *
     *  @return A pointer to the Primitive Assembly input attribute array of 3D space.
     *
     */

    QuadFloat *get3DAttributes();
    
};

} // namespace gpu3d

#endif
