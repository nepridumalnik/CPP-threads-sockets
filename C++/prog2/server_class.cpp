#include "sock_include.h"

class Server{
    public:
        Server(int num){//Инициализация сервера

            sock = socket(AF_INET, SOCK_DGRAM, 0);//Создание сокета, AF_INET - для ipv4, SOCK_DGRAM - служба датаграмм (использование UDP)

            if(sock < 0){
                perror("socket");//Вывод ошибки на экран
                exit(1);//Немедленное окончание программы
            }

            addr.sin_family = AF_INET;//Указание типа сокета
            addr.sin_port = htons(num);//Указание порта сокета
            addr.sin_addr.s_addr = htonl(INADDR_ANY);//Указание ip адреса сокета, INADDR_ANY - все адреса локального хоста (0.0.0.0)

            if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0){//Установка связывания
            perror("bind");
            exit(2);
            }        
        }

        void start(){//Запуск прослушивания сокета
            while(true){
                bytes_read = recvfrom(sock, received_info, 64, 0, NULL, NULL);//Чтение данных из совета sock в received_info, в количестве 64 байт, флаг 0
                received_info[bytes_read] = '\0';//Запись информации в память
                manipulation(received_info);//Обработка полученной информации
            }
        }

    private:
        int sock;//Адрес сокета
        struct sockaddr_in addr;//Структура с хранимой информацией о соединении
        char received_info[64];//Для полученного массива, в который будет записываться информация
        int bytes_read;
        
        void manipulation(char received_info[]){
            int size = 0;
            while(received_info[size] != '\0'){//Подсчёт количества элементов полученного массива
                size++;
            }
            
            if(size > 2 && size % 32 == 0){//Если количество элементов меньше, чем 2 и не кратно 32
                cout << "Строка - " << received_info << ", длина - " << size << endl;//Вывод информации об полученном массиве
            } else cout << "Ошибка!!!\n";//Иначе ошибка
            
        }
};