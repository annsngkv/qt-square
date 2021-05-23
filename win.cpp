#include "win.h"
#include <QVBoxLayout>
#include <QMessageBox>

Win::Win(QWidget *parent):QWidget(parent)
{
    /*
     * объект класса QTextCodec – для русификации интерфейса
    */
    codec = QTextCodec::codecForName("Windows-1251");

    /*
     * Устанавливаем заголовок
    */
    setWindowTitle(codec->toUnicode("Возведение в квадрат"));

    /*
     * Создаем рамку
    */
    frame = new QFrame(this);

    /*
     * Добавляем тень
     *
     * Рамка и содержимое отображаются приподнятыми;
     * при рисовании выводится приподнятая линия с использованием светлых
     * и темных цветов текущей цветовой группы
     *
     * http://qtdocs.narod.ru/4.1.0/doc/html/qframe.html#Shadow-enum
    */
    frame->setFrameShadow(QFrame::Raised);

    /*
     * Определяем форму рамки
     *
     * QFrame рисует панель, которая делает содержимое приподнятым или утопленным
     *
     * http://qtdocs.narod.ru/4.1.0/doc/html/qframe.html#Shape-enum
    */
    frame->setFrameShape(QFrame::Panel);

    /*
     * Создаем метку ввода
     * метод toUnicode необходим для перекодировки в Unicode
    */
    inputLabel = new QLabel(codec->toUnicode("Введите число:"), this);

    /*
     * Создаем редактор ввода
    */
    inputEdit = new QLineEdit("", this);

    /*
     * Указатель на объект класса StrValidator
    */
    StrValidator *v = new StrValidator(inputEdit);

    /*
     * Устанавливает для редактора условие на вводимый текст v.
     * Это позволяет устанавливать любые ограничения на вводимый текст.
     *
     * http://qtdocs.narod.ru/4.1.0/doc/html/qlineedit.html#setValidator
    */
    inputEdit->setValidator(v);

    /*
     * Создаем метку вывода
     * метод toUnicode необходим для перекодировки в Unicode
    */
    outputLabel = new QLabel(codec->toUnicode("Результат:"), this);

    /*
     * Создаем редактор вывода
    */
    outputEdit = new QLineEdit("", this);

    /*
     * Создание кнопок
    */
    nextButton = new QPushButton(codec->toUnicode("Следующее"), this);
    exitButton = new QPushButton(codec->toUnicode("Выход"), this);

    /*
     * Выполняем компоновку приложения
     */

    /*
     * QVBoxLayout – вертикальны компоновщик – управляет расположением
     * виджетов в окне по вертикали;
     *
     * Этот объект срезу при создании связывается с объектом frame;
    */
    QVBoxLayout *vLayout1 = new QVBoxLayout(frame);

    /*
     * Добавлеям в вертикальный менеджер компоновки следующие виджеты:
     * -метку ввода;
     * -редактор ввода;
     * -метку вывода;
     * -редактор вывода.
    */
    vLayout1->addWidget(inputLabel);
    vLayout1->addWidget(inputEdit);
    vLayout1->addWidget(outputLabel);
    vLayout1->addWidget(outputEdit);

    /*
     * Для реализации «поджатия» виджетов одного к другому используют «пружины».
     * Виджеты, поджатые пружиной, при увеличении размеров окна остаются рядом.
     * Для добавления пружины используют метод addStretch
    */
    vLayout1->addStretch();

    /*
     * QVBoxLayout – вертикальны компоновщик – управляет расположением
     * виджетов в окне по вертикали;
    */
    QVBoxLayout *vLayout2 = new QVBoxLayout();

    /*
     * Добавлеям в вертикальный менеджер компоновки следующие виджеты:
     * -кнопку "Следующее";
     * -кнопку "Выход".
    */
    vLayout2->addWidget(nextButton);
    vLayout2->addWidget(exitButton);

    /*
     * Для реализации «поджатия» виджетов одного к другому используют «пружины».
     * Виджеты, поджатые пружиной, при увеличении размеров окна остаются рядом.
     * Для добавления пружины используют метод addStretch
    */
    vLayout2->addStretch();

    /*
     * QHBoxLayout – горизонтальный компоновщик – управляет расположением
     * виджетов в окне по горизонтали;
     *
     * Создание элемента компоновки для управления размещением остальных элементов компоновки в окне win
    */
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    /*
     * Добавляем виджет frame
    */
    hLayout->addWidget(frame);

    /*
     * Добавляем ячейку, содержащую другой QLayout
    */
    hLayout->addLayout(vLayout2);

    /*
     * Вызываем метод начальной настройки интерфейса
    */
    begin();

    /*
     * Связываем сигнал нажатия на кнопку "Выход" со слотом close()
    */
    connect(exitButton, &QPushButton::clicked, this, &Win::close);

    /*
     * Связываем сигнал нажатия на кнопку "Следующее" со слотом begin()
    */
    connect(nextButton, &QPushButton::clicked, this, &Win::begin);

    /*
     * Связываем сигнал завершения ввода returnPressed()– сигнал нажатия клавиши Enter со слотом calc()
    */
    connect(inputEdit, &QLineEdit::returnPressed, this, &Win::calc);
}

/*
 * Метод начальной настройки интерфейса
*/
void Win::begin()
{
    /*
     * Удаляем текст, содрежащийся в редакторе ввода.
    */
    inputEdit->clear();

    /*
     * setEnabled - процедура, изменяющая способность принимать и обрабатывать сообщения от клавиатуры и мыши
     * true – способно
     * false – нет
    */
    nextButton->setEnabled(false);

    /*
     * Устанваливаем свойство default false, чтобы кнопка
     * не активизировалась, если пользователь нажимает клавишу Enter
    */
    nextButton->setDefault(false);

    /*
     * setEnabled - процедура, изменяющая способность принимать и обрабатывать сообщения от клавиатуры и мыши
     * true – способно
     * false – нет
    */
    inputEdit->setEnabled(true);

    /*
     * Запрещаем показывать метку вывода
    */
    outputLabel->setVisible(false);

    /*
     * Запрещаем показывать редактор вывода
    */
    outputEdit->setVisible(false);

    /*
     * setEnabled - процедура, изменяющая способность принимать и обрабатывать сообщения от клавиатуры и мыши
     * true – способно
     * false – нет
    */
    outputEdit->setEnabled(false);

    /*
     * Передаем фокус ввода клавиатуры данному реддактору ввода
    */
    inputEdit->setFocus();
}

/*
 * Метод реализации вычислений
*/
void Win::calc()
{
    bool ok = true;
    double r, a;

    /*
     * Считываем введенное значение в редакторе ввода
    */
    QString str = inputEdit->text();
    /*
     * Функция, возвращающая строку, преобразованную в значение типа double
     * Возвращает 0.0, если преобразование не удалось.
     * Если во время преобразования возникает ошибка, то *ok устанавливается в false;
     * в противном случае *ok будет установлен в true.
     *
     * http://doc.crossplatform.ru/qt/4.7.x/qstring.html#toDouble
    */
    a = str.toDouble(&ok);

    /*
     * Если введено числовое значение
    */
    if (ok) {
        /*
         * Вычисляем квадрат введенного числа
        */
        r=a*a;

        /*
         * Функция, устанавливающая строку в печатное представление числа
        */
        str.setNum(r);

        /*
         * Вставляем полученное значение в редактор вывода с помощью функции setText
        */
        outputEdit->setText(str);

        /*
         * Запрещаем принимать сообщения от клавиатуры и мыши редактору ввода
        */
        inputEdit->setEnabled(false);

        /*
         * Показываем метку вывода
        */
        outputLabel->setVisible(true);

        /*
         * Показываем редактор вывода
        */
        outputEdit->setVisible(true);

        /*
         * Активизируем кнопку по нажатию пользователем Enter
        */
        nextButton->setDefault(true);

        /*
         * Разрешаем принимать сообщения от клавиатуры и мыши
        */
        nextButton->setEnabled(true);

        /*
         * Передаем фокус кнопке "Следующий"
        */
        nextButton->setFocus();
    } else {
        if (!str.isEmpty()) {
            /*
             * Вывод  сообщение об ошибке в специальном окне
             * при вводе неправильных (например, буквенных) исходных данных
            */
            QMessageBox msgBox(QMessageBox::Information,
                codec->toUnicode("Возведение в квадрат."),
                codec->toUnicode("Введено неверное значение."),
                QMessageBox::Ok);

            msgBox.exec();
        }
    }
}
