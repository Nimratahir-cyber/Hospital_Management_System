#include<iostream>
#include<windows.h>
#include<sstream>
#include<fstream>
#include<iomanip>
#include<string>
#include<vector>
#include<conio.h>

using namespace std;
// a function to remove start and end spaces
string trim(string s)
{
    int start = 0, end = s.length() - 1;

    while (start <= end && s[start] == ' ')
        start++;

    while (end >= start && s[end] == ' ')
        end--;

    return s.substr(start, end - start + 1);
}
//-------------abstract class-------------
class person{
protected:
string name;
public:
virtual void setter()=0;
virtual string getter()=0;
};

//-----------------patients class----------------
class patient: public person{
private:
int age, admit, discharge, room_id;
string disease, doctor_name;
public:
void setter() override {
    cout<<"enter patient's name"<<endl;
    getline(cin,name);
    cout<<"enter disease name"<<endl;
    getline(cin,disease);
    cout<<"enter doctor's name"<<endl;
    getline(cin,doctor_name);
    cout<<"enter patient's age"<<endl;
    cin>>age;
    cout<<"enter admitting date"<<endl;
    cin>>admit;
    cout<<"enter the date to be discharge"<<endl;
    cin>>discharge;
    cout<<"enter room id to be admitted"<<endl;
    start:
    cin >> room_id;
    cin.ignore();
    //To check if room is available or not
    ifstream rfile("room.txt");
    ofstream outfile("temp.txt"); 

    string line;
    bool found = false;

    while(getline(rfile, line)) {
    stringstream ss(line);
    string r1, r2, r3;

    getline(ss, r1, '|');
    getline(ss, r2, '|');
    getline(ss, r3);

    r1 = trim(r1);
    r2 = trim(r2);
    r3 = trim(r3);

    if(r1 == to_string(room_id)) {
        found = true;

        if(r3 == "1") {
            outfile << r1 << " | " << r2 << " | 0" << endl;
        }
        else {
            cout << "Room not available. Choose another one" << endl;

            rfile.close();
            outfile.close();
            remove("temp.txt");
            goto start; //control goes to input room id again
        }
    }
    else {
        outfile << line << endl;
    }
    }

    rfile.close();
    outfile.close();
    remove("room.txt");
    rename("temp.txt","room.txt");// rename the temporary file with the previous fiile's name
    if(!found)
    {
        cout<<"room id not found"<<endl;
    }

    }
    string getter() override{
    return name+" | "+disease+" | "+doctor_name+" | "+to_string(age)+" | "+to_string(admit)+" | "+to_string(discharge)+" | "+to_string(room_id);
    }

};

    //--------------------doctors class--------------------
    class doctor: public person
    {
    private:
    string specialization, available_days;
    int salary;
    public:
    void setter() override
    {
    cout<<"enter doctor's name"<<endl;
    getline(cin,name);
    cout<<"doctor's specialization"<<endl;
    getline(cin,specialization);
    cout<<"doctor's availability in a week"<<endl;
    getline(cin,available_days);
    cout<<"enter doctor's salary"<<endl;
    cin>>salary;
    cin.ignore();
    }
    string getter() override
    {
    return name+" | "+specialization+" | "+available_days+" | "+to_string(salary);
    }

};

//----------------------rooms class---------------------
class room
{
private:
int room_id, expense_per_day ; bool isavailable;
public:
void setter()
{
    cout<<"enter room's id"<<endl;
    cin>>room_id;
    cout<<"enter expense of the room per day"<<endl;
    cin>>expense_per_day;
    isavailable=true;
    cin.ignore();
}
string getter()
{
    return to_string(room_id)+" | "+to_string(expense_per_day)+" | "+to_string(isavailable);
}
};

//-----------------------bills generating class-------------------
class bill
{
public:
    void generate_bill()
    {
        string patientname;
        float expenses;
        cout<<"enter patient's name"<<endl;
        getline(cin,patientname);
        ifstream pfile("patient.txt");
        string line;
        bool found=false;
        while(getline(pfile,line)){ // to get patient's information
            stringstream ss(line);
             
            string name,disease, doctor_name,age, admit, discharge, room_id;
            getline(ss,name,'|');
            getline(ss,disease,'|');
            getline(ss,doctor_name,'|');
            getline(ss,age,'|');
            getline(ss,admit,'|');
            getline(ss,discharge,'|');
            getline(ss,room_id);
            name=trim(name);
            disease=trim(disease);
            doctor_name=trim(doctor_name);
            age=trim(age);
            admit=trim(admit);
            discharge=trim(discharge);
            room_id=trim(room_id);
            if(name==patientname){
                found=true;
                int days=stoi(discharge)-stoi(admit); // to calculate number of days
                ifstream rfile("room.txt");// to get room's information
                string line;

                while(getline(rfile, line)) {
                stringstream ss(line);
                string r1, r2, r3;

                getline(ss, r1, '|');
                getline(ss, r2, '|');
                getline(ss, r3);

                r1 = trim(r1);
                r2 = trim(r2);
                r3 = trim(r3);
                if(room_id==r1){
                    expenses=days*stoi(r2); // here it calculate total expenses
                }
                 }
                 rfile.close();
                 cout<<"patient's name:   "<<patientname<<endl;
                 cout<<"bill generated:   "<<expenses<<endl;
        }
    }
    if(!found){
        cout<<"\n\npatient not found!"<<endl;
    }
    Sleep(4000);
    system("cls");

}
};

//---------------------to add a new patient-----------------
void add_patient()
{
    patient p;
    ofstream pfile("patient.txt", ios::app);
    if(!pfile){
        cout<<"there's an error in opening the file!"<<endl;
    }
    p.setter();
    pfile<<p.getter()<<endl;
    cout<<"Patient added successfully"<<endl;
    getch();
}

//-------------------to view all patients data-----------------
void view_patients()
{   
    cout<<"---------------All patients data---------------"<<endl;
    ifstream pfile("patient.txt");
    string line;
        cout << left
         << setw(15) << "Name"
         << setw(15) << "Disease"
         << setw(20) << "Doctor"
         << setw(5)  << "Age"
         << setw(10) << "Admit"
         << setw(10) << "Discharge"
         << setw(8)  << "Room"
         << endl;

    cout << "-----------------------------------------------------------------------\n";
    while(getline(pfile,line)){
        vector<string>fields;
        stringstream ss(line);
        string temp;

        while(getline(ss,temp,'|')){
            fields.push_back(temp);
        }


    for(int i=0;i< fields.size();i++){
    fields[i]=trim(fields[i]);
    }

            cout << left
                 << setw(15) << fields[0]
                 << setw(15) << fields[1]
                 << setw(20) << fields[2]
                 << setw(5)  << fields[3]
                 << setw(10) << fields[4]
                 << setw(10) << fields[5]
                 << setw(8)  << fields[6]
                 << endl;


}
    getch();
}

//---------------------to search a specific patient--------------------
void search_patient()
{
    string name;
    cout<<"enter patient's name"<<endl;
    getline(cin,name);
    ifstream pfile("patient.txt");
    bool found=false;
    string line;
    while(getline(pfile,line)){
        stringstream ss(line);
        string pname;
        getline(ss,pname,'|');
        pname=trim(pname);
        if(pname==name){
            found=true;
            cout<<line<<endl;
        }
    }
    if(!found){
        cout<<"Patient not found"<<endl;
    }
    getch();
}

//-----------------------to add a new doctor----------------
void add_doctor()
{
    doctor d;

    ofstream dfile("doctor.txt", ios::app);
    if(!dfile){
        cout<<"there's an error in opening the file"<<endl;
    }
    d.setter();
    dfile<<d.getter()<<endl;
    cout<<"Doctor added successfully"<<endl;
    getch();
}

//----------------------to view all doctors---------------------
void view_doctors()
{
    cout<<"----------------All doctors data---------------------------------------"<<endl;

    ifstream dfile("doctor.txt");
    string line;
    cout << left
     << setw(20) << "Name"
     << setw(20) << "Specialization"
     << setw(25) << "Available Days"
     << setw(10) << "Salary"
     << endl;
     cout<<"----------------------------------------------------------------------"<<endl;
    while(getline(dfile,line)){
        stringstream ss(line);
        string temp;
        vector<string>fields;
        while(getline(ss,temp,'|')){
            fields.push_back(temp);
        }
        for(int i=0;i<fields.size();i++){
            fields[i]=trim(fields[i]);
        }
    cout << left
     << setw(20) << fields[0]
     << setw(20) << fields[1]
     << setw(25) << fields[2]
     << setw(10) << fields[3]
     << endl;
    }
    getch();
}

//---------------------to search a specific doctor--------------------
void search_doctor()
{
    string name;
    cout<<"enter doctor's name"<<endl;
    getline(cin,name);
    ifstream dfile("doctor.txt");
    string line;
    bool found=false;
    while(getline(dfile,line)){
        stringstream ss(line);
        string dname;
        getline(ss,dname,'|');
        dname=trim(dname);
        if(name==dname){
            found=true;
            cout<<line<<endl;
        }
    }
    if(!found){
        cout<<"doctor not found"<<endl;
    }
    getch();
}

//-------------------to add a new room---------------------
void add_room()
{
    room r;
    r.setter();
    ofstream rfile("room.txt", ios::app);
    rfile<<r.getter()<<endl;
    cout<<"---------------Room added successfully---------------"<<endl;
    getch();  
}

//----------------------to view all rooms-------------------
void view_rooms()
{
    cout<<"---------------All rooms data-------------------------"<<endl;
    cout<<left
    <<setw(15)<< "room id"
    <<setw(25)<< "expense per day"
    <<setw(15)<< "availability"
    <<endl;
    cout<<"-------------------------------------------------------"<<endl;
    ifstream rfile("room.txt");
    string line;
    while(getline(rfile,line)){
        stringstream ss(line);
        string temp;
        vector<string>fields;
        while(getline(ss,temp,'|')){
            fields.push_back(temp);
        }
        for(int i=0;i<fields.size();i++)
        {
            fields[i]=trim(fields[i]);
        }
        cout<<left
        <<setw(15)<< fields[0]
        <<setw(25)<< fields[1]
        <<setw(15)<< fields[2]
        <<endl;
    }
    getch();
}

//----------------------to search a specific room----------------------
void search_rooms()
{
    string room_id;
    cout<<"enter room's id"<<endl;
    cin>>room_id;
    cin.ignore();
    ifstream rfile("room.txt");
    string line;
    bool found=false;
    while(getline(rfile,line)){
        stringstream ss(line);
        string id;
        getline(ss,id,'|');
        id=trim(id);
        if(room_id==id){
            found=true;
            cout<<line<<endl;
        }
    }
    if(!found){
        cout<<"room not found"<<endl;
    }
    getch();
}

//----------------hospital management function-----------------
void Hospital_management_system()
{
    int choice=0;
    while(choice!=11){
        Sleep(2000);
        system("cls");
    cout<<"---------------HOSPITAL MANAGEMENT SYSTEM---------------"<<endl;
    cout<<"1. Add a patient"<<endl;
    cout<<"2. Add a doctor"<<endl;
    cout<<"3. Add a room"<<endl;
    cout<<"4. View all patients"<<endl;
    cout<<"5. View all doctors"<<endl;
    cout<<"6. View all rooms"<<endl;
    cout<<"7. Search a patient"<<endl;
    cout<<"8. Search a doctor"<<endl;
    cout<<"9. Search a room"<<endl;
    cout<<"10. Generate total bill"<<endl;
    cout<<"11. Exit from this page"<<endl;
    cout<<"\n\n enter your choice"<<endl;
    cin>>choice;
    cin.ignore();
    switch(choice){
        case 1:
        add_patient();
        break;
        case 2:
        add_doctor();
        break;
        case 3:
        add_room();
        break;
        case 4:
        view_patients();
        break;
        case 5:
        view_doctors();
        break;
        case 6:
        view_rooms();
        break;
        case 7:
        search_patient();
        break;
        case 8:
        search_doctor();
        break;
        case 9:
        search_rooms();
        break;
        case 10:
        bill b;
        b.generate_bill();
        break;
        case 11:
        cout<<"exiting from Hospital management system";
        for(int i=0;i<4;i++){
            cout<<". ";
            Sleep(1000);
        }
        system("cls");
        cout<<endl;
        break;
        default:
        cout<<"invalid choice"<<endl;

    }
    }
}



//------------------class for logging in to hospital management system---------------------
class login{
private:
    string username, password;
public:
    void setter(string uname,string  pword)
     {
        username=uname;
        password=pword;
     }
     string getter(){
        return username +" | "+ password;
     }
     
};

//-----------------to register to this system---------------------
void registration()
{
    system("cls");
    login l;
    string uname, pword;
    cout<<"enter your name"<<endl;
    getline(cin,uname);
    cout<<"enter a strong password"<<endl;
    start:
    getline(cin,pword);
    if(pword.length()<8){
    cout<<"please enter password that has 8 or more characters"<<endl;
    goto start;
    }
    else{
        l.setter(uname,pword);
        ofstream outfile("thisfile.txt", ios::app);
        if(!outfile){
            cout<<"oops! there's an error in opening the file"<<endl;
        }
        outfile << l.getter()<<endl;
        outfile.close();
        cout<<"you have been registered successfully !"<<endl;
        Sleep(3000);
        system("cls");
    }

}

//--------------------to log in to this system-----------------------
void loginfunc(){
    system("cls");
    string uname, pword;
    cout<<"enter your name"<<endl;
    getline(cin,uname);
    cout<<"enter your password"<<endl;
    getline(cin,pword);
    ifstream infile("thisfile.txt");
    string line;
    bool found=false;
    while(getline(infile,line)){
        stringstream ss(line);
        string username, password;
        getline(ss,username, '|');
        getline(ss,password, '|');
        username=trim(username);
        password=trim(password);
        if(uname==username && pword==password){

            cout<<"please wait";
            for(int i=0;i<4;i++){
                cout<<". ";
                Sleep(1000);
            }
            cout<<"\nyou have logged in successfully" <<endl;
            cout<<"\n\n---------------Welcome to this page---------------"<<endl;
            Sleep(2000);
            system("cls");
            found=true;
            // to enter to Hospital management system
            Hospital_management_system();
            
        }

    }
            if(!found){
            cout<<"incorrect username or password"<<endl;
             Sleep(2000);
            system("cls");           
        }
    infile.close();
}

//-------------------to exit from this program--------------------
void exit(){
    cout<<"exiting the program";
     for(int i=0;i<4;i++){
                cout<<". ";
                Sleep(500);
     }

}

int main(){
    int choice;
    while(choice!=3){
    cout<<"---------------registration page-----------"<<endl;
    cout<<"1. register to this website"<<endl;
    cout<<"2. login to this website"<<endl;
    cout<<"3. exit from this website"<<endl;
    cout<<"enter your choice :"<<endl;
    cin>>choice;
    cin.ignore();
    switch(choice){
        case 1:
        registration();
        break;
        case 2:
        loginfunc();
        break;
        case 3:
        exit();
        break;
        default:
        cout<<"invalid input"<<endl;
    }
    }
}