// ObjectFileGenerator.cpp
#include "ObjectFileGenerator.h"
#include <fstream>
#include <cstring>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach/vm_prot.h>
#include <iostream>

bool ObjectFileGenerator::writeObject(const std::string &filename,
                                      const std::vector<uint32_t> &code) {

    std::cout << "Code size: " << code.size() << std::endl;
    for (auto instr : code) {
        std::cout << std::hex << instr << std::endl;  // 打印机器码
    }
    // 1) 计算各部分大小/偏移
    const uint32_t segcmd_sz    = sizeof(segment_command_64) + sizeof(section_64);
    const uint32_t symcmd_sz    = sizeof(symtab_command);
    const uint32_t ncmds        = 2;  // __TEXT + SYMTAB
    const uint32_t sizeofcmds   = segcmd_sz + symcmd_sz;
    const uint32_t fileoff_code = sizeof(mach_header_64) + sizeofcmds;
    const uint32_t codesize     = uint32_t(code.size() * 4);

    // 字符串表： "\0_main\0"
    std::vector<char> strtab = {'\0','_','m','a','i','n','\0'};
    const uint32_t nsyms   = 1;
    const uint32_t symoff  = fileoff_code + codesize;

    std::cout << "Symbol offset: " << symoff << std::endl;

    const uint32_t stroff  = symoff + nsyms * sizeof(nlist_64);
    const uint32_t strsize = uint32_t(strtab.size());

    // 2) Mach-O Header
    mach_header_64 mh{};
    mh.magic      = MH_MAGIC_64;
    mh.cputype    = CPU_TYPE_ARM64;
    mh.cpusubtype = CPU_SUBTYPE_ARM64_ALL;
    mh.filetype   = MH_OBJECT;
    mh.ncmds      = ncmds;
    mh.sizeofcmds = sizeofcmds;
    mh.flags      = 0;
    mh.reserved   = 0;

    // 3) LC_SEGMENT_64 for __TEXT/__text
    segment_command_64 sc{};
    sc.cmd      = LC_SEGMENT_64;
    sc.cmdsize  = segcmd_sz;
    std::strncpy(sc.segname, "__TEXT", sizeof(sc.segname));
    sc.vmaddr   = 0;
    sc.vmsize   = codesize;
    sc.fileoff  = fileoff_code;
    sc.filesize = codesize;
    sc.maxprot  = VM_PROT_READ | VM_PROT_WRITE;
    sc.initprot = VM_PROT_READ | VM_PROT_WRITE;
    sc.nsects   = 1;
    sc.flags    = 0;

    section_64 sect{};
    std::strncpy(sect.sectname, "__text", sizeof(sect.sectname));
    std::strncpy(sect.segname,  "__TEXT", sizeof(sect.segname));
    sect.addr    = 0;
    sect.size    = codesize;
    sect.offset  = fileoff_code;
    sect.align   = 2;  // 4-byte align
    sect.reloff  = 0;
    sect.nreloc  = 0;
    sect.flags   = 0;
    sect.reserved1 = sect.reserved2 = sect.reserved3 = 0;

    // 4) LC_SYMTAB
    symtab_command stc{};
    stc.cmd      = LC_SYMTAB;
    stc.cmdsize  = symcmd_sz;
    stc.symoff   = symoff;
    stc.nsyms    = nsyms;
    stc.stroff   = stroff;
    stc.strsize  = strsize;

    // 5) 写入 header + load commands + section
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) return false;
    ofs.write(reinterpret_cast<char*>(&mh),  sizeof(mh));
    ofs.write(reinterpret_cast<char*>(&sc),  sizeof(segment_command_64));
    ofs.write(reinterpret_cast<char*>(&sect), sizeof(section_64));
    ofs.write(reinterpret_cast<char*>(&stc), sizeof(stc));

    // 6) 写入机器码
    ofs.seekp(fileoff_code, std::ios::beg);
    for (auto instr : code) {
        ofs.put(char(instr & 0xFF));
        ofs.put(char((instr >> 8) & 0xFF));
        ofs.put(char((instr >> 16) & 0xFF));
        ofs.put(char((instr >> 24) & 0xFF));
    }

    // 7) 写入符号表 (_main)
    ofs.seekp(symoff, std::ios::beg);
    nlist_64 nl{};
    nl.n_un.n_strx = 1;               // "_main" 在 strtab 的偏移
    nl.n_type      = N_SECT | N_EXT;  // 定义在 section、对外可见
    nl.n_sect      = 1;               // 第一节 __text
    nl.n_desc      = 0;
    nl.n_value     = 0;               // 从节首开始
    ofs.write(reinterpret_cast<char*>(&nl), sizeof(nl));

    // 8) 写入字符串表
    ofs.seekp(stroff, std::ios::beg);
    ofs.write(strtab.data(), strtab.size());

    return true;
}
