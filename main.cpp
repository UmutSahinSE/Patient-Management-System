#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#define NUMBER_OF_DRUG_TYPES 6

using namespace std;

class secretary;
class baseClinic;

class baseTest //XRay->radiology , blood->lab
{
protected:
    string testName;
public:
    string getTestName(){ return testName; }
};

class baseBloodTest:public baseTest
{

};

class cardiologyBloodTest:public baseBloodTest
{
public:
    cardiologyBloodTest():testName("cardiologyBloodTest"){}
};

class endocrinologyBloodTest:public baseBloodTest
{
public:
    endocrinologyBloodTest():testName("endocrinologyBloodTest") {}
};

class baseRadiologicalTest:public baseTest
{

};

class cardiologyEKGTest:public baseRadiologicalTest
{
public:
    cardiologyEKGTest():testName("EKG") {}
};

class orthopedicsXRayTest:public baseRadiologicalTest
{
public:
    orthopedicsXRayTest():testName("X-RAY") {}
};

//################################################################################

class baseInsurance //Insurances can be created via factory but not sure. What should we put inside?
{

};

class governmentInsurance:public baseInsurance
{

};

class otherInsurance:public baseInsurance //I don't know what other type of insurances are. We should modify the class name
{

};

//################################################################################

class demographicInfo
{
private:
    string email;
    string telephoneNum;
public:
    void setInfo(string setEmail, string setTelephoneNum)
    {
        email=setEmail;
        telephoneNum=setTelephoneNum;
    }
    const string getEmail() {
        return email;
    }
};

//###############################################################################

class patient
{
private:
    string name;
    demographicInfo* patientDemographicInfo;
    baseInsurance* patientInsurance;
    vector<baseTest*>* testsHaveDone;

public:
    patient(){}
    ~patient()
    {
        delete patientInsurance;
        delete patientDemographicInfo;
        delete testsHaveDone;
    }
    patient(string Name="NoName", demographicInfo* Info=NULL, baseInsurance* insurance=NULL,vector<baseTest*>* Tests=NULL)
    {
        name=Name;
        patientDemographicInfo=Info;
        patientInsurance=insurance;
        testsHaveDone=Tests;
    }
    vector<baseTest*>* getTestsHaveDone() {
        return testsHaveDone;
    }
    const string getEmail() {
        return patientDemographicInfo->getEmail();
    }

    const string getName(){
        return name;
    }

};

//##############################################################################

class secretaryCommand
{
protected:
    baseClinic* clinic;
    patient* requestingPatient;
public:
    secretaryCommand(){}
    secretaryCommand(baseClinic* givenClinic, patient* givenPatient)
    {
        clinic=givenClinic;
        requestingPatient=givenPatient;
    }
    ~secretaryCommand()
    {

    }
    virtual void execute()=0;
    virtual string getCommandName()=0;
};

class askForClinics:public secretaryCommand
{
public:
    void execute()
    {
        cout<<requestingPatient->getName()<<" asked for clinic locations:"<<endl;
        if(clinic->getClinicName() != "radiology")
            cout<<"Radiology Clinic is located in:"<<endl;//a location will made up for each
        if(clinic->getClinicName() != "lab")
            cout<<"Lab Clinic is located in:"<<endl;
        if(clinic->getClinicName() != "cardiology")
            cout<<"Cardiology Clinic is located in:"<<endl;
        if(clinic->getClinicName() != "orthopedics")
            cout<<"Orthopedics Clinic is located in:"<<endl;
        if(clinic->getClinicName() != "endocrinology")
            cout<<"Endocrinology Clinic is located in:"<<endl;
    }
    string getCommandName(){return "askForClinics";}
};

class askForAnAppointment:public secretaryCommand
{
public:
    void execute()
    {
        cout<<"An appointment is made in "<<clinic->getClinicName()<<" clinic for "<<requestingPatient->getName()<<endl;
    }
    string getCommandName(){return "askForAppointment";}
};

class seeDoctor:public secretaryCommand
{
public:
    void execute()
    {
        cout<<"Doctor in "<<clinic->getClinicName()<<" clinic is ready to see "<<requestingPatient->getName()<<endl;
    }
    string getCommandName(){return "seeDoctor";}
};

class checkTests:public secretaryCommand
{
public:
    checkTests(baseClinic *pClinic, patient *pPatient) : secretaryCommand(pClinic, pPatient) {

    }

    void execute()
    {
        vector<baseTest*>* currentTests=requestingPatient->getTestsHaveDone();
        vector<string>* requiredTestsOfClinic=clinic->getRequiredTests();
        cout<<"Secretary in "<<clinic->getClinicName()<<" clinic started to check tests for "<<requestingPatient->getName()<<endl;
        for(int i=0;i<requiredTestsOfClinic->size();i++)
        {
            cout<<clinic->getClinicName()<<" clinic require "<<requiredTestsOfClinic->at(i)<<" test.";
            bool testFound=false;
            for(int j=0;j<currentTests->size();j++)
            {
                if(requiredTestsOfClinic->at(i)==currentTests->at(j)->getTestName())
                {
                    testFound=true;
                    cout<<requestingPatient->getName()<<" has done "<<requiredTestsOfClinic->at(i)<<" test before."<<endl;
                    break;
                }
            }
            if(!testFound)
            {
                cout<<requestingPatient->getName()<<" haven't done "<<requiredTestsOfClinic->at(i)<<" test before."<<endl;
                //create a new test from clinic related with requiredTestsOfClinic->at(i) and add result to requesting Patient
            }
        }
    }
    string getCommandName(){return "checkTests";}
};
//################################################################################

class secretary //This part will be modified. It will hold a command vector acting as a history. When patient gives a seeDoctor command, it checks if there was a Checktests command in the history.
{
private:
    vector<secretaryCommand*> previousCommandsByCurrentPatient;
    patient* currentPatient;
    baseClinic* assignedClinic;
public:
    secretary(baseClinic* Clinic)
    {
        assignedClinic=Clinic;
    }
    ~secretary()
    {

    }
    void acceptNewPatient(patient* newPatient)
    {
        cout<<"Secretary from "<<assignedClinic->getClinicName()<<" clinic accepted "<<currentPatient->getName()<<" to hear his requests"<<endl;
        previousCommandsByCurrentPatient.erase(previousCommandsByCurrentPatient.begin(),previousCommandsByCurrentPatient.end());
        currentPatient=newPatient;
    }
    void acceptRequest(secretaryCommand* newCommand)
    {
        if(newCommand->getCommandName()=="seeDoctor")
        {
            bool testsHaveBeenChecked=false;
            for(int i=0;i<previousCommandsByCurrentPatient.size();i++)
            {
                if(previousCommandsByCurrentPatient[i]->getCommandName()=="checkTests")
                {
                    testsHaveBeenChecked=true;
                    break;
                }
            }
            if(!testsHaveBeenChecked)
            {
                cout<<currentPatient->getName()<<" requested to see the doctor from "<<assignedClinic->getClinicName()<<". However patient's tests haven't been checked before. "<<endl;
                secretaryCommand* checkFromSecretary=new checkTests(assignedClinic,currentPatient);
                checkFromSecretary->execute();
                previousCommandsByCurrentPatient.push_back(checkFromSecretary);
            }
        }
        newCommand->execute();
        previousCommandsByCurrentPatient.push_back(newCommand);
    }

};

class baseClinic //Clinic==Department
{
protected:
    string clinicName;
    vector<string> requiredTests;
    secretary* assignedSecretry;
public:
    baseClinic(){assignedSecretry=new secretary(this);}
    ~baseClinic(){}
    string getClinicName() { return clinicName; }
    virtual vector<string>* getRequiredTests(){ return &requiredTests;}

};

class Mutex{    //Stub to manage a mutex
public:
    void lock()
    {
        cout<<"Mutex acquired the lock"<<endl;
    }
    void unlock()
    {
        cout<<"Mutex released the lock"<<endl;
    }

};

//Singleton Class
class radiologyClinic:public baseClinic //This class may act as a factory class to create tests
{
private:
    radiologyClinic():clinicName("radiology")
    {
        //this class will produce Test objects. Test type will be decided in checkTests command.
        //requiredTests.push_back("Something about radiology");
        //...
    }
    //Prevent Copying
    radiologyClinic(const radiologyClinic&);
    radiologyClinic& operator=(const radiologyClinic&);

    static radiologyClinic *instance;
    vector<string> requiredTests;
    static Mutex mutex;//symbolic mutex
public:
    static radiologyClinic *GetradiologyClinic(){
        if(instance == NULL){
            mutex.lock();
            if(instance == NULL){
                instance = new radiologyClinic();
            }
            mutex.unlock();
        }
        return instance;

    }

    /*string GetrequiredTest(){
        return requiredTests(rand() % requiredTests.size());
    }*/
};
Mutex radiologyClinic::mutex;
radiologyClinic* radiologyClinic::instance = NULL;

class labClinic:public baseClinic
{
public:
    labClinic():clinicName("lab"){}
};

class cardiologyClinic:public baseClinic
{
public:
    cardiologyClinic():clinicName("cardiology")
    {
        requiredTests.push_back("EKG");
        requiredTests.push_back("cardiologyBloodTest");
    }

};

class orthopedicsClinic:public baseClinic
{
public:
    orthopedicsClinic():clinicName("orthopedics")
    {
        requiredTests.push_back("X-RAY");
    }
};

class endocrinologyClinic:public baseClinic
{
public:
    endocrinologyClinic():clinicName("endocrinology")
    {
        requiredTests.push_back("endocrinologyBloodTest");
    }
};

//##############################################################################
class drugRecord//maybe can become an observer
{
private:
    vector<patient*> drugOwners[NUMBER_OF_DRUG_TYPES];//vector of patients for 6 different drugs
public:
    void addPatientToRecord(patient* patientToAdd, int whichDrug)
    {
        drugOwners[whichDrug].push_back(patientToAdd);
    }
    void informAllPatients(int whichDrug)//inform all drug owners about side effects
    {
        for(int i=0;i<drugOwners[whichDrug].size();i++)
        {
            cout<<"Patient with email: "<<drugOwners[whichDrug][i]->getEmail()<<" have been informed"<<endl;
        }
    }

};

//###############################################################################

int main() {

    return 0;
}