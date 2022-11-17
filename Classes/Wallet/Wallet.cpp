#include "Wallet.h"

Wallet::Wallet() {
    if (!texture.loadFromFile("../Storage/Coin_Gems/Coin.png")) {
        MessageBox(nullptr, "Unable to open coinTexture.", "Error!", MB_OK);
        return;
    }
    if (!anim.loadFromXML("../Storage/Coin_Gems/Coin.xml", texture)) {
        MessageBox(nullptr, "Unable to open coin animation.", "Error!", MB_OK);
        return;
    }
    anim.animMap["Coin"].loop = true;
    anim.set("Coin");

    gold = 0;
}

void Wallet::setGoldText() {
    goldText.setFont(font);
    std::stringstream tmp;
    tmp << gold;
    goldText.setString(tmp.str());
    goldText.setCharacterSize(25);
    goldText.setFillColor(Color::White);
    sf::Vector2f textPos;
    textPos.x = 520;
    textPos.y = 10;
    goldText.setPosition(textPos);
}

void Wallet::draw(sf::RenderWindow & window) {
    window.draw(goldText);
    anim.draw(window, 480, 10);
}

int Wallet::getGold() const {
    return gold;
}

bool Wallet::isAfford(int amount) const {
    if (this->gold >= amount)
        return true;
    return false;
}

void Wallet::pay(int amount) {
    gold -= amount;

    std::stringstream tmp;
    tmp << gold;
    goldText.setString(tmp.str());
}

//void Wallet::setPosition(const sf::Vector2f position) {
//    coin.setPosition(position);
//
//    sf::Vector2f textPos;
//    textPos.x = position.x + coin.getGlobalBounds().width * 3 / 2;
//    textPos.y = position.y + coin.getGlobalBounds().height / 2 - goldText.getGlobalBounds().height*2/3;
//
//    goldText.setPosition(textPos);
//}
//
//void Wallet::deposit(int amount) {
//    gold += amount;
//    std::stringstream tmp;
//    tmp << gold;
//    goldText.setString(tmp.str());
//}
//
//sf::Vector2f Wallet::getSize() {
//    sf::Vector2f size;
//    size.x = (goldText.getPosition().x + goldText.getGlobalBounds().width) - coin.getPosition().x;
//
//    if (goldText.getGlobalBounds().height <= coin.getGlobalBounds().height)
//        size.y = coin.getGlobalBounds().height;
//    else size.y = goldText.getGlobalBounds().height;
//
//    return size;
//}

void Wallet::setFont(sf::Font new_font) {
    font = new_font;
}