/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/

#include "cmVisualStudio11MultiPlatformTargetGenerator.h"
#include "cmGeneratorTarget.h"
#include "cmTarget.h"
#include "cmComputeLinkInformation.h"
#include "cmGeneratedFileStream.h"
#include "cmGeneratorExpression.h"
#include "cmMakefile.h"
#include "cmSourceFile.h"
#include "cmVisualStudioGeneratorOptions.h"
#include "cmLocalVisualStudio7Generator.h"
#include "cmVS10CLFlagTable.h"
#include "cmVS10LinkFlagTable.h"
#include "cmVS10LibFlagTable.h"
#include "cmVS11CLFlagTable.h"
#include "cmVS11LinkFlagTable.h"
#include "cmVS11LibFlagTable.h"
#include "cmVS12CLFlagTable.h"
#include "cmVS12LinkFlagTable.h"
#include "cmVS12LibFlagTable.h"

#include <cmsys/auto_ptr.hxx>

cmVisualStudio11MultiPlatformTargetGenerator::cmVisualStudio11MultiPlatformTargetGenerator(cmTarget* target,
                                  cmGlobalVisualStudio11Generator* gg)
: cmVisualStudio10TargetGenerator(target, gg)                                  
{
  this->target = target;
  this->platforms = gg->GetMultiPlatforms();
}


cmVisualStudio11MultiPlatformTargetGenerator::~cmVisualStudio11MultiPlatformTargetGenerator(void)
{
}

void cmVisualStudio11MultiPlatformTargetGenerator::WriteSingleProjectConfiguration(const std::string& configuration, const std::string& platform)
{
  if (platforms.empty())
  {
    cmVisualStudio10TargetGenerator::WriteSingleProjectConfiguration(configuration, platform);
  }
  else
  {
    for(auto iter = platforms.begin(); iter != platforms.end(); ++iter)
    {
        cmVisualStudio10TargetGenerator::WriteSingleProjectConfiguration(configuration, *iter);
    }
  }
}

void cmVisualStudio11MultiPlatformTargetGenerator::WriteSingleProjectConfigurationValues(const std::string& configuration, const std::string& platform)
{
  if (platforms.empty())
  {
      cmVisualStudio10TargetGenerator::WriteSingleProjectConfigurationValues(configuration, platform);
  }
  else
  {
    for(auto iter = platforms.begin(); iter != platforms.end(); ++iter)
    {
        cmVisualStudio10TargetGenerator::WriteSingleProjectConfigurationValues(configuration, *iter);
    }
  }
}

void cmVisualStudio11MultiPlatformTargetGenerator::WriteSinglePathAndIncrementalLinkOptions(cmTarget::TargetType ttype, const std::string& configuration, const std::string& platform)
{
  if (platforms.empty())
  {
    cmVisualStudio10TargetGenerator::WriteSinglePathAndIncrementalLinkOptions(ttype, configuration, platform);
  }
  else
  {
    for(auto iter = platforms.begin(); iter != platforms.end(); ++iter)
    {
      cmVisualStudio10TargetGenerator::WriteSinglePathAndIncrementalLinkOptions(ttype, configuration, *iter);
    }
  }
}

void cmVisualStudio11MultiPlatformTargetGenerator::WriteSingleItemDefinitionGroup(const std::string& configuration, const std::string& platform)
{
  if (platforms.empty())
  {
      cmVisualStudio10TargetGenerator::WriteSingleItemDefinitionGroup(configuration, platform);
  }
  else
  {
    for(auto iter = platforms.begin(); iter != platforms.end(); ++iter)
    {
        cmVisualStudio10TargetGenerator::WriteSingleItemDefinitionGroup(configuration, *iter);
    }
  }
}

void cmVisualStudio11MultiPlatformTargetGenerator::WriteSingleCustomBuild(
    const std::string& configuration, 
    const std::string& platform, 
    cmSourceFile* source, 
    cmCustomCommand const &command, 
    cmLocalVisualStudio7Generator* lg, 
    const std::string& comment)
{
  if (platforms.empty())
  {
    cmVisualStudio10TargetGenerator::WriteSingleCustomBuild(configuration, platform, source, command, lg, comment);
  }
  else
  {
    for(auto iter = platforms.begin(); iter != platforms.end(); ++iter)
    {
      cmVisualStudio10TargetGenerator::WriteSingleCustomBuild(configuration, *iter, source, command, lg, comment);
    }
  }
}