#pragma once
#include <iostream>
#include <string>

using namespace std;

class Candidate {
private:
    string candidateID;
    string fullName;
    string className;

public:
// Constructor mặc định và tham số
Candidate(string id = "", string name = "", string cName = "");

// Getters & Setters
string getCandidateID() const;
string getFullName() const;
string getClassName() const;

void setCandidateID(const string& id);
void setFullName(const string& name);
void setClassName(const string& cName);

friend istream& operator>>(istream& in, Candidate& c);
    friend ostream& operator<<(ostream& out, const Candidate& c);
};