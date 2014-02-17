/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2000-2011 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include "cmGlobalVisualStudio11Generator.h"
#include "cmLocalVisualStudio10Generator.h"
#include "cmMakefile.h"

static const char vs11generatorName[] = "Visual Studio 11 2012";

// Map generator name without year to name with year.
static const char* cmVS11GenName(const char* name, std::string& genName)
{
  if(strncmp(name, vs11generatorName, sizeof(vs11generatorName)-6) != 0)
    {
    return 0;
    }
  const char* p = name + sizeof(vs11generatorName) - 6;
  if(cmHasLiteralPrefix(p, " 2012"))
    {
    p += 5;
    }
  genName = std::string(vs11generatorName) + p;
  return p;
}

class cmGlobalVisualStudio11Generator::Factory
  : public cmGlobalGeneratorFactory
{
public:
  virtual cmGlobalGenerator* CreateGlobalGenerator(const char* name) const
    {
    std::string genName;
    const char* p = cmVS11GenName(name, genName);
    if(!p)
      { return 0; }
    name = genName.c_str();
    if(strcmp(p, "") == 0)
      {
      return new cmGlobalVisualStudio11Generator(
        name, NULL, NULL, "Win32");
      }
    if(strcmp(p, " Win64") == 0)
      {
      return new cmGlobalVisualStudio11Generator(
        name, "x64", "CMAKE_FORCE_WIN64", "Win64");
      }
    if(strcmp(p, " ARM") == 0)
      {
      return new cmGlobalVisualStudio11Generator(
        name, "ARM", NULL, "ARM");
      }
    if(strcmp(p, " Windows-Phone-8") == 0)
      {
      return new cmGlobalVisualStudio11Generator(
          name, NULL, NULL, "Win32;ARM", "v110_wp80");
      }

    if(*p++ != ' ')
      {
      return 0;
      }

    std::set<std::string> installedSDKs =
      cmGlobalVisualStudio11Generator::GetInstalledWindowsCESDKs();

    if(installedSDKs.find(p) == installedSDKs.end())
      {
      return 0;
      }

    cmGlobalVisualStudio11Generator* ret =
      new cmGlobalVisualStudio11Generator(name, p, NULL, "", "");
    ret->WindowsCEVersion = "8.00";
    return ret;
    }

  virtual void GetDocumentation(cmDocumentationEntry& entry) const
    {
    entry.Name = vs11generatorName;
    entry.Brief = "Generates Visual Studio 11 (VS 2012) project files.";
    }

  virtual void GetGenerators(std::vector<std::string>& names) const
    {
    names.push_back(vs11generatorName);
    names.push_back(vs11generatorName + std::string(" ARM"));
    names.push_back(vs11generatorName + std::string(" Win64"));
    names.push_back(vs11generatorName + std::string(" Windows-Phone-8"));

    std::set<std::string> installedSDKs =
      cmGlobalVisualStudio11Generator::GetInstalledWindowsCESDKs();
    for(std::set<std::string>::const_iterator i =
        installedSDKs.begin(); i != installedSDKs.end(); ++i)
      {
      names.push_back(std::string(vs11generatorName) + " " + *i);
      }
    }
};

//----------------------------------------------------------------------------
cmGlobalGeneratorFactory* cmGlobalVisualStudio11Generator::NewFactory()
{
  return new Factory;
}

//----------------------------------------------------------------------------
cmGlobalVisualStudio11Generator::cmGlobalVisualStudio11Generator(
  const char* name, 
  const char* platformName,
  const char* additionalPlatformDefinition,
  const char* defaultMultiPlatform,
  const char* platformToolset)
  : cmGlobalVisualStudio10Generator(name, platformName,
                                   additionalPlatformDefinition)
{
  std::string vc11Express;
  this->ExpressEdition = cmSystemTools::ReadRegistryValue(
    "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VCExpress\\11.0\\Setup\\VC;"
    "ProductDir", vc11Express, cmSystemTools::KeyWOW64_32);
  this->PlatformToolset = platformToolset;
  this->defaultMultiPlatform = defaultMultiPlatform;
}

//----------------------------------------------------------------------------
bool
cmGlobalVisualStudio11Generator::MatchesGeneratorName(const char* name) const
{
  std::string genName;
  if(cmVS11GenName(name, genName))
    {
    return genName == this->GetName();
    }
  return false;
}

//----------------------------------------------------------------------------
void cmGlobalVisualStudio11Generator::WriteSLNHeader(std::ostream& fout)
{
  fout << "Microsoft Visual Studio Solution File, Format Version 12.00\n";
  if (this->ExpressEdition)
    {
    fout << "# Visual Studio Express 2012 for Windows Desktop\n";
    }
  else
    {
    fout << "# Visual Studio 2012\n";
    }
}

//----------------------------------------------------------------------------
void cmGlobalVisualStudio11Generator
::EnableLanguage(std::vector<std::string>const &  lang,
                 cmMakefile *mf, bool optional)
{
  cmGlobalVisualStudio10Generator::EnableLanguage(lang, mf, optional);
  if(!mf->GetDefinition("CMAKE_MSVC_PLATFORMS"))
  {
  mf->AddCacheDefinition(
    "CMAKE_MSVC_PLATFORMS",
    this->defaultMultiPlatform.c_str(),
    "Semicolon separated list of platforms, e.g. Win32, x64, x64, ARM ",
    cmCacheManager::STRING);
  }

  const char* ct
    = this->CMakeInstance->GetCacheDefinition("CMAKE_MSVC_PLATFORMS");
  if (!ct)
  {
    ct = this->defaultMultiPlatform.c_str();
  }
  this->multiPlatforms.clear();
  cmGeneratorExpression::Split(ct, this->multiPlatforms);
}

//----------------------------------------------------------------------------
void
cmGlobalVisualStudio11Generator
::WriteSolutionConfigurations(std::ostream& fout)
{
  fout << "\tGlobalSection(SolutionConfigurationPlatforms) = preSolution\n";
  for(std::vector<std::string>::iterator i = this->Configurations.begin();
      i != this->Configurations.end(); ++i)
    {
      for (std::vector<std::string>::iterator j = this->multiPlatforms.begin();
           j != this->multiPlatforms.end(); ++j)
      {
        fout << "\t\t" << *i << "|" << *j
          << " = "  << *i << "|" << *j << "\n";
      }
    }
  fout << "\tEndGlobalSection\n";
}

void cmGlobalVisualStudio11Generator::WriteProjectConfigurations(
    std::ostream& fout, const char* name, cmTarget::TargetType type,
    const std::set<std::string>& configsPartOfDefaultBuild,
    const char* platformMapping)
{
  std::string guid = this->GetGUID(name);
  for(std::vector<std::string>::iterator i = this->Configurations.begin();
      i != this->Configurations.end(); ++i)
  {
    for (std::vector<std::string>::iterator j = this->multiPlatforms.begin();
      j != this->multiPlatforms.end(); ++j)
    {
      fout << "\t\t{" << guid << "}." << *i
          << ".ActiveCfg = " << *i << "|"
          << *j << "\n";
      std::set<std::string>::const_iterator
        ci = configsPartOfDefaultBuild.find(*i);
      if(!(ci == configsPartOfDefaultBuild.end()))
      {
      fout << "\t\t{" << guid << "}." << *i
            << ".Build.0 = " << *i << "|"
            << *j << "\n";
      }
    }
  }
}

//----------------------------------------------------------------------------
cmLocalGenerator *cmGlobalVisualStudio11Generator::CreateLocalGenerator()
{
  cmLocalVisualStudio10Generator* lg =
    new cmLocalVisualStudio10Generator(cmLocalVisualStudioGenerator::VS11);
  lg->SetPlatformName(this->GetPlatformName());
  lg->SetGlobalGenerator(this);
  return lg;
}

//----------------------------------------------------------------------------
bool cmGlobalVisualStudio11Generator::UseFolderProperty()
{
  // Intentionally skip over the parent class implementation and call the
  // grand-parent class's implementation. Folders are not supported by the
  // Express editions in VS10 and earlier, but they are in VS11 Express.
  return cmGlobalVisualStudio8Generator::UseFolderProperty();
}

//----------------------------------------------------------------------------
std::set<std::string>
cmGlobalVisualStudio11Generator::GetInstalledWindowsCESDKs()
{
  const char sdksKey[] = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\"
                         "Windows CE Tools\\SDKs";

  std::vector<std::string> subkeys;
  cmSystemTools::GetRegistrySubKeys(sdksKey, subkeys,
                                    cmSystemTools::KeyWOW64_32);

  std::set<std::string> ret;
  for(std::vector<std::string>::const_iterator i =
      subkeys.begin(); i != subkeys.end(); ++i)
    {
    std::string key = sdksKey;
    key += '\\';
    key += *i;
    key += ';';

    std::string path;
    if(cmSystemTools::ReadRegistryValue(key.c_str(),
                                        path,
                                        cmSystemTools::KeyWOW64_32) &&
        !path.empty())
      {
      ret.insert(*i);
      }
    }

  return ret;
}
