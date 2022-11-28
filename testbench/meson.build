testexe = executable(
    'test_peakdetect', # test executable name 
    'test_peakdetect.cc', # Test source
    include_directories : incdir,
    link_with: lib_peakdetect,
    dependencies : doctest_dep) 

# test execution 
test('Peak Detection Test', testexe)

# we can specify other test execution passing arguments or environment variables
#test('Uuid test with args and env', testexe, args : ['arg1', 'arg2'], env : ['FOO=bar'])