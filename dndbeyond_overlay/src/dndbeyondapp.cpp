//
// Created by Bradley Remedios on 11/20/24.
//
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <bpl/graphics/FontCache.h>
#include <bpl/graphics/RenderObject.h>
#include <bpl/graphics/LogicObject.h>
#include <bpl/graphics/Window.h>
#include <bpl/graphics/EventLoop.h>
#include <bpl/graphics/ui/Window.h>
#include <bpl/dndbeyond/Api.h>

#include "OverlayUpdater.h"

#define OVERLAY_WIDTH 640
#define OVERLAY_HEIGHT 120

int RunOverlay() {
    std::cout << "D&D Beyond Overlay";

    if (SDL_Init(SDL_INIT_VIDEO)< 0) {
        std::cerr << "SDL Could not initialize.  SDL ERROR: " << SDL_GetError() << std::endl;

        return -1;
    }

    if (TTF_Init() < 0) {
        std::cerr << "SDL TTF Could not initialize.  SDL ERROR: " << SDL_GetError() << std::endl;

        SDL_Quit();
        return -1;
    }


    do {
        bpl::graphics::WindowPtr window = bpl::graphics::Window::CreateInstance("D&D Beyond Overlay", 640, 120, false);

        if (!window->isValid()) {
            std::cerr << "Failed to create window" << std::endl;

            break;
        }

        bpl::graphics::RendererPtr renderer = bpl::graphics::Renderer::CreateInstance(window);

        if (!renderer->isValid()) {
            std::cerr << "Failed to create renderer" << std::endl;

            break;
        }

        bpl::graphics::ui::Window* uiWindowPtr = new bpl::graphics::ui::Window("resources/overlays/player-overview.json");

        if (!uiWindowPtr->Load(renderer)) {
            std::cerr << "Failed to load UI Window" << std::endl;

            delete uiWindowPtr;

            break;
        }

        bpl::graphics::RenderObjectPtr renderObj = bpl::graphics::RenderObjectPtr(uiWindowPtr);

        bpl::graphics::EventLoopPtr loop = std::make_shared<bpl::graphics::EventLoop>();

        OverlayUpdater* updater = new OverlayUpdater(renderObj);

        bpl::graphics::LogicObjectPtr logicObj = bpl::graphics::LogicObjectPtr(updater);

        loop->setFramerate(30);
        loop->setRenderer(renderer);
        loop->addRenderObject(renderObj);
        loop->addLogicObject(logicObj);
        loop->Run();

    } while (false);

    bpl::graphics::FontCache::getInstance()->Clear();

    TTF_Quit();
    SDL_Quit();

    return 0;
} // RunOverlay

int RunApp() {

    std::cout << "dndbeyondapp" << std::endl;


    std::cout << "Getting D&D Beyond Character Sheet" << std::endl;

    auto characterData = bpl::dndbeyond::Api::GetCharacterData("96556934");

    if (nullptr == characterData.get()) {
        std::cerr << "GetCharacterData failed" << std::endl;
        return -1;
    }

    std::string name = characterData->getApiData().getName();

    int baseHp = characterData->getApiData().getBaseHitPoints();
    int bonusHp = characterData->getApiData().getBonusHitPoints();
    int tempHp = characterData->getApiData().getTemporaryHitPoints();
    int removedHp = characterData->getApiData().getRemovedHitPoints();

    std::cout << name << std::endl;
    std::cout << "    Hit Points: " << baseHp + bonusHp + tempHp - removedHp << std::endl;
    std::cout << "        Base:      " << baseHp << std::endl;
    std::cout << "        Bonus:     " << bonusHp << std::endl;
    std::cout << "        Temporary: " << tempHp << std::endl;
    std::cout << "        Removed:   " << removedHp << std::endl << std::endl;
    std::cout << "    Stats:" << std::endl;
    std::cout << "        Strength:     " << characterData->getApiData().getStats().getStat(bpl::dndbeyond::api::STAT_STR) << " (+" << characterData->getApiData().getStats().getStatMod(bpl::dndbeyond::api::STAT_STR) << ")" << std::endl;
    std::cout << "        Dexterity:    " << characterData->getApiData().getStats().getStat(bpl::dndbeyond::api::STAT_DEX) << " (+" << characterData->getApiData().getStats().getStatMod(bpl::dndbeyond::api::STAT_DEX) << ")" << std::endl;
    std::cout << "        Constitution: " << characterData->getApiData().getStats().getStat(bpl::dndbeyond::api::STAT_CON) << " (+" << characterData->getApiData().getStats().getStatMod(bpl::dndbeyond::api::STAT_CON) << ")" << std::endl;
    std::cout << "        Intelligence: " << characterData->getApiData().getStats().getStat(bpl::dndbeyond::api::STAT_INT) << " (+" << characterData->getApiData().getStats().getStatMod(bpl::dndbeyond::api::STAT_INT) << ")" << std::endl;
    std::cout << "        Wisdom:       " << characterData->getApiData().getStats().getStat(bpl::dndbeyond::api::STAT_WIS) << " (+" << characterData->getApiData().getStats().getStatMod(bpl::dndbeyond::api::STAT_WIS) << ")" << std::endl;
    std::cout << "        Charisma:     " << characterData->getApiData().getStats().getStat(bpl::dndbeyond::api::STAT_CHA) << " (+" << characterData->getApiData().getStats().getStatMod(bpl::dndbeyond::api::STAT_CHA) << ")" << std::endl;
    return 0;

} // RunApp

int main (int argc, char**argv) {
    bool enableOverlay = false;

    if (2 == argc) {
        std::string option = argv[1];

        if (option == "--enable-overlay") {
            enableOverlay = true;
        }
    }

    //if (enableOverlay) {
        return RunOverlay();
    //}
    //else {
    //    std::cout << "D&D Beyond Viewer";
    //    return RunApp();
    //}
} // main