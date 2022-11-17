#include "AnimationManager.h"

// On Windows, backslash '\\' is directory separator in paths
// On UNIX paths separated with slash '/'.
#if defined(_WIN32)
const char DIR_SEPARATOR = '\\';
#else
const char DIR_SEPARATOR = '/';
#endif

using namespace tinyxml2;

AnimationManager::~AnimationManager() {
    animMap.clear();
}

void AnimationManager::create(const std::string& name, Texture &texture, int x, int y, int w, int h, int count, float speed, int step, bool Loop) {
    Animation a;
    a.speed = speed;
    a.loop = Loop;
    a.sprite.setTexture(texture);
    a.sprite.setOrigin(0,h);

    for (int i=0;i<count;i++)
    {
        a.frames.emplace_back( IntRect(x+i*step, y, w, h)  );
        a.frames_flip.emplace_back( IntRect(x+i*step+w, y, -w, h)  );
    }
    animMap[name] = a;
    currentAnim = name;
}

bool AnimationManager::loadFromXML(std::string fileName,Texture &t) {
    tinyxml2::XMLDocument animFile;

    if (animFile.LoadFile(fileName.c_str()) != XML_SUCCESS)
        return false;
    XMLElement *head = animFile.FirstChildElement("sprites");

    XMLElement *animElement = head->FirstChildElement("animation");
    while(animElement) {
        Animation anim;
        currentAnim = animElement->Attribute("title");
        int delay = atoi(animElement->Attribute("delay"));
        anim.speed = 1.0/delay;
        anim.sprite.setTexture(t);

        XMLElement *cut = animElement->FirstChildElement("cut");
        while (cut) {
            int x = atoi(cut->Attribute("x"));
            int y = atoi(cut->Attribute("y"));
            int w = atoi(cut->Attribute("w"));
            int h = atoi(cut->Attribute("h"));

            anim.frames.emplace_back( IntRect(x,y,w,h) );
            anim.frames_flip.emplace_back( IntRect(x+w,y,-w,h)  );
            cut = cut->NextSiblingElement("cut");
        }

        anim.sprite.setOrigin(0,anim.frames[0].height);

        animMap[currentAnim] = anim;
        animElement = animElement->NextSiblingElement("animation");
    }
    return true;
}

void AnimationManager::set(std::string name) {
    currentAnim = name;
    animMap[currentAnim].flip=0;
}

void AnimationManager::draw(RenderWindow &window,int x, int y) {
    animMap[currentAnim].sprite.setPosition(x, y);
    window.draw(animMap[currentAnim].sprite);
}

void AnimationManager::flip(bool b) {
    animMap[currentAnim].flip = b;
}

void AnimationManager::tick(float time) {
    animMap[currentAnim].tick(time);
}

void AnimationManager::pause() {
    animMap[currentAnim].isPlaying=false;
}

void AnimationManager::play() {
    animMap[currentAnim].isPlaying=true;
}

void AnimationManager::play(const std::string& name) {
    animMap[name].isPlaying=true;
}

bool AnimationManager::isPlaying() {
    return animMap[currentAnim].isPlaying;
}

float AnimationManager::getH() {
    return animMap[currentAnim].frames[0].height;
}

float AnimationManager::getW() {
    return animMap[currentAnim].frames[0].width;
}