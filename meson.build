project(
    'pyramid',
    'c',
    version         : '0.1',
    license         : 'Unlicense',
    license_files   : 'LICENSE',
    default_options : ['warning_level=everything', 'default_library=static', 'c_std=c17'],
)

subdir('src')

# Generate a pkg-config file
if not meson.is_subproject()
    pkg_mod = import('pkgconfig')
    pkg_mod.generate(
        name : meson.project_name(),
        version : meson.project_version(),
        libraries : [pyramid_lib],
        description : 'Common data structures and algorithms, implemented in C.',
    )
endif

# Testing ------------------------------------------------------------------------------------------

if get_option('tests') or get_option('dev')
    criterion_dep = dependency(
        'criterion',
        default_options: ['tests=false', 'samples=false'],
    )
    
    subdir('tests')
endif
