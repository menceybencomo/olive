/***

  Olive - Non-Linear Video Editor
  Copyright (C) 2022 Olive Team

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

***/

#ifndef SEQUENCEVIEWERPANEL_H
#define SEQUENCEVIEWERPANEL_H

#include "panel/viewer/viewer.h"

namespace olive {

class SequenceViewerPanel : public ViewerPanel
{
  Q_OBJECT
public:
  SequenceViewerPanel();

public slots:
  void StartCapture(const TimeRange &time, const Track::Reference &track);

protected:
  virtual void Retranslate() override;

};

}

#endif // SEQUENCEVIEWERPANEL_H
