project(
  'euler.c',
  'c',
  default_options: ['c_str=c11'],
  version: '0.1.0',
  license: 'MIT')

libeuler = subproject('libeuler')
libeuler_dep = libeuler.get_variable('libeuler_dep')

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required : false)

sources = [
  'src/euler.c',
  'src/all.c',
  'src/solve001.c'
]

solutions = library(
  'eulerc',
  sources,
  dependencies: libeuler_dep)

euler = executable(
  'euler',
  'src/main.c',
  link_with: solutions,
  dependencies: [libeuler_dep, m_dep])
