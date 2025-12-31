# frozen_string_literal: true

Gem::Specification.new do |spec|
  spec.name          = 'libosdp'
  spec.version       = '3.1.0'
  spec.authors       = ['Siddharth Chandrasekaran']
  spec.email         = ['sidcha.dev@gmail.com']

  spec.summary       = 'Library implementation of IEC 60839-11-5 OSDP (Open Supervised Device Protocol)'
  spec.description   = 'LibOSDP - A cross-platform open source implementation of OSDP with support for secure channel communication'
  spec.homepage      = 'https://github.com/goToMain/libosdp'
  spec.license       = 'Apache-2.0'
  spec.required_ruby_version = '>= 2.6.0'

  spec.metadata['homepage_uri'] = spec.homepage
  spec.metadata['source_code_uri'] = 'https://github.com/goToMain/libosdp'
  spec.metadata['documentation_uri'] = 'https://libosdp.sidcha.dev/'

  # Specify which files should be added to the gem when it is released.
  spec.files = Dir[
    'lib/**/*.rb',
    'ext/**/*.{c,h,rb}',
    'README.md',
    'LICENSE'
  ]

  spec.bindir        = 'bin'
  spec.executables   = []
  spec.require_paths = ['lib']
  spec.extensions    = ['ext/osdp/extconf.rb']

  # Development dependencies
  spec.add_development_dependency 'rake', '~> 13.0'
  spec.add_development_dependency 'rake-compiler', '~> 1.2'
end
