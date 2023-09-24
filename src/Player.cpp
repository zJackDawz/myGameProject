#include "Player.h"

Player::Player(int initialValue) {
    memberVariable = initialValue;
}

int Player::getValue() {
    return memberVariable;
}

void Player::setValue(int newValue) {
    memberVariable = newValue;
}