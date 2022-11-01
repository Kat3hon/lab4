#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;

int main()
{
   //устанавливаем все текстурки из файлов
    addTextures();

// Объект, который, собственно, является главным окном приложения
    RenderWindow window(VideoMode(1920, 1080), "Tower Defence", Style::Default);

// Главный цикл приложения: выполняется, пока открыто окно
    while (window.isOpen())
    {
// Обрабатываем очередь событий в цикле
        Event event;
        while (window.pollEvent(event))
        {
// Пользователь нажал на «крестик» и хочет закрыть окно?
            if (event.type == Event::Closed)
                window.close(); // тогда закрываем его
        }
// Установка цвета фона
        window.clear(Color(250, 220, 100, 0));


// Отрисовка окна
        window.display();
    }

    return 0;
}
