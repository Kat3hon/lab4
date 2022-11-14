#pragma once
#include "../baseHeaders.h"
#include "../Animation/Animation.h"

class AnimationManager {
public:
    std::string currentAnim; //текущая анимация
    std::map<std::string, Animation> animList; //таблица анимаций

    AnimationManager() = default;
    ~AnimationManager();

    //создание анимаций вручную
    //название анимации, текстура, левый верхний угол, ширина и высота, кол-во фреймов, скорость, шаг и зацикленность анимации
    void create(const std::string& name, Texture &texture, int x, int y, int w, int h, int count, float speed, int step=0, bool Loop=true);

    //загрузка из файла XML
    void loadFromXML(std::string fileName,Texture &t);

    //установить анимацию по названию (например "die")
    void set(std::string name);

    void draw(RenderWindow &window,int x=0, int y=0);

    //
    void flip(bool b=true); //задаёт свойство зеркальности текущей анимации

    void tick(float time); //прокручивает текущую анимацию

    void pause(); //остановить текущую анимацию

    void play(); //запустить текущую анимацию

    void play(const std::string& name); //запустить анимацию по имени

    bool isPlaying(); //узнать играет ли анимация

    float getH(); //получить высоту анимации

    float getW(); //получить широту анимации

};
