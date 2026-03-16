# Multi-Threaded TCP Scheduling Server (C++)

## Overview

This project implements a **multi-threaded TCP server in C++ using the Winsock API** that processes client requests through a **custom text-based protocol**.

The server supports basic commands and also performs **CPU scheduling simulations** such as **First Come First Serve (FCFS)** and **Round Robin (RR)**. Multiple clients can connect simultaneously, and each client request is handled using a **dedicated thread**.

This project demonstrates core **Operating Systems and Networking concepts**, including socket programming, concurrency, and scheduling algorithms.

---

## Features

* Multi-threaded TCP server using **Winsock**
* Handles **multiple concurrent clients**
* Custom request-response **protocol**
* CPU scheduling simulation
* Implemented algorithms:

  * FCFS (First Come First Serve)
  * Round Robin Scheduling
* Computes scheduling metrics:

  * Average waiting time
  * Average turnaround time
* Real-time request processing

---

## Architecture

Client requests are processed using a **thread-per-connection model**.

```
Client 1 ─┐
Client 2 ─┤
Client 3 ─┤ → TCP Server → Request Parser → Scheduling Engine → Response
Client N ─┘
```

---

## Project Structure

```
scheduler_server
│
├── server.cpp        # Multi-threaded TCP server
├── client.cpp        # Test client
├── protocol.h        # Command parser and protocol logic
├── scheduler.h       # CPU scheduling algorithms
└── README.md
```

---

## Custom Protocol

The system uses a **simple text-based protocol**:

```
COMMAND|DATA
```

### Supported Commands

#### Echo

Returns the same message sent by the client.

```
ECHO|hello
```

Response:

```
ECHO|hello
```

---

#### Get Server Time

```
TIME
```

Response example:

```
TIME|Mon Mar 16 20:35:12 2026
```

---

#### FCFS Scheduling

Input format:

```
FCFS|arrival,burst;arrival,burst;arrival,burst
```

Example:

```
FCFS|0,5;1,3;2,8
```

Response example:

```
GANTT: P1 P2 P3 | AVG_WAIT=3.33 | AVG_TURN=8.66
```

---

#### Round Robin Scheduling

Input format:

```
RR|quantum|arrival,burst;arrival,burst;arrival,burst
```

Example:

```
RR|2|0,5;1,3;2,8
```

Response example:

```
GANTT: P1 P2 P3 P1 P3
```

---

## Requirements

* Windows OS
* MinGW / g++
* Winsock library (included with Windows)

---

## Compilation

Compile the server and client using g++:

```
g++ server.cpp -lws2_32 -o server.exe -mconsole
g++ client.cpp -lws2_32 -o client.exe -mconsole
```

---

## Running the Application

### Step 1 — Start Server

```
./server.exe
```

Expected output:

```
Server running on port 8080
```

---

### Step 2 — Start Client

Open another terminal in the same directory:

```
./client.exe
```

---

### Step 3 — Send Commands

Example commands to test:

```
ECHO|hello
TIME
FCFS|0,5;1,3;2,8
RR|2|0,5;1,3;2,8
```

---

## Concepts Demonstrated

### Networking

* TCP socket programming
* Winsock API
* Client-server architecture

### Concurrency

* Multithreading with `std::thread`
* Thread-per-connection model

### Operating Systems

* CPU scheduling algorithms
* Process scheduling metrics
* Gantt chart simulation

---

## Future Improvements

Possible enhancements include:

* Thread pool implementation
* Priority scheduling
* Shortest Job First (SJF)
* Graphical Gantt chart visualization
* Improved error handling and logging

---

## Author

Navitha E
Integrated M.Tech Computer Science

---
