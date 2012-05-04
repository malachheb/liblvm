# -*- encoding: utf-8 -*-

Gem::Specification.new do |s|
  s.name = %q{liblvm}
  s.version = "1.0.0"

  s.required_rubygems_version = Gem::Requirement.new(">= 0") if s.respond_to? :required_rubygems_version=
  s.authors = ["Mehrez Alachheb"]
  s.date = %q{2012-01-04}
  s.default_executable = %q{liblvm}
  s.description = %q{liblvm is a ruby gem to use the linux library liblvm2 in ruby}
  s.email = %q{lachheb.mehrez@gmail.com}
  s.homepage = "https://github.com/malachheb/liblvm"
  s.extensions = ["ext/extconf.rb"]
  s.extra_rdoc_files = ["README.md"]
  s.files = ["README.md", "ext/extconf.rb", "ext/liblvm.c","lib/", "lib/liblvm.rb"]
  s.homepage = %q{}
  s.require_paths = [["lib"]]
  s.rubygems_version = %q{1.3.6}
  s.summary = %{ liblvm is a ruby gem to use the linux library liblvm2 in ruby }
end
