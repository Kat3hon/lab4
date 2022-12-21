#include "Weapon.h"
#include "ElementType.h"
#include "EnemyManager.h"

#include <vector>
#include <unordered_map>
#include <windows.h>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class WeaponManager {

    std::vector<Weapon::Ptr> weapons;
    //std::unordered_map<ElementType, sf::Rect<int>> towers_textures_coords;
    //std::unordered_map<ElementType, sf::Rect<int>> trap_textures_coords;
    //sf::Texture tileset;

public:
    WeaponManager();

    void update();

    void push(const Weapon::Ptr &weapon);

    void pop(const Weapon::Ptr &weapon);

    //void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void handleEnemyLockOn(EnemyManager* enemyManager);
};
