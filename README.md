*This activity has been created as part of the 42 curriculum by sasilves, jzelada-*

---

## Description

**push_swap** is a sorting project with strict constraints. Its goal is to sort a list of integers using only two stacks (`a` and `b`) and a limited set of operations, while keeping the generated instruction sequence as short as possible.

The program implements four sorting strategies. The default adaptive strategy selects a method according to the initial disorder of the input. Each strategy can also be selected explicitly.

---

## Project structure

```text
push_swap/
├── Makefile
├── README.md
├── includes/
│   ├── push_swap.h          # Main header, shared includes and parsing prototypes
│   ├── checker_bonus.h      # Bonus instruction reader prototype
│   ├── stack.h              # t_node, t_stack and stack function prototypes
│   ├── operations.h         # Prototypes for the 11 stack operations
│   ├── algorithms.h         # Sorting and positioning function prototypes
│   └── bench.h              # t_ops_count and t_bench
├── srcs/
│   ├── main/
│   │   ├── main.c                   # Entry point, initialization and strategy dispatch
│   │   ├── main_utils.c             # Strategy and benchmark flag parsing
│   │   ├── checker_bonus.c          # Instruction execution and final result
│   │   └── checker_utils_bonus.c    # Bounded instruction reader without heap allocation
│   ├── parsing/
│   │   ├── parsing.c                # Integer validation, duplicate detection and stack creation
│   │   └── parsing_utils.c          # Space-separated argument handling
│   ├── operations/
│   │   ├── operations_swap.c        # sa, sb, ss
│   │   ├── operations_push.c        # pa, pb
│   │   ├── operations_rotate.c      # ra, rb, rr
│   │   └── operations_reverse_rotate.c  # rra, rrb, rrr
│   ├── algorithms/
│   │   ├── algorithm_utils.c        # Sorted-state check
│   │   ├── algorithm_position.c     # Minimum/maximum positioning
│   │   ├── sort_simple.c            # Selection sort and small-input routines
│   │   ├── sort_medium.c            # Index-window chunk sort
│   │   ├── sort_complex.c           # Binary LSD radix sort
│   │   └── sort_adaptive.c          # Disorder-based strategy selection
│   └── utils/
│       ├── stack/
│       │   ├── stack.c              # Stack/node allocation and cleanup
│       │   └── stack_index.c        # Rank assignment from 0 to n - 1
│       ├── disorder/
│       │   └── disorder.c           # Inversion-based disorder calculation
│       └── bench/
│           └── bench.c              # Benchmark output to stderr
└── libft/                           # Custom C library, including the ft_atol extension
```

---

## Instructions

### Compilation

The project requires a POSIX environment, a C compiler, Make and `ar`. The Makefiles use `cc` with `-Wall -Wextra -Werror`.

```bash
make          # Build push_swap and libft
make bonus    # Build checker and libft
make clean    # Remove object and generated dependency files
make fclean   # Also remove the executables and libft.a
make re       # Rebuild push_swap from scratch
```

Run `make bonus` after `make re` if you also need to rebuild the checker. Header and library dependencies are tracked, and repeating a build without changes does not relink the executables.

### Usage

```bash
./push_swap [--simple | --medium | --complex | --adaptive] [--bench] <integers>
```

Place flags before the numbers. Integers may be passed as separate arguments or as space-separated strings. The first number is placed at the top of stack `a`; stack `b` starts empty.

| Flag | Description |
|---|---|
| `--simple` | Select minimum-selection sorting, O(n²) in stack operations |
| `--medium` | Select index-window chunk sorting, targeting O(n√n) |
| `--complex` | Select binary LSD radix sorting, O(n log n) |
| `--adaptive` | Select a strategy according to the initial disorder; this is the default |
| `--bench` | Write disorder, strategy information and operation counts to stderr |

Running `push_swap` without arguments exits without output. An already sorted input produces no sorting instructions. If `--bench` is enabled for a numeric input, its metrics are still written to stderr.

### Checker bonus

The `checker` program reads instructions from standard input and applies them to the supplied numbers:

```bash
ARG="4 67 3 87 23"
./push_swap $ARG | ./checker $ARG
# OK
```

- Prints `OK` when stack `a` is sorted in ascending order and stack `b` is empty.
- Prints `KO` when the final state does not satisfy both conditions.
- Prints `Error` to stderr for invalid arguments, malformed instructions, allocation failures or read errors.
- Accepts the 11 operation names, each terminated by `\n`.
- Rejects empty lines, surrounding spaces, NUL bytes, unknown operation names and an incomplete final instruction.
- Accepts legal operations that have no effect on an empty or single-element stack.
- Without arguments, exits without output.

For an interactive check, press **Ctrl+D** on an empty line to finish entering instructions. An empty instruction stream is valid: the checker evaluates the initial state.

### Examples

```bash
# Basic sorting
./push_swap 5 3 1 4 2

# Pass the same input as a quoted string
./push_swap "5 3 1 4 2"

# Select the simple strategy and count its instructions
./push_swap --simple 5 4 3 2 1 | wc -l

# Validate the generated instructions
ARG="4 67 3 87 23"
./push_swap --complex $ARG | ./checker $ARG

# Display metrics while hiding sorting instructions
./push_swap --bench 5 3 1 4 2 >/dev/null

# Generate and sort 500 unique random numbers on Linux
shuf -i 0-9999 -n 500 > args.txt
./push_swap $(cat args.txt) | wc -l
```

### Error handling

The program writes `Error\n` to stderr and exits with a nonzero status when:

- An argument is empty, contains only spaces or is not a valid integer.
- A number is outside the `int` range.
- Two arguments represent the same integer, including alternative forms such as `0` and `-0`.
- A flag is unknown.
- More than one strategy flag is supplied, including repetitions of the same strategy.
- A required memory allocation fails.

The parser validates the complete number and its `int` range before calling `ft_atol`. This additional Libft function returns a `long` and handles conversion overflow by saturating to `LONG_MIN` or `LONG_MAX`. The parser independently rejects values outside the `int` range.

---

## Available operations

| Operation | Description |
|---|---|
| `sa` | Swap the first two elements of `a` |
| `sb` | Swap the first two elements of `b` |
| `ss` | Apply `sa` and `sb` together |
| `pa` | Move the top element of `b` to the top of `a` |
| `pb` | Move the top element of `a` to the top of `b` |
| `ra` | Rotate `a` upward; its first element becomes its last |
| `rb` | Rotate `b` upward |
| `rr` | Apply `ra` and `rb` together |
| `rra` | Rotate `a` downward; its last element becomes its first |
| `rrb` | Rotate `b` downward |
| `rrr` | Apply `rra` and `rrb` together |

In `push_swap`, operations that change a stack are printed to stdout and counted in `t_ops_count`. The checker reuses the same functions with `ops == NULL` to execute silently. A legal operation on a stack too small to change has no effect and is not an error.

---

## Algorithms

The complexity classes below refer to the number of emitted **push_swap operations**. Preprocessing CPU costs are described separately.

### 1. Simple — O(n²)

**Strategy:** minimum-selection sorting adapted to two stacks.

The algorithm finds the minimum remaining value in `a`, moves it to the top using the shorter rotation direction, and pushes it to `b`. Once only the largest value remains in `a`, all elements are returned from `b` with `pa`.

For inputs of up to five elements, it uses dedicated routines: `simple_sort_two`, `simple_sort_three` and `simple_sort_five`. The four- and five-element routine moves the smallest elements to `b`, sorts the remaining three, then restores the saved elements.

**Complexity:** O(n²) stack operations in the worst case. Extracting each minimum can require a number of rotations proportional to the current stack size.

### 2. Medium — index-window chunk sort

**Strategy:** distribute values using a moving window of normalized indices.

The window width is approximately 1.4 × √n. Let `pushed` be the number of elements already sent to `b`:

- If the top index is at most `pushed`, execute `pb` and then `rb` when that rotation has an effect.
- If it is at most `pushed + range`, execute `pb`.
- Otherwise, rotate `a` and inspect its next element.

Once `a` is empty, repeatedly bring the maximum remaining index in `b` to the top using the shorter rotation direction, then execute `pa`.

**Target complexity in movements:** O(n√n), using a window width proportional to √n. Measured operation counts are listed in the performance comparison.

### 3. Complex — O(n log n)

**Strategy:** binary LSD radix sort over normalized indices.

Each value is assigned a rank from 0 to n - 1. For each bit, from least to most significant, indices whose bit is zero are pushed to `b`; indices whose bit is one remain in `a` through rotation. The elements in `b` are then returned to `a`. The process uses O(log n) bit passes.

**Complexity:** O(n log n) stack operations: O(log n) passes, each producing O(n) movements.

Both medium and complex reuse the simple strategy's small-input routines for at most five elements. All strategies return immediately if the input is already sorted.

### 4. Adaptive — automatic selection

**Strategy:** select one of the previous methods using the disorder calculated before any movement.

Disorder is the percentage of inverted pairs: positions `i < j` for which `a[i] > a[j]`.

```text
disorder (%) = inverted_pairs / total_pairs × 100
total_pairs  = n × (n - 1) / 2
```

For fewer than two elements, disorder is defined as 0%.

| Disorder range | Selected method | Movement complexity |
|---|---|---|
| Below 20% | Minimum selection | O(n²) |
| From 20% to below 50% | Index-window chunk sort | Target O(n√n) |
| At least 50% | Binary LSD radix sort | O(n log n) |

**Threshold rationale:**

- **20%** separates the low-disorder branch, which uses the simple selection method and its small-input routines. A low inversion percentage alone does not guarantee a short operation sequence for this method.
- **50%** routes inputs with a larger inversion ratio to radix sort, whose movement bound does not depend on the particular value ordering. The middle branch uses chunk sorting, which produced fewer operations than radix in the random samples shown below.

The low-disorder branch retains its O(n²) worst-case bound. This implementation does not claim an O(n) guarantee for every input below the 20% threshold. Adaptive selection follows these rules rather than comparing all possible instruction sequences.

The two stacks store O(n) nodes. The sorting routines use O(1) additional working memory beyond those nodes. Parsing also allocates token copies proportional to the input text and token count. Rank assignment, duplicate detection and the direct inversion calculation each take O(n²) CPU time in this implementation; these preprocessing costs are distinct from the emitted-operation model.

---

## Data structures

### t_node — doubly linked node

```c
typedef struct s_node
{
    int             value;    // Original integer
    int             index;    // Normalized rank from 0 to n - 1
    struct s_node   *prev;
    struct s_node   *next;
}                   t_node;
```

### t_stack

```c
typedef struct s_stack
{
    t_node  *head;   // Top of the stack
    t_node  *tail;   // Bottom of the stack
    int     size;   // Number of elements
}           t_stack;
```

### t_bench

```c
typedef struct s_bench
{
    int         enabled;         // Whether --bench is enabled
    double      disorder;        // Initial disorder, from 0.0 to 100.0
    const char  *strategy_name;  // Selected strategy
    const char  *complexity;     // Movement complexity label
    t_ops_count ops;             // Per-operation counters
}   t_bench;
```

---

## Benchmark mode

With `--bench`, metrics are printed to stderr after sorting. Sorting instructions remain on stdout.

The following output corresponds to:

```bash
./push_swap --bench --complex 6 1 4 2 5 3 >/dev/null
```

```text
[bench] disorder: 53.33%
[bench] strategy: complex (O(n*log(n)))
[bench] total ops: 29
[bench] sa: 0
[bench] sb: 0
[bench] ss: 0
[bench] pa: 11
[bench] pb: 11
[bench] ra: 7
[bench] rb: 0
[bench] rr: 0
[bench] rra: 0
[bench] rrb: 0
[bench] rrr: 0
```

Send instructions to the checker while saving the metrics separately:

```bash
./push_swap --bench --complex 5 3 1 4 2 2>bench.txt | ./checker 5 3 1 4 2
# OK
```

---

## Performance targets

| Input size | Minimum target | Good performance | Excellent performance |
|---|---|---|---|
| 100 numbers | < 2,000 operations | < 1,500 operations | < 700 operations |
| 500 numbers | < 12,000 operations | < 8,000 operations | < 5,500 operations |

---

## Performance comparison

The following figures are mean operation counts from 200 random samples per input size in the audit test suite. Each sample contains unique values drawn from -1,000,000 to 999,999. The figures describe those samples and are not guarantees for every input.

| Strategy | Movement complexity | 100 elements | 500 elements |
|---|---|---:|---:|
| `simple` | O(n²) | 1,450.36 | 32,344.40 |
| `medium` | Target O(n√n) | 574.88 | 5,066.22 |
| `complex` | O(n log n) | 1,084 | 6,784 |
| `adaptive` / default | Depends on the selected branch | 820.96 | 5,967.02 |

An asymptotically better strategy does not necessarily produce fewer operations for every small input. The benchmark mode can be used to compare methods on the same numbers.

---

## Resources

- Knuth, D. E. — *The Art of Computer Programming, Volume 3: Sorting and Searching*.
- [Push_swap visualizer](https://github.com/o-reo/push_swap_visualizer).
- [Big-O Cheat Sheet](https://www.bigocheatsheet.com/).
- Wikipedia — [Radix sort](https://en.wikipedia.org/wiki/Radix_sort) and [Insertion sort](https://en.wikipedia.org/wiki/Insertion_sort).

### AI usage

AI was used to support code review, testing, and documentation.

---

## Contributions

| Login | Contribution |
|---|---|
| sasilves | Stack operations; simple sorting and small-input routines; medium, complex and adaptive strategies; minimum/maximum positioning; stack structures and index assignment; project cleanup and testing. |
| jzelada- | Argument parsing, including quoted inputs and flag validation; benchmark calculations and output; bonus checker; modular headers; Libft integration; Makefile; README and testing. |
