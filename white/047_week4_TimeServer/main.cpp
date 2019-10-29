/*
 * main.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: Anton Dogadaev
 */
#include <iostream>
#include <exception>
#include <string>
#include <system_error>

using namespace std;

int counter = 0;

string AskTimeServer() {
    /* Для тестирования повставляйте сюда код, реализующий различное поведение этой функии:
       * нормальный возврат строкового значения
       * выброс исключения system_error
       * выброс другого исключения с сообщением.
    */
	if (counter == 0) {
		counter++;
		return "01:01:01";
	}
	if (counter == 1) {
		counter++;
		throw system_error(error_code());
		return "02:02:02";
	}
	if (counter == 3) {
		counter++;
		throw domain_error("bla-bla-bla");
		return "03:03:03";
	}
}

class TimeServer {
public:
    string GetCurrentTime() {
        /* Реализуйте этот метод:
            * если AskTimeServer() вернула значение, запишите его в LastFetchedTime и верните
            * если AskTimeServer() бросила исключение system_error, верните текущее значение
            поля LastFetchedTime
            * если AskTimeServer() бросила другое исключение, пробросьте его дальше.
        */
    	try {
    		LastFetchedTime = AskTimeServer();
    	} catch (system_error& e) {

    	}
    	return LastFetchedTime;
    }

private:
    string LastFetchedTime = "00:00:00";
};

int main() {
    // Меняя реализацию функции AskTimeServer, убедитесь, что это код работает корректно
    TimeServer ts;
    try {
        cout << ts.GetCurrentTime() << endl;
        cout << ts.GetCurrentTime() << endl;
        cout << ts.GetCurrentTime() << endl;
    } catch (exception& e) {
        cout << "Exception got: " << e.what() << endl;
    }
    return 0;
}
