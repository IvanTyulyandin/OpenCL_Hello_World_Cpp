#include <CL/cl2.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    auto platform = platforms[0];

    std::cout << "OpenCL version for platform \"" << platform.getInfo<CL_PLATFORM_NAME>()
            << "\" is \"" << platform.getInfo<CL_PLATFORM_VERSION>() << "\"\n";

    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_CPU, &devices);

    auto ctx = cl::Context(devices);

    std::ifstream helloWorldFile("kernel.cl", std::ifstream::in);

    std::stringstream buffer;
    buffer << helloWorldFile.rdbuf();

    auto src = buffer.str();

    auto prg = cl::Program(ctx, src);

    auto err = prg.build();
    if (err != CL_SUCCESS) {
        std::cout << "Build error\n";
        auto info = prg.getBuildInfo<CL_PROGRAM_BUILD_LOG>();
        for (auto&& i : info) {
            std::cout << "Device: " << i.first.getInfo<CL_DEVICE_NAME>()
                      << ", error: " << i.second << '\n';
        }
        return 0;
    } else {
        std::cout << "Got kernels: "
             << prg.getInfo<CL_PROGRAM_KERNEL_NAMES>() << '\n';
    }

    // Since prg may contains many kernels,
    // second parameter must be a kernel name
    auto kernel = cl::Kernel(prg, "helloWorld", &err);

    if (err != CL_SUCCESS) {
        std::cout << "Failed to get kernel from program, error code is " << err << '\n';
    }

    // https://www.khronos.org/registry/OpenCL/specs/opencl-cplusplus-1.2.pdf
    // page 73:
    //
    // cl::CommandQueue::enqueueTask is equivalent to calling cl::CommandQueue::enqueueNDRangeKernel
    // with work_dim = 1, global = NULLRange, global [0] set to 1 and local [0] set to 1.
    //
    // quite old spec, but it works

    auto offset = cl::NullRange;
    auto global = cl::NDRange(1);
    auto local  = cl::NDRange(1);
    auto queue  = cl::CommandQueue(ctx, devices[0]);

    err = queue.enqueueNDRangeKernel(kernel, offset, global, local);

    if (err != CL_SUCCESS) {
        std::cout << "Error! Code " << err << '\n';
    }

    return 0;
}
