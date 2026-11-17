#include "miniposix/pipe.hpp"

#include <cerrno>
#include <system_error>
#include <unistd.h>

namespace miniposix {

Pipe Pipe::create() {
    // TODO: Use a Linux pipe creation call; put its read and write descriptors
    // into the two UniqueFd members. If creation fails, throw
    // std::system_error with errno and do not leak either descriptor.
    int fds[2] = {-1, -1};
    if(::pipe(fds) == -1) {
        const int error = errno;
        throw std::system_error(error, std::generic_category(), "pipe");
    }

    Pipe created;
    created.read_end_.reset(fds[0]);
    created.write_end_.reset(fds[1]);
    return created;
}

} // namespace miniposix
