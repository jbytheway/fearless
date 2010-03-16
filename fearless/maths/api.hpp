#ifndef FEARLESS_MATHS__API_HPP
#define FEARLESS_MATHS__API_HPP

#if defined(_MSC_VER)
  /* The __declspec stuff for ensuring symbols are exported from DLLs and
   * imported back into libraries */
  #ifdef FEARLESS_MATHS_EXPORTS
    #define FEARLESS_MATHS_API __declspec(dllexport)
  #else
    #define FEARLESS_MATHS_API __declspec(dllimport)
  #endif //FEARLESS_MATHS_EXPORTS
#else
  #if defined(__GNUC__) && (__GNUC__ >= 4)
    #define FEARLESS_MATHS_API __attribute__ ((visibility ("default")))
  #else
    #define FEARLESS_MATHS_API
  #endif
#endif

#endif // FEARLESS_MATHS__API_HPP

