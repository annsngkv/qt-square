#include "win.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    /*
     * Cоздание объекта-приложения
    */
    QApplication app(argc, argv);

    /*
     * Cоздание объекта управления окном
    */
    Win win(0);

    /*
     * Визуализация окна win
    */
    win.show();

    /*
     * Запуск цикла обработки сообщений приложения
    */
    return app.exec();
}
