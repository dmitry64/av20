GIT = $$system(git --version)
GIT = $$section(GIT, ' ', 0, 0)
contains( GIT, git ) {
    HAS_GIT=TRUE
} else {
    HAS_GIT=FALSE
}

contains(HAS_GIT, TRUE) {
    message("has git: yes")

    CURRENT_BRANCH = $$system(git symbolic-ref HEAD)
    CURRENT_BRANCH = $$section(CURRENT_BRANCH, '/', 0, 2)
    CURRENT_BRANCH = $$section(CURRENT_BRANCH, '/', 2, 2)
    message("current branch:" $$CURRENT_BRANCH)

    CURRENT_TAG = $$system(git describe --long --tags --always)
    CURRENT_COMMIT_SHA1 = $$section(CURRENT_TAG, '-', 2, 2)
    message("commit SHA1:" $$CURRENT_COMMIT_SHA1)
    CURRENT_TAG = $$section(CURRENT_TAG, '-', 0, 0).$$section(CURRENT_TAG, '-', 1, 1)
    message("current tag:" $$CURRENT_TAG)

    CURRENT_PREFIX = $$section(CURRENT_BRANCH, , 0, 3)
    contains(CURRENT_PREFIX, [Rr][Cc]-) {
        CURRENT_VERSION = $$CURRENT_TAG
        message("Building rc-brunch version")
        CONFIG(debug, debug|release) {
            message("But debug version build")
        }
    } else {
        CONFIG(debug, debug|release) {
            DEBUG_BUILD="d"
        }

        CONFIG(debug, debug|release) {
            CURRENT_VERSION = $$CURRENT_TAG$$DEBUG_BUILD-$$CURRENT_COMMIT_SHA1-$$CURRENT_BRANCH
        }
        CONFIG(release, debug|release) {
            CURRENT_VERSION = $$CURRENT_TAG

        }
        message("Building trunk version")
    }
}
else {
    warning("no git, sorry!")
    CURRENT_VERSION="unknown"
}
message("current version:" $$CURRENT_VERSION)

DEFINES += APP_VERSION=\\\"$${CURRENT_VERSION}\\\"
