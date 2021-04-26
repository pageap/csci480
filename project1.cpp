/************************************
 *
 * CSCI 480 Assignment 1
 *
 * Author:  Adam Page
 * z-ID:   
 * Date Due:    9/15/2020
 *
 * PROGRAM: Bitwise Operators & IEEE-754 Floating Point Number Decoding
 * Reading virtual /proc files
 * 
 **************************************/
#include <iostream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <bits/stdc++.h> 
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::get;
using std::size_t;
using std::mega;
using std::stringstream;
using std::ifstream;
using std::ostringstream;


//getSysInfo prototype
void getSysInfo(string att); 
//getOS prototype
void getOS(string att);		
//getHost prototype
void getHost(string att);	
//getOSRelease prototype
void getOSRelease(string att);	
//getVersion prototype
void getVersion(string att);
//getCores prototype
void getCores();		
//getFunctiononingTime prototype
void getFunctioningTime();	
//getPhysicalCore prototype
void getPhysicalCore();	
//getCoreInfo prototype
void getCoreInfo();		
//getCoreTimeInfo prototype
void getCoreTimeInfo();	
//getSwapDevicesSize prototype
void getSwapDevicesSize();	



// displays and execute program.
int main() {
	//display part A
	cout << "-----------------------------------" << endl;
	cout << "Part A: " << endl;
	cout << "-Questions about turings OS." << endl;
	cout << "*************************" << endl;
	cout << "-Operating System: "; 
	getOS("ostype");
	cout << "-Host: "; 
	getHost("hostname");
	cout << "-Release: "; 
	getOSRelease("osrelease");
	cout << "-Version: "; 
	getVersion("version");
	cout << "*********************************" << endl;
	cout << endl << endl;
	// display part B
	cout << "Part B: " << endl;
	cout << "-Questions about turing processors : " << endl;
	cout<< "*************************" << endl;
	getCores();
	getPhysicalCore();
	getFunctioningTime();
	cout << "*********************************" << endl;
	cout << endl << endl;
	//display part C
	cout << "Part C: "<<endl;
	cout << "-For Processor 0 answer these questions : " << endl;
	cout << "*************************" << endl;
	getCoreInfo();
	cout << "*********************************" << endl;
	cout << endl << endl;
	//display part D
	cout<< "part D: "<< endl;
	cout << "-For processor 0, answer these questions" << endl;
	cout << "************************************" << endl;
	getCoreTimeInfo();
	cout << "*********************************" << endl;
	cout << endl << endl;
	//diplay Part E
	cout << "Part: E "<< endl;
	cout << "-What is the size of turings swap device in MB" << endl;
	cout << "*********************************************" << endl;
	getSwapDevicesSize();
	cout << "**********************************************" << endl;
	return 0;
}
//get the core
void getCores()
{
	size_t pos = 0;
	int cpuNum = 0;
	string count = "";

	//create an  input stream
	ifstream file{ "/proc/cpuinfo" };
	//cast the input stream to string
	string const cpuInfo = static_cast<ostringstream&>(ostringstream{} << file.rdbuf()).str();

	//gets position of the word processor
	pos = cpuInfo.rfind("processor") + 12;
	count = cpuInfo.substr(pos, 2);

	stringstream data(count);
	data >> cpuNum;
	//increments the  processor count by ++
	cpuNum++;
	//print # of processors
	cout << "Number of processors: " << cpuNum << endl;
}


//use void getSysInfo to "get" and print out system inofrmation

void getSysInfo(string att)
{
	std::ifstream f("/proc/sys/kernel/"+att);
	    if (f.is_open())
        std::cout << f.rdbuf();
}
//void getVersion then calls getSysInfo
void getVersion(string att)
{

	getSysInfo(att);
}


//use void getOS and calls getSysInfo which gets the operating system information
void getOS(string att)
{
	getSysInfo(att);
}

//use void getOSRelease by calling getSysInfo
void getOSRelease(string att)
{
	getSysInfo(att);
}

//same as above but gets Host
void getHost(string att)
{
	getSysInfo(att);
}

//void getPhysicalCore to get  and prints # physical multi-core chips
void getPhysicalCore()
{
	//set to 0
    int last = 0;
    int phyId = 0;
    string lastPhyId = "test";


    ifstream file{"/proc/cpuinfo"};
    string const fileContent = static_cast<ostringstream&>
    (ostringstream{} << file.rdbuf()).str();

    last = fileContent.rfind("physical id") + 14;
    lastPhyId = fileContent.substr(last, 2);
    stringstream s(lastPhyId);
    s >> phyId;
    phyId ++;
    cout << "-How many physical multi-core chips? " << phyId;
}

void getCoreInfo()
{
	//initialized the variables and set string names
	string vendorCore= "";
	string modelCoreName="";
	string physicalAddressSize="";
	string virtualAddressSize = "";
	
	//creates and input stream then cast stream into string 
	ifstream inFile("/proc/cpuinfo");
	string const coreInfo = static_cast<ostringstream&>(ostringstream{} << inFile.rdbuf()).str();
	
	//finds the position for the processor #0 string
	size_t found = coreInfo.rfind("processor : 0");
	//use if statement to check for core 0 and checks if its the right one 
	if(found){
		//finds the position of the vendor id string and gets the info
		size_t pos = coreInfo.rfind("vendor_id");
		vendorCore = coreInfo.substr(pos+12, 12);
		
		//finds the position of the model string and gets the info
		pos = coreInfo.rfind("model");
		modelCoreName = coreInfo.substr(pos+13, 26);
		
		//find  position of the address size string and gets the physical address
		pos = coreInfo.rfind("address size");
		physicalAddressSize = coreInfo.substr(pos+16,8);
		
	
		//gets the string with the virtual address
		virtualAddressSize = coreInfo.substr(pos+34, 8);
		//displays questions and answers
		cout << "-Who is the vendor? " << vendorCore << endl;
		cout << "-What is the model name? " << modelCoreName << endl;
		cout << "-What is its physical address size? " << physicalAddressSize <<endl;
		cout << "-What is its virtual address size? " << virtualAddressSize;
		cout << endl;
	}	
}




//use void getFunctioningTime to get how long the server 
//and host has been up then it prints it out
//sets all int variables to 0
void getFunctioningTime()
{
    ifstream inFile;
    string uptime = "";
    int days = 0;
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
 
	//opens file /proc/time
    inFile.open("/proc/uptime");
    inFile >> uptime;
    //closes file /proc/time
    inFile.close();

	//conver to int
    stringstream uptimeSec(uptime);

	//conversion to seconds, minutes, hours, and days
    uptimeSec >> seconds; 
    minutes = seconds%60;
    hours = minutes%60;
    days = hours%24;
	//diplays time and days 
	cout << endl << "-Time running in seconds: " << seconds;
    cout << endl <<"-Time running in : ";
    cout << " days: " << days << " hours: " << hours << " minutes: " 
    << minutes << " seconds: " << seconds <<endl;
}



// use void getCoreTimeInfo to atrieve vendor, physical address size, model name, and virtual address
//then prints to outuserMideTime.

void getCoreTimeInfo()
{
	string userMode = "";
	string userModeLow = "";
	string systemMode = "";
	string idleMode = "";
	int userModeLowTime = 0;
	int totalUserMode;
	int seconds = 0;
	int userModeTime = 0; 
	int systemModeSeconds=0;
	int idleSec=0;
	int idleMin=0;
	int idleHours=0;
	int idleDays=0;
		
	ifstream inFile("/proc/stat");
	string const statInfo = static_cast<ostringstream&>(ostringstream{} << inFile.rdbuf()).str();
	size_t pos = statInfo.rfind("cpu0");
	
	userMode = statInfo.substr(pos+5, 4);
	stringstream um(userMode);
	um >> userModeTime;
	
	//get user low usage
	userModeLow = statInfo.substr(pos+10,3);
	stringstream uml(userModeLow);
	uml >> userModeLowTime;
	
	
	//the user usage + user low usage
	totalUserMode = userModeTime + userModeLowTime;
	//convert into readable time
	seconds = totalUserMode / 0.001;
	seconds /= 60;
	
	cout << "-How long has it spent time in user mode in seconds , "<<endl<< "(including low-priority user mode)? " << seconds << endl;
	
	systemMode = statInfo.substr(pos+14, 4);
	stringstream systemSeconds(systemMode);
	systemSeconds >> systemModeSeconds; 
	systemModeSeconds/= 0.001;
	cout << "-How long has it spent time in system mode in seconds? " << systemModeSeconds << endl; 
	
	
	

	idleMode = statInfo.substr(pos+18, 6);
	stringstream idleSeconds(idleMode);
	idleSeconds >> idleSec;
	idleSec /= 0.001;
	idleSec /=60;
	cout << "-How long has it been idle in seconds? " << idleSec << endl;
	
	//adds the values to time
	idleMin = idleSec / 60;
	idleHours = idleMin / 60;
	idleDays =  idleHours / 24;
	
	
	cout << "-How long has it been idle in days, hours, minutes and seconds? " <<endl<<"Days:" << idleDays << " Hours: " << idleHours
	<<" Minutes: " << idleMin << " Seconds: " << idleSec <<endl; 
	
	
}



//use void getSwapDevicesSize for step E to get swap device size into MB

void getSwapDevicesSize(){
	string swapSize = "";
	int sizeInMB = 0;
	
	//creates input stream
	ifstream inFile("/proc/swaps");
	string const swapInfo = static_cast<ostringstream&>(ostringstream{} << inFile.rdbuf()).str();
	//find the size
	size_t pos = swapInfo.rfind("Size");
	//gets the substring located at pos
	swapSize = swapInfo.substr(pos+69, 8);
	
	//converts stream to intr
	stringstream mega(swapSize);
	mega >> sizeInMB;
	
	//converts kilobytes into Megabytes as requested
	sizeInMB *= 0.0009765625; 
	
	cout << "-turings swap device in MB: " << sizeInMB << " MB"<< endl;
	cout << endl;
}













