#ifndef FREEZE_TURRET_H
#define FREEZE_TURRET_H
#include "Turret.hpp"

class FreezeTurret : public Turret {
public:
    static const int Price;
    FreezeTurret(float x, float y);
    void CreateBullet() override;
};
#endif   // FREEZETURRET_HPP
