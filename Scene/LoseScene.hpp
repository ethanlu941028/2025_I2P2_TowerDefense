#ifndef LOSESCENE_HPP
#define LOSESCENE_HPP
#include "Engine/IScene.hpp"
#include <allegro5/allegro_audio.h>
#include <memory>
#include <string>

namespace Engine {
    class Label;
    class ImageButton;
};

class LoseScene final : public Engine::IScene {
private:
    float ticks;
    ALLEGRO_SAMPLE_ID bgmId;

    // for name input
    std::string nameInput;
    Engine::Label* nameLabel;

    void SaveRecord(const std::string& name, int score);
    void OnSaveClick(int dummy);
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;

public:
    explicit LoseScene() = default;
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void HandleEvent(const ALLEGRO_EVENT& event) ;  // to capture key events
    void BackOnClick(int stage);
};

#endif   // LOSESCENE_HPP
