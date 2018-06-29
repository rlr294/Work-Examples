This is an operating simulator that takes in a configuration file and a meta data file containing commands that
simulate what a program might do.  The simulator handles scheduling the programs commands and outputs which process of the
program is being selected, the state the process is being put in, which command is being executed, and the current
runtime of the entire program.  It has 5 different scheduling methods that can be changed within the configuration file.

Compile using GNU Make (type 'make' into a command line where the GNU Compiler Collection is installed)

Run with the command:
/.Sim05 config1.cnf

The configuration file is customizable, notable features to change are:
	CPU Scheduling Code: changes which scheduling type is used
		'FCFS-N' - First Come First Serve, non-preemptive
		'SJF-N' - Shortest Job First, non-preemptive
		'SRTF-P' - Shortest Runtime First, preemptive
		'FCFS-P' - First Come First Serve, preemptive
		'RR-P' - Round Robin, preemptive
		
	Log To: changes where the simulator output is displayed
		'Monitor' - Output is printed to the command line
		'Both' - Output is printed to the command line and saved in a file, specified by 'Log File Path'

You can also change the metadata file to change what the program being simulated is doing.  
Acceptable instructions include:

	'S(start)0' - Start the Simulation
	'S(end)0' - End the Simulation
	'A(start)0' - Start a process
	'A(end)0' - End a process
	'M(allocate)#' - Memory Allocation
	'M(access)#' - Memory Access
	'I(hard drive)#' - Hard Drive Input
	'I(keyboard)#' - Keyboard Input
	'O(hard drive)#' - Hard Drive Output
	'O(printer)#' - Printer Output
	'O(monitor)#' - Monitor Output
	'P(run)#' - Process Run Operation

The #'s represent the number of cycles each instruction will take.  Time per cycle can be adjusted in the configuration file if desired.