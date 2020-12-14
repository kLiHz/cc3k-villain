#include "../races.hpp"

Item * Human::drop_reward(){
    auto g1 = new Gold(Gold::NORMAL);
    //auto g2 = new Gold(Gold::NORMAL);
    // TODO:
    return g1;
}

Item * Merchant::drop_reward() {
    auto g = new Gold(Gold::MERCHANT_HOARD);
    return g;
}

Item * Dragon::drop_reward() {
    auto g = new Gold(Gold::DRAGON_HOARD);
    return g;
}