#ifndef FEARLESS__API_HPP
#define FEARLESS__API_HPP

#if defined(_MSC_VER)
  /* The __declspec stuff for ensuring symbols are exported from DLLs and
   * imported back into libraries */
  #ifdef FEARLESS_EXPORTS
    #define FEARLESS_API __declspec(dllexport)
  #else
    #define FEARLESS_API __declspec(dllimport)
  #endif //FEARLESS_EXPORTS
#else
  #if defined(__GNUC__) && (__GNUC__ >= 4)
    #define FEARLESS_API __attribute__ ((visibility ("default")))
  #else
    #define FEARLESS_API
  #endif
#endif

#endif // FEARLESS__API_HPP

