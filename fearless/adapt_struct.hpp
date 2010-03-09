#ifndef FEARLESS__ADAPT_STRUCT_HPP
#define FEARLESS__ADAPT_STRUCT_HPP

#define FEARLESS_ADAPT_STRUCT_HELPER(r, class, member) \
  (decltype(class::member), member)

// Easier-to-use version of FUSION_ADAPT_STRUCT taking advantage of decltype
#define FEARLESS_ADAPT_STRUCT(class, members) \
  BOOST_FUSION_ADAPT_STRUCT(                  \
      class,                                  \
      BOOST_PP_SEQ_FOR_EACH(FEARLESS_ADAPT_STRUCT_HELPER, class, members) \
    )

#endif // FEARLESS__ADAPT_STRUCT_HPP

