#ifndef WINSCENE_HPP
#define WINSCENE_HPP
#include "Engine/IScene.hpp"
#include <allegro5/allegro_audio.h>
#include <string>

namespace Engine {
    class Label;
    class ImageButton;
};

class WinScene final : public Engine::IScene {
private:
    float ticks;
    ALLEGRO_SAMPLE_ID bgmId;

    // for name input
    std::string nameInput;
    Engine::Label* nameLabel;

    void SaveRecord(const std::string& name, int score);
    void OnSaveClick(int dummy);

public:
    explicit WinScene() = default;
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void HandleEvent(const ALLEGRO_EVENT& event) ;  // to capture key events
    void BackOnClick(int stage);
};

#endif   // WINSCENE_HPP