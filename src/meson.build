pyramid_inc = include_directories (
    '../include',
    '.',
)

pyramid_src = files (
    'dynamic_array.c',
)

pyramid_lib = library(
    meson.project_name(),
    include_directories: pyramid_inc,
    sources: pyramid_src,
    install: not meson.is_subproject(),
)

pyramid_dep = declare_dependency(
    link_with: pyramid_lib,
    include_directories: pyramid_inc,
)

if not meson.is_subproject()
    pkg_mod = import('pkgconfig')
    pkg_mod.generate(
        name       : meson.project_name(),
        description: 'Common data structures and algorithms. For C, in C.',
        version    : meson.project_version(),
        url        : 'https://github.com/calebrjc/pyramid', 
        libraries  : [pyramid_lib],
    )
endif
