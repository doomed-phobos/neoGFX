// window.hpp
/*
  neogfx C++ App/Game Engine
  Copyright (c) 2015, 2020 Leigh Johnston.  All Rights Reserved.
  
  This program is free software: you can redistribute it and / or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include <neogfx/neogfx.hpp>
#include <neogfx/hid/video_mode.hpp>
#include <neogfx/gui/window/i_window.hpp>
#include <neogfx/gui/widget/decorated.hpp>
#include <neogfx/gui/widget/nest.hpp>
#include <neogfx/gui/widget/i_nested_window.hpp>
#include <neogfx/hid/i_surface_window.hpp>
#include <neogfx/gui/widget/framed_widget.hpp>
#include <neogfx/gui/widget/scrollable_widget.hpp>
#include <neogfx/gui/layout/vertical_layout.hpp>
#include <neogfx/gui/layout/border_layout.hpp>
#include <neogfx/gui/widget/normal_title_bar.hpp>

namespace neogfx
{
    class i_window_manager;

    class window : public decorated<framed_scrollable_widget, i_window>
    {
        typedef decorated<framed_scrollable_widget, i_window> base_type;
    public:
        define_declared_event(Window, window_event, neogfx::window_event&)
        define_declared_event(DismissingChildren, dismissing_children, const i_widget*)
        define_declared_event(Closed, closed)
        define_declared_event(PaintOverlay, paint_overlay, i_graphics_context&)
    private:
        class nested_details;
        class client;
        typedef std::optional<normal_title_bar> optional_title_bar;
    public:
        struct fullscreen_window_cannot_nest : std::logic_error { fullscreen_window_cannot_nest() : std::logic_error("neogfx::window::fullscreen_window_cannot_nest") {} };
        struct parentless_window_cannot_nest : std::logic_error { parentless_window_cannot_nest() : std::logic_error("neogfx::window::parentless_window_cannot_nest") {} };
    public:
        window(window_style aStyle = window_style::Default, frame_style aFrameStyle = frame_style::WindowFrame, neogfx::scrollbar_style aScrollbarStyle = neogfx::scrollbar_style::Normal);
        window(const window_placement& aPlacement, window_style aStyle = window_style::Default, frame_style aFrameStyle = frame_style::WindowFrame, neogfx::scrollbar_style aScrollbarStyle = neogfx::scrollbar_style::Normal);
        window(const window_placement& aPlacement, const std::string& aWindowTitle, window_style aStyle = window_style::Default, frame_style aFrameStyle = frame_style::WindowFrame, neogfx::scrollbar_style aScrollbarStyle = neogfx::scrollbar_style::Normal);
        window(const std::string& aWindowTitle, window_style aStyle = window_style::Default, frame_style aFrameStyle = frame_style::WindowFrame, neogfx::scrollbar_style aScrollbarStyle = neogfx::scrollbar_style::Normal);
        window(i_widget& aParent, window_style aStyle = window_style::Default, frame_style aFrameStyle = frame_style::WindowFrame, neogfx::scrollbar_style aScrollbarStyle = neogfx::scrollbar_style::Normal);
        window(i_widget& aParent, const window_placement& aPlacement, window_style aStyle = window_style::Default, frame_style aFrameStyle = frame_style::WindowFrame, neogfx::scrollbar_style aScrollbarStyle = neogfx::scrollbar_style::Normal);
        window(i_widget& aParent, const window_placement& aPlacement, const std::string& aWindowTitle, window_style aStyle = window_style::Default, frame_style aFrameStyle = frame_style::WindowFrame, neogfx::scrollbar_style aScrollbarStyle = neogfx::scrollbar_style::Normal);
        window(i_widget& aParent, const std::string& aWindowTitle, window_style aStyle = window_style::Default, frame_style aFrameStyle = frame_style::WindowFrame, neogfx::scrollbar_style aScrollbarStyle = neogfx::scrollbar_style::Normal);
        ~window();
    private:
        window(i_widget* aParent, const window_placement& aPlacement, const std::optional<std::string>& aWindowTitle, window_style aStyle, frame_style aFrameStyle, neogfx::scrollbar_style aScrollbarStyle);
    public:
        window_style style() const override;
        void set_style(window_style aStyle) override;
    public:
        const i_window_manager& window_manager() const override;
        i_window_manager& window_manager() override;
    public:
        bool is_surface() const override;
        bool has_surface() const override;
        const i_surface_window& surface() const override;
        i_surface_window& surface() override;
        bool has_native_surface() const override;
        const i_native_surface& native_surface() const override;
        i_native_surface& native_surface() override;
        bool has_native_window() const override;
        const i_native_window& native_window() const override;
        i_native_window& native_window() override;
    public:
        bool has_parent_window(bool aSameSurface = true) const override;
        const i_window& parent_window() const override;
        i_window& parent_window()  override;
        bool is_parent_of(const i_window& aChildWindow) const override;
        bool is_owner_of(const i_window& aChildWindow) const override;
        const i_window& ultimate_ancestor() const override;
        i_window& ultimate_ancestor() override;
    public:
        const i_nest& nest() const override;
        i_nest& nest() override;
        bool is_nested() const override;
        const i_nested_window& as_nested() const override;
        i_nested_window& as_nested() override;
        bool is_nest() const override;
        const i_nest& as_nest() const override;
        i_nest& as_nest() override;
    public:
        bool is_strong() const override;
        bool is_weak() const override;
    public:
        bool can_close() const override;
        bool is_closed() const override;
        void close() override;
    public:
        color frame_color() const override;
    public:
        bool is_root() const override;
        const i_window& root() const override;
        i_window& root() override;
        void set_parent(i_widget& aParent) override;
        bool can_defer_layout() const override;
        bool is_managing_layout() const override;
        void layout_items_completed() override;
    public:
        void widget_added(i_widget&) override;
        void widget_removed(i_widget& aWidget) override;
    public:
        bool device_metrics_available() const override;
        const i_device_metrics& device_metrics() const override;
    public:
        void resized() override;
        widget_part hit_test(const point& aPosition) const override;
    public:
        neogfx::size_policy size_policy() const override;
        size minimum_size(const optional_size& aAvailableSpace = {}) const override;
    public:
        using widget::update;
        bool update(const rect& aUpdateRect) override;
        void render(i_graphics_context& aGc) const override;
        void paint(i_graphics_context& aGc) const override;
    public:
        color background_color() const override;
    public:
        using widget::show;
        bool show(bool aVisible) override;
    public:
        neogfx::scrolling_disposition scrolling_disposition(const i_widget& aChildWidget) const override;
    public:
        const std::string& title_text() const override;
        void set_title_text(const std::string& aTitleText) override;
    public:
        bool is_active() const override;
        void activate() override;
        bool is_iconic() const override;
        void iconize() override;
        bool is_maximized() const override;
        void maximize() override;
        bool is_restored() const override;
        void restore() override;
        bool is_fullscreen() const override;
        void enter_fullscreen(const video_mode& aVideoMode) override;
        point window_position() const override;
        const window_placement& placement() const override;
        void set_placement(const window_placement& aPlacement) override;
        void center(bool aSetMinimumSize = true) override;
        void center_on_parent(bool aSetMinimumSize = true) override;
        bool window_enabled() const override;
        void counted_window_enable(bool aEnable) override;
        void modal_enable(bool aEnable) override;
    public:
        bool is_dismissing_children() const override;
        bool can_dismiss(const i_widget* aClickedWidget) const override;
        dismissal_type_e dismissal_type() const override;
        bool dismissed() const override;
        void dismiss() override;
    public:
        bool ready_to_render() const override;
        void set_ready_to_render(bool aReady) override;
        double rendering_priority() const override;
        double fps() const override;
        double potential_fps() const override;
    public:
        point mouse_position() const override;
    public:
        neogfx::padding border() const override;
        rect widget_part_rect(widget_part_e aWidgetPart) const override;
    public:
        bool has_client_widget() const override;
        const i_widget& client_widget() const override;
        i_widget& client_widget() override;
        void set_client(i_widget& aClient) override;
        void set_client(std::shared_ptr<i_widget> aClient) override;
    public:
        using base_type::has_layout;
        using base_type::layout;
        bool has_layout(standard_layout aStandardLayout) const override;
        const i_layout& layout(standard_layout aStandardLayout, layout_position aPosition = layout_position::None) const override;
        i_layout& layout(standard_layout aStandardLayout, layout_position aPosition = layout_position::None) override;
    public:
        bool requires_owner_focus() const override;
        bool has_entered_widget() const override;
        i_widget& entered_widget() const override;
    public:
        bool has_focused_widget() const override;
        i_widget& focused_widget() const override;
        void set_focused_widget(i_widget& aWidget, focus_reason aFocusReason) override;
        void release_focused_widget(i_widget& aWidget) override;
    protected:
        void mouse_entered(const point& aPosition) override;
        void mouse_left() override;
    protected:
        void update_modality(bool aEnableAncestors) override;
        void update_click_focus(i_widget& aCandidateWidget, const point& aClickPos) override;
        void dismiss_children(const i_widget* aClickedWidget = nullptr) override;
    public:
        bool is_widget() const override;
        const i_widget& as_widget() const override;
        i_widget& as_widget() override;
    private:
        void init();
    private:
        i_window_manager& iWindowManager;
        i_window* iParentWindow;
        mutable neogfx::window_placement iPlacement;
        bool iClosed;
        sink iSink;
        std::optional<neogfx::nest> iNest;
        std::unique_ptr<i_surface_window> iSurfaceWindow;
        std::unique_ptr<i_nested_window> iNestedWindowDetails;
        bool iReadyToRender;
        std::string iTitleText;
        window_style iStyle;
        int32_t iCountedEnable;
        i_widget* iEnteredWidget;
        i_widget* iFocusedWidget;
        bool iDismissingChildren;
        std::optional<destroyed_flag> iSurfaceDestroyed;
    };
}