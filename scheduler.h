#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <algorithm>

struct Process {
    int pid;
    int arrival;
    int burst;
};

std::vector<Process> parseProcesses(std::string data) {

    std::vector<Process> processes;
    std::stringstream ss(data);
    std::string token;
    int pid = 1;

    while(std::getline(ss, token, ';')) {

        std::stringstream ps(token);
        std::string a,b;

        std::getline(ps,a,',');
        std::getline(ps,b,',');

        Process p;
        p.pid = pid++;
        p.arrival = std::stoi(a);
        p.burst = std::stoi(b);

        processes.push_back(p);
    }

    return processes;
}

std::string FCFS(std::vector<Process> processes) {

    int time = 0;
    double totalWait = 0;
    double totalTurn = 0;

    std::string gantt = "GANTT:";

    for(auto &p : processes) {

        if(time < p.arrival)
            time = p.arrival;

        int wait = time - p.arrival;
        int turn = wait + p.burst;

        totalWait += wait;
        totalTurn += turn;

        gantt += " P" + std::to_string(p.pid);

        time += p.burst;
    }

    double avgWait = totalWait / processes.size();
    double avgTurn = totalTurn / processes.size();

    std::stringstream result;

    result << gantt
           << " | AVG_WAIT=" << avgWait
           << " | AVG_TURN=" << avgTurn;

    return result.str();
}

std::string RoundRobin(std::vector<Process> processes, int quantum) {

    std::queue<Process> q;

    for(auto p : processes)
        q.push(p);

    std::string gantt = "GANTT:";

    while(!q.empty()) {

        Process p = q.front();
        q.pop();

        if(p.burst > quantum) {

            gantt += " P" + std::to_string(p.pid);
            p.burst -= quantum;
            q.push(p);

        } else {

            gantt += " P" + std::to_string(p.pid);
        }
    }

    return gantt;
}

#endif