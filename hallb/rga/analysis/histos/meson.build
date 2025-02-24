sub_dir_name = meson.current_source_dir().split('/').get(-1)
LD += {
    'name' : sub_dir_name,
    'sources' : files(
        'histos.cc',
    ),
    'headers' : files(
        'histos.h',
    ),
    'dependencies' : [root_deps],
}
