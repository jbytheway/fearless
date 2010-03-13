#ifndef FEARLESS_MATHS__ISTHREEVECTOR_HPP
#define FEARLESS_MATHS__ISTHREEVECTOR_HPP

namespace fearless { namespace maths {

template<typename T, typename Enabler = void>
struct IsThreeVector : std::false_type {};

}}

#endif // FEARLESS_MATHS__ISTHREEVECTOR_HPP

