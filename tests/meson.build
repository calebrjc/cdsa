pyramid_tests_root = meson.source_root() / 'tests'

pyramid_tests = [
    pyramid_tests_root / 'dynamic_array.test.c'
]

# Generate test executables
foreach test : pyramid_tests
    test_name = test.replace(pyramid_tests_root + '/', '').substring(0, -2).underscorify()
    test_exe = executable(
        test_name,
        sources     : [test],
        dependencies: [pyramid_dep, criterion_dep],
    )
    test(test_name, test_exe)
endforeach
