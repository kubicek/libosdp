#
#  Copyright (c) 2020-2025 Siddharth Chandrasekaran <sidcha.dev@gmail.com>
#
#  SPDX-License-Identifier: Apache-2.0
#

require 'mkmf'

# Get the repository root directory
repo_root = File.expand_path('../../../..', __FILE__)

# Add include directories
$INCFLAGS << " -I#{repo_root}/utils/include"
$INCFLAGS << " -I#{repo_root}/include"
$INCFLAGS << " -I#{repo_root}/src"
$INCFLAGS << " -I#{repo_root}/src/crypto"

# Add source directories
$srcs = []

# Utils sources
utils_sources = [
  'utils/src/list.c',
  'utils/src/queue.c',
  'utils/src/slab.c',
  'utils/src/utils.c',
  'utils/src/logger.c',
  'utils/src/disjoint_set.c',
  'utils/src/crc16.c',
]

# Library sources
lib_sources = [
  'src/osdp_common.c',
  'src/osdp_phy.c',
  'src/osdp_sc.c',
  'src/osdp_file.c',
  'src/osdp_pd.c',
  'src/osdp_cp.c',
  'src/crypto/tinyaes_src.c',
  'src/crypto/tinyaes.c',
]

# Ruby extension sources (current directory)
ext_sources = [
  'module.c',
  'base.c',
  'cp.c',
  'pd.c',
  'data.c',
  'utils.c',
]

# Add all source files with their full paths
utils_sources.each { |src| $srcs << "#{repo_root}/#{src}" }
lib_sources.each { |src| $srcs << "#{repo_root}/#{src}" }
ext_sources.each { |src| $srcs << src }

# Define macros for optional features
$defs << '-DOPT_OSDP_PACKET_TRACE'

create_makefile('osdp/osdp_sys')
