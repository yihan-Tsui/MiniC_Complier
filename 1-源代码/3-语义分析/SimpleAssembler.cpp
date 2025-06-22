// SimpleAssembler.cpp
#include <fstream>
#include <cstring>
#include <vector>
#include <cstdint>
#include <mach-o/loader.h>
#include <mach/vm_prot.h>

int main() {
    // 1) 计算 header + load commands 大小
    uint32_t ncmds      = 1;
    uint32_t sizeofcmds = sizeof(segment_command_64) + sizeof(section_64);
    uint32_t fileoff    = sizeof(mach_header_64) + sizeofcmds;

    // 2) 构造并写入 Mach-O 头
    mach_header_64 mh{};
    mh.magic      = MH_MAGIC_64;
    mh.cputype    = CPU_TYPE_ARM64;
    mh.cpusubtype = CPU_SUBTYPE_ARM64_ALL;
    mh.filetype   = MH_OBJECT;
    mh.ncmds      = ncmds;
    mh.sizeofcmds = sizeofcmds;
    mh.flags      = 0;
    mh.reserved   = 0;

    // 3) LC_SEGMENT_64
    segment_command_64 sc{};
    sc.cmd      = LC_SEGMENT_64;
    sc.cmdsize  = sizeofcmds;
    std::strncpy(sc.segname, "__TEXT", sizeof(sc.segname));
    sc.vmaddr   = 0;
    sc.vmsize   = 0;
    sc.fileoff  = fileoff;
    sc.filesize = 0;                // 还没写机器码，先留 0
    sc.maxprot  = VM_PROT_READ|VM_PROT_WRITE;
    sc.initprot = VM_PROT_READ|VM_PROT_WRITE;
    sc.nsects   = 1;
    sc.flags    = 0;

    // 4) section_64 描述 __text
    section_64 sec{};
    std::strncpy(sec.sectname, "__text", sizeof(sec.sectname));
    std::strncpy(sec.segname,  "__TEXT", sizeof(sec.segname));
    sec.addr    = 0;
    sec.size    = 0;                // 真实大小写入之后再回填
    sec.offset  = fileoff;          // 段内容从 fileoff 开始
    sec.align   = 2;                // 4 字节对齐
    sec.reloff  = 0;
    sec.nreloc  = 0;
    sec.flags   = 0;

    // 5) 打开文件，先写 header + load commands + section table
    std::ofstream ofs("out.o", std::ios::binary);
    ofs.write(reinterpret_cast<char*>(&mh),  sizeof(mh));
    ofs.write(reinterpret_cast<char*>(&sc),  sizeof(sc));
    ofs.write(reinterpret_cast<char*>(&sec), sizeof(sec));

    // 6) 定义要写入 __text 的机器码（例子：简单的 ret 指令）
    //    ret 的编码是 0xd65f03c0
    //    你可以把这里换成你自己用手写编码表算出的指令序列
    std::vector<uint32_t> code = {
            0xd503201f, // nop
            0xd65f03c0  // ret
    };

    // 7) 回到 fileoff，写入机器码
    ofs.seekp(fileoff, std::ios::beg);
    for (auto instr : code) {
        // 小端写 4 字节
        ofs.put(static_cast<char>( instr        & 0xFF));
        ofs.put(static_cast<char>((instr >>  8) & 0xFF));
        ofs.put(static_cast<char>((instr >> 16) & 0xFF));
        ofs.put(static_cast<char>((instr >> 24) & 0xFF));
    }

    // 8) 现在机器码总字节数是 code.size()*4，把实际大小回填到 section 和 segment
    uint32_t codesize = static_cast<uint32_t>(code.size() * 4);

    // 回写 sec.size
    ofs.seekp(sizeof(mach_header_64) + sizeof(segment_command_64)
              + offsetof(section_64, size), std::ios::beg);
    ofs.write(reinterpret_cast<char*>(&codesize), sizeof(codesize));

    // 回写 sc.filesize
    ofs.seekp(sizeof(mach_header_64)
              + offsetof(segment_command_64, filesize), std::ios::beg);
    ofs.write(reinterpret_cast<char*>(&codesize), sizeof(codesize));

    ofs.close();
    return 0;
}
