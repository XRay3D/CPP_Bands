#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <stdint.h>
#include <strstream>
#include <utility>
#include <vector>

using namespace std;

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь

#ifdef __TEST__

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW, // новая
    IN_PROGRESS, // в разработке
    TESTING, // на тестировании
    DONE // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

ostream& operator<<(ostream& s, const TasksInfo& ti)
{
    //{"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
    s << '{';
    for (int ts = 0, count = 0; ts <= static_cast<int>(TaskStatus::DONE); ++ts) {
        TaskStatus i = static_cast<TaskStatus>(ts);
        if (ti.count(i)) {
            if (count++)
                s << ", ";
            switch (i) {
            case TaskStatus::NEW:
                s << "\"NEW\": " << ti.at(i);
                continue;
            case TaskStatus::IN_PROGRESS:
                s << "\"IN_PROGRESS\": " << ti.at(i);
                continue;
            case TaskStatus::TESTING:
                s << "\"TESTING\": " << ti.at(i);
                continue;
            case TaskStatus::DONE:
                s << "\"DONE\": " << ti.at(i);
                continue;
            }
        }
    }
    s << '}';
    return s;
}

#endif

class TeamTasks {
    map<string, TasksInfo> data;

public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const
    {
        return data.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person)
    {
        ++data[person][TaskStatus::NEW];
    }
#ifdef __TEST__
    void AddNewTasks(const string& person, int count)
    {
        data[person][TaskStatus::NEW] += count;
    }
#endif
    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count)
    {
        TasksInfo temp;
        TasksInfo untouched;
        TasksInfo updated;
        for (const auto& [key, val] : data[person]) {
            switch (key) {
            case TaskStatus::NEW: {
                if (val > 0) {
                    int count = val;
                    while (count > 0 && task_count > 0) {
                        temp[TaskStatus::IN_PROGRESS]++;
                        updated[TaskStatus::IN_PROGRESS]++;
                        --count;
                        --task_count;
                    }
                    if (count > 0) {
                        temp[TaskStatus::NEW] += count;
                        untouched[TaskStatus::NEW] += count;
                    }
                }
                break;
            }
            case TaskStatus::IN_PROGRESS: {
                if (val > 0) {
                    int count = val;
                    while (count > 0 && task_count > 0) {
                        temp[TaskStatus::TESTING]++;
                        updated[TaskStatus::TESTING]++;
                        --count;
                        --task_count;
                    }
                    if (count > 0) {
                        temp[TaskStatus::IN_PROGRESS] += count;
                        untouched[TaskStatus::IN_PROGRESS] += count;
                    }
                }
                break;
            }
            case TaskStatus::TESTING: {
                if (val > 0) {
                    int count = val;
                    while (count > 0 && task_count > 0) {
                        temp[TaskStatus::DONE]++;
                        updated[TaskStatus::DONE]++;
                        --count;
                        --task_count;
                    }
                    if (count > 0) {
                        temp[TaskStatus::TESTING] += count;
                        untouched[TaskStatus::TESTING] += count;
                    }
                }
                break;
            }
            case TaskStatus::DONE: {
                if (val > 0) {
                    temp[TaskStatus::DONE] += val;
                }
                break;
            }
            }
        }
        data[person] = temp;
        return tuple<TasksInfo, TasksInfo>(updated, untouched);

        //        TasksInfo tTmp = data[person];
        //        TasksInfo updated;
        //        TasksInfo untouched;

        //        for (int iTs = 0, iLast = 0; iTs <= static_cast<int>(TaskStatus::DONE); ++iTs) {
        //            TaskStatus i = static_cast<TaskStatus>(iTs);
        //            if (task_count || iLast) {
        //                int t = tTmp[i];
        //                if (iLast)
        //                    updated[i] = iLast;
        //                if (int v = t - task_count; v > 0)
        //                    untouched[i] = v;
        //                if (i == TaskStatus::DONE)
        //                    break;
        //                tTmp[i] += iLast;
        //                tTmp[i] -= task_count;
        //                if (tTmp[i] < 1) {
        //                    iLast = task_count + tTmp[i];
        //                    task_count -= iLast;
        //                    tTmp.erase(i);
        //                } else {
        //                    iLast = task_count;
        //                    task_count = 0;
        //                }
        //            }
        //        }
        //        data[person] = tTmp;
        //        return { updated, untouched };
    }
};

int main()
{
    TeamTasks tasks;
#ifdef __TEST__
    if (/* DISABLES CODE */ (1)) {
        strstream cin;
        cin << "AddNewTasks Alice 5" << endl;
        cin << "PerformPersonTasks Alice 1" << endl;
        cin << "PerformPersonTasks Alice 1" << endl;
        cin << "PerformPersonTasks Alice 1" << endl;
        cin << "GetPersonTasksInfo Alice" << endl;
        cin << "PerformPersonTasks Alice 1" << endl;
        cin << "PerformPersonTasks Alice 1" << endl;
        cin << "PerformPersonTasks Alice 1" << endl;
        cin << "GetPersonTasksInfo Alice" << endl;
        cin << "PerformPersonTasks Alice 1" << endl;
        cin << "PerformPersonTasks Alice 1" << endl;
        cin << "PerformPersonTasks Alice 1" << endl;
        cin << "GetPersonTasksInfo Alice" << endl;
        cin << "PerformPersonTasks Alice 1" << endl;
        cin << "PerformPersonTasks Alice 1" << endl;
        cin << "PerformPersonTasks Alice 1" << endl;
        cin << "GetPersonTasksInfo Alice" << endl;
        cin << "PerformPersonTasks Alice 1" << endl;
        cin << "PerformPersonTasks Alice 1" << endl;
        cin << "PerformPersonTasks Alice 1" << endl;
        cin << "GetPersonTasksInfo Alice" << endl;

        //        cin << "PerformPersonTasks Alice 5" << endl;
        //        cin << "PerformPersonTasks Alice 1" << endl;
        //        cin << "AddNewTasks Alice 5" << endl;
        //        cin << "PerformPersonTasks Alice 2" << endl;
        //        cin << "GetPersonTasksInfo Alice" << endl;
        //        cin << "PerformPersonTasks Alice 4" << endl;
        //        cin << "GetPersonTasksInfo Alice" << endl;
        string cmd, name;
        while (cin >> cmd >> name) {
            if (cmd == "AddNewTasks") {
                int cnt;
                cin >> cnt;
                tasks.AddNewTasks(name, cnt);
                cout << tasks.GetPersonTasksInfo(name) << endl;
            } else if (cmd == "PerformPersonTasks") {
                int cnt;
                cin >> cnt;
                TasksInfo updated_tasks, untouched_tasks;
                tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks(name, cnt);
                cout << '[' << updated_tasks << ", " << untouched_tasks << ']' << endl;
            } else if (cmd == "GetPersonTasksInfo") {
                cout << tasks.GetPersonTasksInfo(name) << endl;
            }
        }
        return 0;
    }

#endif
    return 0;
}
