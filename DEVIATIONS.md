# MISRA C++ 2023 Deviation Register

Active deviations from the MISRA C++ 2023 ruleset as enforced by Parasoft
C/C++test. One entry per deviation, each justifying why a rule is waived for a specific scope and
naming the controls that bound the residual risk.

## Scope

This register applies to every chapter in this repository. Each entry
names its file scope explicitly; rules not listed here are enforced
without deviation across the codebase.

## Active deviations

### DEV-0001: Bounded recursion in flood-fill solution 1

```yaml
deviation_id: DEV-0001
rule: MISRACPP2023-8_2_10-a
rule_category: Required
rule_title: Functions shall not call themselves, either directly or indirectly
scope:
  files:
    - chapter3/src/flood_fill/bounded.cpp
  sites:
    - chapter3/src/flood_fill/bounded.cpp:36
justification: |
  Chapter 3 §3.3.1 demonstrates depth-bounded recursion as an intermediate
  step between the naive recursive form (which crashes with stack
  exhaustion on realistic inputs) and the fully iterative solutions in
  §3.3.2 and §3.3.3. floodFillBounded recurses up to kMaxSafeDepth and
  returns FloodFillStatus::kDepthLimitExceeded once the bound is reached.
  
  This transforms the original stack overflow into a checked, observable failure 
  mode that the caller can react to. Replacing the recursion with iteration would 
  erase the chapter's  load-bearing comparison.
risk: |
  Stack exhaustion at runtime if any of these change without redoing the
  derivation: target stack budget (currently 4 KB), per-frame cost
  (currently 48 bytes at -O2 measured on bounded.cpp), compiler version,
  optimization level. If the actual stack frame grows past the assumed
  size or the surrounding stack consumption (ISRs, RTOS housekeeping,
  caller frames) exceeds the reserved 1 KB margin, the depth check
  becomes insufficient to prevent overflow.
mitigation: |
  - kMaxSafeDepth derivation is documented in
    chapter3/include/flood_fill/bounded.h beside the constant. The
    comment names the target stack budget, the measured per-frame cost,
    the arithmetic ceiling (4096/48 = 85), the reserved margin (25% =
    1024 bytes), and the chosen value (64).
  - Per-frame cost is reproducible by any maintainer via
    `g++ -fstack-usage` on bounded.cpp.
  - The derivation comment explicitly instructs maintainers to redo the
    calculation if the toolchain, optimization level, or stack budget
    changes. Bumping kMaxSafeDepth without redoing the derivation is
    forbidden.
  - The depth-limit check inside floodFillBounded returns
    kDepthLimitExceeded before the recursion can overflow. Callers are
    expected to surface this status (the [[nodiscard]] convention used
    to enforce this at compile time and may be reinstated).
  - The function is inline-annotated with a parasoft-suppress directive
    referencing this deviation ID at the call site.
status: active
opened: xxxx-xx-xx
last_reviewed: xxxx-xx-xx
reviewer: N/A
```

---

## Closed deviations

None.
