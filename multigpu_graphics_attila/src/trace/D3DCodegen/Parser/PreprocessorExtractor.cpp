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

#include "Parser/PreprocessorExtractor.hpp"

using namespace std;
using namespace regex;
using namespace dxcodegen::Parser;

////////////////////////////////////////////////////////////////////////////////

const rpattern patro_prepro_ifdef("^(\\s*#ifdef\\s+)(.*?)$", "", MULTILINE | GLOBAL | NOBACKREFS);
const rpattern patro_prepro_ifndef("^(\\s*#ifndef\\s+)(.*?)$", "", MULTILINE | GLOBAL | NOBACKREFS);
const rpattern patro_prepro_else("^(\\s*#else\\s*)$", "", MULTILINE | GLOBAL | NOBACKREFS);
const rpattern patro_prepro_endif("^(\\s*#endif\\s*)$", "", MULTILINE | GLOBAL | NOBACKREFS);
const rpattern patro_prepro_define("^(\\s*#define\\s+)(.*?)$", "", MULTILINE | GLOBAL | NOBACKREFS);
const rpattern patro_prepro_if("^(\\s*#if\\s*)(.*?)$", "", MULTILINE | GLOBAL | NOBACKREFS);
const rpattern patro_prepro_include("^(\\s*#include\\s+)(.*?)$", "", MULTILINE | GLOBAL | NOBACKREFS);
const rpattern patro_prepro_undef("^(\\s*#undef\\s+)(.*?)$", "", MULTILINE | GLOBAL | NOBACKREFS);
const rpattern patro_prepro_pragma("^(\\s*#pragma\\s+)(.*?)$", "", MULTILINE | GLOBAL | NOBACKREFS);

////////////////////////////////////////////////////////////////////////////////

PreprocessorExtractor::PreprocessorExtractor(string& cadena) :
IExtractor(cadena)
{
}

////////////////////////////////////////////////////////////////////////////////

PreprocessorExtractor::MatchResults PreprocessorExtractor::Match(string& cadena)
{
  MatchResults resultat;
  subst_results results;

  if (patro_prepro_ifdef.substitute(cadena, results) > 0)
  {
    resultat.matched = true;
    resultat.text.clear();
    return resultat;
  }

  if (patro_prepro_ifndef.substitute(cadena, results) > 0)
  {
    resultat.matched = true;
    resultat.text.clear();
    return resultat;
  }

  if (patro_prepro_else.substitute(cadena, results) > 0)
  {
    resultat.matched = true;
    resultat.text.clear();
    return resultat;
  }

  if (patro_prepro_endif.substitute(cadena, results) > 0)
  {
    resultat.matched = true;
    resultat.text.clear();
    return resultat;
  }

  if (patro_prepro_define.substitute(cadena, results) > 0)
  {
    resultat.matched = true;
    resultat.text.clear();
    return resultat;
  }

  if (patro_prepro_if.substitute(cadena, results) > 0)
  {
    resultat.matched = true;
    resultat.text.clear();
    return resultat;
  }

  if (patro_prepro_include.substitute(cadena, results) > 0)
  {
    resultat.matched = true;
    resultat.text.clear();
    return resultat;
  }

  if (patro_prepro_undef.substitute(cadena, results) > 0)
  {
    resultat.matched = true;
    resultat.text.clear();
    return resultat;
  }

  if (patro_prepro_pragma.substitute(cadena, results) > 0)
  {
    resultat.matched = true;
    resultat.text.clear();
    return resultat;
  }

  return resultat;
}

////////////////////////////////////////////////////////////////////////////////

void PreprocessorExtractor::Parse(const MatchResults& resultat)
{
}

////////////////////////////////////////////////////////////////////////////////
