#include <iostream>
#include <vector>

using namespace std;

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

class baseTest //
{
     //XRay->radiology , blood->lab
};

class baseBloodTest:public baseTest
{

};

class cardiologyBloodTest:public baseBloodTest
{

};

class endocrinologyBloodTest:public baseBloodTest
{

};

class baseRadiologicalTest:public baseTest
{

};

class cardiologyEKGTest:public baseRadiologicalTest
{

};

class orthopedicsXRayTest:public baseRadiologicalTest
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
    const vector<baseTest *> &getTestsHaveDone() {
        return testsHaveDone;
    }
    const string getEmail() {
        return patientDemographicInfo.getEmail();
    }


};

//##############################################################################

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

class baseClinic //Clinic==Department
{
protected:

public:
    virtual void askForTest(patient* currentPatient){}
};

class radiologyClinic:public baseClinic //will be modified to be a singleton later, this class may act as a factory class to create tests
{

};

class labClinic:public baseClinic
{

};

class cardiologyClinic:public baseClinic
{
public:
    void askForTest(patient* currentPatient)
    {
        //will search through test vector of patient and see if required tests have done
        //if not, it will request associated clinic to administer test.
    }
};

class orthopedicsClinic:public baseClinic
{

};

class endocrinologyClinic:public baseClinic
{

};

//################################################################################



int main() {

    return 0;
}