/*
 *  Copyright (C) 2011-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <string>
#include <vector>

#if defined(HAVE_QT_GUI)
# include <qtandroid/jni/Display.h>
#else
# include <android/jni/Display.h>
#endif // defined(HAVE_QT_GUI)

#include "windowing/Resolution.h"

class CAndroidUtils
{
public:
  CAndroidUtils();
  virtual ~CAndroidUtils();
  virtual bool  GetNativeResolution(RESOLUTION_INFO *res) const;
  virtual bool  SetNativeResolution(const RESOLUTION_INFO &res);
  virtual bool  ProbeResolutions(std::vector<RESOLUTION_INFO> &resolutions);

protected:
  mutable int m_width;
  mutable int m_height;
};
