//
// Created by Bradley Remedios on 11/20/24.
//

#ifndef OVERLAYWINDOW_H
#define OVERLAYWINDOW_H

#include <chrono>

#include <bpl/graphics/LogicObject.h>
#include <bpl/graphics/ui/Window.h>

#include <bpl/dndbeyond/CharacterData.h>

class OverlayUpdater  : public bpl::graphics::LogicObject{
public:
    OverlayUpdater(bpl::graphics::RenderObjectPtr& renderObject);
    ~OverlayUpdater() override = default;

//    void SetSelection(const std::string& selection);

    void Logic(bpl::graphics::RendererPtr& renderer) override;
private:
    void UpdatePlayerDetails_(bpl::graphics::RendererPtr& renderer);
    bool UpdateFiles_(bpl::graphics::RendererPtr& renderer, const std::string characterId, bpl::dndbeyond::CharacterDataPtr ptr, bool forceUpdate);

    std::chrono::time_point<std::chrono::system_clock>  m_nextUpdate = std::chrono::system_clock::now();
    std::chrono::milliseconds                           m_nextUpdateInterval = std::chrono::milliseconds(10000);

    bpl::graphics::RenderObjectPtr m_renderObject;
    bpl::graphics::ui::Window* m_uiWindow=nullptr;
    bool m_firstRun = true;
}; // OverlayWindow

#endif //OVERLAYWINDOW_H