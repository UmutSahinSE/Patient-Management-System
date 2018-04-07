#include <iostream>

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

class baseClinic //Clinic==Department
{
protected:
public:
    void askForTest(){}
};

class radiologyClinic:public baseClinic
{

};

class labClinic:public baseClinic
{

};

class cardiologyClinic:public baseClinic
{

};

class orthopedicsClinic:public baseClinic
{

};

class endocrinologyClinic:public baseClinic
{

};

//################################################################################

class baseTest //like Mcdonalds food,drink; Burgerking food,drink example
{
    baseClinic departmentAdministered; //XRay->radiology , blood->lab
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

class baseXRayTest:public baseTest
{

};

class cardiologyXRayTest:public baseXRayTest
{

};

class orthopedicsXRayTest:public baseXRayTest
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
};

//###############################################################################

//drug classes here

//###############################################################################

class patient
{
private:
    demographicInfo patientDemographicInfo;
    baseInsurance patientInsurance;

};

//##############################################################################

int main() {

    return 0;
}