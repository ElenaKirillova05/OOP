#include "../include/visitor.h"
#include "../include/bear.h"
#include "../include/vup.h"
#include "../include/vykhuhol.h"

bool AttackerVisitor::visit(Bear &bear) {
    return false;
}

bool AttackerVisitor::visit(Vup &vup) {
    return true;
}

bool AttackerVisitor::visit(Vykhuhol &vykhuhol) {
    return true;
}