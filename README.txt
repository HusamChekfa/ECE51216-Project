Husam Chekfa, David Adams
ECE 51216 Online - Spring 2025
Group 1
______________________________
Option 1
C++ 20
______________________________
i. Directory Structure

Group1_C++20 (folder)
	README.txt
	mySAT (executable)
	All_Timing_Data.pdf
	Group1_Final_Report.pdf
	Code (folder)
		main.cpp
		Parser.cpp
		Parser.h
		Heuristics.cpp
		Heuristics.h
		Clause.cpp
		Clause.h
	SAT (folder)
		some small .cnf files for early stage testing
		many subfolders (6399 total CNFs) from https://www.cs.ubc.ca/~hoos/SATLIB/benchm.html
	
Notes about directory structure:

All_Timing_Data.pdf:
Contains every data point we used for the results section of the report.
Data collected by running every benchmark in the SAT folder's subfolders.
This timing was collected using the <chrono> C++ Library.

Code folder:
main.cpp calls DPLL and prints the result.
Parser.cpp and .h contain our homemade parser code.
Heuristics.cpp and .h contain DPLL and the three heuristics we implemented (CHAFF BCP, DLIS, Unate branching)
Clause.cpp and .h contain the struct Clause we wrote to contain the clauses we parse.

SAT folder:
The immediate files you see are very small cnfs that were used for very early testing, many of which are trivial cases.
The subfolders inside are the main test cases we used totaling to 6399. Folder and .cnf naming convention is as follows: uf = SAT, uuf = UNSAT, #variables - #clauses; files also include the number from 1-1000
______________________________
ii. How to Compile

Step 1. Open folder "Code" in terminal ECEPROG
Step 2. Copy paste the following line:
g++ -std=c++20 -O3 main.cpp Heuristics.cpp Parser.cpp Clause.cpp -o mySAT
______________________________
iii. How to Run

In ECEPROG, place the executable in the same folder as the benchmark.cnf file and type:

mySAT benchmark.cnf

Note: MUST WRITE benchmark.cnf, NOT JUST benchmark

Note: This can also be run from anywhere in the filesystem. Simply swap mySAT and benchmark.cnf with their filepaths (..filepath1../mySAT ..filepath2../benchmark.cnf).
