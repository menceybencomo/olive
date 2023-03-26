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

#include "generatorwithmerge.h"

#include "node/math/merge/merge.h"

namespace olive {

#define super Node

const QString GeneratorWithMerge::kBaseInput = QStringLiteral("base_in");

GeneratorWithMerge::GeneratorWithMerge()
{
  AddInput(kBaseInput, NodeValue::kTexture, InputFlags(kInputFlagNotKeyframable));
  SetEffectInput(kBaseInput);
  SetFlag(kVideoEffect);
}

void GeneratorWithMerge::Retranslate()
{
  super::Retranslate();

  SetInputName(kBaseInput, tr("Base"));
}

ShaderCode GeneratorWithMerge::GetShaderCode(const ShaderRequest &request) const
{
  if (request.id == QStringLiteral("mrg")) {
    return ShaderCode(FileFunctions::ReadFileAsString(":/shaders/alphaover.frag"));
  }

  return ShaderCode();
}

NodeValue GeneratorWithMerge::GetMergableJob(const ValueParams &p, TexturePtr job) const
{
  NodeValue tex_meta = GetInputValue(p, kBaseInput);

  if (TexturePtr base = tex_meta.toTexture()) {
    // Push as merge node
    ShaderJob merge;

    merge.SetShaderID(QStringLiteral("mrg"));
    merge.Insert(MergeNode::kBaseIn, tex_meta);
    merge.Insert(MergeNode::kBlendIn, NodeValue(NodeValue::kTexture, job, this));

    return NodeValue(NodeValue::kTexture, base->toJob(merge), this);
  } else {
    // Just push generate job
    return NodeValue(NodeValue::kTexture, job, this);
  }
}

}
