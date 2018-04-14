#include <iostream>
#include <vector>

using namespace std;

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
    cardiologyBloodTest():testName("cardiologyBloodTest") {}
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

class otherInsuraance:public baseInsurance //I don't know what other type of insurances are. We should modify the class name
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
    demographicInfo patientDemographicInfo;
    baseInsurance patientInsurance;
    vector<baseTest*> testsHaveDone;

public:
    vector<baseTest*>* getTestsHaveDone() {
        return &testsHaveDone;
    }
    const string getEmail() {
        return patientDemographicInfo.getEmail();
    }

};

//##############################################################################

class baseClinic //Clinic==Department
{
protected:
    string clinicName;
    vector<string> requiredTests;
public:
    baseClinic(){}

    string getClinicName() { return clinicName; }
    virtual vector<string>* getRequiredTests(){ return &requiredTests;}

};

class radiologyClinic:public baseClinic //will be modified to be a singleton later, this class may act as a factory class to create tests
{
public:
    radiologyClinic():clinicName("radiology")
    {
        //this class will produce Test objects. Test type will be decided in checkTests command.
    }
};

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

//################################################################################

class secretaryCommand
{
public:
    virtual void execute(baseClinic* clinic,patient* requestingPatient)=0;//Made a mistake, these parameters should be class members as pointers.
};

class askForClinics:public secretaryCommand
{
public:
    void execute(baseClinic* clinic,patient* requestingPatient)
    {
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
};

class askForAnAppointment:public secretaryCommand
{
public:
    void execute(baseClinic* clinic,patient* requestingPatient)
    {
        cout<<"An appointment is made in "<<clinic->getClinicName()<<" clinic."<<endl;
    }
};

class seeDoctor:public secretaryCommand
{
public:
    void execute(baseClinic* clinic,patient* requestingPatient)
    {

    }
};

class checkTests:public secretaryCommand
{
public:
    void execute(baseClinic* clinic,patient* requestingPatient)
    {
        vector<baseTest*>* currentTests=requestingPatient->getTestsHaveDone();
        for(int i=0;i<clinic->getRequiredTests()->size();i++)
        {
            for(int j=0;j<currentTests->size();j++)
            {
                if(currentTests->at(j)->getTestName()==clinic->getRequiredTests()->at(i))
                {
                    //create a test with clinic and add it to patient, dont forget secretary was the invoker. Test Clinic should be the receiver.
                }
            }
        }

    }
};
//################################################################################

class drugRecord
{
private:
    vector<patient*> drugOwners[6];//vector of patients for 6 different drugs
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

class secretary //This part will be modified. It will hold a command vector acting as a history. When patient gives a seeDoctor command, it checks if there was a Checktests command in the history.
{
private:

    baseClinic* assignedClinic;
public:
    secretary(baseClinic* Clinic)
    {
        assignedClinic=Clinic;
    }
    ~secretary()
    {
        delete assignedClinic;

    }
    void acceptRequest(secretaryCommand* newCommand)
    {

    }
    void Repeat()
    {

    }

};

//##############################################################################



int main() {

    return 0;
}