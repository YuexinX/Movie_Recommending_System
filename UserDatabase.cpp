#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "utility.h"
using namespace std;

UserDatabase::UserDatabase()
:loaded(false)
{
    // Replace this line with correct code.
}

bool UserDatabase::load(const string& filename)
{
    if(loaded)
        return false;
    std::ifstream inFile(filename);
    if(!inFile)
    {
        std::cerr<<"can't find the file\n";
        return false;
    }
    std::string name;
    std::string email;
    std::string line;
    while(getline(inFile, name)&&getline(inFile, email))
    {
        std::vector<std::string> history;
        getline(inFile, line);
        int num_his = stoi(line);
        for(int i=0; i<num_his; i++)
        {
            getline(inFile, line);
            history.push_back(lowerCase(line));
        }
        User nUser(name, email, history);
        m_profile.insert(email, nUser);
        if(getline(inFile, line)&&line.empty())
            continue;
    }
    loaded = true;
    return true;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    User *p;
    TreeMultimap<std::string, User>::Iterator it;
    it =m_profile.find(email);// Replace this line with correct code.
    if(it.is_valid())
        p = &it.get_value();
    else
        p = nullptr;
    return p;
}

