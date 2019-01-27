{
	'includes': [
		'shark/utils/utils.gypi',
		'shark/shark.gypi',
		'shark/js/js.gypi',
		'tools/default_target.gypi',
	],

	'variables': {
		'shark_product_dir%': '<(output)/../shark-tools/product',
		'shark_product_so_subdir%': '<(os)/<(arch)',
		'conditions': [
			['os=="android"', {
				'shark_product_so_subdir': '<(os)/jniLibs/<(android_abi)'
			}],
		],
	},
	
	'targets': [{
		'target_name': 'shark-lib',
		'product_name': 'shark',
		'type': 'none',
		'dependencies': [
			'shark-utils', 
			'shark-gui', 
			'shark-js', 
		],
		'conditions': [
			['library_output=="shared_library" and OS not in "mac"', {
				'type': 'shared_library',
				'direct_dependent_settings': {
					'defines': [ 'XX_USIXX_SHARED' ],
				},
			}],
		],
		'direct_dependent_settings': {
			'include_dirs': [ '.' ],
			'xcode_settings': {
			 'OTHER_LDFLAGS': '-all_load',
			},
			'mac_bundle_resources': [
				'libs/shark',
			],
			'conditions': [
				['cplusplus_exceptions==1', {
					'xcode_settings': {
						'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
					},
					'cflags_cc': [ '-fexceptions' ], 
				}],
				['cplusplus_rtti==1', {
					'xcode_settings': { 
						'GCC_ENABLE_CPP_RTTI': 'YES', 
					},
					'cflags_cc': [ '-frtti', ], 
				}],
			],
		}, # direct_dependent_settings
	}, {
		'target_name': 'shark_copy_so', 
		'type': 'none',
		'dependencies': [ 'shark-lib' ],
		
		'conditions': [
			# copy libshark.so to product directory
			['debug==0 and library_output=="shared_library" and OS not in "mac"', {
				'copies': [{
					'destination': '<(shark_product_dir)/<(shark_product_so_subdir)',
					'files': [
						'<(output)/lib.target/libshark.so',
					],
				}], # copies
			}],
			# output mac shared library for "shark.framework"
			['debug==0 and library_output=="shared_library" \
				and OS in "mac" and project=="make"', {
				'actions': [{
					'action_name': 'shark_apple_dylib',
					'variables': {
						'embed_bitcode': '',
						'conditions': [
							['arch in "arm arm64" and without_embed_bitcode==0', {
								'embed_bitcode': '-fembed-bitcode',
							}],
							['use_v8==0 and os=="ios"', {
								'v8libs': [ '<(output)/libv8-link.a', ],
								'v8libs_l': '-lv8-link',
							}, {
								'v8libs': [ 
									'<(output)/libv8_base.a',
									'<(output)/libv8_libbase.a',
									'<(output)/libv8_libsampler.a',
									'<(output)/libv8_builtins_setup.a',
									'<(output)/libv8_builtins_generators.a',
									'<(output)/libv8_nosnapshot.a',
									'<(output)/libv8_libplatform.a',
								],
								'v8libs_l': '-lv8_base '
														'-lv8_libbase '
														'-lv8_libsampler '
														'-lv8_builtins_setup '
														'-lv8_builtins_generators '
														'-lv8_nosnapshot '
														'-lv8_libplatform ',
							}],
						],
					},
					'inputs': [
						'<(output)/libshark-utils.a', 
						'<(output)/libshark-gui.a', 
						'<(output)/libshark-js.a',
						'<(output)/libminizip.a',
						'<(output)/libopenssl.a',
						'<(output)/libuv.a',
						'<(output)/libhttp_parser.a',
						'<(output)/libreachability.a',
						'<(output)/libtess2.a',
						'<(output)/libft2.a',
						'<(output)/libtinyxml2.a',
						'<(output)/obj.target/ffmpeg/libffmpeg.a',
						'<(output)/libnode.a',
						'<(output)/libnghttp2.a',
						'<(output)/libcares.a',
						'<@(v8libs)',
					],
					'outputs': [
						'<(output)/libshark.dylib',
					],
					'action': [ 'sh', '-c', 
						'cd <(output);'
						'find obj.target/shark-utils ' 
						'obj.target/shark-gui '
						'obj.target/shark-js '
						'obj.target/node/node -name *.o > shark.LinkFileList;'
						'clang++ '
						'-arch <(arch_name) -dynamiclib '
						'-isysroot <(sysroot) '
						'-L<(output) '
						'-L<(output)/obj.target/ffmpeg '
						'-L<(sysroot)/System/Library/Frameworks '
						'-stdlib=libc++ '
						'-filelist <(output)/shark.LinkFileList '
						'-o <@(_outputs) '
						'-single_module '
						'-install_name @rpath/shark.framework/shark '
						'-Xlinker -rpath -Xlinker @executable_path/Frameworks '
						'-Xlinker -rpath -Xlinker @loader_path/Frameworks '
						'-miphoneos-version-min=<(version_min) '
						'<(embed_bitcode) '
						'-dead_strip '
						'-fobjc-arc '
						'-fobjc-link-runtime  '
						# Link static library
						'-lminizip '
						'-lopenssl '
						'-luv '
						'-lhttp_parser '
						'-lreachability '
						'-ltess2 '
						'-lft2 '
						'-ltinyxml2 '
						'-lffmpeg '
						'-lnode '
						'-lnghttp2 '
						'-lcares '
						'<(v8libs_l) '
						# Link system library
						'-framework Foundation '
						'-framework SystemConfiguration '
						'-framework OpenGLES '
						'-framework CoreGraphics '
						'-framework UIKit '
						'-framework QuartzCore '
						'-framework AudioToolbox '
						'-framework CoreVideo '
						'-framework VideoToolbox '
						'-framework CoreMedia '
						'-framework JavaScriptCore '
						'-framework MessageUI '
						'-liconv '
						'-lbz2 '
						'-lsqlite3 '
						'-lz'
					],
				}]
			}],
		], # conditions
	}],
	
	'conditions': [
		['os not in "ios osx" or project=="xcode"', {
			'includes': [
				'test/test.gypi',
				'test/test2.gypi',
				'tools/tools.gypi',
			],
		}],
	],
}