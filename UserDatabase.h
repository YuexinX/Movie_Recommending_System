//
//  UserDatabase.hpp
//  Project 4
//
//  Created by Time Thief on 3/14/23.
//

#ifndef UserDatabase_h
#define UserDatabase_h


#include <string>
#include <vector>
#include "treemm.h"
class User;

class UserDatabase
{
  public:
    UserDatabase();
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;
    
    
  private:
    bool loaded;
   // std::vector<User> user_profiles;
    TreeMultimap<std::string, User> m_profile;
};

#endif /* UserDatabase_hpp */
