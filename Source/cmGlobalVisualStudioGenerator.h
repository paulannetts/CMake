/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef cmGlobalVisualStudioGenerator_h
#define cmGlobalVisualStudioGenerator_h

#include "cmGlobalGenerator.h"

/** \class cmGlobalVisualStudioGenerator
 * \brief Base class for global Visual Studio generators.
 *
 * cmGlobalVisualStudioGenerator provides functionality common to all
 * global Visual Studio generators.
 */
class cmGlobalVisualStudioGenerator : public cmGlobalGenerator
{
public:
  cmGlobalVisualStudioGenerator();
  virtual ~cmGlobalVisualStudioGenerator();

  /**
   * Basic generate implementation for all VS generators.
   */
  virtual void Generate();

  /**
   * Configure CMake's Visual Studio macros file into the user's Visual
   * Studio macros directory.
   */
  virtual void ConfigureCMakeVisualStudioMacros();

  /**
   * Where does this version of Visual Studio look for macros for the
   * current user? Returns the empty string if this version of Visual
   * Studio does not implement support for VB macros.
   */
  virtual std::string GetUserMacrosDirectory();

  /**
   * What is the reg key path to "vsmacros" for this version of Visual
   * Studio?
   */
  virtual std::string GetUserMacrosRegKeyBase();

  enum MacroName {MacroReload, MacroStop};

  /**
   * Call the ReloadProjects macro if necessary based on
   * GetFilesReplacedDuringGenerate results.
   */
  virtual void CallVisualStudioMacro(MacroName m,
                                     const char* vsSolutionFile = 0);

  // return true if target is fortran only
  bool TargetIsFortranOnly(cmTarget const& t);

  /** Get the top-level registry key for this VS version.  */
  std::string GetRegistryBase();

  /** Get the top-level registry key for the given VS version.  */
  static std::string GetRegistryBase(const char* version);

  /** Return true if the generated build tree may contain multiple builds.
      i.e. "Can I build Debug and Release in the same tree?" */
  virtual bool IsMultiConfig() { return true; }

  /** Return true if building for Windows CE */
  virtual bool TargetsWindowsCE() const { return false; }

  class TargetSet: public std::set<cmTarget const*> {};
  struct TargetCompare
  {
    bool operator()(cmTarget const* l, cmTarget const* r) const;
  };
  class OrderedTargetDependSet;

  virtual void FindMakeProgram(cmMakefile*);

protected:
  // Does this VS version link targets to each other if there are
  // dependencies in the SLN file?  This was done for VS versions
  // below 8.
  virtual bool VSLinksDependencies() const { return true; }

  virtual const char* GetIDEVersion() = 0;

  virtual void AddPlatformDefinitions(cmMakefile* mf);

  virtual bool ComputeTargetDepends();
  class VSDependSet: public std::set<cmStdString> {};
  class VSDependMap: public std::map<cmTarget const*, VSDependSet> {};
  VSDependMap VSTargetDepends;
  void ComputeVSTargetDepends(cmTarget&);

  bool CheckTargetLinks(cmTarget& target, const char* name);
  std::string GetUtilityForTarget(cmTarget& target, const char*);
  virtual std::string WriteUtilityDepend(cmTarget const*) = 0;
  std::string GetUtilityDepend(cmTarget const* target);
  typedef std::map<cmTarget const*, cmStdString> UtilityDependsMap;
  UtilityDependsMap UtilityDepends;
  const char* AdditionalPlatformDefinition;

private:
  virtual std::string GetVSMakeProgram() = 0;
  void PrintCompilerAdvice(std::ostream&, std::string, const char*) const {}
  void ComputeTargetObjects(cmGeneratorTarget* gt) const;

  void FollowLinkDepends(cmTarget const* target,
                         std::set<cmTarget const*>& linked);

  class TargetSetMap: public std::map<cmTarget*, TargetSet> {};
  TargetSetMap TargetLinkClosure;
  void FillLinkClosure(cmTarget const* target, TargetSet& linked);
  TargetSet const& GetTargetLinkClosure(cmTarget* target);
};

class cmGlobalVisualStudioGenerator::OrderedTargetDependSet:
  public std::multiset<cmTargetDepend,
                       cmGlobalVisualStudioGenerator::TargetCompare>
{
public:
  typedef cmGlobalGenerator::TargetDependSet TargetDependSet;
  typedef cmGlobalVisualStudioGenerator::TargetSet TargetSet;
  OrderedTargetDependSet(TargetDependSet const&);
  OrderedTargetDependSet(TargetSet const&);
};

#endif
