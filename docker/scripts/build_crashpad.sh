#!/usr/bin/env bash
# Copyright (C) 2020 Olive Team
# SPDX-License-Identifier: GPL-3.0-or-later

set -ex

# Get Google's build tools
git clone --depth 1 https://chromium.googlesource.com/chromium/tools/depot_tools.git
PATH="$(pwd)/depot_tools:$PATH"
export PATH

# Build Crashpad with Clang (default)
# Toolchain can be controlled with env vars CC, CXX and AR
mkdir crashpad
cd crashpad
fetch crashpad
cd crashpad
# TODO: Do we want to set any special args here? For example:
# gn gen --args="target_cpu=\"x64\" is_debug=true" out/Default
gn gen out/Default
ninja -C out/Default

# Include list
echo 'out/Default/crashpad_handler' > /tmp/crashpad_include_list.txt
find . \( -type f -o -type l \) \
    -name "*.h" -o \
    -name "*.o" -o \
    -name "*.a" | cut -c3- >> /tmp/crashpad_include_list.txt

# Exclude list
echo '**/.git/**
compat/android/**
compat/ios/**
compat/mac/**
compat/non_elf/**
compat/win/**
handler/mac/**
handler/win/**
infra/**
minidump/test/**
out/Default/**_test*
snapshot/fuchsia/**
snapshot/ios/**
snapshot/mac/**
snapshot/win/**
test/**
third_party/fuchsia/**
third_party/gyp/gyp/test/**
third_party/mini_chromium/mini_chromium/base/fuchsia/**
third_party/mini_chromium/mini_chromium/testing/**
tools/mac/**
util/fuchsia/**
util/ios/**
util/mac/**
util/win/**' > /tmp/crashpad_exclude_list.txt

rsync -av \
    --files-from=/tmp/crashpad_include_list.txt \
    --exclude-from=/tmp/crashpad_exclude_list.txt \
    --prune-empty-dirs \
    . "${OLIVE_INSTALL_PREFIX}/crashpad"

cd ../..

# Build Breakpad for minidump_stackwalk
mkdir breakpad
cd breakpad
fetch breakpad
cd src
./configure --prefix="${OLIVE_INSTALL_PREFIX}"
make
make install -j$(nproc)
