#include "miniposix/unique_fd.hpp"

#include <unistd.h>

namespace miniposix {

UniqueFd::UniqueFd(int fd) noexcept {
    // TODO: Adopt fd, including descriptor 0. Only -1 means empty.
    fd_ = fd;
}

UniqueFd::~UniqueFd() noexcept {
    // TODO: Close the owned descriptor, if any.
    reset();
}

UniqueFd::UniqueFd(UniqueFd&& other) noexcept {
    // TODO: Transfer ownership from other; leave other empty.
    fd_ = other.release();
}

UniqueFd& UniqueFd::operator=(UniqueFd&& other) noexcept {
    // TODO: Release any descriptor currently owned by *this, then transfer
    // other. Self move assignment must be safe.
    if(this != &other) {
        reset(other.release());
    }
    return *this;
}

int UniqueFd::get() const noexcept {
    return fd_;
}

int UniqueFd::release() noexcept {
    // TODO: Return the descriptor without closing it; leave *this empty.
    const int released = fd_;
    fd_ = -1;
    return released;
}

void UniqueFd::reset(int fd) noexcept {
    // TODO: Close the current descriptor and adopt fd. Handle reset(get()).
    if(fd == fd_) {
        return;
    }
    if(fd_ != -1) {
        ::close(fd_);
    }
    fd_ = fd;
}

} // namespace miniposix
