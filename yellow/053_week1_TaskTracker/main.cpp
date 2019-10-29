/*
 * main.cpp
 *
 *  Created on: Oct 30, 2018
 *      Author: Anton Dogadaev
 */
#include <map>
#include <string>
#include <tuple>
#include <iostream>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
	NEW,          // новая
	IN_PROGRESS,  // в разработке
	TESTING,      // на тестировании
	DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
	// Получить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const string& person) const {
		return mPersons.at(person);
	}

	// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
	void AddNewTask(const string& person) {
		mPersons[person][TaskStatus::NEW]++;
	}

	// Обновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(
			const string& person, int task_count) {
		TasksInfo updated_tasks;
		TasksInfo old_tasks;
		for (const auto& task_info : mPersons[person]) {
			TaskStatus status = task_info.first;
			int task_num = task_info.second;
			if (status != TaskStatus::DONE && task_count != 0) {
				uint32_t min_count = min(task_count, task_num);
				TaskStatus new_status = static_cast<TaskStatus>(
						static_cast<int>(status)+1);
				updated_tasks[new_status] += min_count;
				if (task_num - min_count != 0) {
					old_tasks[status] = task_num - min_count;
				}
				task_count -= min_count;
			} else {
				old_tasks[status] = task_num;
			}
		}
		if (mPersons.erase(person) > 0) {
			mPersons[person] = old_tasks;
			for (const auto& task_info : updated_tasks) {
				mPersons[person][task_info.first] += task_info.second;
			}
		}
		old_tasks.erase(TaskStatus::DONE);
		return tie(updated_tasks, old_tasks);
	}
private:
	map<string, TasksInfo> mPersons;
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
	cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
			", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
			", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
			", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
	TeamTasks tasks;
	tasks.AddNewTask("Ilia");
	for (int i = 0; i < 3; ++i) {
		tasks.AddNewTask("Ivan");
	}
	cout << "Ilia's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
	cout << "Ivan's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

	TasksInfo updated_tasks, untouched_tasks;

	tie(updated_tasks, untouched_tasks) =
			tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);

	tie(updated_tasks, untouched_tasks) =
			tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);

	return 0;
}


