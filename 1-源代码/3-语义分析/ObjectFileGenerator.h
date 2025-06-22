#ifndef OBJECT_FILE_GENERATOR_H
#define OBJECT_FILE_GENERATOR_H

#include <vector>
#include <cstdint>
#include <string>

/// 把一段 32-bit ARM64 指令流写成一个 Mach-O 64-bit relocatable object (.o) 文件
class ObjectFileGenerator {
public:
    /// \param filename 输出文件名，比如 "out.o"
    /// \param code     每个元素是一条 32-bit 小端机器指令
    /// \return         true 成功，false 失败
    static bool writeObject(const std::string &filename,
                            const std::vector<uint32_t> &code);
};

#endif // OBJECT_FILE_GENERATOR_H
