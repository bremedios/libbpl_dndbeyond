//
// Created by Bradley Remedios on 11/20/24.
//
#include <iostream>
#include <filesystem>

#include <bpl/net/Http.h>
#include <bpl/graphics/draw/ops/Fill.h>
#include <bpl/graphics/draw/ops/Image.h>
#include <bpl/graphics/draw/ops/Text.h>

#include <bpl/dndbeyond/Api.h>

#include "OverlayUpdater.h"
#include "Debug.h"

#define FONT_INTRO "fonts/Roboto-Regular.ttf"

OverlayUpdater::OverlayUpdater(bpl::graphics::RenderObjectPtr& renderObject) {
    m_renderObject = renderObject;

    m_uiWindow = dynamic_cast<bpl::graphics::ui::Window*>(renderObject.get());
} // OverlayUpdater

bool OverlayUpdater::UpdateFiles_(bpl::graphics::RendererPtr& renderer, const std::string characterId, bpl::dndbeyond::CharacterDataPtr ptr, bool forceUpdate) {
    DEBUG_MSG("Updating files...");

    if (!std::filesystem::exists(".cached")) {
        DEBUG_MSG("Cache  folder does not exist, creating");

        if (!std::filesystem::create_directory(".cached")) {
            ERROR_MSG("Failed to create directory .cached");

            return false;
        }
    }

    if (forceUpdate || !std::filesystem::exists(".cached/avatar.jpg")) {
        DEBUG_MSG("Avatar does not exist or update forced");

        bpl::net::Http http;

        if (!http.Create()) {
            ERROR_MSG("Api::GetCharacterData: http.Create() failed");

            return false;
        }

        if (!http.Get(ptr->getDecorations().getAvatarUrl())) {
            ERROR_MSG("Api::GetCharacterData: http get failed for " << ptr->getDecorations().getAvatarUrl());

            return false;
        }

        if (!http.getPayload().Save(std::string(".cached/avatar.jpg"))) {
            ERROR_MSG("http.getPayload().Save(" << ".cached/" + characterId << "...) failed");

            return false;
        }

        if (m_uiWindow->getJsonLoader().GetOpMap().contains("avatar")) {
            bpl::graphics::draw::ops::OpPtr ptr = m_uiWindow->getJsonLoader().GetOpMap()["avatar"];

            bpl::graphics::draw::ops::ImagePtr imagePtr = std::dynamic_pointer_cast<bpl::graphics::draw::ops::Image>(ptr);

            if (!imagePtr->Reload(renderer)) {
                ERROR_MSG("Failed to reload avatar image");

                return false;
            }
        }
        else {
            DEBUG_MSG("No avatar in uiWindow, cannot reload avatar");
        }
    }

    return true;
} // UpdateFiles_

void OverlayUpdater::UpdatePlayerDetails_(bpl::graphics::RendererPtr& renderer) {
    auto characterData = bpl::dndbeyond::Api::GetCharacterData("96556934");

    if (nullptr == characterData.get()) {
        std::cerr << "GetCharacterData failed" << std::endl;
        return;
    }

    std::string name = characterData->getApiData().getName();

    int baseHp = characterData->getApiData().getBaseHitPoints();
    int bonusHp = characterData->getApiData().getBonusHitPoints();
    int tempHp = characterData->getApiData().getTemporaryHitPoints();
    int removedHp = characterData->getApiData().getRemovedHitPoints();

    int totalHitPoints = baseHp + bonusHp;
    int actualHitPoints = totalHitPoints + tempHp - removedHp;
    int ac = characterData->getApiData().getArmorClass();

    std::string hitPoints = std::to_string(actualHitPoints) + " / " + std::to_string(totalHitPoints);

    float injurePercent = 1.0f - (static_cast<float>(actualHitPoints) / static_cast<float>(totalHitPoints));

    uint8_t red = 0;
    uint8_t green = 255;
    uint8_t blue = 0;

    if (injurePercent < 0.5f) {
      green = 255;
      red = static_cast<uint8_t>(255.0f * injurePercent * 2.0f);
    }
    else {
        red = 255;
        green = static_cast<uint8_t>(255.0f * (1.0f - injurePercent) * 2.0f);
    }
#if 0
    if (injurePercent > 0.10f) {
        red = 0;
        blue = 0;
        green = 255;
    }
    else if (injurePercent > 0.20f) {
        red = 0;
        blue = 0;
        green = 0;
    }
    else if (injurePercent > 0.30f) {
        red = 0;
        blue = 0;
        green = 0;
    }
    else if (injurePercent > 0.40f) {
        red = 0;
        blue = 0;
        green = 0;
    }
    else if (injurePercent > 0.50f) {
        red = 255;
        blue = 0;
        green = 255;
    }
    else if (injurePercent > 0.60f) {
        red = ;
        blue = 0;
        green = 0;
    }
    else if (injurePercent > 0.70f) {
        red = 0;
        blue = 0;
        green = 0;
    }
    else if (injurePercent > 0.80f) {
        red = 0;
        blue = 0;
        green = 0;
    }
    else if (injurePercent > 0.90f) {
        red = 255;
        blue = 0;
        green = 0;
    }
#endif

    UpdateFiles_(renderer, "96556934", characterData, m_firstRun);

    m_firstRun = false;

    if (m_uiWindow->getJsonLoader().GetOpMap().contains("player-name")) {
        bpl::graphics::draw::ops::OpPtr ptr = m_uiWindow->getJsonLoader().GetOpMap()["player-name"];

        bpl::graphics::draw::ops::TextPtr textPtr = std::dynamic_pointer_cast<bpl::graphics::draw::ops::Text>(ptr);

        textPtr->setValue(name);
    }

    if (m_uiWindow->getJsonLoader().GetOpMap().contains("hit-points")) {
        bpl::graphics::draw::ops::OpPtr ptr = m_uiWindow->getJsonLoader().GetOpMap()["hit-points"];

        bpl::graphics::draw::ops::TextPtr textPtr = std::dynamic_pointer_cast<bpl::graphics::draw::ops::Text>(ptr);

        textPtr->setValue(std::to_string(actualHitPoints));
    }

    if (m_uiWindow->getJsonLoader().GetOpMap().contains("hit-point-max")) {
        bpl::graphics::draw::ops::OpPtr ptr = m_uiWindow->getJsonLoader().GetOpMap()["hit-point-max"];

        bpl::graphics::draw::ops::TextPtr textPtr = std::dynamic_pointer_cast<bpl::graphics::draw::ops::Text>(ptr);

        textPtr->setValue(std::to_string(totalHitPoints));
    }

    if (m_uiWindow->getJsonLoader().GetOpMap().contains("background")) {
        bpl::graphics::draw::ops::OpPtr ptr = m_uiWindow->getJsonLoader().GetOpMap()["background"];

        bpl::graphics::draw::ops::FillPtr fillPtr = std::dynamic_pointer_cast<bpl::graphics::draw::ops::Fill>(ptr);

        fillPtr->setColor(red, green, blue);
    }

    if (m_uiWindow->getJsonLoader().GetOpMap().contains("armor-class")) {
        bpl::graphics::draw::ops::OpPtr ptr = m_uiWindow->getJsonLoader().GetOpMap()["armor-class"];

        bpl::graphics::draw::ops::TextPtr textPtr = std::dynamic_pointer_cast<bpl::graphics::draw::ops::Text>(ptr);

        textPtr->setValue(std::to_string(ac));
    }

}//UpdatePlayerDetails_

void OverlayUpdater::Logic(bpl::graphics::RendererPtr& renderer, bpl::controls::InputPtr& input) {
    auto now = std::chrono::system_clock::now();

    if (now > m_nextUpdate) {
        m_nextUpdate = std::chrono::system_clock::now() + m_nextUpdateInterval;

        UpdatePlayerDetails_(renderer);
    }
} // Update