#include "includes.h"
#include "sock.h"

class Connection{
    public:
        Connection(){}

        void initialize(int num){
            sock = socket(AF_INET, SOCK_DGRAM, 0);//Создание сокета, AF_INET - для ipv4, SOCK_DGRAM - служба датаграмм (использование UDP)

            if(sock < 0){
                    perror("socket");//Вывод ошибки на экран
                    exit(1);//Немедленное окончание программы
                }

                addr.sin_family = AF_INET;//Указание типа сокета
                addr.sin_port = htons(num);//Указание порта сокета
                addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);//Указание ip адреса сокета, INADDR_LOOPBACK - интерфейс внутренней петли
        }

        void send(char &buf, int lenght){//Отправка сообщения
            char tosend[128] = "";//Создание переменной сообщения для отправки

            for(int i = 0; i < lenght; i++){//Перенос символов из буфера в сообщения для отправки
                tosend[i] = *(&buf + i);
            }
            sendto(sock, tosend, sizeof(tosend), 0, (struct sockaddr *)&addr, sizeof(addr));//Отправка сообщения
        }
    
    private:
        int sock;//Адрес сокета
        struct sockaddr_in addr;//Структура с хранимой информацией о соединении
};

class Interaction{
    public:
        Interaction(int num, char &buff){//Создание объекта с указанием номера порта и передачей указателя на буфер
            cout << "Объект создан\n";//Запись об успешном создании
            
            buf = &buff;//Сохранение указателя в атрибут класса

            initialize(num);//Инициализация соединения по сокету
        }

        void sendto(){//Отправка сообщения
            if(isConnected){//Если разрешено соединение
                connect.send(*buf, text.length());//Отправка сообщения с помощью объекта соединения
                buf[0] = {};//Очищение буфера
            }
        }

        void startThreads(){//Метод запуска потоков программы
            thread output([&](){//Запуск с помощью лямбда-функции
                outputThread();//Запуск потока вывода информации
            });

            thread input([&](){
                inputThread();//Запуск потока ввода информации
            });

            input.join();//Ожидание завершения потока, чтобы программа не завершилась раньше времени
        }

        void outputThread(){//Поток вывода информации
            while(true){
                sleep_for(milliseconds(200));//Ожидание 200 миллисекунд для разрешения чтения буфера
                if (isWork) {//Если читать буфер разрешено
                    sendto();//Отправка сообщение из буфера адресату
                }
            }
        }

        void inputThread(){
            cout << "Введите строку 64 символа или менее только из чисел\nВведите exit, чтобы выйти\n";
            bool condition = false;//Переменная блокировки выполнения проверки условий
        while(true) {
            isWork = false;//Переменная разрешения
            cin >> text;//Ввод информации пользователем
            if(text == "exit") exit(0);//Для завершения рабоыт программы
            condition = true;//Переменная хранения выполнения всех условий
            cout << "Введённый текст - " << text << ", количество символов - " << text.length() << endl;//Вывод информации о введённом тексте
            if(text.length() > 64){
                cout << "Размер строки больше 64, введите заново\n";
                continue;
            }

            for(unsigned short i = 0; i < text.length(); i++){//Проверка на наличие нечисленных значений
                if(text[i] < 47 || text[i] > 58){//Промежуток от 47 до 58 - коды символьных значений цифр
                    cout << "Обнаружена буква, введите строку только из чисел\n";
                    condition = false;
                    break;
                }
            }

            if(condition){//Если условие выполняется, перестановка элементов в порядке убывания
                char temp;//Временная переменная хранения значения подменяемой ячейки
                for(int i = 0; i < text.length() - 1; i++){
                    for(int j = 0; j < text.length() - i - 1; j++){
                        if(int(text[j]) < int(text[j + 1])){
                            temp = text[j];
                            text[j] = text[j + 1];
                            text[j + 1] = temp;
                        }
                    }
                }
            }

            int count = 0;
            string newText = "";//Новая переменная для хранения текста с 
            while(count != text.length()){//Замена чётных чисел на "KB"
                if(text[count] == '0') newText += '0';
                else{
                    if((text[count] - '0') %2 == 0){
                    newText += "KB";
                } else newText += text[count];
                }
                count++;
            }

            text = newText;
            
            for(int i = 0; i < text.length(); i++){//Подстановка символов из строчной переменной text в буфер
                buf[i] = text[i];
            }
                        
            if(condition) isWork = true;//Если все условия соблюдены, разрешить чтение из буфера и отправку информации
            sleep_for(milliseconds(201));//Ожидание выполнения
            }
        }

        void initialize(int num){//Инициализация соединения
            connect.initialize(num);
            isConnected = true;//Подтверждения соединения
        }

    private:
        Connection connect;//Создание объекта соединения
        char *buf;//Указатель на буфер
        bool isWork = false, isConnected = false;
        string text = "";//Строка для хранения вводимой информации
};