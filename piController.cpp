#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include <cstring>
#include <wiringPi.h>
#include <cstdlib>

using namespace std;

void loadHtml(string filename_);
int inputVal();
void driveControl(int direction_, int motorspeed_);

#define motorSpeed 500

int main(int argc, char **argv, char **envp){
    loadHtml("control-page.html");
    int inputValue = inputVal();
    driveControl(inputValue, motorSpeed);
    return 0;
}

void driveControl(int direction_, int motorspeed_){
    if(wiringPiSetup() == -1){
        printf("<a style=\"font-family:Helvetica;\">GPIO setup failed</a>");
        exit(1);
    }
    pinMode(0, OUTPUT);
    pinMode(1, PWM_OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    
    switch(direction_){
        case 1:
        driveControl(0, 0);
        pwmWrite(1, motorspeed_);
        digitalWrite(0, 1);
        digitalWrite(4, 1);
        printf("<a style=\"font-family:Helvetica;\">LEFT</a>");
        break;
        case 2:
        driveControl(0, 0);
        pwmWrite(1, motorspeed_);
        digitalWrite(2, 1);
        digitalWrite(3, 1);
        printf("<a style=\"font-family:Helvetica;\">RIGHT</a>");
        break;
        case 3:
        driveControl(0, 0);
        pwmWrite(1, motorspeed_);
        digitalWrite(0, 1);
        digitalWrite(3, 1);
        printf("<a style=\"font-family:Helvetica;\">RIGHT</a>");
        break;
        case 4:
        driveControl(0, 0);
        pwmWrite(1, motorspeed_);
        digitalWrite(2, 1);
        digitalWrite(4, 1);
        printf("<a style=\"font-family:Helvetica;\">RIGHT</a>");
        break;
        default:
        digitalWrite(0, 0);
        digitalWrite(1, 0);
        digitalWrite(2, 0);
        digitalWrite(3, 0);
        digitalWrite(4, 0);
    }
}

void loadHtml(string filename_){
    string fileName = "./html/";
    fileName.append(filename_.c_str());
    ifstream fileRead;
    fileRead.exceptions( std::ifstream::failbit | std::ifstream::badbit );
    string htmlLine = "";

    try{
        fileRead.open(fileName);
        printf("Content-type:text/html\n\n");
        do{
            getline(fileRead, htmlLine);
            printf("%s\n",htmlLine.c_str());
        }while(htmlLine!="</html>"&&!fileRead.eof());
        fileRead.close();
    }
    catch (std::ifstream::failure e){
        printf("Error while reading HTML file\n");
        std::cerr << "Exception opening/reading/closing file\n";
    }        
}

int inputVal(){
    char *queryPtr = getenv("QUERY_STRING");
    char query[255];
    snprintf(query, 255, "%s", queryPtr);
    char queryChr = query[6];
    int a = queryChr-'0';
    return a;
}

// bash to compile: g++ piController.cpp -o pi-controller -lwiringPi && sudo chown root pi-controller && sudo chgrp root pi-controller && sudo chmod +s pi-controller