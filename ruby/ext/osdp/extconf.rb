#
#  Copyright (c) 2020-2025 Siddharth Chandrasekaran <sidcha.dev@gmail.com>
#
#  SPDX-License-Identifier: Apache-2.0
#

require 'mkmf'

# Get the repository root directory
repo_root = File.expand_path('../../../..', __FILE__)

# Generate osdp_config.h from template
def generate_config_header(repo_root)
  template_path = File.join(repo_root, 'src', 'osdp_config.h.in')
  output_path = File.join(repo_root, 'src', 'osdp_config.h')
  
  return if File.exist?(output_path)
  
  template = File.read(template_path)
  
  # Get git info safely
  require 'open3'
  git_branch, _ = Open3.capture2('git', 'rev-parse', '--abbrev-ref', 'HEAD', :err => File::NULL)
  git_rev, _ = Open3.capture2('git', 'log', '--pretty=format:%h', '-n', '1', :err => File::NULL)
  git_tag, _ = Open3.capture2('git', 'describe', '--exact-match', '--tags', :err => File::NULL)
  git_diff, _ = Open3.capture2('git', 'diff', '--quiet', '--exit-code', :err => File::NULL)
  
  git_branch = git_branch.strip
  git_rev = git_rev.strip
  git_tag = git_tag.strip
  git_diff = git_diff.strip
  
  # Replace template variables
  config = template.gsub('@PROJECT_VERSION@', '3.1.0')
                   .gsub('@PROJECT_NAME@', 'libosdp')
                   .gsub('@GIT_BRANCH@', git_branch)
                   .gsub('@GIT_REV@', git_rev)
                   .gsub('@GIT_TAG@', git_tag)
                   .gsub('@GIT_DIFF@', git_diff)
                   .gsub('@REPO_ROOT@', repo_root)
  
  File.write(output_path, config)
end

generate_config_header(repo_root)

# Add include directories
$INCFLAGS << " -I#{repo_root}/utils/include"
$INCFLAGS << " -I#{repo_root}/include"
$INCFLAGS << " -I#{repo_root}/src"
$INCFLAGS << " -I#{repo_root}/src/crypto"

# Define macros for optional features
$defs << '-DOPT_OSDP_PACKET_TRACE'

# Add source directories to VPATH so make can find them
$VPATH ||= []
$VPATH << "#{repo_root}/utils/src"
$VPATH << "#{repo_root}/src"
$VPATH << "#{repo_root}/src/crypto"

# List all source files (just the base names)
$srcs = [
  # Utils sources
  'list.c',
  'queue.c',
  'slab.c',
  'utils.c',
  'logger.c',
  'disjoint_set.c',
  'crc16.c',
  'pcap_gen.c',
  # Library sources
  'osdp_common.c',
  'osdp_phy.c',
  'osdp_sc.c',
  'osdp_file.c',
  'osdp_pd.c',
  'osdp_cp.c',
  'osdp_diag.c',
  'tinyaes_src.c',
  'tinyaes.c',
  # Ruby extension sources (current directory)
  'module.c',
  'base.c',
  'cp.c',
  'pd.c',
  'data.c',
  'rb_utils.c',
]

create_makefile('osdp/osdp_sys')
