project('rga_analysis', 'cpp',
        default_options : ['cpp_std=c++17'],
        version : run_command('git', 'describe', '--tags', '--abbrev=0', '--always', check : true).stdout().strip(),
        meson_version : '>= 1.6.0'
)


# root dependencies
# check that root-config is found
if run_command('root-config', '--version', check : true).returncode() != 0
    error('ROOT not found. Please install ROOT or disable the use_root option')
endif

ROOT_link_args = []
ROOT_LIBS_NEEDED = ['root', 'Core', 'RIO', 'Tree', 'Hist', 'Gpad', 'Graf']
ROOT_inc_dirs = include_directories(run_command('root-config', '--incdir', check : true).stdout().strip())
ROOT_config_link_args = run_command('root-config', '--libs', check : true).stdout().strip().split()
foreach link_arg : ROOT_config_link_args
    foreach lib : ROOT_LIBS_NEEDED
        if link_arg.contains(lib)
            ROOT_link_args += link_arg
            break  # Exit the inner loop as we found a match
        endif
    endforeach
endforeach

root_deps = declare_dependency(
    include_directories : [ROOT_inc_dirs],
    link_args : ROOT_link_args,
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
            include_directories : all_includes + additional_includes,
            link_with: all_libs
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
