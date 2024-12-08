#include <iostream>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include "../comm/comm.hpp"
#include "../fss-base/dcf/distributed_comparison_function.hpp"
#include "../fss-base/ddcf/dual_dcf.hpp"
#include "../fss-base/dpf/distributed_point_function.hpp"
#include "../fss-base/prg/prg.hpp"
#include "../fss-gate/comp/integer_comparison.hpp"
#include "../fss-gate/fm-index/fss_fmi.hpp"
#include "../fss-gate/internal/fsskey_io.hpp"
#include "../fss-gate/rank/fss_rank.hpp"
#include "../fss-gate/zt/zero_test_dpf.hpp"
#include "../tools/secret_sharing.hpp"
#include "../tools/tools.hpp"
#include "../utils/file_io.hpp"
#include "../utils/utils.hpp"

int main() {
    auto func1 = add(10, 3);
    auto func2 = mult(func1, 10);
    return func2;
}
