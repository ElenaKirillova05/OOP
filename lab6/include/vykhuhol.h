#pragma once
#include "npc.h"

struct Vykhuhol : public NPC {
    Vykhuhol(int x, int y);
    Vykhuhol(std::istream &is);

    void print() override;

    bool accept(Visitor &visitor) override;

    bool fight(std::shared_ptr<Bear> other) override;
    bool fight(std::shared_ptr<Vup> other) override;
    bool fight(std::shared_ptr<Vykhuhol> other) override;

    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Vykhuhol &vykhuhol);
};