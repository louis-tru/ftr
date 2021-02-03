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

#ifndef __ftr__util__string__
#define __ftr__util__string__

#include "./buffer.h"
#include <vector>
#include <stdarg.h>

namespace ftr {

	typedef        char                  Char;
	typedef        ArrayString<uint16_t> String16;
	typedef        ArrayString<uint32_t> String32;
	typedef const  char                  cChar;
	typedef const  ArrayString<uint16_t> cString16;
	typedef const  ArrayString<uint32_t> cString32;

	template<typename T, typename A>
	class FX_EXPORT ArrayString: public Object {
		public:
			// constructors
			ArrayString(); // empty string constructors
			ArrayString(const ArrayString& s); // copy constructors
			ArrayString(ArrayString&& s); // right value copy constructors
			ArrayString(ArrayBuffer<T, A>&& data); // right value copy constructors
			ArrayString(const T* s); // copy constructors
			ArrayString(const T* s, uint32_t len); // copy constructors
			ArrayString(const T* a, uint32_t a_len, const T* b, uint32_t b_len); // copy constructors
			ArrayString(T c); // char to string constructors
			template<typename T2>
			ArrayString(T2 i); // number to string constructors
			
			virtual ~ArrayString();
			virtual String to_string() const;
			
			/**
			 * @func format string
			 */
			static ArrayString format(cChar* format, ...);

			inline bool is_empty() const;
			inline const T* str_c() const;
			inline const T* operator*() const;

			inline T operator[](uint32_t index) const;
			inline uint32_t length() const;
			inline uint32_t capacity() const;

			// assign operator, call assign()
			ArrayString& operator=(const T* s);
			ArrayString& operator=(const ArrayString& s);
			ArrayString& operator=(ArrayString&& s);
			// assign value operator
			ArrayString& assign(const T* s, uint32_t len); // operator=
			// operator+
			// concat string, create new string
			// call ArrayString(const T* a, uint32_t a_len, const T* b, uint32_t b_len)
			ArrayString operator+(const T* s) const;
			ArrayString operator+(const ArrayString& s) const;
			ArrayString operator+(const T s) const;
			// operator+=
			// concat string to current this, call append()
			ArrayString& operator+=(const T* s);
			ArrayString& operator+=(const ArrayString& s);
			ArrayString& operator+=(const T s);
			// append string to current this
			ArrayString& append(const T* s, uint32_t len = 0); // operator+=
			ArrayString& append(const ArrayString& s); // operator+=
			ArrayString& append(const T s); // operator+=
			// get string hash code
			uint64_t hash_code() const;
			// collapse to array buffer
			ArrayBuffer<T, A> collapse();
			ArrayString<T, A> copy() const;
			// operator compare
			bool operator==(const T* s) const;
			inline bool operator==(const ArrayString& s) const { return operator==(s._str->_val); }
			bool operator!=(const T* s) const;
			inline bool operator!=(const ArrayString& s) const { return operator!=(s._str->_val); }
			bool operator> (const T* s) const;
			inline bool operator> (const ArrayString& s) const { return operator>(s._str->_val); }
			bool operator< (const T* s) const;
			inline bool operator< (const ArrayString& s) const { return operator<(s._str->_val); }
			bool operator>=(const T* s) const;
			inline bool operator>=(const ArrayString& s) const { return operator>=(s._str->_val); }
			bool operator<=(const T* s) const;
			inline bool operator<=(const ArrayString& s) const { return operator<=(s._str->_val); }
			// trim
			ArrayString trim() const;
			ArrayString trim_left() const;
			ArrayString trim_right() const;
			// substr
			ArrayString substr(uint32_t start, uint32_t length = 0xFFFFFFFF) const;
			ArrayString substring(uint32_t start, uint32_t end = 0xFFFFFFFF) const;
			// upper, lower
			ArrayString& upper_case(); // change current this string
			ArrayString& lower_case(); // change current this string
			ArrayString  to_upper_case() const; // create new string
			ArrayString  to_lower_case() const; // create new string
			// index_of
			int index_of(const ArrayString& s, uint32_t start = 0) const;
			int last_index_of(const ArrayString& s, uint32_t start = 0x7FFFFFFF) const;
			// replace
			ArrayString replace(const ArrayString& s, const ArrayString& rep) const;
			ArrayString replace_all(const ArrayString& s, const ArrayString& rep) const;
			// split
			std::vector<ArrayString> split(const ArrayString& sp) const;
			// to number
			template<typename T2> T2   to_number()        const;
			template<typename T2> bool to_number(T2* out) const;

		private:
			class LongStr;
			ArrayString(LongStr* str); // ref copy constructors
			T*       val();
			LongStr* _str; // long string
			// T   _short[32]; // to be optimized
			friend class LongStr;
	};

}

// -------------------------------------- IMPL --------------------------------------

namespace ftr {

	class FX_EXPORT _Str {
		public:
		typedef void* (*Alloc)(uint32_t);
		typedef void* (*AAlloc)(void*, uint32_t, uint32_t*, uint32_t);
		struct Size { uint32_t len; uint32_t capacity; };
		static cChar ws[8];
		static bool to_number(const void* i, int sizeof_i, int len_i, int32_t* o);
		static bool to_number(const void* i, int sizeof_i, int len_i, uint32_t* o);
		static bool to_number(const void* i, int sizeof_i, int len_i, int64_t* o);
		static bool to_number(const void* i, int sizeof_i, int len_i, uint64_t* o);
		static bool to_number(const void* i, int sizeof_i, int len_i, float* o);
		static bool to_number(const void* i, int sizeof_i, int len_i, double* o);
		static int32_t format(char* o, uint32_t len_o, cChar* f, ...);
		static void* format(Size* size, int size_of, Alloc alloc, cChar* f, ...);
		static void* format(Size* size, int size_of, Alloc alloc, cChar* f, va_list arg);
		static void* format(Size* size, int size_of, Alloc alloc, int32_t i);
		static void* format(Size* size, int size_of, Alloc alloc, uint32_t i);
		static void* format(Size* size, int size_of, Alloc alloc, int64_t i);
		static void* format(Size* size, int size_of, Alloc alloc, uint64_t i);
		static void* format(Size* size, int size_of, Alloc alloc, float i);
		static void* format(Size* size, int size_of, Alloc alloc, double i);
		static String to_string(const void* ptr, uint32_t len, int size_of);
		static void  strcpy(void* o, int sizeof_o, const void* i, int sizeof_i, uint32_t len);
		template <typename Output, typename Input>
		static void strcpy(Output* o, const Input* i, uint32_t len) {
			strcpy(o, sizeof(Output), i, sizeof(Input), len);
		}
		static uint32_t strlen(const void* s, int size_of);
		template <typename T>
		static uint32_t strlen(const T* s) {
			return strlen(s, sizeof(T));
		}
		static int memcmp(const void* s1, const void* s2, uint32_t len, int size_of);
		// 1 > , -1 <, 0 ==
		template <typename T>
		static int memcmp(const T* s1, const T* s2, uint32_t len) {
			return _Str::memcmp(s1, s2, len, sizeof(T));
		}
		static int32_t index_of(
			const void* s1, uint32_t s1_len,
			const void* s2, uint32_t s2_len, uint32_t start, int size_of
		);
		static int32_t last_index_of(
			const void* s1, uint32_t s1_len,
			const void* s2, uint32_t s2_len, uint32_t start, int size_of
		);
		static void* replace(
			const void* s1, uint32_t s1_len,
			const void* s2, uint32_t s2_len,
			const void* rep, uint32_t rep_len,
			int size_of, uint32_t* out_len, uint32_t* capacity_out, bool all, AAlloc realloc
		);
	};

	template<typename T, typename A> class ArrayString<T, A>::LongStr {
		public:
			LongStr(): _length(0), _capacity(0), _val(nullptr), _ref(1) {}
			LongStr(uint32_t len): _length(len), _capacity(0), _val(nullptr), _ref(1) {
				realloc(len + 1); _val[len] = 0;
			}
			LongStr(const LongStr& str): _length(str._length), _capacity(0), _val(nullptr), _ref(1) {
				realloc(str._capacity);
				::memcpy(_val, str._val, _capacity);
			}
			LongStr(ArrayBuffer<T, A>& arr)
				: _length(arr.length()), _capacity(arr.capacity()), _val(arr.collapse()), _ref(1) {
				if (!_val) {
					_length = _capacity = 0;
					realloc(1); _val[0] = 0;
				}
			}
			LongStr(uint32_t len, uint32_t capacity, T* val)
				: _length(len), _capacity(capacity), _val(val), _ref(1) {
			}

			LongStr* retain() {
				_ref++;
				return this;
			}

			void release() {
				FX_ASSERT(_ref > 0);
				if ( --_ref == 0 ) {
					A:free(_val);
					_val = nullptr;
					delete this; // 只有当引用记数变成0才会释放
				}
			}

			void detach(ArrayString* host) {
				// TODO 修改需要从共享核心中分离出来, 多个线程同时使用一个LongStr可能的安全问题
				if ( _ref > 1 ) { // 大于1表示为共享核心
					host->_str = new LongStr(*this);
					release();
				}
			}

			void realloc(uint32_t capacity) {
				_val = (T*)A::aalloc(_val, capacity, &_capacity, sizeof(T));
			}

			ArrayBuffer<T, A> collapse(ArrayString* host) {
				if (_length == 0) {
					return ArrayBuffer<T, A>();
				} else {
					T* val = _val;
					uint32_t length = _length, capacity = _capacity;
					if (ref() > 1) {
						val = LongStr(*this)._val; // alloc new mem space
					} else {
						_val = nullptr;
					}
					host->_str = empty()->retain(); // use empty string
					release(); // release ref
					return ArrayBuffer<T, A>::from(val, length, capacity);
				}
			}

			inline int ref() const { return _ref; }

			static LongStr* empty() {
				static LongStr* str(new LongStr(0));
				return str;
			}

			static LongStr* empty_retain() {
				return empty()->retain();
			}

			uint32_t _length, _capacity;
			T*       _val;
			std::atomic_int _ref;
	};

	// --------------------------------------------------------------------------------

	template <typename T, typename A>
	ArrayString<T, A>::ArrayString(): _str(LongStr::empty_retain()) {
	}

	template <typename T, typename A>
	ArrayString<T, A>::ArrayString(const ArrayString& s): _str(s._str->retain()) {
	}

	template <typename T, typename A>
	ArrayString<T, A>::ArrayString(ArrayString&& s): _str(s._str) {
		s._str = LongStr::empty_retain();
	}

	template <typename T, typename A>
	ArrayString<T, A>::ArrayString(ArrayBuffer<T, A>&& data): _str(new LongStr(data)) {
	}

	template <typename T, typename A>
	ArrayString<T, A>::ArrayString(const T* s)
		: ArrayString<T, A>(s, _Str::strlen(s)) {
	}

	template <typename T, typename A>
	ArrayString<T, A>::ArrayString(const T* s, uint32_t len): _str(new LongStr(len)) {
		_Str::strcpy(val(), s, len);
	}

	template <typename T, typename A>
	ArrayString<T, A>::ArrayString(const T* a, uint32_t a_len, const T* b, uint32_t b_len): _str(new LongStr(a_len + b_len)) {
		_Str::strcpy(val(),         a, a_len);
		_Str::strcpy(val() + a_len, b, b_len);
	}

	template <typename T, typename A>
	ArrayString<T, A>::ArrayString(const T c): _str(new LongStr(1)) {
		_str->_val[0] = c;
	}

	template <typename T, typename A>
	template <typename T2>
	ArrayString<T, A>::ArrayString(T2 i) {
		_Str::Size size;
		T* str = (T*)_Str::format((_Str::Size*)_str, (int)sizeof(T), &A::alloc, i);
		_str = str ? new LongStr(size.len, size.capacity, str): LongStr::empty_retain();
	}
	
	template <typename T, typename A>
	ArrayString<T, A>::ArrayString(LongStr* str): _str(str) {
	}
	
	template <typename T, typename A>
	ArrayString<T, A>::~ArrayString() {
		_str->release();
	}

	template <typename T, typename A>
	ArrayString<T, A> ArrayString<T, A>::format(cChar* f, ...) {
		va_list arg;
		va_start(arg, f);
		_Str::Size size;
		T* str = (T*)_Str::format(&size, sizeof(T), &A::alloc, f, arg);
		va_end(arg);
		return str ? ArrayString(new LongStr(size.len, size.capacity, str)): ArrayString();
	}

	// --------------------------------------------------------------------------------

	template <typename T, typename A>
	bool ArrayString<T, A>::is_empty() const { return length() == 0; }
	
	template <typename T, typename A>
	T ArrayString<T, A>::operator[](uint32_t index) const { return str_c()[index]; }

	template <typename T, typename A>
	const T* ArrayString<T, A>::str_c() const { return _str->_val; }

	template <typename T, typename A>
	const T* ArrayString<T, A>::operator*() const { return _str->_val; }

	template <typename T, typename A>
	uint32_t ArrayString<T, A>::length() const { return _str->_length; }

	template <typename T, typename A>
	uint32_t ArrayString<T, A>::capacity() const { return _str->_capacity; }
	
	template <typename T, typename A>
	T* ArrayString<T, A>::val() { return _str->_val; }

	// --------------------------------------------------------------------------------

	template <typename T, typename A>
	ArrayString<T, A>& ArrayString<T, A>::operator=(const T* s) {
		return assign(s, _Str::strlen(s));
	}

	template <typename T, typename A>
	ArrayString<T, A>& ArrayString<T, A>::operator=(const ArrayString& s) {
		if (_str != s._str) {
			_str->release();
			_str = s._str->retain();
		}
		return *this;
	}

	template <typename T, typename A>
	ArrayString<T, A>& ArrayString<T, A>::operator=(ArrayString&& s) {
		if (_str != s._str) {
			_str = s._str;
			s._str = LongStr::empty_retain();
		}
		return *this;
	}

	template <typename T, typename A>
	ArrayString<T, A>& ArrayString<T, A>::assign(const T* s, uint32_t len) {
		if (_str->ref() > 1) { // 当前不是唯一引用,抛弃核心创建一个新的核心
			_str->release();
			_str = len ? new LongStr(len): LongStr::empty_retain();
		} else { // 当唯一引用时,调用自动调整容量
			_str->realloc(len + 1);
			_str->_length = len;
		}
		_Str::strcpy(val(), s, len); // copy str
		return *this;
	}

	template <typename T, typename A>
	ArrayString<T, A> ArrayString<T, A>::operator+(const T* s) const {
		return ArrayString(str_c(), length(), s, _Str::strlen(s));
	}

	template <typename T, typename A>
	ArrayString<T, A> ArrayString<T, A>::operator+(const ArrayString& s) const {
		return ArrayString(str_c(), length(), s.str_c(), s.length());
	}
	
	template <typename T, typename A>
	ArrayString<T, A> ArrayString<T, A>::operator+(const T s) const {
		return ArrayString(str_c(), length(), &s, 1);
	}

	template <typename T, typename A>
	ArrayString<T, A>& ArrayString<T, A>::operator+=(const T* s) {
		return append(s, _Str::strlen(s));
	}

	template <typename T, typename A>
	ArrayString<T, A>& ArrayString<T, A>::operator+=(const ArrayString& s) {
		return length() ? append(s.str_c(), s.length()): operator=(s);
	}
	
	template <typename T, typename A>
	ArrayString<T, A>& ArrayString<T, A>::operator+=(const T s) {
		return append(&s, 1);
	}

	template <typename T, typename A>
	ArrayString<T, A>& ArrayString<T, A>::append(const T* s, uint32_t len) {
		if (len > 0) {
			uint32_t old_length = length();
			uint32_t new_length = old_length + len;

			if (_str->ref() > 1) { // 当前不是唯一引用
				auto old_str = _str;
				_str = new LongStr(new_length);
				_Str::strcpy(_str->_val, old_str->_val, old_length);
				old_str->release(); // 并不会真的释放,只是减少一个引用
			}
			else { // 自动调整容量
				_str->realloc(new_length + 1);
				_str->_length = new_length;
			}
			_Str::strcpy(_str->_val + old_length, s, len);
		}
		return *this;
	}

	template <typename T, typename A>
	ArrayString<T, A>& ArrayString<T, A>::append(const ArrayString& s) {
		return operator+=(s);
	}
	
	template <typename T, typename A>
	ArrayString<T, A>& ArrayString<T, A>::append(const T s) {
		return append(&s, 1);
	}

	uint64_t hash_code(const void* data, uint32_t len);

	template <typename T, typename A>
	uint64_t ArrayString<T, A>::hash_code() const {
		return ftr::hash_code(str_c(), length() * sizeof(T));
	}

	template <typename T, typename A>
	ArrayBuffer<T, A> ArrayString<T, A>::collapse() {
		return _str->collapse(this);
	}

	template <typename T, typename A>
	ArrayString<T, A> ArrayString<T, A>::copy() const {
		return length() ? ArrayString(str_c(), length()): ArrayString();
	}

	template <typename T, typename A>
	String ArrayString<T, A>::to_string() const {
		return _Str::to_string(str_c(), length(), sizeof(T));
	}
	
	template <>
	String ArrayString<>::to_string() const;

	template <typename T, typename A>
	ArrayString<T, A> ArrayBuffer<T, A>::collapse_string() {
		return ArrayString<T, A>(std::move(*this));
	}
	
	template <typename T, typename A>
	String ArrayBuffer<T, A>::join(cString& sp) {
		std::vector<String> strs;
		int total = 0;
		for (int i = 0; i < _length; i++) {
			if (i) strs.push_back(sp);
			auto s = _val[i].to_string();
			total += s.length();
			strs.push_back(std::move(s));
		}
		auto buff = Buffer::from(total, total + 1);
		int i = 0;
		for (int i = 0; i < _length; i++) {
			int j = i; i += strs[i].length();
			buff.write(strs[i].str_c(), -1, strs[i].length());
		}
		buff[total] = 0;
		return String(std::move(buff));
	}
	
	// --------------------------------------------------------------------------------

	template <typename T, typename A>
	bool ArrayString<T, A>::operator==(const T* s) const {
		return _Str::memcmp(str_c(), s, length()) == 0;
	}

	template <typename T, typename A>
	bool ArrayString<T, A>::operator!=(const T* s) const {
		return _Str::memcmp(str_c(), s, length()) != 0;
	}

	template <typename T, typename A>
	bool ArrayString<T, A>::operator>(const T* s) const {
		return _Str::memcmp(str_c(), s, length()) > 0;
	}

	template <typename T, typename A>
	bool ArrayString<T, A>::operator<(const T* s) const {
		return _Str::memcmp(str_c(), s, length()) < 0;
	}

	template <typename T, typename A>
	bool ArrayString<T, A>::operator>=(const T* s) const {
		return _Str::memcmp(str_c(), s, length()) >= 0;
	}

	template <typename T, typename A>
	bool ArrayString<T, A>::operator<=(const T* s) const {
		return _Str::memcmp(str_c(), s, length()) <= 0;
	}

	// --------------------------------------------------------------------------------

	template <typename T, typename A>
	ArrayString<T, A> ArrayString<T, A>::trim() const {
		uint32_t start = 0;
		uint32_t len = length();
		uint32_t end = len;
		const T* _val = str_c();
		for (; start < len; start++) {
			if (strchr(_Str::ws, _val[start]) == nullptr) {
				break;
			}
		}
		if (start == len) {
			return ArrayString(); // empty string
		} else {
			for (; end > 0; end--) {
				if (strchr(_Str::ws, _val[end - 1]) == nullptr) {
					break;
				}
			}
		}
		if (start == 0 && end == len) {
			return ArrayString(*this);
		}
		return substring(start, end);
	}

	template <typename T, typename A>
	ArrayString<T, A> ArrayString<T, A>::trim_left() const {
		const T* _val = str_c();
		auto len = length();
		for (uint32_t start = 0; start < len; start++) {
			if (strchr(_Str::ws, _val[start]) == nullptr) {
				if (start == 0) {
					return ArrayString(*this);
				} else {
					return substring(start);
				}
			}
		}
		return ArrayString();
	}

	template <typename T, typename A>
	ArrayString<T, A> ArrayString<T, A>::trim_right() const {
		const T* _val = str_c();
		auto len = length();
		for (uint32_t end = len; end > 0; end--) {
			if (strchr(_Str::ws, _val[end - 1]) == nullptr) {
				if (end == len) {
					return ArrayString(*this);
				} else {
					return substring(0, end);
				}
			}
		}
		return ArrayString();
	}

	template <typename T, typename A>
	ArrayString<T, A> ArrayString<T, A>::substr(uint32_t start, uint32_t len) const {
		return ArrayString(WeakArrayBuffer<T, A>(str_c(), length()).copy(start, start + len));
	}

	template <typename T, typename A>
	ArrayString<T, A> ArrayString<T, A>::substring(uint32_t start, uint32_t end) const {
		return ArrayString(WeakArrayBuffer<T, A>(str_c(), length()).copy(start, end));
	}

	// --------------------------------------------------------------------------------

	template <typename T, typename A>
	ArrayString<T, A>&  ArrayString<T, A>::upper_case() {
		_str->detach(this);
		T* s = val();
		for (uint32_t i = 0, len = length(); i < len; i++, s++) {
			*s = ::toupper(*s);
		}
		return *this;
	}

	template <typename T, typename A>
	ArrayString<T, A>&  ArrayString<T, A>::lower_case() {
		_str->detach(this);
		T* s = val();
		for (uint32_t i = 0, len = length(); i < len; i++, s++) {
			*s = ::tolower(*s);
		}
		return *this;
	}

	template <typename T, typename A>
	ArrayString<T, A> ArrayString<T, A>::to_upper_case() const {
		return ArrayString(*this).upper_case();
	}

	template <typename T, typename A>
	ArrayString<T, A> ArrayString<T, A>::to_lower_case() const {
		return ArrayString(*this).upper_case();
	}

	// --------------------------------------------------------------------------------

	template <typename T, typename A>
	int ArrayString<T, A>::index_of(const ArrayString& s, uint32_t start) const {
		return _Str::index_of(str_c(), length(), s.str_c(), s.length(), start, sizeof(T));
	}

	template <typename T, typename A>
	int ArrayString<T, A>::last_index_of(const ArrayString& s, uint32_t start) const {
		return _Str::last_index_of(str_c(), length(), s.str_c(), s.length(), start, sizeof(T));
	}

	// --------------------------------------------------------------------------------

	template <typename T, typename A>
	ArrayString<T, A> ArrayString<T, A>::replace(const ArrayString& s, const ArrayString& rep) const {
		uint32_t len, capacity;
		T* val = (T*)_Str::replace(
			str_c(), length(), s.str_c(), s.length(),
			rep.str_c(), rep.length(), sizeof(T), &len, &capacity, false, &MemoryAllocator::aalloc
		);
		return ArrayString(new LongStr(len, capacity, val));
	}

	template <typename T, typename A>
	ArrayString<T, A> ArrayString<T, A>::replace_all(const ArrayString& s, const ArrayString& rep) const {
		uint32_t len, capacity;
		T* val = (T*)_Str::replace(
			str_c(), length(), s.str_c(), s.length(),
			rep.str_c(), rep.length(), sizeof(T), &len, &capacity, true, &MemoryAllocator::aalloc
		);
		return ArrayString(new LongStr(len, capacity, val));
	}

	// --------------------------------------------------------------------------------

	template <typename T, typename A>
	std::vector<ArrayString<T, A>>
	ArrayString<T, A>::split(const ArrayString& sp) const {
		std::vector<ArrayString<T, A>> r;
		int splen = sp.length();
		int prev = 0;
		int index = 0;
		while ((index = index_of(sp, prev)) != -1) {
			r.push_back(substring(prev, index));
			prev = index + splen;
		}
		r.push_back( substring(prev) );
		return r;
	}

	// --------------------------------------------------------------------------------

	template<typename T, typename A>
	template<typename T2>
	T2 ArrayString<T, A>::to_number() const {
		T2 o;
		_Str::to_number(str_c(), sizeof(T), length(), &o);
		return o;
	}

	template<typename T, typename A>
	template<typename T2>
	bool ArrayString<T, A>::to_number(T2* o) const {
		return _Str::to_number(str_c(), sizeof(T), length(), o);
	}

}

namespace std {
	template<typename T, typename A>
	struct hash<ftr::ArrayString<T, A>> {
		size_t operator()(const ftr::ArrayString<T, A>& val) const {
			return val.hash_code();
		}
	};
}

#endif
