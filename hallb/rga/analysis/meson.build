project('rga_analysis', 'cpp',
        default_options : ['cpp_std=c++20'],
        version : run_command('git', 'describe', '--tags', '--abbrev=0', '--always', check : true).stdout().strip(),
        meson_version : '>= 1.6.0'
)


root_deps = dependency('root',
                       version : '>=6.32.08',
                       include_type : 'preserve'
)

# init lists
############
LD = []
all_libs = []
all_includes = []
empty_dict = { 'na' : [''] }
all_lib_names = []  # Store library names as linker flags


subdir('utils')
subdir('histos')

# compilation loop
foreach L : LD

    this_lib_name = L['name'] # key name must be present

    sources = L.get('sources', [''])
    headers = L.get('headers', [''])
    this_deps = L.get('dependencies', [])
    additional_includes = L.get('additional_includes', [''])

    if not sources.contains('')
        this_library = shared_library(
            this_lib_name,
            sources,
            install : true,
            dependencies : this_deps,
            include_directories : all_includes + additional_includes
        )
        if not all_libs.contains(this_library)
            all_libs += this_library
            all_lib_names += 'lib' + this_lib_name + '.a' # Add as linker flag
            message(' Adding Library ' + this_lib_name)
        endif
    endif

    # header files
    if not headers.contains('')
        install_headers(headers)
    endif

    foreach include_dir : additional_includes
        if not all_includes.contains(include_dir)
            all_includes += include_dir
        endif
    endforeach
    if not all_includes.contains(this_lib_name) and not sources.contains('')
        all_includes += this_lib_name
    endif
endforeach
