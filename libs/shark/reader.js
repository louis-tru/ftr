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

export process.binding('shark_reader');

 /**
	* @func readStream(path[,cb])
	* @arg path {String}
	* @arg [cb] {Function}
	* @ret {uint} return read id
	*
	* @func readFile(path[,encoding[,cb]])
	* @arg path {String}
	* @arg [encoding] {Encoding}
	* @arg [cb] {Function}
	* @ret {uint} return read id
	*
	* @func readFileSync(path[,encoding])
	* @arg path {String}
	* @arg [encoding] {Encoding}
	* @ret {Buffer} return read Buffer
	*
	* @func readdirSync(path),ls(path)
	* @arg path {String}
	* @ret {Array}
	*
	* @func existsSync(path)
	* @arg path {String}
	* @ret {bool}
	*
	* @func isFileSync(path)
	* @arg path {String}
	* @ret {bool}
	*
	* @func isDirectorySync(path)
	* @arg path {String}
	* @ret {bool}
	*
	* @func abort(id)
	* @arg id {uint} abort id
	*
	*/
	