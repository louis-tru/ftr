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

#ifndef __ftr__util__event__
#define __ftr__util__event__

#include "./util.h"
#include "./error.h"
#include <unordered_map>
#include <list>
#include <functional>

#define FX_EVENT(name, ...) \
	public: inline ftr::EventNoticer<__VA_ARGS__>& on##name () { return _on##name; } \
	private:ftr::EventNoticer<__VA_ARGS__> _on##name; public:

#define FX_INIT_EVENT(name)   _on##name(#name, this)
#define FX_ON(name, ...)      on##name().on( __VA_ARGS__ )
#define FX_ONCE(name, ...)    on##name().once( __VA_ARGS__ )
#define FX_OFF(name, ...)     on##name().off( __VA_ARGS__ )
#define FX_TRIGGER(name, ...) on##name().trigger( __VA_ARGS__ )

namespace ftr {

	template<class SendData = Object, class Sender = Object, class ReturnValue = int> class Event;
	template<class Event = Event<>> class EventNoticer;

	template<class T_SendData, class T_Sender, class T_ReturnValue>
	class FX_EXPORT Event: public Object {
			FX_HIDDEN_ALL_COPY(Event);
		public:
			typedef T_SendData       SendData;
			typedef T_Sender         Sender;
			typedef T_ReturnValue    ReturnValue;
			typedef const SendData   cSendData;
			typedef EventNoticer<Event> Noticer;
			ReturnValue return_value;
		private:
			Noticer*    _noticer;
			cSendData*  _data;
		public:
			Event(cSendData& data = SendData())
				: return_value(), _noticer(nullptr), _data(&data) {}
			Event(cSendData& data, ReturnValue&& r_value)
				: return_value(std::move(r_value)), _noticer(nullptr), _data(&data) {}

			// "new" method alloc can call，Otherwise, fatal exception will be caused
			virtual void release() {
				_noticer = nullptr;
				_data = nullptr;
				Object::release();
			}
			inline Noticer* noticer() { return this->_noticer; }
			inline String name() const { return this->_noticer->_name; }
			inline Sender* sender() { return this->_noticer->_sender; }
			inline cSendData* data() const { return _data; }
			
			class BasicEventNoticer: public Object {
				protected:
					inline static void set_event(Noticer* noticer, Event& evt) {
						evt._noticer = noticer;
					}
			};

			friend class BasicEventNoticer;
	};

	template<class Event>
	class FX_EXPORT EventNoticer: public Event::BasicEventNoticer {
			FX_HIDDEN_ALL_COPY(EventNoticer);
		public:
			typedef Event EventType;
			typedef typename Event::SendData        SendData;
			typedef typename Event::cSendData       cSendData;
			typedef typename Event::Sender          Sender;
			typedef typename Event::ReturnValue     ReturnValue;
			typedef std::function<void(Event&)>     ListenerFunc;

		protected:
			class Listener {
				public:
					inline Listener(EventNoticer* noticer) { _noticer = noticer; }
					virtual ~Listener() { }
					virtual void call(Event& evt) = 0;
					virtual bool is_on_listener() { return false; }
					virtual bool is_on_static_listener() { return false; }
					virtual bool is_on_shell_listener() { return false; }
					virtual bool is_on_func_listener() { return false; }
				protected:
					EventNoticer* _noticer;
			};
			
			// On
			template<class Scope> class OnListener: public Listener {
				public:
					typedef void (Scope::*ListenerFunc)(Event& evt);
					inline OnListener(EventNoticer* noticer, ListenerFunc listener, Scope* scope)
					: Listener(noticer), _scope(scope), _listener( listener ) {}
					virtual bool is_on_listener() { return true; }
					virtual void call(Event& evt) { (_scope->*_listener)(evt); }
					inline bool equals(ListenerFunc listener) { return _listener == listener; }
					inline bool equals(Scope* scope) { return _scope == scope; }
				protected:
					Scope*       _scope;
					ListenerFunc _listener;
			};

			// ONCE
			template<class Scope> class OnceListener: public OnListener<Scope> {
				public:
					typedef typename OnListener<Scope>::ListenerFunc ListenerFunc;
					inline OnceListener(EventNoticer* noticer, ListenerFunc listener, Scope* scope)
					: OnListener<Scope>(noticer, listener, scope) {}
					virtual void call(Event& evt) {
						(this->_scope->*this->_listener)(evt);
						this->_noticer->off2(this);
					}
			};
			
			// STATIC
			template<class Data> class OnStaticListener: public Listener {
				public:
					typedef void (*ListenerFunc)(Event& evt, Data* data);
					inline OnStaticListener(EventNoticer* noticer, ListenerFunc listener, Data* data)
					: Listener(noticer), _listener(listener), _data(data) {}
					virtual bool is_on_static_listener() { return true; }
					virtual void call(Event& evt) { _listener(evt, _data); }
					inline bool equals(ListenerFunc listener) { return _listener == listener; }
					inline bool equals(Data* data) { return _data == data; }
				protected:
					ListenerFunc _listener;
					Data*        _data;
			};
			
			// Once STATIC
			template<class Data> class OnceStaticListener: public OnStaticListener<Data> {
				public:
					typedef typename OnStaticListener<Data>::ListenerFunc ListenerFunc;
					inline OnceStaticListener(EventNoticer* noticer, ListenerFunc listener, Data* data)
					: OnStaticListener<Data>(noticer, listener, data) {}
					virtual void call(Event& evt) {
						this->_listener(evt);
						this->_noticer->off2(this);
					}
			};
			
			// Function
			class OnLambdaFunctionListener: public Listener {
				public:
					inline OnLambdaFunctionListener(EventNoticer* noticer, ListenerFunc&& listener, int id)
					: Listener(noticer), _listener(std::move(listener)), _id(id) {}
					virtual bool is_on_func_listener() { return true; }
					virtual void call(Event& evt) { _listener(evt); }
					inline bool equals(int id) { return id == _id; }
				protected:
					ListenerFunc _listener;
					int          _id;
			};
			
			// Once Function
			class OnceLambdaFunctionListener: public OnLambdaFunctionListener {
				public:
					inline OnceLambdaFunctionListener(EventNoticer* noticer, ListenerFunc&& listener, int id)
					: OnLambdaFunctionListener(noticer, std::move(listener), id) {}
					virtual void call(Event& evt) {
						this->_listener(evt);
						this->_noticer->off2(this);
					}
			};
			
			// SHELL
			class OnShellListener: public Listener {
				public:
					inline OnShellListener(EventNoticer* noticer, EventNoticer* shell)
					: Listener(noticer), _shell(shell) {}
					virtual bool is_on_shell_listener() { return true; }
					virtual void call(Event& evt) {
						this->_shell->trigger(evt);
						this->_noticer->set_event2(evt);
					}
					inline bool equals(EventNoticer* shell) { return _shell == shell; }
				protected:
					EventNoticer* _shell;
			};
			
			// Once Shell
			class OnceShellListener: public OnShellListener {
				public:
					inline OnceShellListener(EventNoticer* noticer, EventNoticer* shell)
					: OnShellListener(noticer, shell) {}
					virtual void action(Event& evt) {
						this->_shell->trigger(evt);
						this->_noticer->set_event2(evt);
						this->_noticer->off2(this);
					}
			};
			
		private:

			typedef typename std::list<Listener*>::iterator iterator;
			struct LWrap {
				Listener* listener;
				Listener* operator->() { return listener; }
				Listener* value() { return listener; }
				void del() { delete listener; listener = nullptr; }
			};
			String             _name;
			Sender*            _sender;
			std::list<LWrap>*  _listener;
			friend class  ftr::Event<SendData, Sender, ReturnValue>;
			friend class  OnShellListener;
			friend class  OnceShellListener;
			
		public:
			
			inline EventNoticer(cString& name, Sender* sender = nullptr)
				: _name(name), _sender(sender), _listener(nullptr) {}
			
			virtual ~EventNoticer() {
				if (_listener) {
					off();
					Release(_listener);
				}
			}
			
			/**
			* @fun name
			*/
			inline String name() const { return _name; }
			
			/**
			* @func sender
			*/
			inline Sender* sender() const { return _sender; }
			
			/**
			* @fun count # 获取侦听器数量
			*/
			inline int count() const {
				return _listener ? _listener->length() : 0;
			}

			template<class Scope>
			void on(void (Scope::*listener)(Event&), Scope* scope) throw(Error) {
				get_listener();
				assert2(listener, scope);
				_listener->push( { new OnListener<Scope>(this, listener, scope) } );
			}

			template <class Data>
			void on( void (*listener)(Event&, Data*), Data* data = nullptr) throw(Error) {
				get_listener();
				assert_static(listener, data);
				_listener->push( { new OnStaticListener<Data>(this, listener, data) } );
			}

			void on( ListenerFunc listener, int id = 0) {
				get_listener();
				_listener->push( { new OnLambdaFunctionListener(this, std::move(listener), id) } );
			}

			void on(EventNoticer* shell) throw(Error) {
				get_listener();
				assert_shell(shell);
				_listener->push( { new OnShellListener(this, shell) } );
			}

			template<class Scope>
			void once(void (Scope::*listener)(Event&), Scope* scope) throw(Error) {
				get_listener();
				assert2(listener, scope);
				_listener->push( { new OnceListener<Scope>(this, listener, scope) } );
			}
			
			template <class Data>
			void once( void (*listener)(Event&, Data*), Data* data = nullptr) throw(Error) {
				get_listener();
				assert_static(listener, data);
				_listener->push( { new OnceStaticListener<Data>(this, listener, data) } );
			}
			
			void once( ListenerFunc listener, int id = 0) {
				get_listener();
				_listener->push( { new OnceLambdaFunctionListener(this, std::move(listener), id) } );
			}
			
			void once(EventNoticer* shell) throw(Error) {
				get_listener();
				assert_shell(shell);
				_listener->push( { new OnceShellListener(this, shell) } );
			}

			template<class Scope>
			void off( void (Scope::*listener)(Event&) ) {
				if (_listener) {
					typedef OnListener<Scope> OnListener2;
					for ( auto& i : *_listener ) {
						if ( i.value().value() && i.value()->is_on_listener() &&
								static_cast<OnListener2*>(i.value().value())->equals( listener ) ) {
							i.value().del();
						}
					}
				}
			}

			template<class Scope>
			void off( void (Scope::*listener)(Event&), Scope* scope) {
				if (_listener) {
					typedef OnListener<Scope> OnListener2;
					for ( auto& i : *_listener ) {
						if( i.value().value() && i.value()->is_on_listener() &&
								static_cast<OnListener2*>(i.value().value())->equals(listener) &&
								static_cast<OnListener2*>(i.value().value())->equals( scope ) ) {
							i.value().del();
							break;
						}
					}
				}
			}
			
			template<class Data>
			void off( void (*listener)(Event&, Data*) ) {
				if (_listener) {
					typedef OnStaticListener<Data> OnListener2;
					for ( auto& i : *_listener ) {
						if ( i.value().value() && i.value()->is_on_static_listener() &&
								static_cast<OnListener2*>(i.value().value())->equals(listener) ) {
							i.value().del();
							break;
						}
					}
				}
			}
			
			template<class Data>
			void off( void (*listener)(Event&, Data*), Data* data) {
				if (_listener) {
					typedef OnStaticListener<Data> OnListener2;
					for ( auto& i : *_listener ) {
						if ( i.value().value() && i.value()->is_on_static_listener() &&
								static_cast<OnListener2*>(i.value().value())->equals(listener) &&
								static_cast<OnListener2*>(i.value().value())->equals(data) ) {
							i.value().del();
							break;
						}
					}
				}
			}
			
			void off(int id) {
				if (_listener) {
					for ( auto& i : *_listener ) {
						if ( i.value().value() && i.value()->is_on_func_listener() &&
									static_cast<OnLambdaFunctionListener*>(i.value().value())->equals(id)
							)
						{//
							i.value().del();
						}
					}
				}
			}
			
			template<class Scope>
			void off(Scope* scope) {
				if (_listener) {
					typedef OnListener<Scope> OnListener2;
					typedef OnStaticListener<Scope> OnListener3;
					for ( auto& i : *_listener ) {
						if ( i.value().value &&
								(
									(
										i.value()->is_on_listener() &&
										static_cast<OnListener2*>(i.value().value())->equals(scope)
									) ||
									(
										i.value()->is_on_static_listener() &&
										static_cast<OnListener3*>(i.value().value())->equals(scope)
									)
								)
							)
						{//
							i.value().del();
						}
					}
				}
			}
			
			void off(EventNoticer* shell) {
				if (_listener) {
					for ( auto& i : *_listener ) {
						if ( i.value().value() && i.value()->is_on_shell_listener() &&
								static_cast<OnShellListener*>(i.value())->equals( shell ) )
						{ //
							i.value().del();
							break;
						}
					}
				}
			}

			void off() {
				if (_listener) {
					for ( auto& i : *_listener ) {
						i.value().del();
					}
				}
			}
			
			ReturnValue trigger() {
				if (_listener) {
					Event evt;
					return std::move( trigger(evt) );
				}
				return std::move( ReturnValue() );
			}
			
			ReturnValue trigger(cSendData& data) {
				if (_listener) {
					Event evt(data);
					return std::move( trigger(evt) );
				}
				return std::move( ReturnValue() );
			}
			
			ReturnValue& trigger(Event& evt) {
				if (_listener) {
					set_event2(evt);
					for (auto i = _listener->begin(); i != _listener->end(); ) {
						auto j = i++;
						Listener* listener = j.value().listener;
						if ( listener ) {
							// TODO:
							// listener->mListener 如果为空指针或者野指针,会导致程序崩溃。。
							// 应该在对像释放前移除事件侦听器，这对于大型gui程序无GC的c++是非常糟糕的,
							// 在VC中有delegate,在QT中有SIGNAL/SLOT,
							// 幸好我们的程序是运行在js环境中的,无需对原生的api有过多的依赖。
							listener->call(evt);
						} else {
							_listener->del(j);
						}
					}
				}
				return evt.return_value;
			}
		
		private:

			inline void set_event2(Event& evt) {
				this->set_event(reinterpret_cast<typename Event::Noticer*>(this), evt);
			}
			
			inline void get_listener() {
				ASSERT(!_name.is_null());
				if (_listener == nullptr) {
					_listener = new std::list<LWrap>();
				}
			}
			
			void off2(Listener* listener) {
				for ( auto& i : *_listener ) {
					if ( i.value().value() == listener ) {
						i.value().del();
						break;
					}
				}
			}
			
			template<class Scope>
			void assert2(void (Scope::*listener)(Event&), Scope* scope) throw(Error) {
				typedef OnListener<Scope> OnListener2;
				for ( auto& i : *_listener ) {
					if ( i.value().value() && i.value()->is_on_listener() ) {
						FX_CHECK( !(static_cast<OnListener2*>(i.value().value())->equals( listener ) &&
												static_cast<OnListener2*>(i.value().value())->equals( scope )),
												ERR_DUPLICATE_LISTENER,
												"Noticers have been added over the letter");
					}
				}
			}
			
			template<class Data>
			void assert_static(void (*listener)(Event&, Data*), Data* data) throw(Error) {
				typedef OnStaticListener<Data> OnStaticListener2;
				for ( auto& i : *_listener ) {
					if ( i.value().value() && i.value()->is_on_static_listener() ) {
						FX_CHECK( !(static_cast<OnStaticListener2*>(i.value().value())->equals( listener ) &&
												static_cast<OnStaticListener2*>(i.value().value())->equals( data )),
												ERR_DUPLICATE_LISTENER,
												"Noticers have been added over the letter");
					}
				}
			}
			
			void assert_shell(EventNoticer* shell) throw(Error) {
				for ( auto& i : *_listener ) {
					if ( i.value().value() && i.value()->is_on_shell_listener() ) {
						FX_CHECK( !static_cast<OnShellListener*>(i.value().value())->equals( shell ),
											ERR_DUPLICATE_LISTENER,
											"Noticers have been added over the letter");
					}
				}
			}
	};

	/**
	* @class Notification
	*/
	template<
		class Event = Event<>,
		class Name  = String,
		class Basic = Object
	>
	class FX_EXPORT Notification: public Basic {
			FX_HIDDEN_ALL_COPY(Notification);
		public:
			typedef Event EventType;
			typedef Name  NameType;
			typedef EventNoticer<Event>            Noticer;
			typedef typename Event::SendData       SendData;
			typedef typename Event::cSendData      cSendData;
			typedef typename Event::Sender         Sender;
			typedef typename Event::ReturnValue    ReturnValue;
			typedef typename Noticer::ListenerFunc ListenerFunc;

			inline Notification()
				: _noticers(nullptr) {
			}
			
			virtual ~Notification() {
				if ( _noticers ) {
					for (auto& i : *_noticers) {
						delete i.value();
					}
					Release(_noticers);
					_noticers = nullptr;
				}
			}

			Noticer* get_noticer(const Name& name) const {
				if ( _noticers != nullptr ) {
					auto it = _noticers->find(name);
					if (!it.is_null()) {
						return &it.value()->value;
					}
				}
				return nullptr;
			}

			bool has_noticer(const Name& name) const {
				if ( _noticers != nullptr ) {
					return _noticers->find(name) != _noticers->end();
				}
				return false;
			}
			
			/**
			* 是否没有任何事件
			* @ret {bool}
			*/
			inline bool is_noticer_none() const {
				return _noticers == nullptr || _noticers->size() == 0;
			}
			
			/**
			* 侦听器变化会通知到该函数,比如添加删除事件侦听器
			* @arg name {const Type&}
			* @arg count {int}
			*/
			virtual void trigger_listener_change(const Name& name, int count, int change) {}
			
			template<class Scope>
			inline void add_event_listener(const Name& name,
										void (Scope::*listener)(Event&),
										Scope* scope) {
				auto del = get_noticer2(name);
				del->on(listener, scope);
				trigger_listener_change(name, del->count(), 1);
			}
			
			template<class Scope>
			inline void add_event_listener_once(const Name& name,
											void (Scope::*listener)(Event&),
											Scope* scope) {
				auto del = get_noticer2(name);
				del->once(listener, scope);
				trigger_listener_change(name, del->count(), 1);
			}
			
			template<class Data>
			inline void add_event_listener(const Name& name,
										void (*listener)(Event&, Data*),
										Data* data = nullptr) {
				auto del = get_noticer2(name);
				del->once(listener, data);
				trigger_listener_change(name, del->count(), 1);
			}
			
			template<class Data>
			inline void add_event_listener_once(const Name& name,
											void (*listener)(Event&, Data*),
											Data* data = nullptr) {
				auto del = get_noticer2(name);
				del->once(listener, data);
				trigger_listener_change(name, del->count(), 1);
			}
			
			inline void add_event_listener( const Name& name, ListenerFunc listener, int id = 0) {
				auto del = get_noticer2(name);
				del->on(listener, id);
				trigger_listener_change(name, del->count(), 1);
			}
			
			inline void add_event_listener_once( const Name& name, ListenerFunc listener, int id = 0) {
				auto del = get_noticer2(name);
				del->once(listener, id);
				trigger_listener_change(name, del->count(), 1);
			}
			
			inline void add_event_listener(const Name& name, Noticer* shell) {
				auto del = get_noticer2(name);
				del->on(shell);
				trigger_listener_change(name, del->count(), 1);
			}
			
			/**
			* 添加一个侦听器,只侦听一次,后被卸载
			*/
			inline void add_event_listener_once(const Name& name, Noticer* shell) {
				auto del = get_noticer2(name);
				del->once(shell);
				trigger_listener_change(name, del->count(), 1);
			}
			
			template<class Scope>
			inline void remove_event_listener(const Name& name,
											void (Scope::*listener)(Event&)
											) {
				auto del = get_noticer(name);
				if (del) {
					del->off(listener);
					trigger_listener_change(name, del->count(), -1);
				}
			}
			
			template<class Scope>
			inline void remove_event_listener(const Name& name,
											void (Scope::*listener)(Event&), Scope* scope) {
				auto del = get_noticer(name);
				if (del) {
					del->off(listener, scope);
					trigger_listener_change(name, del->count(), -1);
				}
			}
			
			template<class Data>
			inline void remove_event_listener(const Name& name,
												void (*listener)(Event&, Data*)
											) {
				auto del = get_noticer(name);
				if (del) {
					del->off(listener);
					trigger_listener_change(name, del->count(), -1);
				}
			}
			
			template<class Data>
			inline void remove_event_listener(const Name& name,
											void (*listener)(Event&, Data*),
											Data* data) {
				auto del = get_noticer(name);
				if (del) {
					del->off(listener, data);
					trigger_listener_change(name, del->count(), -1);
				}
			}
			
			/**
			* @func off
			*/
			inline void remove_event_listener(const Name& name, int id) {
				auto del = get_noticer(name);
				if (del) {
					del->off(id);
					trigger_listener_change(name, del->count(), -1);
				}
			}
			
			/**
			* @func off
			*/
			inline void remove_event_listener(int id) {
				if (_noticers) {
					auto end = _noticers->end();
					for (auto i = _noticers->begin(); i != end; i++) {
						NoticerWrap* item = &i.value();
						item->value.off(id);
						trigger_listener_change(item->name, item->value.count(), -1);
					}
				}
			}
			
			/**
			* 卸载这个范围里的所有侦听器
			*/
			template<class Scope> 
			inline void remove_event_listener(Scope* scope) {
				if (_noticers) {
					for ( auto& i : *_noticers ) {
						NoticerWrap* inl = i.value();
						inl->value.off(scope);
						trigger_listener_change(inl->name, inl->value.count(), -1);
					}
				}
			}
			
			inline void remove_event_listener(const Name& name, Noticer* shell) {
				auto del = get_noticer(name);
				if (del) {
					del->off(shell);
					trigger_listener_change(name, del->count(), -1);
				}
			}
			
		protected:
			
			/**
			* 卸载指定事件名称上的全部侦听函数
			*/
			inline void remove_event_listener(const Name& name) {
				auto del = get_noticer(name);
				if (del) {
					del->off();
					trigger_listener_change(name, del->count(), -1);
				}
			}
			
			/**
			* 卸载全部侦听函数
			*/
			inline void remove_event_listener() {
				if (_noticers) {
					for ( auto& i : *_noticers ) {
						NoticerWrap* inl = i.value();
						inl->value.off();
						trigger_listener_change(inl->name, inl->value.count(), -1);
					}
				}
			}
			
			/**
			* 触发事件
			* @arg name {const Key&}
			* NOTE: 这个方法能创建默认事件数据
			*/
			inline ReturnValue trigger(const Name& name) {
				auto del = get_noticer(name);
				return std::move( del ? del->trigger(): ReturnValue() );
			}
			
			/*
			* 触发事件
			* @arg name {const Key&}
			* @arg evt {cSendData&}
			*/
			inline ReturnValue trigger(const Name& name, cSendData& data) {
				auto del = get_noticer(name);
				return std::move( del ? del->trigger(data): ReturnValue() );
			}
			
			/*
			* 触发事件
			* @arg name {const Key&}
			* @arg evt {Event&}
			*/
			inline ReturnValue& trigger(const Name& name, Event& evt) {
				auto del = get_noticer(name);
				return del ? del->trigger(evt): evt.return_value;
			}
		
		private:

      struct NoticerWrap {
        inline NoticerWrap() { FX_UNREACHABLE(); }
        inline NoticerWrap(const Name& t, Sender* sender)
        : name(t), value(t.to_string(), sender) { }
        Name    name;
        Noticer value;
      };

			typedef std::unordered_map<Name, NoticerWrap*> Noticers;
			
			Noticer* get_noticer2(const Name& name) {
				if (_noticers == nullptr) {
					_noticers = new Noticers();
				}
				auto it = _noticers->find(name);
				if (it != _noticers->end()) {
					return &it.value()->value;
				} else {
					return &_noticers->set(name, new NoticerWrap(name, static_cast<Sender*>(this)))->value;
				}
			}

			Noticers* _noticers;
	};

}
#endif
