#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Bullet/FreezeBullet.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"
#include "FreezeTurret.hpp"
#include "Scene/PlayScene.hpp"

const int FreezeTurret::Price = 150;
FreezeTurret::FreezeTurret(float x, float y)
    : Turret("play/tower-base.png", "play/FreezeTurret.png", x, y, 500, Price, 1, 10) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}
void FreezeTurret::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new FreezeBullet(Position + normalized * 36 , diff, rotation, this));
    AudioHelper::PlayAudio("missile.wav");
}
