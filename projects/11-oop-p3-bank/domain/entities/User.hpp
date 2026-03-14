#pragma once

#include <string>

class User {

	public:

		enum Permission {
           NONE = 0,
           VIEW_CLIENTS = 1 << 0,
           ADD_CLIENT = 1 << 1,
           DELETE_CLIENT = 1 << 2,
           UPDATE_CLIENT = 1 << 3,
           TRANSACTIONS = 1 << 4,
           MANAGE_USERS = 1 << 5,
           All = 0xFFFFFFFF
         };

        private:

            std::string _username;
            std::string _passwordHash;
                int _permissions;

        public:

            User(const std::string& username, const std::string& passwordHash,
              int permissions);

            const std::string& getUsername() const;
            const std::string& getPasswordHash() const;

            int getPermissions() const;
            

            bool hasPermission(Permission permission) const;
            void addPermission(Permission permission);
            void removePermission(Permission permission);

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

};