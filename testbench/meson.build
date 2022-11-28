testexe = executable(
    'test_peakdetect', # test executable name 
    'test_peakdetect.cc', # Test source
    include_directories : incdir,
    link_with: lib_peakdetect,
    dependencies : doctest_dep) 

# test execution 
test('C++ peakdet', testexe)

test('Python bindings', py3,
    args : files('test_bf_peakdetect.py'))
