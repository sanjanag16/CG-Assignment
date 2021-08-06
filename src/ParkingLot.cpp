#include "ParkingLot.h"
#include <iostream>
#include <map>
#include <math.h>
#include <vector>
#include <set>
#include <queue>
#include  <sstream>
using namespace std;

ParkingLot::Car::Car(const string &regNo, const int &age) {
    this->regNo = regNo;
    this->age = age;
}
void ParkingLot::createParkingLot(int lotCount) {
    try {
        if(lotCount<0)
            throw lotCount;
        this->MAX_SIZE = lotCount;
    } catch (int lot) {
        cout<<"Invalid lot count"<<endl;
    }

    availableSlots.assign(MAX_SIZE+1,0);
    cout<<"Created parking lot with "<<lotCount<<" slots"<<endl;
}

void ParkingLot::park(string regNo, int age) {
    if (this->MAX_SIZE == 0) {
        cout<<"Sorry, parking lot is not created"<<endl;
    } else if (isFull()) {
        cout<<"Sorry, parking lot is full"<<endl;
    } else {
        int vac;
        for(int i=1;i<=MAX_SIZE;i++){
            if(availableSlots[i]==0){
                vac = i;
                break;
            }
        }
        availableSlots[vac] = 1;
        carToSlot[regNo] = vac;
        ageToSlot[age].push_back(vac);
        slotToRegNo[vac] = regNo;
        regNoToAge[regNo] = age;
        ageToRegn[age].push_back(regNo);
        CURRENT_CARS++;
        cout<<"Car with vehicle registration number \""<<regNo<<"\" has been parked at slot number "<<vac<<endl;
    }
}

void ParkingLot::leave(int slotNo) {
    if (this->MAX_SIZE == 0) {
        cout<<"Sorry, parking lot is not created"<<endl;
    }
    else if(isEmpty()) {
        cout<<"Parking lot is empty"<<endl;
    }
    else if(availableSlots[slotNo]==1){
        availableSlots[slotNo] = 0;
        string regNo = slotToRegNo[slotNo];
        int age = regNoToAge[regNo];
        carToSlot.erase(regNo);
        for(auto i = ageToSlot[age].begin(); i != ageToSlot[age].end() ;i++){
            if(*i==slotNo){
                ageToSlot[age].erase(i);
                break;
            }
        }
        CURRENT_CARS--;
        slotToRegNo.erase(slotNo);
        cout<<"Slot number "<<slotNo<<" vacated, the car with vehicle registration number \""<<regNo<<"\" left the space, the driver of the car was of age "<<age<<endl;
    }
    else{
        cout<<"Slot number "<<slotNo<<" is already empty"<<endl;
    }
}


void ParkingLot::getRegistrationNumbersFromAge(int age)  {
    if (this->MAX_SIZE == 0) {
        cout<<"Sorry, parking lot is not created"<<endl;
    } else if(ageToRegn[age].size()>0){
        cout<<"The following are the registration number of cars with driver of age "<<age<<endl;
        for(string no: ageToRegn[age]){
            cout<<no<<endl;
        }
    }
    else {
        cout<<"Not found"<<endl<<endl;
    }
}

void ParkingLot::getSlotNumbersFromAge(int age) {
    if (this->MAX_SIZE == 0) {
        cout<<"Sorry, parking lot is not created"<<endl;
    } else if (ageToSlot[age].size()>0){
        cout<<"Following are the slots occupied by the drivers of age "<<age<<endl;
        for(int slot:ageToSlot[age]){
            cout<<slot<<" ";

        }
        cout<<endl;
    } else {
        cout<<"Not found"<<endl;
    }
}


void ParkingLot::getSlotNumberFromRegNo(string regNo) {
    if (this->MAX_SIZE == 0) {
        cout<<"Sorry, parking lot is not created"<<endl<<endl;
    }else if(carToSlot[regNo]){
        cout<<carToSlot[regNo]<<endl;
    }
    else {
        cout<<"Not found"<<endl;
        cout<<endl;
    }
}
