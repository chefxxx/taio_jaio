# ------------------------------------------------------------------------------ #
#                               Add eigen lib                                    #
# ------------------------------------------------------------------------------ #

message(STATUS "Adding Eigen...")

include(FetchContent)

FetchContent_Declare(
        eigen
        GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
        GIT_PROGRESS   TRUE
)
FetchContent_MakeAvailable(eigen)