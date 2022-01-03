#ifndef TABLE_H
#define TABLE_H
#include <string>
#include <vector>
#include <list>

 const int numBuckets = 997;


class Table
{
public:
    Table(std::string keyColumn, const std::vector<std::string>& columns);
    ~Table();
    bool good() const;
    bool insert(const std::string& recordString);
    void find(std::string key, std::vector<std::vector<std::string>>& records) const;
    int select(std::string query, std::vector<std::vector<std::string>>& records) const;

    // We prevent a Table object from being copied or assigned by
    // making the copy constructor and assignment operator unavailable.
    Table(const Table&) = delete;
    Table& operator=(const Table&) = delete;

    
private:

    std::string m_key;
    std::vector<std::string> m_col;
    int hashFunc(std::string hashString) const;
    std::vector<std::list<std::vector<std::string>>> table;
    
    
    int m_pos;
    bool operatorCheck(std::string t) const;
    bool validColumn(std::string t) const;
    bool validCount(std::string t) const;
    bool numericalComp(std::string t) const;
    

    




};

class StringParser
{
public:
    StringParser(std::string text = "")
    {
        setString(text);
    }

    void setString(std::string text)
    {
        m_text = text;
        m_start = 0;
    }

    bool getNextField(std::string& field);

private:
    std::string m_text;
    size_t m_start;
};







#endif // !TABLE_H
