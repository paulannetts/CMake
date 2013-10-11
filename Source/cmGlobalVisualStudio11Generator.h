/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2000-2011 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef cmGlobalVisualStudio11Generator_h
#define cmGlobalVisualStudio11Generator_h

#include "cmGlobalVisualStudio10Generator.h"


/** \class cmGlobalVisualStudio11Generator  */
class cmGlobalVisualStudio11Generator:
  public cmGlobalVisualStudio10Generator
{
public:
  cmGlobalVisualStudio11Generator(const char* name,
    const char* architectureId, const char* additionalPlatformDefinition, 
    const char* defaultMultiPlatform, const char* platformToolset = "v110");
  static cmGlobalGeneratorFactory* NewFactory();

  virtual void EnableLanguage(std::vector<std::string>const& languages,
                              cmMakefile *, bool optional);

  virtual void WriteSLNHeader(std::ostream& fout);
  virtual void WriteSolutionConfigurations(std::ostream& fout);
  virtual void WriteProjectConfigurations(
    std::ostream& fout, const char* name, cmTarget::TargetType type,
    const std::set<std::string>& configsPartOfDefaultBuild,
    const char* platformMapping = NULL);

  ///! create the correct local generator
  virtual cmLocalGenerator *CreateLocalGenerator();

  /** TODO: VS 11 user macro support. */
  virtual std::string GetUserMacrosDirectory() { return ""; }

  const std::vector<std::string>& GetMultiPlatforms() { return this->multiPlatforms; };
protected:
  virtual const char* GetIDEVersion() { return "11.0"; }
  bool UseFolderProperty();
private:
  class Factory;
  std::vector<std::string> multiPlatforms;
  std::string defaultMultiPlatform;
};
#endif
