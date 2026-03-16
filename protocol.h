#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#include <sstream>
#include <ctime>
#include "scheduler.h"

std::string processRequest(std::string req) {
    req.erase(std::remove(req.begin(), req.end(), '\n'), req.end());
    req.erase(std::remove(req.begin(), req.end(), '\r'), req.end());
    if(req.find("TIME") == 0) {

        time_t now = time(0);
        char* dt = ctime(&now);

        return std::string("TIME|") + dt;
    }

    if(req.find("ECHO|") == 0) {

        return req;
    }

    if(req.find("FCFS|") == 0) {

        std::string data = req.substr(5);

        auto processes = parseProcesses(data);

        return FCFS(processes);
    }

    if(req.find("RR|") == 0) {

        std::stringstream ss(req.substr(3));

        std::string qstr;
        std::string pdata;

        std::getline(ss,qstr,'|');
        std::getline(ss,pdata);

        int quantum = std::stoi(qstr);

        auto processes = parseProcesses(pdata);

        return RoundRobin(processes,quantum);
    }

    return "ERROR|Unknown command";
}

#endif