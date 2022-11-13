#include "ObjectXML.h"

int ObjectXML::GetPropertyInt(const std::string& name) {
    return std::stoi(properties[name]);
}

float ObjectXML::GetPropertyFloat(const std::string& name) {
    return std::stof(properties[name]);
}

std::string ObjectXML::GetPropertyString(const std::string& name) {
    return properties[name];
}