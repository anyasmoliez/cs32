#include "Table.h"
#include <functional>
#include <iostream>
#include <cstdlib>
#include <cctype>
using namespace std;




bool StringParser::getNextField(std::string& fieldText)
{
    m_start = m_text.find_first_not_of(" \t\r\n", m_start);
    if (m_start == std::string::npos)
    {
        m_start = m_text.size();
        fieldText = "";
        return false;
    }
    if (m_text[m_start] != '\'')
    {
        size_t end = m_text.find_first_of(" \t\r\n", m_start + 1);
        fieldText = m_text.substr(m_start, end - m_start);
        m_start = end;
        return true;
    }
    fieldText = "";
    for (;;)
    {
        m_start++;
        size_t end = m_text.find('\'', m_start);
        fieldText += m_text.substr(m_start, end - m_start);
        m_start = (end != std::string::npos ? end + 1 : m_text.size());
        if (m_start == m_text.size() || m_text[m_start] != '\'')
            break;
        fieldText += '\'';
    }
    return true;
}

Table::Table(std::string keyColumn, const std::vector<std::string>& columns) { 
    m_col = columns;
    m_key = keyColumn;
    table.resize(numBuckets);
    

}

Table::~Table() {

}

int Table::hashFunc(std::string hashString) const {//function to hash keys
    std::hash<std::string>str_hash;
    unsigned int hashValue = str_hash(hashString);
    unsigned int num_bucket = hashValue % numBuckets;
    return num_bucket;
}

bool Table::good() const {

    
    for (size_t i = 0; i < m_col.size();i++)
        for (size_t j = i + 1;j < m_col.size();j++) //check for duplicates
            if (m_col[i] == m_col[j])
                return false;

    for (size_t i = 0;i < m_col.size();i++) {
        if (m_col[i] == "") //checks for empty strings
            return false;
    }

            if (m_col.empty())
                return false;
            for (size_t i = 0; i < m_col.size();i++) { //checks that key value is in column
                if (m_key == m_col[i])
                    return true;

            }

            return false;

        
}

bool Table::insert(const string& recordString) {
    std::vector<std::string> record;
    list<vector<string>>recordVector;

    if (!good())
        return false;
    //finding the key value position in constructor
    int pos = -1;
    for (size_t i = 0; i < m_col.size();i++) {
        pos++;
        if (m_key == m_col[i])
            break;
    }
    
    m_pos = pos;  //store pos for later use
    StringParser q;
    q = recordString;
    string r = recordString;  //finding the key value in recordString
    for (int i = 0;i <= pos;i++) {
        q.getNextField(r);
    }
    


    int bucket = hashFunc(r);


    StringParser s;
    s = recordString;
    int count = 0;
    string t=recordString;
   
    while (s.getNextField(t) == true) {
        count++;
    }
    StringParser sRecord = recordString;
    std::string tRecord;
    if (count == m_col.size()) {
        for (int i = 0; i < count;i++) {
            sRecord.getNextField(tRecord);  //inserting  record string into vector
            record.push_back(tRecord);
            
        }
        table[bucket].push_back(record);
      
        return true;
    }
    return false;
}

void Table::find(string key, vector<vector<string>>& records) const {
    records.clear();
   int buckets = hashFunc(key);
   
    list<vector<string>>::const_iterator it;
   
   
    for (it = table[buckets].begin();it != table[buckets].end();it++) {//iterate thru list at bucket 
        if ((*it)[m_pos] == key) {  //only push vector if it contains key
            
           records.push_back(*it);
       }
   }
  
    
}

bool Table::operatorCheck(string t) const { //checks that operator is valid
    for (size_t i = 0; i < t.size();i++) {
        if (isalpha(t[i]))
            if (islower(t[i]))
                t[i] = toupper(t[i]); //converting word operators to be all uppercase
    }
    if (t != "<" && t != ">" && t != "==" && t != "=" && t != "!=" && t != "<=" && t != ">=" && t != "LT"
        && t != "LE" && t != "GT" && t != "GE" && t != "NE" && t != "EQ")
        return false;
    return true;
}

bool Table::validColumn(string t) const { //checks that 1st query token is actually a column
    int count = -1;
    for (size_t i = 0; i < m_col.size();i++)
        if (t == m_col[i])
            return true;
  
    

    return false;
}
bool Table::numericalComp(string t) const {//checks if operator is numerical comparison operator
    for (size_t i = 0; i < t.size();i++) {
        if (isalpha(t[i]))
            if (islower(t[i]))
                t[i] = toupper(t[i]);
    }

    if (t == "LT" || t == "LE" || t == "GT" || t == "GE" || t == "NE" || t == "EQ")
        return true;
    else
        return false;



    
}


bool Table::validCount(string t) const { //checking that there are 3 tokens
    int count = 0;
    StringParser s = t;;
       string tester;
      
       while (s.getNextField(tester) == true) {
           count++;
       }
       if (count == 3)
           return true;
       else
           return false;
}

bool stringToDouble(string s, double& d)
{
    char* end;
    d = std::strtof(s.c_str(), &end);
    return end == s.c_str() + s.size() && !s.empty();
}



int Table::select(std::string query, std::vector<std::vector<std::string>>& records) const {
    int position=0;
    StringParser s = query;
    string t;
    string columnName;
    string operatorName;
    string valueName;
    double d;
    string comParisonValue;
    int badCount=0;
    records.clear();
    
    int numCount = 0;
    int stringCount = 0;
    double value = 0.0;

    if (!good())
        return -1;

    if (!validCount(query))
        return -1;

    

    for (int i = 0; i < 3; i++) { //checking for valid query
        s.getNextField(t);
        if (i == 0 && !validColumn(t))  //saving each token for later 
            return -1;
        else if (i == 0 && validColumn(t))
            columnName = t;
        else if (i == 1 && !operatorCheck(t))
            return -1;
        else if (i == 1 && operatorCheck(t))
            operatorName = t;
        else if (i == 2)
            valueName = t;
    }
    for (size_t i = 0; i < m_col.size();i++) {//finding position of token column in contructor column
        if (columnName == m_col[i])
            position = i;


    }


    if (numericalComp(operatorName) && !stringToDouble(valueName, d))  //checking that non-numeric string isn't used with numerical operator
        return -1;
    else if (numericalComp(operatorName) && stringToDouble(valueName, d))
        value = d;

    if (numericalComp(operatorName)) {  //capitalize numerical operators
        for (size_t i = 0; i < operatorName.size();i++) {
            operatorName[i] = toupper(operatorName[i]);
        }
    }

       
        list<vector<string>>::const_iterator p;
        for (int i = 0; i < numBuckets;i++) {//iterate through each bucket
           
            for (p = table[i].begin(); p != table[i].end();p++) {  //iterate through the list 
                    if (numericalComp(operatorName) && !stringToDouble(p->at(position), d)) {//if numerical operator but 3rd token isnt a number
                        badCount++;
                        
                    }
                    else if (numericalComp(operatorName) && stringToDouble(p->at(position), d)) {//compute the associated operators

                        if (operatorName == "LT" && d < value) //pushes value if true
                            records.push_back(*p);
                        else if (operatorName == "LE" && d <= value)
                            records.push_back(*p);
                        else if (operatorName == "GT" && d > value)
                            records.push_back(*p);
                        else if (operatorName == "GE" && d >= value)
                            records.push_back(*p);
                        else if (operatorName == "NE" && d != value)
                            records.push_back(*p);
                        else if (operatorName == "EQ" && d == value)
                            records.push_back(*p);
                      
                    }

                    else if (!numericalComp(operatorName)) {//compute the associated operators
                        if (operatorName == "<" && p->at(position) < valueName)
                            records.push_back(*p);
                        else if (operatorName == "<=" && p->at(position) <= valueName) //pushes values if true
                            records.push_back(*p);
                        else if (operatorName == ">" && p->at(position) > valueName)
                            records.push_back(*p);
                        else if (operatorName == ">=" && p->at(position) >= valueName)
                            records.push_back(*p);
                        else if ((operatorName == "==" || operatorName == "=") && p->at(position) == valueName)
                            records.push_back(*p);
                        else if (operatorName == "!=" && p->at(position) != valueName)
                            records.push_back(*p);
                        
                    }
                
            }

        

        
    }
    if (badCount > 0)
        return badCount;
    else
        return 0;

}



    

