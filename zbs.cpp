#include <iostream>
#include <algorithm>
#include <torch/torch.h>
int main() {
    auto hello = "sss";
    torch::Tensor tensor = torch::eye(3);
    std::cout << tensor << std::endl;
    return 0;
}