project('3d-soft-engine', 'cpp')
add_global_arguments('-msse4.1', language : 'cpp')

threads = dependency('threads')
gtest_dep = dependency('gtest', required : false)
if gtest_dep.found()
  gtest_incdir = []
  gtest_lib = []
else
  gtest_proj = subproject('gtest')
  gtest_incdir = gtest_proj.get_variable('incdir')
  gtest_libsrc = gtest_proj.get_variable('libsources')
  gtest_lib = shared_library('gtest', gtest_libsrc,
      include_directories : gtest_incdir,
      dependencies : threads,
      install : false)
endif

inc = include_directories('src')
inc = [inc, gtest_incdir]

e1 = executable('vec4_test', 
    sources : ['src/vec4_test.cc'],
    include_directories : inc,
    link_with : gtest_lib,
    dependencies : gtest_dep)

test('Vect4 Test', e1)


