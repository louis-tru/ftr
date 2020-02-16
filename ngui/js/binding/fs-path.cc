/* ***** BEGIN LICENSE BLOCK *****
 * Distributed under the BSD license:
 *
 * Copyright (c) 2015, xuewen.chu
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of xuewen.chu nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL xuewen.chu BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ***** END LICENSE BLOCK ***** */

#include "nutils/fs.h"
#include "ngui/js/js.h"

/**
 * @ns ngui::js
 */

JS_BEGIN

/**
 * @class NativePath
 */
class NativePath {
 public:

	/**
	 * @func executable()
	 * @ret {String}
	 */
	static void executable(FunctionCall args) {
		JS_WORKER(args);
		JS_RETURN( Path::executable() );
	}
	
	/**
	 * @func documents([path])
	 * @arg path {String}
	 * @ret {String}
	 */
	static void documents(FunctionCall args) {
		JS_WORKER(args);
		if (args.Length() == 0 || !args[0]->IsString(worker)) {
			JS_RETURN( Path::documents() );
		}
		JS_RETURN( Path::documents( args[0]->ToStringValue(worker)) );
	}
	
	/**
	 * @func temp([path])
	 * @arg path {String}
	 * @ret {String}
	 */
	static void temp(FunctionCall args) {
		JS_WORKER(args);
		if (args.Length() == 0 || !args[0]->IsString(worker)) {
			JS_RETURN( Path::temp() );
		}
		JS_RETURN( Path::temp( args[0]->ToStringValue(worker)) );
	}
	
	/**
	 * @func resources([path])
	 * @arg path {String}
	 * @ret {String}
	 */
	static void resources(FunctionCall args) {
		JS_WORKER(args);
		if (args.Length() == 0 || !args[0]->IsString(worker)) {
			JS_RETURN( Path::resources() );
		}
		JS_RETURN( Path::resources( args[0]->ToStringValue(worker)) );
	}

	/**
	 * @func cwd()
	 * @ret {String}
	 */
	static void cwd(FunctionCall args) {
		JS_WORKER(args);
		JS_RETURN( Path::cwd() );
	}
	
	/**
	 * @func chdir(path)
	 * @arg path {String}
	 * @ret {bool}
	 */
	static void chdir(FunctionCall args) {
		JS_WORKER(args);
		if (args.Length() == 0 || !args[0]->IsString(worker)) {
			JS_RETURN( false );
		}
		JS_RETURN( Path::chdir(args[0]->ToStringValue(worker)) );
	}
	
	static void binding(Local<JSObject> exports, Worker* worker) {
		JS_SET_METHOD(executable, executable);
		JS_SET_METHOD(documents, documents);
		JS_SET_METHOD(temp, temp);
		JS_SET_METHOD(resources, resources);
		JS_SET_METHOD(cwd, cwd);
		JS_SET_METHOD(chdir, chdir);
	}
};

JS_REG_MODULE(_path, NativePath);
JS_END
