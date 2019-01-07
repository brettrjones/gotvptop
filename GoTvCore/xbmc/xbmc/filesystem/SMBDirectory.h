#pragma once
/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "IDirectory.h"
#include "SMBFile.h"
#include "MediaSource.h"

namespace XFILE
{
class CSMBDirectory : public IDirectory
{
public:
  CSMBDirectory(void);
  ~CSMBDirectory(void) override;
  bool GetDirectory(const GoTvUrl& url, CFileItemList &items) override;
  DIR_CACHE_TYPE GetCacheType(const GoTvUrl& url) const override { return DIR_CACHE_ONCE; };
  bool Create(const GoTvUrl& url) override;
  bool Exists(const GoTvUrl& url) override;
  bool Remove(const GoTvUrl& url) override;

  int Open(const GoTvUrl &url);

private:
  int OpenDir(const GoTvUrl &url, std::string& strAuth);
};
}
