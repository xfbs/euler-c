project(
  'euler.c',
  'c',
  default_options: ['c_str=c11'],
  version: '0.1.0',
  license: 'MIT')

libeuler = subproject('libeuler')
libeuler_dep = libeuler.get_variable('libeuler_dep')

libopenbsd_bcrypt = subproject('bcrypt')
libopenbsd_bcrypt_dep = libopenbsd_bcrypt.get_variable('libopenbsd_bcrypt_dep')

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required : false)

solved = ['001']

sources = [
  'src/euler.c',
  'src/all.c',
]

foreach n : solved
  sources += 'src/solve/solve@0@.c'.format(n)
endforeach

include = include_directories('src')

solutions = library(
  'eulerc',
  sources,
  include_directories: include,
  dependencies: [libeuler_dep, libopenbsd_bcrypt_dep])

euler = executable(
  'euler',
  'src/main.c',
  link_with: solutions,
  include_directories: include,
  dependencies: [libeuler_dep, libopenbsd_bcrypt_dep, m_dep])
