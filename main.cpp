#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#define NUMBER_OF_DRUG_TYPES 4

using namespace std;

class secretary;
class baseClinic;
class baseTestDepartment;
class radiologyDepartment;
class labDepartment;
class baseTestRequest;

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

class drugInfo //Base class for drug information
{
protected:
    double dosage;
    bool sideEffects;
    string drugName;
    int drugIndex;

public:
    int getDrugIndex() {
        return drugIndex;
    }

protected:
    informAllPatients(); //Update from drugRecord

};

class DrugA: public drugInfo
{
    DrugA():drugIndex(0){}
};

class DrugB: public drugInfo
{
    DrugB():drugIndex(1){}
};

class DrugC: public drugInfo
{
    DrugC():drugIndex(2){}
};

class DrugD: public drugInfo
{
    DrugD():drugIndex(3){}
};
//###################################################

class baseTest //XRay->radiology , blood->lab
{
protected:
    string testName;
public:
    string getTestName(){ return testName; }
    virtual drugInfo* prescribeRelatedDrug()=0;
};

class baseBloodTest:public baseTest
{

};

class cardiologyBloodTest:public baseBloodTest
{
public:
    cardiologyBloodTest():testName("cardiologyBloodTest"){}
    drugInfo* prescribeRelatedDrug(){ return new DrugA;}
};

class endocrinologyBloodTest:public baseBloodTest
{
public:
    endocrinologyBloodTest():testName("endocrinologyBloodTest") {}
    drugInfo* prescribeRelatedDrug(){ return new DrugB;}
};

class baseRadiologicalTest:public baseTest
{

};

class cardiologyEKGTest:public baseRadiologicalTest
{
public:
    cardiologyEKGTest():testName("EKG") {}
    drugInfo* prescribeRelatedDrug(){ return new DrugC;}
};

class orthopedicsXRayTest:public baseRadiologicalTest
{
public:
    orthopedicsXRayTest():testName("X-RAY") {}
    drugInfo* prescribeRelatedDrug(){ return new DrugD;}
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
    vector<drugInfo*> drugInformationsPatientHolds;
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

    vector<drugInfo *>* getDrugsPatientHolds() const {
        return &drugInformationsPatientHolds;
    }

    void addDrugInfo(drugInfo* added){drugInformationsPatientHolds.push_back(added);}

    void Update(){
        cout<<"The massage has sent"<<endl;
    }


};

//##############################################################################

class secretaryCommand
{
protected:
    baseClinic* clinic;
    static radiologyDepartment* radiology;
    static vector<labDepartment*>* labDepartments;
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
    static void initializeTestDepartments(radiologyDepartment* rad, vector<labDepartment*>* labs)
    {
        radiology=rad;
        labDepartments=labs;
    }
};

class askForClinics:public secretaryCommand
{
public:
    askForClinics(baseClinic *pClinic, patient *pPatient) : secretaryCommand(pClinic, pPatient) {

    }
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
    askForAnAppointment(baseClinic *pClinic, patient *pPatient) : secretaryCommand(pClinic, pPatient) {

    }
    void execute()
    {
        cout<<"An appointment is made in "<<clinic->getClinicName()<<" clinic for "<<requestingPatient->getName()<<endl;
    }
    string getCommandName(){return "askForAppointment";}
};

class seeDoctor:public secretaryCommand
{
public:
    seeDoctor(baseClinic *pClinic, patient *pPatient) : secretaryCommand(pClinic, pPatient) {

    }
    void execute()
    {
        cout<<"Doctor in "<<clinic->getClinicName()<<" clinic is ready to see "<<requestingPatient->getName()<<endl;
        vector<baseTest*>* testsOfPatient=requestingPatient->getTestsHaveDone();
        for(int i=0;i<testsOfPatient->size();i++)
        {
            drugInfo* drugInfoToAdd=testsOfPatient->at(i)->prescribeRelatedDrug();
            requestingPatient->addDrugInfo(drugInfoToAdd);
        }
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
        vector<baseTestRequest*>* requiredTestsOfClinic=clinic->getRequiredTests();
        cout<<"Secretary in "<<clinic->getClinicName()<<" clinic started to check tests for "<<requestingPatient->getName()<<endl;
        for(int i=0;i<requiredTestsOfClinic->size();i++)
        {
            cout<<clinic->getClinicName()<<" clinic require "<<requiredTestsOfClinic->at(i)<<" test.";
            bool testFound=false;
            for(int j=0;j<currentTests->size();j++)
            {
                if(requiredTestsOfClinic->at(i)->getTestName()==currentTests->at(j)->getTestName())
                {
                    testFound=true;
                    cout<<requestingPatient->getName()<<" has done "<<requiredTestsOfClinic->at(i)<<" test before."<<endl;
                    break;
                }
            }
            if(!testFound)
            {
                cout<<requestingPatient->getName()<<" haven't done "<<requiredTestsOfClinic->at(i)<<" test before."<<endl;
                baseTestDepartment* departmentToTestWith;
                if(requiredTestsOfClinic->at(i)->getType()=="radiological")
                {
                    departmentToTestWith=radiology;
                }
                else if(requiredTestsOfClinic->at(i)->getType()=="blood")
                {
                    departmentToTestWith=labDepartments->at(0);//Normally it can be any other lab department. But there is no need to increase complexity.
                }
                departmentToTestWith->createTest(requiredTestsOfClinic->at(i));
                currentTests->push_back(departmentToTestWith->getTestResult());
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

    baseClinic *getAssignedClinic() const {
        return assignedClinic;
    }
};

//#######################################################

class baseTestRequest
{
protected:
    string testType;
    string testName;
public:
    virtual baseTest* requestTest()=0;
    string getType(){ return testType;}
    string getTestName(){ return testName;}
};

class EKGrequest:public baseTestRequest
{
public:
    EKGrequest():testType("radiological"),testName("EKG"){}
    baseTest* requestTest(){ return new cardiologyEKGTest;}
};

class XRAYrequest:public baseTestRequest
{
public:
    XRAYrequest():testType("radiological"),testName("X-RAY"){}
    baseTest* requestTest(){ return new orthopedicsXRayTest;}
};
class endocrinologyBloodTestRequest:public baseTestRequest
{
public:
    endocrinologyBloodTestRequest():testType("blood"),testName("endocrinologyBloodTest"){}
    baseTest* requestTest(){ return new endocrinologyBloodTest;}
};
class cardiologyBloodTestRequest:public baseTestRequest
{
public:
    cardiologyBloodTestRequest():testType("blood"),testName("cardiologyBloodTest"){}
    baseTest* requestTest(){ return new cardiologyBloodTest;}
};


//##########################################################

class baseTestDepartment
{
protected:
    string expectedTestType;
public:
    virtual void createTest(baseTestRequest* request)
    {
        if(request->getType()==expectedTestType)//Template method
        {
            setTestResult(request->requestTest());
        }
    }
    virtual void setTestResult(baseTest* result)=0;
    virtual baseTest* getTestResult(){}
};

//Singleton Class
class radiologyDepartment:public baseTestDepartment //This class may act as a factory class to create tests
{
private:
    radiologyDepartment():expectedTestType("radiological"){ }
    radiologyDepartment(const radiologyDepartment&);
    radiologyDepartment& operator=(const radiologyDepartment&);

    static radiologyDepartment *instance;
    static Mutex mutex;//symbolic mutex
    baseTest* testResult;
public:
    static radiologyDepartment *GetInstance(){
        if(instance == NULL){
            mutex.lock();
            if(instance == NULL){
                instance = new radiologyDepartment();
            }
            mutex.unlock();
        }
        return instance;
    }
    void setTestResult(baseTest* result){ testResult=result; }
    baseTest* getTestResult() { return testResult;}

};
Mutex radiologyDepartment::mutex;
radiologyDepartment* radiologyDepartment::instance = NULL;

class labDepartment:public baseTestDepartment
{
protected:
    baseTest* testResult;
public:
    labDepartment():expectedTestType("blood"){}
    void setTestResult(baseTest* result){ testResult=result; }
    baseTest* getTestResult() { return testResult;}

};

//#########################################################

class baseClinic //Clinic==Department
{
protected:
    string clinicName;
    vector<baseTestRequest*> requiredTests;
    secretary* assignedSecretry;
public:
    baseClinic(){assignedSecretry=new secretary(this);}
    ~baseClinic(){}
    string getClinicName() { return clinicName; }
    virtual vector<baseTestRequest*>* getRequiredTests(){ return &requiredTests;}

};

class cardiologyClinic:public baseClinic
{
public:
    cardiologyClinic():clinicName("cardiology")
    {
        requiredTests.push_back(new EKGrequest);
        requiredTests.push_back(new cardiologyBloodTestRequest);
    }

};

class orthopedicsClinic:public baseClinic
{
public:
    orthopedicsClinic():clinicName("orthopedics")
    {
        requiredTests.push_back(new XRAYrequest);
    }
};

class endocrinologyClinic:public baseClinic
{
public:
    endocrinologyClinic():clinicName("endocrinology")
    {
        requiredTests.push_back(new endocrinologyBloodTestRequest);
    }
};

//##############################################################################
class drugRecord//maybe can become an observer
{
private:
    vector<patient*> drugOwners[NUMBER_OF_DRUG_TYPES];//vector of patients for 6 different drugs
public:
    ~drugRecord(){};
    drugRecord(){};
    void addPatientToRecord(patient* patientToAdd) //'Attach' from observer pattern
    {
        vector<drugInfo*>* drugsOfPatient=patientToAdd->getDrugsPatientHolds();
        for(int i=0;i<drugsOfPatient->size();i++)
        {
            drugOwners[drugsOfPatient->at(i)->getDrugIndex()].push_back(patientToAdd);
        }
    }
    void releasePatientFromRecord(patient* patientToLeave){ //'Detach' from observer pattern
        vector<drugInfo*>* drugsOfPatient=patientToLeave->getDrugsPatientHolds();
        for(int i=0;i<drugsOfPatient->size();i++)
        {
            for (unsigned int i = 0;i  < drugOwners[drugsOfPatient->at(i)->getDrugIndex()].size() ; i++) {
                if(drugOwners[drugsOfPatient->at(i)->getDrugIndex()][i]->getEmail() == patientToLeave->getEmail()){
                    drugOwners[drugsOfPatient->at(i)->getDrugIndex()].erase(drugOwners[drugsOfPatient->at(i)->getDrugIndex()].begin()+i);
                    return;
                }

            }
        }


    }
    void informAllPatients(int whichDrug)//inform all drug owners about side effects 'Update' function
    {
        for(int i=0;i<drugOwners[whichDrug].size();i++)
        {
            cout<<"Patient with email: "<<drugOwners[whichDrug][i]->getEmail()<<" have been informed"<<endl;
        }
    }
};

//###############################################################################


int main() {
    radiologyDepartment* radiology=radiologyDepartment::GetInstance();
    vector<labDepartment*> labs;
    labs.push_back(new labDepartment);
    baseClinic* endo=new endocrinologyClinic;
    baseClinic* card=new cardiologyClinic;
    baseClinic* orth=new orthopedicsClinic;
    secretary endoSecretary(endo);
    secretary cardSecretary(card);
    secretary orthSecretary(orth);
    drugRecord record;
    bool endLoop=false;

    while(!endLoop)
    {
        while(true)
        {
            string result="";
            cout<<"Please enter number of the option:"<<endl;
            cout<<"1) New patient"<<endl;
            cout<<"2) Exit"<<endl;
            cin>>result;
            if(result=="1")
            {
                break;
            }
            else if(result=="2")
            {
                endLoop=true;
                break;
            }
        }
        if(!endLoop)
        {
            //patient demographics... will be created here.
            patient* Patient=new patient("aaa",new demographicInfo,new baseInsurance);
            secretary* secretaryForClinic;
            while (true)
            {
                string result;
                cout<<"Choose which clinic to go:"<<endl;
                cout<<"1)Endocrinology Clinic"<<endl;
                cout<<"2)Orthopedics Clinic"<<endl;
                cout<<"3)Cardiology Clinic"<<endl;
                cin>>result;
                if(result=="1") secretaryForClinic=&endoSecretary;
                else if(result=="1") secretaryForClinic=&endoSecretary;
                else if(result=="1") secretaryForClinic=&endoSecretary;
                else continue;
                secretaryForClinic->acceptNewPatient(Patient);
                break;
            }
            while (true)
            {
                string result;
                cout<<"Choose what do you want secretary to do:"<<endl;
                cout<<"1)Check patient's tests"<<endl;
                cout<<"2)Ask for directions of other clinics."<<endl;
                cout<<"3)Ask for appointment"<<endl;
                cout<<"4)See the doctor."<<endl;
                cout<<"5)Patient wants to leave."<<endl;
                cin>>result;
                if(result=="5")
                {
                    cout<<"Patient leaves the clinic.";
                    break;
                }
                else if(result=="1")
                {
                    secretaryCommand* checkTestCommand=new checkTests(secretaryForClinic->getAssignedClinic(),Patient);
                    secretaryForClinic->acceptRequest(checkTestCommand);
                    continue;
                }
                else if(result=="2")
                {
                    secretaryCommand* directionsCommand=new askForClinics(secretaryForClinic->getAssignedClinic(),Patient);
                    secretaryForClinic->acceptRequest(directionsCommand);
                    continue;
                }
                else if(result=="3")
                {
                    secretaryCommand* appointmentCommand=new askForAnAppointment(secretaryForClinic->getAssignedClinic(),Patient);
                    secretaryForClinic->acceptRequest(appointmentCommand);
                    continue;
                }
                else if(result=="4")
                {
                    secretaryCommand* doctorCommand=new seeDoctor(secretaryForClinic->getAssignedClinic(),Patient);
                    secretaryForClinic->acceptRequest(doctorCommand);
                    continue;
                }
                else
                {
                    cout<<"Wrong input"<<endl;
                    continue;
                }
            }
            record.addPatientToRecord(Patient);
        }
    }

    return 0;
}