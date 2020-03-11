{
	'targets': [
	{
		'target_name': 'ngui-v8',
		'type': '<(output_shared)',
		'dependencies': [
			'depe/v8-link/v8-link.gyp:v8-link',
			'depe/v8-link/v8-link.gyp:v8_libplatform-link',
		],
	},
	{
		'target_name': 'ngui-node',
		'type': '<(output_shared)',
		'dependencies': [
			'nxkit',
			'ngui',
			'ngui-js',
			'ngui-v8',
			'depe/node/node.gyp:node',
		],
	},
	{
		'target_name': 'ngui-js',
		'type': '<(output_type)',
		'include_dirs': [
			'../..',
			'../../out',
			'../../depe/node/deps/uv/include',
			'../../depe/node/deps/openssl/openssl/include',
		],
		'dependencies': [
			'nxkit',
			'ngui',
			'ngui-v8',
		],
		'direct_dependent_settings': {
			'include_dirs': [ '../..' ],
			'mac_bundle_resources': [],
		},
		'defines': [ 'NODE_WANT_INTERNALS=1' ],
		'sources': [
			'js-1.h',
			'js-cls.cc',
			'js.cc',
			'js.h',
			'ngui.h',
			'ngui.cc',
			'str.h',
			'str.cc',
			'v8.cc',
			'value.h',
			'wrap.h',
			'wrap.cc',
			'node.cc',
			# binding nxkit
			'binding/cb-1.h',
			'binding/cb.cc',
			'binding/fs-1.h',
			'binding/fs.cc',
			'binding/fs-reader.cc',
			'binding/fs-path.cc',
			'binding/http.cc',
			'binding/util.cc',
			'binding/storage.cc',
			'binding/json-1.h',
			'binding/json.cc',
			'binding/event-1.h',
			'binding/event.cc',
			'binding/sys.cc',
			'binding/event.cc',
			'binding/timer.cc',
			'binding/console.cc',
			'binding/buffer.cc',
			# binding ngui
			'binding/value.cc',
			'binding/binding.cc',
			'binding/action.cc',
			'binding/action-frame.cc',
			'binding/app.cc',
			'binding/audio-player.cc',
			'binding/video.cc',
			'binding/media.cc',
			'binding/div.cc',
			'binding/display-port.cc',
			'binding/indep.cc',
			'binding/image.cc',
			'binding/layout.cc',
			'binding/box.cc',
			'binding/view.cc',
			'binding/root.cc',
			'binding/span.cc',
			'binding/sprite.cc',
			'binding/hybrid.cc',
			'binding/text-font.cc',
			'binding/text-node.cc',
			'binding/label.cc',
			'binding/limit.cc',
			'binding/panel.cc',
			'binding/button.cc',
			'binding/scroll.cc',
			'binding/css.cc',
			'binding/font.cc',
			'binding/text.cc',
			'binding/input.cc',
			'binding/background.cc',
		],
		'conditions': [
			['v8_enable_inspector==1', { 'defines': [ 'HAVE_INSPECTOR=1' ] }],
			['node_use_openssl=="true"', { 'defines': [ 'HAVE_OPENSSL=1' ] }],
			['node_use_dtrace=="true"', { 'defines': [ 'HAVE_DTRACE=1' ] }],
		],
		'actions': [
			{
				'action_name': 'build_ngui_',
				'inputs': [
					'../../libs/ngui/tsconfig.json',
				],
				'outputs': [],
				'action': [ 'sh', '-c', 'cd libs/ngui && npm run build' ]
			},
			{
				'action_name': 'gen_inl_js_natives',
				'variables': {
					'files': [
						'../../out/_event.js',
						'../../out/_value.js',
					],
				},
				'inputs': [
					'../../tools/gen-js-natives.js',
					'<@(files)',
				],
				'outputs': [
					'../../out/native-inl-js.h',
					'../../out/native-inl-js.cc',
				],
				'action': [
					'<(node)',
					'<@(_inputs)',
					'',
					'INL',
					'wrap',
					'<@(_outputs)',
				],
				'process_outputs_as_sources': 1,
			},
			{
				'action_name': 'gen_lib_js_natives',
				'variables': {
					'files': [
						'../../out/_pkg.js',
						'../../out/_pkgutil.js',
					],
				},
				'inputs': [
					'../../tools/gen-js-natives.js',
					'<@(files)',
				],
				'outputs': [
					'../../out/native-lib-js.h',
					'../../out/native-lib-js.cc',
				],
				'action': [
					'<(node)',
					'<@(_inputs)',
					'',
					'LIB',
					'wrap',
					'<@(_outputs)',
				],
				'process_outputs_as_sources': 1,
			},
			{
				'action_name': 'gen_ext_js_natives_',
				'variables': {
					'NGUI': 'libs/ngui/out/ngui',
					'files': [
						'../../libs/ngui/out/ngui/_action.js',
						'../../libs/ngui/out/ngui/_common.js',
						'../../libs/ngui/out/ngui/_event.js',
						'../../libs/ngui/out/ngui/_ext.js',
						'../../libs/ngui/out/ngui/_path.js',
						'../../libs/ngui/out/ngui/_pkgutil.js',
						'../../libs/ngui/out/ngui/_util.js',
						'../../libs/ngui/out/ngui/_view.js',
						'../../libs/ngui/out/ngui/action.js',
						'../../libs/ngui/out/ngui/app.js',
						'../../libs/ngui/out/ngui/buffer.js',
						'../../libs/ngui/out/ngui/checkbox.js',
						'../../libs/ngui/out/ngui/css.js',
						'../../libs/ngui/out/ngui/ctr.js',
						'../../libs/ngui/out/ngui/dialog.js',
						'../../libs/ngui/out/ngui/display_port.js',
						'../../libs/ngui/out/ngui/event.js',
						'../../libs/ngui/out/ngui/font.js',
						'../../libs/ngui/out/ngui/fs.js',
						'../../libs/ngui/out/ngui/http.js',
						'../../libs/ngui/out/ngui/media.js',
						'../../libs/ngui/out/ngui/nav.js',
						'../../libs/ngui/out/ngui/overlay.js',
						'../../libs/ngui/out/ngui/package.json',
						'../../libs/ngui/out/ngui/path.js',
						'../../libs/ngui/out/ngui/pkg.js',
						'../../libs/ngui/out/ngui/index.js',
						'../../libs/ngui/out/ngui/reader.js',
						'../../libs/ngui/out/ngui/stepper.js',
						'../../libs/ngui/out/ngui/storage.js',
						'../../libs/ngui/out/ngui/sys.js',
						'../../libs/ngui/out/ngui/timer.js',
						'../../libs/ngui/out/ngui/util.js',
						'../../libs/ngui/out/ngui/value.js',
					],
				},
				'inputs': [
					'../../tools/gen-js-natives.js',
					'<@(files)',
				],
				'outputs': [
					'../../out/native-ext-js.h',
					'../../out/native-ext-js.cc',
				],
				'action': [
					'<(node)',
					'<@(_inputs)',
					'ngui',
					'EXT',
					'',
					'<@(_outputs)',
				],
				'process_outputs_as_sources': 1,
			},
		],
	},
	],

	'conditions': [
		['os!="ios"', {
			'targets+': [
			{
				'target_name': 'ngui_exec',
				'product_name': 'ngui',
				'type': 'executable',
				'dependencies': [
					'nxkit',
					'ngui',
					'ngui-js',
					'ngui-media',
					'ngui-node',
					'ngui-v8',
				],
				'sources': [
					'main.cc',
				],
				'ldflags': [ '<@(other_ldflags)' ],
			}],
		}]
	],
}
