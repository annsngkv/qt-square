#ifndef win_h
#define win_h
#include <QtGui>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <QWidget>

/*
 * Наследуемся от класса QWidget – базовый класс всех виджетов
*/
class Win : public QWidget
{
    /*
     * Обязательный макрос, так как класс Win определяет новые слоты
    */
    Q_OBJECT // макрос Qt, обеспечивающий корректное создание сигналов и слотов
    protected:
        /*
         * Объявляем указатель на объект класса QTextCodec - один из семейства классов, определенных
         * для работы с разными, в том числе национальными кодировками в Qt
        */
        QTextCodec *codec; // перекодировщик

        /*
         * Объявляем указатель на объект класса QFrame, который является базовым классом для виджетов способных иметь рамку.
        */
        QFrame *frame; // рамка

        /*
         * Объявляем указатель на объект класса QLabel - метка – виджет, с помощью которого высвечивается
         * текст "Введите число"
        */
        QLabel *inputLabel; // метка ввода

        /*
         * Объявляем указатель на объект класса QLineEdit - виджет, представляющий собой редактор однострочного текста
        */
        QLineEdit *inputEdit; // строчный редактор ввода

        /*
         * Объявляем указатель на объект класса QLabel - метка – виджет, с помощью которого высвечивается
         * текст "Результат"
        */
        QLabel *outputLabel; // метка вывода

        /*
         * Объявляем указатель на объект класса QLineEdit - виджет, представляющий собой редактор однострочного текста
        */
        QLineEdit *outputEdit; // строчный редактор вывода

        /*
         * Объявляем указатели на объекты класса QPushButton - виджет-кнопка
        */
        QPushButton *nextButton; // кнопка "Следующее"
        QPushButton *exitButton; // кнопка "Выход"

    public:
        /*
         * Конструктор базового класса QWidget с двумя параметрами
         * 1-й параметр - родитель, так как он установлен в 0, то у нашего класса нет родителей
         *
         * 2-й параметр - флаги – битовая комбинация, отвечающая за тип окна: обычное,
         * диалоговое, контекстное меню, панель инструментов, выпадающая подсказка и т.п.
         * Так как здесь этот параметр опущен, то он берется по умолчанию – обычное окно.
        */
        Win(QWidget *parent = 0);

    /*
     * Класс окна добавляет к множеству стандартно объявленных слотов еще два слота –
     * методы начальной настройки и реализации вычислений
     *
     * Слот вызывается когда вырабатывается сигнал, с которым он связан.
     * Слот это обычная функция в C++ и может вызываться обычным способом;
     * единственная его особенность, что с ним можно соединсять сигналы.
    */
    public slots:
        void begin(); // метод начальной настройки интерфейса
        void calc(); // метод реализации вычислений
};

/*
 * Специальный класс валидатор StrValidator,
 * наследуемый от класса QValidator
*/
class StrValidator:public QValidator // класс компонента проверки ввода
{
    public:
        StrValidator(QObject *parent):QValidator(parent){}
        // метод всегда принимает вводимую строку
        virtual State validate(QString &str,int &pos)const { return Acceptable; }
};
#endif