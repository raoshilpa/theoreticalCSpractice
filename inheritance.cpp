#include <iostream>
#include <string>
using namespace std;

enum CallType {
    VOICE, TEXT
};


class Medium {
    
//    The Medium class must not have a default constructor. The only constructor you may declare for Medium must have exactly one parameter. That parameter must be of type string, and it must be a useful parameter.
    
    string mID;
//    string mConnect;
    
public:

    // CallType type = TEXT
    Medium(string param) : mID(param) { }
    
    string getID() const {
        return mID;
    }
    
//    string getConnect() const {
//        return mConnect;
//    }
    
    virtual string connect() const = 0;
//    const virtual string id() = 0;
    
    string id() const {
        return mID;
    }
    
    virtual string transmit(string msg) const {
        string result = "text: " + msg;
        return result;
    }
    
    virtual ~Medium() {
        
    }
    
    // destructor must say "cleaning up"
    
};



class TwitterAccount : public Medium {
    
    string mConnect = "Tweet";
    
public:
//     Tweet using id UCLABruinAlert, sending text: Major power outage in West L.A.
//    cout << m->connect() << " using id " << m->id()
//         << ", sending " << m->transmit(msg) << endl;
    
    TwitterAccount(string s) : Medium(s) {
        
    }
   
    string connect() const {
        return mConnect;
    }
    
    ~TwitterAccount() {
        
        string result = "Destroying the Twitter account " + getID() + ".";
        cout << result << endl;
        
    }
    
};



class Phone : public Medium {
    
//    Call using id (310) 825 3894, sending voice: Major power outage in West L.A.
//    Call using id (213) 389 9060, sending text: Major power outage in West L.A.
    //    cout << m->connect() << " using id " << m->id()
    //         << ", sending " << m->transmit(msg) << endl;
    
    CallType mType;
//    string mID;
    string mConnect = "Call";

public:
    
    
//    child::child(int a) : parent(a)
    
    Phone(string s, CallType type) : Medium(s) {
        mType = type;
    }

    ~Phone() {
        
        string result = "Destroying the phone " + getID() + ".";
        cout << result << endl;
    
    }
    
    string connect() const {
        return mConnect;
    }

    CallType getType() const {
        return mType;
    }
    
    string transmit(string msg) const {
        string typeThing;
        string result;
        
        switch(mType) { // how to get type
                    
                case VOICE:
                    typeThing = "voice: ";
                    break;
                default:
                    typeThing = "text: ";
                    break;
                
        }
        
        result = typeThing + msg;
        return result;
        
    }
    
};



class EmailAccount : public Medium {
    
    // Email using id sdsd@ucla.edu, sending text: Major power outage in West L.A.
    //    cout << m->connect() << " using id " << m->id() << ", sending " << m->transmit(msg) << endl;
    
    string mConnect = "Email";
    
public:
    
    EmailAccount(string s) : Medium(s) { }
    
    string connect() const {
        return(mConnect);
    }
    
    ~EmailAccount() {
        
        string result = "Destroying the email account " + getID() + ".";
        cout << result << endl;
        
    }
    
};

// Tweet using id UCLABruinAlert, sending text:
void send(const Medium* m, string msg)
{
    cout << m->connect() << " using id " << m->id() << ", sending " << m->transmit(msg) << endl;
}


int main()
{
    Medium* media[4];
    media[0] = new TwitterAccount("UCLABruinAlert");
      // Phone users may prefer messages to be left as voice or text.
    media[1] = new Phone("(310) 825 3894", VOICE);
    media[2] = new Phone("(213) 389 9060", TEXT);
    media[3] = new EmailAccount("jbroon@ucla.edu");

    cout << "Send the message." << endl;
    for (int k = 0; k < 4; k++)
        send(media[k], "Major power outage in West L.A.");

      // Clean up the media before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete media[k];
    
}

//Send the message.
//Tweet using id UCLABruinAlert, sending text: Major power outage in West L.A.
//Call using id (310) 825 3894, sending voice: Major power outage in West L.A.
//Call using id (213) 389 9060, sending text: Major power outage in West L.A.
//Email using id jbroon@ucla.edu, sending text: Major power outage in West L.A.
//Cleaning up.
//Destroying the Twitter account UCLABruinAlert.
//Destroying the phone (310) 825 3894.
//Destroying the phone (213) 389 9060.
//Destroying the email account jbroon@ucla.edu.
