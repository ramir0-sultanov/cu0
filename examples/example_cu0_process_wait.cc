#include <cu0/proc.hxx>
#include <iostream>

//! @note supported features may vary on different platforms
//! @note
//!     if some feature is not supported ->
//!         a compile-time warning will be present
//!     else (if all features are supported) ->
//!         no feature-related compile-time warnings will be present
#ifndef __unix__
#warning __unix__ is not defined => \
    cu0::Process::wait() will not be used in the example
int main() {}
#else
#if !__has_include(<sys/types.h>) || !__has_include(<sys/wait.h>)
#warning <sys/types.h> or <sys/wait.h> is not found => \
    cu0::Process::wait() will not be used in this example
int main() {}
#else

int main() {
  auto someProcess = cu0::Process::create(cu0::Executable{
    .binary = "someExecutable"
  });
  if (!someProcess.has_value()) {
    std::cout << "Error: the process was not created" << '\n';
  }
  //! @note not supported on all platforms yet
  //! @note the wait function waits for a process to terminate
  //! @note will block until the process is terminated
  const auto exitCode = someProcess->wait().exitCode();
  if (!exitCode.has_value()) {
    std::cout << "Error: the exit code was not obtained" << '\n';
  } else {
    std::cout << "Exit code of the created process: " << *exitCode << '\n';
  }
}

#endif
#endif
