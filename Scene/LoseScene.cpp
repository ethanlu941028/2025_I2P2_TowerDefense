#include <functional>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <ctime>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "LoseScene.hpp"
#include "PlayScene.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"

void LoseScene::Initialize() {
    ticks = 0;
    nameInput.clear();
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    AddNewObject(new Engine::Image("lose/benjamin-happy.png", halfW, halfH, 0, 0, 0.5, 0.5));
    AddNewObject(new Engine::Label("You Lose :(", "pirulen.ttf", 48, halfW, halfH / 4 + 10, 255, 255, 255, 255, 0.5, 0.5));

    nameLabel = new Engine::Label("_", "pirulen.ttf", 60,halfW, halfH, 255, 0, 0, 255, 0.5, 0.5);
    AddNewObject(nameLabel);

    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&LoseScene::BackOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
    bgmInstance = AudioHelper::PlaySample("astronomia.ogg", false, AudioHelper::BGMVolume, PlayScene::DangerTime);
}
void LoseScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}

void LoseScene::Update(float deltaTime) {
    ticks += deltaTime;
    if (ticks > 4 && ticks < 100 &&
        dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
        ticks = 100;}
}

void LoseScene::OnSaveClick(int) {
    std::string name = nameInput.empty() ? "Anonymous" : nameInput;
    int score = -87878787;
    SaveRecord(name, score);
    Engine::GameEngine::GetInstance().ChangeScene("scoreboard-scene");
}

void LoseScene::BackOnClick(int stage) {
    // Change to select scene.
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

void LoseScene::SaveRecord(const std::string& name, int score) {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::ofstream file("Resource/scoreboard.txt", std::ios::app);
    file << name << " " << score << " ";
    file << std::put_time(&tm, "%Y-%m-%d_%H:%M:%S") << "\n";
}

void LoseScene::HandleEvent(const ALLEGRO_EVENT& event) {
    if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
        if (event.keyboard.unichar >= 32 && event.keyboard.unichar <= 126 && nameInput.size() < 16) {
            nameInput += static_cast<char>(event.keyboard.unichar);
        } else if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && !nameInput.empty()) {
            nameInput.pop_back();
        } else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
            std::string name = nameInput.empty() ? "Anonymous" : nameInput;
            int score = -87878787;
            SaveRecord(name, score);
            Engine::GameEngine::GetInstance().ChangeScene("scoreboard-scene");
        }
        // update display
        nameLabel->Text = nameInput + "_";
    }
}

