#include "domain/value_objects/Role.hpp"

//  Adding a new role means:
//    1. Define its permission bitmask here as a named constructor.
//    2. Add its name string to Role::from().
//  That is the only file that changes

Role::Role(std::string name, int permissions) : _name(std::move(name)), _permissions(permissions) {}

Role Role::admin() {

    return Role("Admin",
                Permission::ListClients | Permission::AddClient | Permission::UpdateClient
                    | Permission::DeleteClient | Permission::Deposit | Permission::Withdraw
                    | Permission::Transfer | Permission::ViewLogs | Permission::ManageUsers);
}

Role Role::teller() {

    return Role("Teller",
                Permission::ListClients | Permission::Deposit | Permission::Withdraw
                    | Permission::Transfer);
}

Role Role::viewer() {

    return Role("Viewer", Permission::ListClients);
}

Role Role::from(const std::string& roleName) {

    if (roleName == "Admin")
        return admin();
    if (roleName == "Teller")
        return teller();
    if (roleName == "Viewer")
        return viewer();

    throw std::invalid_argument(
        "Role::from - unknown role name: '" + roleName + "'. "
        "Valid roles are: Admin, Teller, Viewer."
    );
}

bool Role::can(int permission) const {
    return (_permissions & permission) != 0;
}

const std::string& Role::name() const {
    return _name;
}

int Role::permissions() const {
    return _permissions;
}

bool Role::operator==(const Role& other) const {
    return _permissions == other._permissions;
}

bool Role::operator!=(const Role& other) const {
    return !(*this == other);
}