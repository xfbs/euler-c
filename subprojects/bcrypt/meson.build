project(
  'openbsd_bcrypt',
  'c',
  default_options: ['c_str=c11'])

include = include_directories('.')

libopenbsd_bcrypt = both_libraries(
  'openbsd_bcrypt',
  'bcrypt.c',
  'blowfish.c',
  include_directories: include)

libopenbsd_bcrypt_dep = declare_dependency(
  include_directories: include,
  link_with: libopenbsd_bcrypt)

