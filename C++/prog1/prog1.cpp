#include "includes.h"
#include "Interaction.cpp"

int main(){
    char buffer[] = "";//Буфер

    Interaction inter(3425, *buffer);//Создание объекта взаимодействия, передача номера порта 3425 - TCP/UDP порт и указателя на буфер
    
    inter.startThreads();//Запуск потоков 
    
    END;
}