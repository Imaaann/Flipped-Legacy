project(
    'Flipped-Legacy', 'c',
    version: '1.0',
    default_options: ['warning_level=2','c_std=c17']
)

curses_dep = dependency('curses', required: true)
glib_dep = dependency('glib-2.0')

include_dir = include_directories('include')

executable(
    'main',
    'src/main.c',
    include_directories: include_dir,
    dependencies: [curses_dep]
)