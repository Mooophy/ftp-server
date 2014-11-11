#ifndef USERS_HPP
#define USERS_HPP

#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>

namespace fs {

/**
 * @brief The Users class
 *
 */
class Users
{
public:
    using Dictionary = std::unordered_map<std::string, std::string>;

    Users() = default;

    /**
     * @brief Ctor
     * @param filename
     */
    Users(const std::string& filename):
        data_{}
    {
        std::ifstream ifs{filename};
        for(std::string name,pwd; ifs >> name >> pwd;/* */)
            data_.insert({name, pwd});
    }

    std::ostream& print()const
    {
        for(const auto& user : data_)
            std::cout << user.first << " " << user.second << std::endl;
        return std::cout;
    }

    bool empty()const
    {
        return data_.empty();
    }

    /**
     * @brief check if username with password
     * @param un    username
     * @param pwd   password
     * @return  bool
     */
    bool check(const std::string& un, const std::string& pwd)const
    {
       auto it = data_.find(un);
       if(it != data_.end() && it->second == pwd)    return true;
       return false;
    }

private:
    Dictionary data_;
};

}//namespace
#endif // USERS_HPP

//! @test
//!
//#include <iostream>
//#include "user.hpp"
//int main()
//{
//    fs::Users users{"users"};
//    users.print();
//    std::cout << users.check("alan","1234") << std::endl;
//    return 0;
//}
//! @output
//!
//admin 0000
//root 1234
//pezy 1234
//moophy 1234
//alan 1234
//1
