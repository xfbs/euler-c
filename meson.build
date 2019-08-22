project(
  'euler-c',
  'c',
  default_options: ['c_str=c11'],
  version: '0.1.0',
  license: 'MIT')

libeuler = subproject('libeuler')
libeuler_dep = libeuler.get_variable('libeuler_dep')

libopenbsd_bcrypt = subproject('bcrypt')
libopenbsd_bcrypt_dep = libopenbsd_bcrypt.get_variable('libopenbsd_bcrypt_dep')

libjansson = dependency('jansson')

libz = dependency('zlib')

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required : false)

python3 = import('python').find_installation('python3')
gen_solved = find_program('scripts/gen_solved.py')
gen_all = find_program('scripts/gen_problems.py')
gen_unsolved = find_program('scripts/gen_unsolved.py')

solved = ['001', '002', '003', '004', '005', '006', '007', '009']
unsolved = ['008', '010', '011', '012', '013', '014', '015', '016', '017', '018', '019', '020', '021', '022', '023', '024', '025', '026', '027', '028', '029', '030', '031', '032', '033', '034', '035', '036', '037', '038', '039', '040', '041', '042', '043', '044', '045', '046', '047', '048', '049', '050', '051', '052', '053', '054', '055', '056', '057', '058', '059', '060', '061', '062', '063', '064', '065', '066', '067', '068', '069', '070', '071', '072', '073', '074', '075', '076', '077', '078', '079', '080', '081', '082', '083', '084', '085', '086', '087', '088', '089', '090', '091', '092', '093', '094', '095', '096', '097', '098', '099', '100', '101', '102']

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
    command: [python3, gen_solved, '@OUTPUT@', n, '@INPUT@'])
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
  dependencies: [libeuler_dep, libopenbsd_bcrypt_dep, libjansson, libz])

euler = executable(
  'euler-c',
  'src/main.c',
  'src/cmd.c',
  'src/cmd_help.c',
  'src/cmd_list.c',
  'src/cmd_check.c',
  'src/cmd_run.c',
  'src/cmd_info.c',
  'src/cmd_view.c',
  link_with: solutions,
  include_directories: include,
  dependencies: [libeuler_dep, libopenbsd_bcrypt_dep, m_dep, libjansson, libz])
