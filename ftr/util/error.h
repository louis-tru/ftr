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

#ifndef __ftr__util__error__
#define __ftr__util__error__

#include "./string.h"
#include "./errno.h"

#if !FX_EXCEPTIONS_SUPPORT
	#error Exceptions must be turned on
#endif

#define FX_THROW(code, ...) throw ftr::Error(code, __VA_ARGS__)
#define FX_CHECK(cond, ...) if(!(cond)) throw ftr::Error(__VA_ARGS__)

#define FX_IGNORE_ERR(block) try block catch (ftr::Error& err) {    \
	FX_DEBUG("%s,%s", "The exception is ignored", err.message().val());     \
}((void)0)

namespace ftr {

	/**
	* @class Error
	*/
	class FX_EXPORT Error: public Object {
		public:
			Error(const Error& err);
			Error(int code, const char* msg, ...);
			Error(int code = ERR_UNKNOWN_ERROR, cString& msg = "Unknown exception");
			virtual ~Error();
			Error& operator=(const Error& e);
			String message() const throw();
			int    code() const throw();
		private:
			int     _code;
			SString _message;
	};

	typedef const Error cError;
}

#endif
