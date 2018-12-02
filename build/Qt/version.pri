# keep it all lowercase to match program naming convention on *nix systems
PROJECT_NAME = GoTvP2P

# Define version numbers here
VER_MAJOR = 3
VER_MINOR = 4
VER_BUGFIX = 0
VER_BUILD = 0
VER_STATUS = alpha # Should be empty for stable releases!

# Don't touch the rest part
PROJECT_VERSION = $${VER_MAJOR}.$${VER_MINOR}.$${VER_BUGFIX}

!equals(VER_BUILD, 0) {
    PROJECT_VERSION = $${PROJECT_VERSION}.$${VER_BUILD}
}

PROJECT_VERSION = $${PROJECT_VERSION}$${VER_STATUS}

DEFINES += GOTV_VERSION_MAJOR=$${VER_MAJOR}
DEFINES += GOTV_VERSION_MINOR=$${VER_MINOR}
DEFINES += GOTV_VERSION_BUGFIX=$${VER_BUGFIX}
DEFINES += GOTV_VERSION_BUILD=$${VER_BUILD}

os2 {
    DEFINES += GOTV_VERSION=\'\"v$${PROJECT_VERSION}\"\'
    DEFINES += GOTV_VERSION_2=\'\"$${PROJECT_VERSION}\"\'
}
else {
    DEFINES += GOTV_VERSION=\\\"v$${PROJECT_VERSION}\\\"
    DEFINES += GOTV_VERSION_2=\\\"$${PROJECT_VERSION}\\\"
}
