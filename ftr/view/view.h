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

#ifndef __ftr__view__view__
#define __ftr__view__view__

#include "../util/object.h"
#include "../value.h"

namespace ftr {

	class Action;

	/**
	 * The basic elements of GUI tree
	 *
	 * @class View
	 */
	class FX_EXPORT View: public Reference {
		FX_HIDDEN_ALL_COPY(View);
		public:

		/**
		 * @constructors
		 */
		View();

		/**
		 * @destructor
		 */
		virtual ~View();

		// *******************************************************************
		/**
		 * parent view
		 *
		 * @func parent()
		 */
		inline View* parent() {
			return _parent;
		}

		/**
		 * first subview
		 *
		 * @func first()
		 */
		inline View* first() {
			return _first;
		}

		/**
		 * last subview
		 *
		 * @func last()
		 */
		inline View* last() {
			return _last;
		}

		/**
		 * Previous sibling view
		 *
		 * @func prev()
		 */
		inline View* prev() {
			return _prev;
		}

		/**
		 * Next sibling view
		 *
		 * @func nect()
		 */
		inline View* next() {
			return _next;
		}

		/**
		 *
		 * Add a sibling view to the front
		 *
		 * @func before(view)
		 */
		void before(View* view);

		/**
		 *
		 * Add a sibling view to the back
		 *
		 * @func after(view)
		 */
		void after(View* view);

		/**
		 * 
		 * Append subview to front
		 * 
		 * @func prepend(child)
		 */
		void prepend(View* child);

		/**
		 *
		 * Append subview to end
		 *
		 * @func append(child)
		 */
		void append(View* child);

		/**
		 *
		 * Remove and destroy self
		 * 
		 * @func remove()
		 */
		virtual void remove();

		/**
		 *
		 * remove all subview
		 *
		 * @func remove_all_child()
		 */
		virtual void remove_all_child();

		/**
		 *
		 * Setting parent parent view
		 *
		 * @func set_parent(parent)
		 */
		protected: virtual void set_parent(View* parent);

		/**
		 *
		 * Redraw view and subview
		 * 
		 * @func draw()
		 */
		virtual void draw();

		/**
		 *
		 * Does the view need to receive or handle event throws from the system
		 *
		 * @func receive()
		 */
		public: inline bool receive() const {
			return _receive;
		}

		/**
		 *
		 * Returns visibility for the view
		 *
		 * @func visible()
		 */
		inline bool visible() const {
			return _visible;
		}

		/**
		* 
		* Returns region visibility for the view
		* 
		* @func region_visible
		*/
		inline bool region_visible() const {
			return _region_visible;
		}
		
		/**
		 * 
		 * Sets whether the view needs to receive or handle event throws from the system
		 *
		 * @func set_receive()
		 */
		void set_receive(bool val);

		/**
		 * 
		 * Setting the visibility properties the view object
		 *
		 * @func set_visible(val)
		 */
		virtual void set_visible(bool val);

		// *******************************************************************
		/**
		 * Returns the objects that automatically adjust view properties
		 *
		 * @func action()
		 */
		inline Action* action() {
			return _action;
		}

		/**
		 * Returns matrix displacement for the view
		 *
		 * @func translate
		 */
		inline Vec2 translate() const {
			return _translate;
		}

		/**
		 * Returns the Matrix scaling
		 *
		 * @func scale()
		 */
		inline Vec2 scale() const {
			return _scale;
		}

		/**
		 * Returns the Matrix skew
		 *
		 * @func skew()
		 */
		inline Vec2 skew() const {
			return _skew;
		}

		/**
		 * Returns the z-axis rotation of the matrix
		 *
		 * @func rotate()
		 */
		inline float rotate() const {
			return _rotate;
		}

		/**
		 * 
		 * Returns x-axis matrix displacement for the view
		 *
		 * @func x()
		 */
		inline float x() const {
			return _translate.x();
		}

		/**
		 * 
		 * Returns y-axis matrix displacement for the view
		 *
		 * @func y()
		 */
		inline float y() const {
			return _translate.y();
		}

		/**
		 * 
		 * Returns x-axis matrix scaling for the view
		 *
		 * @func scale_x()
		 */
		inline float scale_x() const {
			return _scale.x();
		}

		/**
		 * 
		 * Returns y-axis matrix scaling for the view
		 *
		 * @func scale_y()
		 */
		inline float scale_y() const {
			return _scale.y();
		}

		/**
		 * 
		 * Returns x-axis matrix skew for the view
		 *
		 * @func skew_x()
		 */
		inline float skew_x() const {
			return _skew.x();
		}

		/**
		 * 
		 * Returns y-axis matrix skew for the view
		 *
		 * @func skew_y()
		 */
		inline float skew_y() const {
			return _skew.y();
		}

		/**
		 *
		 * Returns the can affect the transparency of subviews
		 *
		 * @func opacity()
		 */
		inline float opacity() {
			return _opacity;
		}

		// *******************************************************************
		/**
		 * Set the `action` properties of the view object
		 *
		 * @func set_action()
		 */
		void set_action(Action* val);

		/**
		 * Set the matrix `translate` properties of the view object
		 *
		 * @func set_translate()
		 */
		void set_translate(Vec2 val);

		/**
		 * Set the matrix `scale` properties of the view object
		 *
		 * @func set_scale()
		 */
		void set_scale(Vec2 val);

		/**
		 * Set the matrix `skew` properties of the view object
		 *
		 * @func set_skew()
		 */
		void set_skew(Vec2 val);

		/**
		 * Set the z-axis  matrix `rotate` properties the view object
		 *
		 * @func set_rotate()
		 */
		void set_rotate(float val);

		/**
		 * 
		 * Setting x-axis matrix displacement for the view
		 *
		 * @func x()
		 */
		void set_x(float val);

		/**
		 * 
		 * Setting y-axis matrix displacement for the view
		 *
		 * @func y()
		 */
		void set_y(float val);

		/**
		 * 
		 * Returns x-axis matrix scaling for the view
		 *
		 * @func scale_x()
		 */
		void scale_x(float val);

		/**
		 * 
		 * Returns y-axis matrix scaling for the view
		 *
		 * @func scale_y()
		 */
		void scale_y(float val);

		/**
		 * 
		 * Returns x-axis matrix skew for the view
		 *
		 * @func skew_x()
		 */
		void skew_x(float val);

		/**
		 * 
		 * Returns y-axis matrix skew for the view
		 *
		 * @func skew_y()
		 */
		void skew_y(float val);

		/**
		 * Set the `opacity` properties the view object
		 *
		 * @func set_opacity()
		 */
		void set_opacity(float val);

		/**
		 * 
		 * setting the layout weight of the view object
		 * 
		 * @func set_layout_weight(val)
		 */
		void set_layout_weight(float val);

		// *******************************************************************
		/**
		 *
		 * 从外向内正向迭代布局，比如一些布局方法是先从外部到内部先确定盒子的明确尺寸
		 * 
		 * @func layout_forward()
		 */
		virtual void layout_forward();

		/**
		 * 
		 * 从内向外反向迭代布局，比如有些视图外部并没有明确的尺寸，
		 * 尺寸是由内部视图挤压外部视图造成的，所以只能先明确内部视图的尺寸
		 * 
		 * @func layout_reverse()
		 */
		virtual void layout_reverse();

		/**
		 * 
		 * Setting the layout offset of the view object in the parent view
		 *
		 * @func set_layout_offset(val)
		 */
		void set_layout_offset(Vec2 val);

		/**
		 * 当一个父布局视图对其中所有的子视图进行布局时，为了调整各个子视图合适位置与尺寸，会调用这个函数对子视图做尺寸上的限制
		 * 这个函数被调用后，其它调用尺寸更改的方法都应该失效，但应该记录被设置的数值一旦解除锁定后设置属性的才能生效
		 * 
		 * 调用`layout_size_lock(false)`解除锁定
		 * 
		 * 子类实现这个方法
		 * 
		 * @func layout_size_lock()
		 */
		virtual void layout_size_lock(bool lock, Vec2 layout_size = Vec2());

		/**
		 * 
		 * This method of the parent view is called when the layout weight of the child view changes
		 *
		 * @func layout_weight_change_notice_from_child(child)
		 */
		virtual void layout_weight_change_notice_from_child(View* child);

		/**
		 *
		 * This method of the parent view is called when the layout size of the child view changes
		 * 
		 * @func layout_size_change_notice_from_child()
		 */
		virtual void layout_size_change_notice_from_child(View* child);

		/**
		 * @func layout_size_change_notice_from_parent(parent)
		 */
		virtual void layout_size_change_notice_from_parent(View* parent);

		// *******************************************************************
		/**
		 * 
		 * Relative to the parent view (layout_offset) to start offset
		 * 
		 * @func layout_offset()
		 */
		inline Vec2 layout_offset() const {
			return _layout_offset;
		}

		/**
		 * 
		 * Relative to the parent view (layout_offset) to start offset，end position
		 * 
		 * @func layout_offset_end()
		 */
		inline Vec2 layout_offset_end() const {
			return _layout_offset + _layout_size;
		}

		/**
		 *
		 * Returns the layout size of view object (if is box view the: size=margin+border+padding+content)
		 *
		 * @func layout_size()
		 */
		Vec2 layout_size() const {
			return _layout_size;
		}

		/**
		 *
		 * Returns the layout content size of object view, 
		 * Returns false to indicate that the size is unknown
		 *
		 * @func layout_content_size(size)
		 */
		virtual bool layout_content_size(Vec2& size);

		/**
		 * Returns internal layout offset compensation of the view, which affects the sub view offset position
		 * 
		 * For example: when a view needs to set the scrolling property scroll of a subview, you can set this property
		 *
		 * @func layout_offset_inside()
		 */
		virtual Vec2 layout_offset_inside();

		/**
		 * 
		 * Returns layout transformation matrix of the object view
		 * 
		 * Mat(layout_offset + layout_origin + translate - parent->layout_inside_offset, scale, rotate, skew)
		 * 
		 * @func layout_matrix()
		 */
		Mat layout_matrix() const;

		/**
		 * Start the matrix transformation from this origin point
		 *
		 * @func layout_origin()
		 */
		inline Vec2 layout_origin() const {
			return _layout_origin;
		}

		/**
		 *
		 * 布局权重（比如在flex布局中代表布局的尺寸）
		 *
		 * @func layout_weight()
		 */
		inline float layout_weight() {
			return _layout_weight;
		}

		/**
		 * 
		 * Returns final transformation matrix of the view layout
		 *
		 * parent.transform_matrix * layout_matrix
		 * 
		 * @func transform_matrix()
		 */
		const Mat& transform_matrix();

		// *******************************************************************
		private: Action *_action; // 动作：在一定的时间内根据动作设定的程序自动修改视图属性
		private: View *_parent;
		private: View *_first, *_last, *_prev, *_next;
		private: View *_next_pre_mark; /* 下一个预处理视图标记 */
																	/* 在绘图前需要调用`layout_forward`与`layout_reverse`处理这些被标记过的视图*/
		private: Vec2  _translate, _scale, _skew; // 平移向量, 缩放向量, 倾斜向量
		private: float _rotate;     // z轴旋转角度值
		private: float _opacity;    // 可影响子视图的透明度值
		protected: Vec2  _layout_origin; // 最终以该点 位移,缩放,旋转,歪斜
		private:   Vec2  _layout_offset; // 相对父视图的开始偏移位置（box包含margin值）
		protected: Vec2  _layout_size; // 在布局中所占用的尺寸（margin+border+padding+content）
		private:  float  _layout_weight; // layout weight
		private:  Mat _transform_matrix; // 父视图矩阵乘以布局矩阵等于最终变换矩阵 (parent.transform_matrix * layout_matrix)
		// private: uint16_t _level; // 在视图树中所处的层级
		protected: bool _visible; // 视图是否可见
		protected: bool _region_visible; // 这个值与`visible`完全无关，这个代表视图在当前显示区域是否可见，这个显示区域大多数情况下就是屏幕
		private: bool _receive; // 视图是否需要接收或处理系统的事件抛出，大部情况下这些事件都是不需要处理的，这样可以提高整体事件处理效率

		FX_DEFINE_INLINE_CLASS(Inl);
	};

}

#endif