#pragma once

#include <string>

class User {

	public:

        private:

            std::string _username;
            std::string _passwordHash;
            std::string _role;

        public:

            User(const std::string& username, const std::string& passwordHash,
              const std::string& _role);

            const std::string& getUsername() const;
            const std::string& getPasswordHash() const;
            const std::string& getRole() const;
            

            /**
             * @brief Changes the username of the User.
             * @param username The new username.
             * @exception std::invalid_argument Thrown if username is empty
             */
            void changeUsername(const std::string& username);

            /**
             * @brief Changes the password of the User.
             * @param password The new passwordHash.
             * 
             */
            void changePasswordHash(const std::string& passwordHash);

            void changeRole(const std::string& role);
};