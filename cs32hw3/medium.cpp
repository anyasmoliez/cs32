

class Medium {
public:
     Medium(string ID);
    virtual string connect() const=0;
     string id() const;
    virtual string transmit(string msg) const;
    virtual ~Medium();

private:
    string m_id;
};
class TwitterAccount : public Medium {
public:
    TwitterAccount( string account);
    virtual string connect() const;
    
    virtual ~TwitterAccount();
private:
    string m_account;

};
class Phone : public Medium {
public:
    Phone( string number, CallType c);
    virtual string connect() const;
    virtual string transmit(string msg) const;
    virtual ~Phone();
private:
   string m_number;
   CallType m_c;

};
class EmailAccount : public Medium {
public:
    EmailAccount(string email);
    virtual string connect() const;
    
    virtual ~EmailAccount();
private:
    string m_email;
    
};

EmailAccount::EmailAccount( string email): Medium(email) {
    m_email = email;
}
string EmailAccount::connect() const {
    return "Email";
}


EmailAccount::~EmailAccount() {
    cout << "Destroying the email account " << m_email << "."<< endl;
}


Phone::Phone(string phone, CallType c):Medium(phone) {
    m_number = phone;
    m_c = c;
}
string Phone::connect() const {
    return "Call";
}

string Phone::transmit(string msg) const {
    string t("text: ");
    string v("voice: ");
    if (m_c == VOICE) {
        return v + msg;

    }
    else
        return t + msg;
    
}
Phone::~Phone() {
    cout << "Destroying the phone " <<m_number  << "."<<endl;
}


TwitterAccount::TwitterAccount( string account):Medium(account) {
    m_account = account;
    
}

string TwitterAccount::connect() const {
    return "Tweet";
}


TwitterAccount::~TwitterAccount() {
    cout << "Destroying the Twitter account " << m_account << "."<<endl;
    
}

Medium::Medium(string ID ):m_id(ID) {
    

}


string Medium::id() const {
    return m_id;
}

string Medium::transmit(string msg) const {
    
  
    
        return "text: " + msg;
}

Medium::~Medium() {

}

