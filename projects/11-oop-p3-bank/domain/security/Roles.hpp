#pragma once

#include "Permissions.hpp"

#include <string>

namespace Role {

constexpr int Admin = Permission::ListClients |

                      Permission::AddClient |

                      Permission::DeleteClient |

                      Permission::UpdateClient |

                      Permission::Deposit |

                      Permission::Withdraw |

                      Permission::Transfer |

                      Permission::ViewLogs |

                      Permission::ManageUsers;

constexpr int Teller =
    Permission::ListClients | Permission::Deposit | Permission::Withdraw | Permission::Transfer;

constexpr int Viewer = Permission::ListClients;

}  // namespace Role

inline int permissionFromRole(const std::string& role) {
    if (role == "Admin")
        return Role::Admin;

    if (role == "Teller")
        return Role::Teller;

    if (role == "Viewer")
        return Role::Viewer;

    return 0;
}

inline std::string roleFromPermissions(int permissions) {
    if (permissions == Role::Admin)
        return "ADMIN";

    if (permissions == Role::Teller)
        return "TELLER";

    if (permissions == Role::Viewer)
        return "VIEWER";

    return "UNKNOWN";
}