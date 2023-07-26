#ifndef MARL_MACRO_H_
#define MARL_MACRO_H_

#define MARL_ASSERT assert
#define MARL_EXPORT


// MARL_UNDEFINED_SANITIZER_ONLY(X) resolves to X if
// MARL_UNDEFINED_SANITIZER_ENABLED is defined to a non-zero value, otherwise
// MARL_UNDEFINED_SANITIZER_ONLY() is stripped by the preprocessor.
#if MARL_UNDEFINED_SANITIZER_ENABLED
#define MARL_UNDEFINED_SANITIZER_ONLY(x) x
#else
#define MARL_UNDEFINED_SANITIZER_ONLY(x)
#endif  // MARL_UNDEFINED_SANITIZER_ENABLED

//#define MARL_USE_UCONTEXT 1

#if _WIN32
#define MARL_WINDOWS 1
#endif

#endif // MARL_MACRO_H_