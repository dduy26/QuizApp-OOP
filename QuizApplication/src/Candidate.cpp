#include "Candidate.h"

Candidate::Candidate(string id, string name, string cName): candidateID(id), fullName(name), className(cName) {}

string Candidate::getCandidateID() const { 
    return candidateID; 
}

string Candidate::getFullName() const { 
    return fullName; 
}

string Candidate::getClassName() const { 
    return className; 
}

void Candidate::setCandidateID(const string& id) { 
    candidateID = id; 
}

void Candidate::setFullName(const string& name) { 
    fullName = name; 
}

void Candidate::setClassName(const string& cName) { 
    className = cName; 
}

//Nhap thông tin thí sinh
istream& operator>>(istream& in, Candidate& c) {
    cout << "Enter Candidate ID: ";
    getline(in >> ws, c.candidateID);
    cout << "Enter Full Name: ";
    getline(in, c.fullName);
    cout << "Enter Class Name: ";
    getline(in, c.className);
    return in;
}

// in thông tin thí sinh
ostream& operator<<(ostream& out, const Candidate& c) {
    out << "Candidate ID: " << c.candidateID << "\n" << "Full Name: " << c.fullName << "\n"<< "Class: " << c.className;
    return out;
}
