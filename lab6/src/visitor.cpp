#include "../include/visitor.h"
#include "../include/bear.h"
#include "../include/vup.h"
#include "../include/vykhuhol.h"

bool AttackerVisitor::visit(Bear &bear) {
    auto temp_bear = std::make_shared<Bear>(bear);
    return attacker_->fight(temp_bear);
}

bool AttackerVisitor::visit(Vup &vup) {
    auto temp_vup = std::make_shared<Vup>(vup);
    return attacker_->fight(temp_vup);
}

bool AttackerVisitor::visit(Vykhuhol &vykhuhol) {
    auto temp_vykhuhol = std::make_shared<Vykhuhol>(vykhuhol);
    return attacker_->fight(temp_vykhuhol);
}