project('3d-soft-engine', 'cpp')
cxx_compiler = meson.get_compiler('cpp')
code = '''#include <x86intrin.h>
int main(int argc, char **argv) {
  __m128 m = _mm_setr_ps(1.0f,1.0f,1.0f,1.0f);
  m = _mm_hadd_ps(m, m);
  return 0;
}
'''
cxx_compiler_id = cxx_compiler.get_id()
if cxx_compiler_id == 'gcc'
  result = cxx_compiler.run(code, args : '-msse4.1', name : 'check sse4.1')
  if result.returncode() == 0
    add_global_arguments('-msse4.1', language : 'cpp')
  endif
else
  message('Compiler ' + cxx_compiler_id + ' not tested for sse4.1')
endif

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
      install : false,
      native : false)
  gtest_lib_native = shared_library('gtest-native', gtest_libsrc,
      include_directories : gtest_incdir,
      dependencies : threads,
      install : false,
      native : true)
endif

inc = include_directories('src')
inc = [inc, gtest_incdir]

e1 = executable('vec4_test', 
    sources : ['src/vec4_test.cc'],
    include_directories : inc,
    link_with : gtest_lib,
    dependencies : gtest_dep,
    native : false)

e2 = executable('vec4_test_native', 
    sources : ['src/vec4_test.cc'],
    include_directories : inc,
    link_with : gtest_lib_native,
    dependencies : gtest_dep,
    native : true)


test('Vect4 Test', e1)
test('Vect4 Test native', e2)


