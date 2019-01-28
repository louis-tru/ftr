{
	'variables': {
		'gui_glsl_files': [
			'gl/glsl/_version.glsl',
			'gl/glsl/_util.glsl',
			'gl/glsl/_box.glsl',
			'gl/glsl/_box-radius.glsl',
			'gl/glsl/sprite.glsl',
			'gl/glsl/box-image.glsl',
			'gl/glsl/box-yuv420p-image.glsl',
			'gl/glsl/box-yuv420sp-image.glsl',
			'gl/glsl/box-border.glsl',
			'gl/glsl/box-border-radius.glsl',
			'gl/glsl/box-background-image.glsl',
			'gl/glsl/box-color.glsl',
			'gl/glsl/box-shadow.glsl',
			'gl/glsl/text-box-color.glsl',
			'gl/glsl/text-texture.glsl',
			'gl/glsl/text-vertex.glsl',
			'gl/glsl/gen-texture.glsl',
		],
		'gui_glsl_cpp_files': [
			'../out/glsl-sprite.h',
			'../out/glsl-sprite.cc',
			'../out/glsl-box-image.h',
			'../out/glsl-box-image.cc',
			'../out/glsl-box-yuv420p-image.h',
			'../out/glsl-box-yuv420p-image.cc',
			'../out/glsl-box-yuv420sp-image.h',
			'../out/glsl-box-yuv420sp-image.cc',
			'../out/glsl-box-border.h',
			'../out/glsl-box-border.cc',
			'../out/glsl-box-border-radius.h',
			'../out/glsl-box-border-radius.cc',
			'../out/glsl-box-background-image.h',
			'../out/glsl-box-background-image.cc',
			'../out/glsl-box-color.h',
			'../out/glsl-box-color.cc',
			'../out/glsl-box-shadow.h',
			'../out/glsl-box-shadow.cc',
			'../out/glsl-text-box-color.h',
			'../out/glsl-text-box-color.cc',
			'../out/glsl-text-texture.h',
			'../out/glsl-text-texture.cc',
			'../out/glsl-text-vertex.h',
			'../out/glsl-text-vertex.cc',
			'../out/glsl-gen-texture.h',
			'../out/glsl-gen-texture.cc',
		],
		'gui_default_font_files': [
			'font/DejaVuSerif.ttf',
			'font/icomoon.ttf',
		],
	},
	'targets':[{
		'target_name': 'qgr-gui',
		'type': '<(library)',
		'include_dirs': [
			'..',
			'../out',
		],
		'dependencies': [
			'qgr-utils', 
			'depe/tess2/tess2.gyp:tess2', 
			'depe/freetype2/freetype2.gyp:ft2',
			'depe/ffmpeg/ffmpeg.gyp:ffmpeg',
			'depe/tinyxml2/tinyxml2.gyp:tinyxml2',
		],
		'direct_dependent_settings': {
			'include_dirs': [ '..' ],
		},
		'sources': [
			'<@(gui_glsl_cpp_files)',
			'../out/font-native.cc',
			'player.h',
			'audio-player.h',
			'div.h',
			'indep.h',
			'image.h',
			'bezier.h',
			'display-port.h',
			'event.h',
			'image-codec.h',
			'label.h',
			'layout.h',
			'box.h',
			'text-font.h',
			'pre-render.h',
			'mathe.h',
			'media-codec.h',
			'view.h',
			'draw.h',
			'root.h',
			'sprite.h',
			'scroll.h',
			'span.h',
			'hybrid.h',
			'text-node.h',
			'texture.h',
			'video.h',
			'value.h',
			'pcm-player.h',
			'action.h',
			'action.cc.inl',
			'action.cc',
			'app.h',
			'app.cc',
			'app-1.h',
			'audio-player.cc',
			'div.cc',
			'indep.cc',
			'box-shadow-1.h',
			'box-shadow.cc',
			'limit.h',
			'limit.cc',
			'limit-indep.h',
			'limit-indep.cc',
			'image.cc',
			'bezier.cc',
			'event.cc',
			'display-port.cc',
			'font.h',
			'font/font-1.h',
			'font/font.cc',
			'font/font.cc.1.inl',
			'font/font.cc.3.inl',
			'font/font.cc.font.inl',
			'font/font.cc.family.inl',
			'font/font.cc.glyph.inl',
			'image/codec.cc',
			'image/codec-tga.cc',
			'image/codec-pvrtc.cc',
			'pre-render.cc',
			'mathe.cc',
			'media-codec.cc',
			'media-codec-1.h',
			'media-codec-1.cc',
			'media-codec-software.cc',
			'label.cc',
			'layout.cc',
			'box.cc',
			'text-rows.cc',
			'text-rows.h',
			'view.cc',
			'draw.cc',
			'gl/gl.cc',
			'gl/gl.h',
			'gl/gl-draw.cc',
			'gl/gl-texture.cc',
			'gl/gl-font.cc',
			'root.cc',
			'sprite.cc',
			'scroll.cc',
			'span.cc',
			'hybrid.cc',
			'text-font.cc',
			'text-node.cc',
			'texture.cc',
			'video.cc',
			'value.cc',
			'panel.h',
			'panel.cc',
			'button.h',
			'button.cc',
			'keyboard.h',
			'keyboard.cc',
			'css.h',
			'css.cc.inl',
			'css.cc',
			'property.h',
			'property.cc',
			'text.h',
			'text.cc',
			'input.h',
			'input.cc',
			'textarea.h',
			'textarea.cc',
			'background.h',
			'background.cc',
			'render-looper.cc',
			'sys.h',
			'sys.cc',
		],
		'conditions': [
			['os=="android"', {
				'sources': [
					'platforms/android-gl-1.h',
					'platforms/android-gl.cc',
					'platforms/android-app.cc',
					'platforms/android-media-codec.cc',
					'platforms/android-pcm-player.cc',
					'platforms/android-pcm-audio-track.cc',
					'platforms/android-keyboard.cc',
					'platforms/android-sys.cc',
					'../android/com/qgr/QgrActivity.java',
					'../android/com/qgr/Android.java',
					'../android/com/qgr/IMEHelper.java',
				],
				'link_settings': { 
					'libraries': [ '-lGLESv3', '-lEGL', '-lOpenSLES', '-lmediandk' ],
				},
			}],
			['os not in "ios osx"', { 
				'dependencies': [
					'depe/libgif/libgif.gyp:libgif', 
					'depe/libjpeg-turbo/libjpeg.gyp:libjpeg', 
					'depe/libpng/libpng.gyp:libpng',
					'depe/libwebp/libwebp.gyp:libwebp',
				],
				'sources': [
					'image/codec-gif.cc',
					'image/codec-jpeg.cc',
					'image/codec-png.cc',
					'image/codec-webp.cc',
				]
			}],
			['os=="ios"', {
				'dependencies': [ 
					'depe/reachability/reachability.gyp:reachability', 
				],
				'sources':[
					'platforms/max-app.h',
					'platforms/ios-app.mm',
					'platforms/ios-ime-helper-1.h',
					'platforms/ios-ime-helper.mm',
					'platforms/ios-gl-1.h',
					'platforms/ios-gl.mm',
					'platforms/mac-image-codec.mm',
					'platforms/mac-media-codec.mm',
					'platforms/mac-pcm-player.mm',
					'platforms/mac-keyboard.mm',
					'platforms/mac-sys.mm',
				],
				'link_settings': {
					'libraries': [
						'$(SDKROOT)/System/Library/Frameworks/OpenGLES.framework',
						'$(SDKROOT)/System/Library/Frameworks/CoreGraphics.framework',
						'$(SDKROOT)/System/Library/Frameworks/UIKit.framework',
						'$(SDKROOT)/System/Library/Frameworks/QuartzCore.framework',
						'$(SDKROOT)/System/Library/Frameworks/MessageUI.framework',
					]
				},
			}],
			['os=="osx"', {
				'dependencies': [ 
					'depe/reachability/reachability.gyp:reachability', 
				],
				'sources': [
					'platforms/max-app.h',
					'platforms/osx-app.mm',
					'platforms/mac-image-codec.mm',
					'platforms/mac-media-codec.mm',
					'platforms/mac-pcm-player.mm',
					'platforms/mac-keyboard.mm',
					'platforms/mac-sys.mm',
					# 'platforms/ios-gl-1.h',
					# 'platforms/ios-gl.mm',
				],
				'link_settings': {
					'libraries': [
						'$(SDKROOT)/System/Library/Frameworks/OpenGL.framework',
						'$(SDKROOT)/System/Library/Frameworks/CoreGraphics.framework',
						'$(SDKROOT)/System/Library/Frameworks/AppKit.framework',
						'$(SDKROOT)/System/Library/Frameworks/QuartzCore.framework',
						'$(SDKROOT)/System/Library/Frameworks/IOKit.framework',
					]
				},
			}],
			['os=="linux"', {
				'sources': [
					'platforms/linux-app.cc',
					'platforms/linux-gl.cc',
					'platforms/linux-keyboard.cc',
					'platforms/linux-media-codec.cc',
					'platforms/linux-pcm-player.cc',
					'platforms/linux-ime-helper.cc',
					'platforms/linux-sys.cc',
				],
				'link_settings': { 
					'libraries': [ 
						'-lGLESv2', '-lEGL', '-lX11', '-lasound',
					],
				},
			}],
			# conditions end
		],
		'actions': [
			{
				'action_name': 'gen_glsl_natives',
				'inputs': [
					'../tools/gen-glsl-natives.js',
					'<@(gui_glsl_files)',
				],
				'outputs': [
					'<@(gui_glsl_cpp_files)',
				],
				'action': [
					'<(node)',
					'<@(_inputs)',
					'glsl-',
					'',
				],
			},
			{
				'action_name': 'gen_font_natives',
				'inputs': [
					'../tools/gen-font-natives.js',
					'<@(gui_default_font_files)',
				],
				'outputs': [
					'../out/font-native.h',
					'../out/font-native.cc',
				],
				'action': [
					'<(node)',
					'<@(_inputs)',
					'<@(_outputs)',
				],
			},
		],
		# end
	}]
}