📘 Intelligent CPU Scheduler Simulator

CA-02 Project for CSE316 – Operating Systems
Developed by Aditya & Sahil

🚀 Overview

This project simulates the working of major CPU Scheduling Algorithms.

It contains:

. A C++ CLI-based Scheduler (backend)

. A Frontend Visualizer (HTML + JS)

. Fully formatted Gantt Charts

. Detailed Result Tables (CT, TAT, WT)

. Exportable PNG Gantt charts

. A complete Menu-Driven System

This tool helps students understand how different scheduling algorithms behave with respect to CPU execution order, waiting time, and turnaround time.

🧮 Algorithms Implemented

The following scheduling algorithms are implemented:

1. First Come First Serve (FCFS)

2. Shortest Job First (SJF) – Non Preemptive

3. Shortest Remaining Time First (SRTF) – Preemptive SJF

4. Priority Scheduling – Non Preemptive

5. Priority Scheduling – Preemptive

6. Round Robin (RR) with configurable time quantum

Each algorithm generates:

✔ Gantt Chart

✔ Completion Time (CT)

✔ Turnaround Time (TAT)

✔ Waiting Time (WT)

✔ Average TAT & WT


🖥️ Project Structure

/
|-- integration/

|      └── main.cpp        (Final integrated C++ scheduler)

|

|-- frontend/

|      └── index.html      (Visualizer + Gantt Chart + Export)
|

|-- screenshots/           (CLI + Frontend outputs)

|      ├── cli_fcfs.png

|      ├── cli_sjf_np.png

|      ├── cli_srtf.png

|      ├── cli_priority_np.png

|      ├── cli_priority_p.png

|      ├── cli_rr.png

|      ├── frontend_fcfs.png

|      ├── frontend_rr.png

|      └── gantt_fcfs.png

|

|-- README.md

📝 Sample Input Used for All Algorithms

Number of Processes: 4

PID  AT  BT  Priority

1    0   5    2

2    1   3    1

3    2   8    3

4    3   6    2

For Round Robin:

Time Quantum = 2

▶️ How to Run (CLI Version – C++)

Using g++

g++ -std=c++17 integration/main.cpp -o scheduler

./scheduler

Program Flow

1. Enter number of processes

2. Enter PID, Arrival Time, Burst Time, Priority

3. Choose scheduling algorithm

4. View Gantt chart + table output

🌐 How to Run (Frontend Visualizer)

1. Go to frontend/ folder

2. Open index.html in a browser

3. Click Load Sample OR enter your own data

4. Select an algorithm from dropdown

5. Click Run Scheduler

6. View:

    . Gantt Chart

    . Execution table

    . Export as PNG

📸 Output Screenshots

CLI Outputs

. FCFS
  
  ![screenshotscli_fcfs png](https://github.com/user-attachments/assets/5da0624b-6845-4da5-834e-5c9b5408fe91)

     
. SJF Non-Preemptive

  ![screenshotscli_sjf_np png](https://github.com/user-attachments/assets/f47b372a-5907-4b0e-b120-221bda7d8688)

  
Frontend Visualizer Outputs

. FCFS

  ![frontend_fcfs](https://github.com/user-attachments/assets/d50920ec-2662-441f-847a-61f28d2dfeae)

 . SRTF

  ![frontend_srtf](https://github.com/user-attachments/assets/192a0d66-d3cc-4ce6-a2ba-48218ed062a3)


 .Round Robin

  ![frontend_rr](https://github.com/user-attachments/assets/0a8e0fc4-1bc8-426f-b8b4-a364dd5ee889)

👥 Contributions

Aditya

 . Implemented all scheduling algorithms in C++

 . Integrated menu-driven CLI

 . Added complete backend logic

 . Generated all CLI outputs

 . Assisted in documentation & analysis

Sahil

 . Developed the entire frontend UI

 . Built table editor, Gantt chart visualizer, Export functionality

 . Added frontend outputs

 . Managed UI/UX and JavaScript logic

📚 Future Enhancements

  . Add multi-CPU support

  . Add I/O burst simulation

  . Add comparison dashboard

  . Add CSV export for reports

✅ Status

 ✔ Project Completed

 ✔ CLI + Frontend tested

 ✔ Screenshots collected

 ✔ Ready for submission

🎓 Thank You!

This project helped us understand CPU scheduling deeply and practically.
