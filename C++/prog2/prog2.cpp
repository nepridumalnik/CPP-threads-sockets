#include "sock_include.h"
#include "server_class.cpp"

int main()
{
    cout << "Start\n";//Сообщение о начале выполнения программы
    Server serv(3425);//Создание объекта программы-сервера, слушающего TCP-UDP порт

    serv.start();//Запуск ожидания получения информации
    //Чтобы выключить программу, нажмите ctrl+c в консоли
    
    END;
}