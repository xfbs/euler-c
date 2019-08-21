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

python3 = import('python').find_installation('python3')
gen_problem_solved = find_program('scripts/gen_euler_solved.py')
gen_all = find_program('scripts/gen_problems.py')
gen_unsolved = find_program('scripts/gen_unsolved.py')

solved = ['001', '002']
unsolved = ['003']

sources = [
  'src/euler.c',
]

foreach n : solved
  sources += 'src/solve/solve@0@.c'.format(n)
endforeach

autogen = []

foreach n : solved
  autogen += custom_target(
    'gen_problem@0@'.format(n),
    output: 'problem@0@.c'.format(n),
    input: ['data/@0@/problem.md'.format(n), 'data/@0@/solution.bcrypt'.format(n)],
    command: [python3, gen_problem_solved, '@OUTPUT@', n, '@INPUT@'])
endforeach

foreach n : unsolved
  autogen += custom_target(
    'gen_problem@0@'.format(n),
    output: 'problem@0@.c'.format(n),
    input: ['data/@0@/problem.md'.format(n), 'data/@0@/solution.bcrypt'.format(n)],
    command: [python3, gen_unsolved, '@OUTPUT@', n, '@INPUT@'])
endforeach

autogen += custom_target(
  'all.c',
  output: ['all.h', 'all.c'],
  command: [python3, gen_all, '@OUTPUT@', solved, unsolved])

include = include_directories('src')

solutions = library(
  'eulerc',
  sources,
  autogen,
  include_directories: include,
  dependencies: [libeuler_dep, libopenbsd_bcrypt_dep])

euler = executable(
  'euler',
  'src/main.c',
  link_with: solutions,
  include_directories: include,
  dependencies: [libeuler_dep, libopenbsd_bcrypt_dep, m_dep])
