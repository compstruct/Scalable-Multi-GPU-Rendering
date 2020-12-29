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

////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "stdafx.h"

////////////////////////////////////////////////////////////////////////////////

namespace dxcodegen
{
  namespace Items
  {
    struct MethodDescriptionParam
    {
      std::string type;
      std::string name;
    };
    
    class MethodDescription
    {
    public:

      void SetType(const std::string& type);
      std::string& GetType();

      void SetName(const std::string& name);
      std::string& GetName();

      void AddParam(const MethodDescriptionParam& param);
      unsigned int GetParamsCount();
      MethodDescriptionParam& GetParam(unsigned int position);

    protected:

      std::string m_type;
      std::string m_name;
      std::vector<MethodDescriptionParam> m_lstParams;

    };
  }
}

////////////////////////////////////////////////////////////////////////////////
