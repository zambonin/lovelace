#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

std::vector<uint32_t> gen_random_set(uint32_t size, uint32_t max_value,
                                     uint32_t seed) {
  std::mt19937 rand(seed);
  std::vector<uint32_t> num_set(size);

  for (uint32_t &value : num_set) {
    value = rand() % max_value;
  }
  std::sort(num_set.begin(), num_set.end());

  return num_set;
}

uint32_t subset_sum(uint32_t element, uint32_t end, uint32_t acc_value,
                    uint32_t objective, const std::vector<uint32_t> &num_set) {
  uint32_t total_subsets = 0, current_value = acc_value + num_set[element], i;

  if (current_value == objective) {
    ++total_subsets;
  } else if (current_value > objective) {
    return total_subsets;
  } else {
    for (i = element + 1; i < end; ++i) {
      total_subsets += subset_sum(i, end, current_value, objective, num_set);
    }
  }

  return total_subsets;
}

uint32_t compute_subsets(const std::vector<uint32_t> &num_set,
                         uint32_t objective) {
  uint32_t result = 0, i;

  for (i = 0; i < num_set.size(); ++i) {
    result += subset_sum(i, num_set.size(), 0, objective, num_set);
  }

  return result;
}

int32_t main(int32_t argc, char **argv) {
  if (argc < 5) {
    std::cerr << "Usage: " << argv[0]
              << " [#items] [max item value] [desired sum] [rand seed]"
              << std::endl;
    return 1;
  }

  std::vector<uint32_t> num_set = gen_random_set(
      std::stoul(argv[1]), std::stoul(argv[2]), std::stoul(argv[4]));
  uint32_t objective = std::stoul(argv[3]);

  std::cout << "Number of subsets = " << compute_subsets(num_set, objective)
            << std::endl;
  return 0;
}
