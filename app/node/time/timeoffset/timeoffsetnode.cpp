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

#include "timeoffsetnode.h"

#include "widget/slider/rationalslider.h"

namespace olive {

const QString TimeOffsetNode::kTimeInput = QStringLiteral("time_in");
const QString TimeOffsetNode::kInputInput = QStringLiteral("input_in");

#define super Node

TimeOffsetNode::TimeOffsetNode()
{
  AddInput(kTimeInput, NodeValue::kRational, QVariant::fromValue(rational(0)), InputFlags(kInputFlagNotConnectable));
  SetInputProperty(kTimeInput, QStringLiteral("view"), RationalSlider::kTime);
  SetInputProperty(kTimeInput, QStringLiteral("viewlock"), true);

  AddInput(kInputInput, NodeValue::kNone, InputFlags(kInputFlagNotKeyframable));
}

void TimeOffsetNode::Retranslate()
{
  super::Retranslate();

  SetInputName(kTimeInput, QStringLiteral("Time"));
  SetInputName(kInputInput, QStringLiteral("Input"));
}

TimeRange TimeOffsetNode::InputTimeAdjustment(const QString &input, int element, const TimeRange &input_time, bool clamp) const
{
  if (input == kInputInput) {
    return TimeRange(GetRemappedTime(input_time.in()), GetRemappedTime(input_time.out()));
  } else {
    return super::InputTimeAdjustment(input, element, input_time, clamp);
  }
}

TimeRange TimeOffsetNode::OutputTimeAdjustment(const QString &input, int element, const TimeRange &input_time) const
{
  /*if (input == kInputInput) {
    rational target_time = GetValueAtTime(kTimeInput, input_time.in()).value<rational>();

    return TimeRange(target_time, target_time + input_time.length());
  } else {
    return super::OutputTimeAdjustment(input, element, input_time);
  }*/
  return super::OutputTimeAdjustment(input, element, input_time);
}

NodeValue TimeOffsetNode::Value(const ValueParams &p) const
{
  return GetInputValue(p, kInputInput);
}

rational TimeOffsetNode::GetRemappedTime(const rational &input) const
{
  return input + GetValueAtTime(kTimeInput, input).value<rational>();
}

}
