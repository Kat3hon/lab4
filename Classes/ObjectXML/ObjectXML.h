#include "../baseHeaders.h"

class ObjectXML {
public:
    ObjectXML(float x, float y, float width, float height): rect(x, y, width, height) {}

    int GetPropertyInt(const std::string& name);
    float GetPropertyFloat(const std::string& name);
    std::string GetPropertyString(const std::string& name);

    std::string name;
    std::string type;
    std::map<std::string, std::string> properties;
    sf::FloatRect rect;
};
