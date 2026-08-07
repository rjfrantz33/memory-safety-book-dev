/// @file common/type_aliases.h
/// @brief Cross-chapter type aliases at the C++ standard-library boundary.
///
/// Each alias satisfies MISRA C++ 2023 Rule 6.9.2 exception #1 (typedef
/// of a basic integer type is permitted) so that call sites interacting
/// with stdlib functions whose signatures use keyword-spelled integer
/// types can avoid 6.9.2 and 7.0.6 simultaneously.

#ifndef CODE_SAMPLES_COMMON_TYPE_ALIASES_H
#define CODE_SAMPLES_COMMON_TYPE_ALIASES_H

namespace common {

/// Boundary alias for std::ostream operator<<(int) and similar.
/// MISRA C++ 2023 Rule 6.9.2 exception #1.
using OstreamInt = int;
static_assert(sizeof(OstreamInt) >= 4);  // Rule 6.9.2 rationale: validate width.

}  // namespace common

#endif  // CODE_SAMPLES_COMMON_TYPE_ALIASES_H
